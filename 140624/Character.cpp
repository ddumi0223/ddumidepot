#include "Character.h"

Character::Character()
{
	CS_Idle* pIdle = new CS_Idle;
	pIdle->SetPositionLink(pos);
	AddEntry(IDLE, pIdle);

	CS_Fire* pFire = new CS_Fire;
	pFire->SetPositionLink(pos);
	AddEntry(FIRE, pFire);

	CS_Go_Forward* pForward = new CS_Go_Forward;
	pForward->SetPositionLink(pos);
	AddEntry(GO_FORWARD, pForward);

	CS_Go_Backward* pBack = new CS_Go_Backward;
	pBack->SetPositionLink(pos);
	AddEntry(GO_BACKWARD, pBack);

	transition(IDLE);
}
Character::~Character()
{}

void Character::SetPosition(const Point& p)
{
	pos = p;
}
