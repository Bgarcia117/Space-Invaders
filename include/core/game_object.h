#pragma once

class GameObject {
public:
	GameObject();

protected:
	virtual void move() = 0;

};