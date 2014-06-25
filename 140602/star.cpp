#include "star.h"

star::star()
: theta(0)
, center(-500, -500)
, speed(0)
{
	
}
star::~star()
{
}
void star::SetAngle(const LONG& angle)
{
	theta = angle;
}
void star::SetCenPos(const Point& pt)
{
	center = pt;
}
void star::SetSpeed(const LONG& s)
{
	speed = s;
}
void star::Update(const Rect &rc, const Point &pt)
{
	center.x = center.x + LONG(speed*sin(theta*D2R));
	center.y = center.y - LONG(speed*cos(theta*D2R));
	if((center.x < rc.left) || (center.x > rc.right) || (center.y < rc.top) || (center.y > rc.bottom))
	{
		center = pt;
	}
}
Point star::GetPos()
{
	return center;
}