#include "game_objects/barrier.h"

constexpr sf::Color LIGHT_GREEN(42, 249, 50);

Barrier::Barrier(const ResourceManager &resourceManager, sf::Vector2f position) :
    GameObject(resourceManager, "barrier", position) {
    setSpriteColor(LIGHT_GREEN);

    // Creating writable barrier texture
    auto barrierBounds = getSprite().getGlobalBounds();
    barrierTexture.emplace(sf::Vector2u(static_cast<unsigned>(barrierBounds.size.x),
                                             static_cast<unsigned>(barrierBounds.size.y)));

    // Draws barrier texture onto the local render texture (0, 0)
    sf::Sprite initialSprite = getSprite();
    initialSprite.setPosition({ 0.0f, 0.0f });
    barrierTexture->clear(sf::Color::Transparent);
    barrierTexture->draw(initialSprite);
    barrierTexture->display();

    // Sprite that displays the texture to the screen
    barrierTextureSprite.emplace(barrierTexture->getTexture());
    barrierTextureSprite->setPosition(position);

    // 2D array for CPU
    barrierImage = barrierTexture->getTexture().copyToImage();
}

void Barrier::update(float deltaTime) {

}

void Barrier::takeDamage(sf::Vector2f impactPos, sf::Sprite explosionShape, const sf::Image& effectsSpriteSheetImg) {
    // Local position on barrier to draw explosion
    sf::Vector2f posOnBarrier = impactPos - getPosition();

    // Centering explosion on impact location
    auto explosionBounds = explosionShape.getLocalBounds();
    explosionShape.setOrigin({ explosionBounds.size.x / 2.0f, explosionBounds.size.y / 2.0f });
    explosionShape.setPosition(posOnBarrier);

    // Settings for draw function
    sf::RenderStates states;

    // Uses explosion sprite as outline/template
    // Factor::Zero ignores the explosion sprite's color
    // Factor::OneMinusSrcAlpha erases barrier pixels where the explosion is opaque
    states.blendMode = sf::BlendMode(sf::BlendMode::Factor::Zero, sf::BlendMode::Factor::OneMinusSrcAlpha);

    // Cutout explosion shape with settings from texture
    barrierTexture->draw(explosionShape, states);

    // Update texture
    barrierTexture->display();

    // Mirrors shape on barrierImage for the CPU to carve
    auto explosionSourceRect = explosionShape.getTextureRect();
    auto explosionScale = explosionShape.getScale();
    auto barrierImageSize = barrierImage->getSize();

    // Size and top left of explosion on barrier image (centered)
    float explosionWidth = explosionSourceRect.size.x * explosionScale.x;
    float explosionHeight = explosionSourceRect.size.y * explosionScale.y;
    float explosionTop = posOnBarrier.y - explosionHeight / 2.0f;
    float explosionLeft = posOnBarrier.x - explosionWidth / 2.0f;

    // Traversing the 2D array of explosion sprite pixels
    // Checks which overlap with the barrier
    for (int pixelY = 0; pixelY < static_cast<int>(explosionHeight); pixelY++) {
        for (int pixelX = 0; pixelX < static_cast<int>(explosionWidth); pixelX++) {

            // Map pixel in game to pixel on sprite sheet
            // Divides to remove the scale applied to match sprite sheet
            int sourcePixelX = explosionSourceRect.position.x + static_cast<int>(pixelX / explosionScale.x);
            int sourcePixelY = explosionSourceRect.position.y + static_cast<int>(pixelY / explosionScale.y);

            // Skips pixels that are transparent in the explosion sprite
            // getPixel() returns an sf::Color with a struct with four fields: r, g, b, a
            // We check the value of a which is opacity
            if (effectsSpriteSheetImg.getPixel({static_cast<unsigned> (sourcePixelX),
                                                          static_cast<unsigned> (sourcePixelY)}).a == 0) {
                continue;
            }

            // Translate explosion's location to barrier image
            int barrierPixelX = static_cast<int> (explosionLeft) + pixelX;
            int barrierPixelY = static_cast<int> (explosionTop) + pixelY;

            // Skip pixels outside of the barrier image bounds
            if (barrierPixelX < 0 || barrierPixelY < 0 || barrierPixelX >= static_cast<int>(barrierImageSize.x) ||
                barrierPixelY >= static_cast<int>(barrierImageSize.y)) {
                continue;
            }

            // Sets pixel to transparent if the sprites overlap
            barrierImage->setPixel({static_cast<unsigned>(barrierPixelX),
                                              static_cast<unsigned>(barrierPixelY)}, sf::Color::Transparent);
        }
    }
}

bool Barrier::collidesWith(const sf::Sprite& otherSprite) {
    auto barrierBounds = getSprite().getGlobalBounds();
    auto otherObjBounds = otherSprite.getGlobalBounds();
    auto overlapRect = barrierBounds.findIntersection(otherObjBounds);

    if (!overlapRect) {
        return false;
    }

    // Converting world coordinates into barrier local coordinates
    // Ensures we hit a pixel that is not transparent
    sf::Vector2f barrierWorldPos = getPosition();
    auto barrierImageSize = barrierImage->getSize();

    // Using max to as a safe guard since overlapRect->pos.x is an unsigned_int
    int overlapLeftX = std::max(0, static_cast<int>(overlapRect->position.x - barrierWorldPos.x));
    int overlapTopY = std::max(0, static_cast<int>(overlapRect->position.y - barrierWorldPos.y));
    int overlapRightX = std::min(static_cast<int>(barrierImageSize.x),
                                 static_cast<int>(overlapRect->position.x + overlapRect->size.x - barrierWorldPos.x));
    int overlapBottomY = std::min(static_cast<int>(barrierImageSize.y),
                                  static_cast<int>(overlapRect->position.y + overlapRect->size.y - barrierWorldPos.y));

    // Check opacity to confirm hit
    for (int pixelY = overlapTopY; pixelY < overlapBottomY; pixelY++) {
        for (int pixelX = overlapLeftX; pixelX < overlapRightX; pixelX++) {
            if (barrierImage->getPixel({static_cast<unsigned>(pixelX), static_cast<unsigned>(pixelY)}).a > 0) {
                return true;
            }
        }
    }

    return false;
}
