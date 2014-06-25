#include "Character.h"

/////////////////////////////////////////////////
// CharacterState Impl
/////////////////////////////////////////////////
CharacterState::CharacterState()
: pos(NULL), pAni(NULL)
{}
CharacterState::~CharacterState()
{
	if (pAni)
	{
		delete pAni;
		pAni = NULL;
	}
}
void CharacterState::SetPositionLink(Point& p)
{
	pos = &p;
}

/////////////////////////////////////////////////
// CS_Idle Impl
/////////////////////////////////////////////////
CS_Idle::CS_Idle()
{
	pAni = new Animation;
	for (int i = 0; i < 7; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("ryu_normal.bmp"), Rect(170*i,0,170 + 170*i,170));
		pImg->SetTransparent(RGB(255,0,255));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
	pAni->SetLoop(true);
}
CS_Idle::~CS_Idle()
{
}

void CS_Idle::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_Idle::Input(DWORD tick)
{
	if ((::GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(FIRE);
	}
	else if ((::GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_FORWARD);	
	}
	else if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_BACKWARD);
	}
}
void CS_Idle::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_Idle::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170,170)));
		pAni->Draw(hdc);
	}
}
void CS_Idle::Leave()
{
}

/////////////////////////////////////////////////
// CS_Fire Impl
/////////////////////////////////////////////////
CS_Fire::CS_Fire()
{
	pAni = new Animation;
	for (int i = 0; i < 12; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("ryu_fire.bmp"), Rect(170*i,0,170 + 170*i,170));
		pImg->SetTransparent(RGB(255,0,255));

		pAni->AddShot(pImg);
	}
	pAni->SetDelay(60);
}
CS_Fire::~CS_Fire()
{
}

void CS_Fire::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_Fire::Input(DWORD tick)
{
}
void CS_Fire::Update(DWORD tick)
{
	if (pAni)
	{
		pAni->Update(tick);
		if (!pAni->IsPlaying())
			m_pMachine->transition(IDLE);
	}
}
void CS_Fire::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170,170)));
		pAni->Draw(hdc);
	}
}
void CS_Fire::Leave()
{
}

CS_Go_Forward::CS_Go_Forward()
{
	pAni = new Animation;
	for (int i = 0; i < 8; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("ryu_go_front.bmp"), Rect(170*i,0,170 + 170*i,170));
		pImg->SetTransparent(RGB(255,0,255));

		pAni->AddShot(pImg);
	}
	pAni->SetDelay(60);
}
CS_Go_Forward::~CS_Go_Forward()
{
}
void CS_Go_Forward::Enter()
{
	if (pAni)
	pAni->Reset();
}
void CS_Go_Forward::Input(DWORD tick)
{
	
}
void CS_Go_Forward::Update(DWORD tick)
{
	if (pAni)
	{
		pAni->Update(tick);
		if (!pAni->IsPlaying())
			m_pMachine->transition(IDLE);
	}
}
void CS_Go_Forward::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170,170)));
		pAni->Draw(hdc);
	}
}
void CS_Go_Forward::Leave()
{
}

CS_Go_Backward::CS_Go_Backward()
{
	pAni = new Animation;
	for (int i = 0; i < 8; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("ryu_go_back.bmp"), Rect(170*i,0,170 + 170*i,170));
		pImg->SetTransparent(RGB(255,0,255));

		pAni->AddShot(pImg);
	}
	pAni->SetDelay(60);
}
CS_Go_Backward::~CS_Go_Backward()
{
}
void CS_Go_Backward::Enter()
{
	if (pAni)
	pAni->Reset();
}
void CS_Go_Backward::Input(DWORD tick)
{
	
}
void CS_Go_Backward::Update(DWORD tick)
{
	if (pAni)
	{
		pAni->Update(tick);
		if (!pAni->IsPlaying())
			m_pMachine->transition(IDLE);
	}
}
void CS_Go_Backward::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(170,170)));
		pAni->Draw(hdc);
	}
}
void CS_Go_Backward::Leave()
{
}