#pragma once
#include "BaseType.h"

class star
{
public:
	star();
	~star();

	void SetAngle(const LONG& angle);
	void SetCenPos(const Point& pt);
	void SetSpeed(const LONG& s);
	void Update(const Rect &ClientRect, const Point& ptMouse);
	Point GetPos();
private:
	LONG theta;
	Point center;
	LONG speed;
};