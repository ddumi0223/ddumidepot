#pragma once

#include "FSM.h"
#include "BaseType.h"
#include "Animation.h"

enum Character_State_id
{
	IDLE,
	FIRE,
	GO_FORWARD,
	GO_BACKWARD,
};


class CharacterState : public State
{
public :
	CharacterState();
	virtual ~CharacterState();

	virtual void Enter() = 0;
	virtual void Input(DWORD tick) = 0;
	virtual void Update(DWORD tick) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Leave() = 0;

	void SetPositionLink(Point& p);
protected :
	Point* pos;
	Animation* pAni;
};

class Character : public StateMachine
{
public :
	Character();
	virtual ~Character();

	void SetPosition(const Point& p);
protected :
	Point pos;
};

class CS_Idle : public CharacterState
{
public :
	CS_Idle();
	virtual ~CS_Idle();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();
};

class CS_Fire : public CharacterState
{
public :
	CS_Fire();
	virtual ~CS_Fire();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();
};

class CS_Go_Forward : public CharacterState
{
public :
	CS_Go_Forward();
	virtual ~CS_Go_Forward();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();
};

class CS_Go_Backward : public CharacterState
{
public :
	CS_Go_Backward();
	virtual ~CS_Go_Backward();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();
};
