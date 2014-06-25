#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static Animation sample1;
	static Animation sample2;
	static Animation sample3;
	static Animation sample4;
	static Point ptMouse;

	static DWORD delay = 80;
	static DWORD delay1 = 80;
	static DWORD delay2 = 80;
	static DWORD delay3 = 80;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		backbuffer.Attach(hWnd);

		// TODO
		for (int i = 0; i < 12; i++)
		{
			Image* pImg = new Image;
			pImg->Load(_T("ryu_fire.bmp"), Rect(170*i,0,170 + 170*i,170));
			pImg->SetTransparent(RGB(255,0,255));

			sample1.AddShot(pImg);
		}

		sample1.SetDelay(delay);
		sample1.SetLoop(true);

		for (int i = 0; i < 7; i++)
		{
			Image* pImg = new Image;
			
			pImg->Load(_T("ryu_normal.bmp"), Rect(170*i,0,170 + 170*i, 170));
			pImg->SetTransparent(RGB(255,0,255));

			sample2.AddShot(pImg);
		}
		
		sample2.SetDelay(delay1);
		sample2.SetLoop(true);

		for (int i = 0; i < 8; i++)
		{
			Image* pImg = new Image;

			pImg->Load(_T("ryu_go_front.bmp"), Rect(170*i, 0, 170 + 170*i, 170));
			pImg->SetTransparent(RGB(255,0,255));

			sample3.AddShot(pImg);			
		}

		sample3.SetDelay(delay2);
		sample3.SetLoop(true);


		for (int i = 0; i < 8; i++)
		{
			Image* pImg = new Image;

			pImg->Load(_T("ryu_go_back.bmp"), Rect(170*i, 0, 170 + 170*i, 170));
			pImg->SetTransparent(RGB(255,0,255));

			sample4.AddShot(pImg);		
		}

		sample4.SetDelay(delay3);
		sample4.SetLoop(true);
		
		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 10, NULL);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		// TODO

		::KillTimer(hWnd, 0);

		backbuffer.Detach();

		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		backbuffer << RGB(255,200,200);

		// TODO
		Point pt1;
		pt1.x = ptMouse.x - 50;
		pt1.y = ptMouse.y - 50;

		sample1.SetRect(Rect(pt1, Size(170,170)));
		sample1.Draw(backbuffer);

		Point pt2;
		pt2.x = ptMouse.x + 50;
		pt2.y = ptMouse.y - 50;

		sample2.SetRect(Rect(pt2, Size(170,170)));
		sample2.Draw(backbuffer);

		Point pt3;
		pt3.x = ptMouse.x - 50;
		pt3.y = ptMouse.y + 50;

		sample3.SetRect(Rect(pt3, Size(170,170)));
		sample3.Draw(backbuffer);
		
		Point pt4;
		pt4.x = ptMouse.x + 50;
		pt4.y = ptMouse.y + 50;

		sample4.SetRect(Rect(pt4, Size(170,170)));
		sample4.Draw(backbuffer);

		std::wostringstream oss;
		oss << _T("ani1 delay : ") << delay << std::endl;
		oss << _T("ani2 delay : ") << delay1 << std::endl;
		oss << _T("ani3 delay : ") << delay2 << std::endl;
		oss << _T("ani4 delay : ") << delay3 << std::endl;
 
		::DrawText(backbuffer, oss.str().c_str(), -1, &rc, DT_TOP);

		backbuffer.Draw();

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}
	else if (uMsg == WM_KEYDOWN)
	{
		if ((::GetAsyncKeyState(VK_ADD) & 0x8000) == 0x8000)
		{	
			if ((::GetAsyncKeyState(VK_CONTROL) & 0x8000) == 0x8000)
			{
				delay1 = max(5, delay1 - 5);
			}
			else
			{
				delay = max(5, delay - 5);
			}
		}
		else if ((::GetAsyncKeyState(VK_SUBTRACT) & 0x8000) == 0x8000)
		{
			if((::GetAsyncKeyState(VK_CONTROL) & 0x8000) == 0x8000)

			{
				delay1 = min(150, delay1 + 5);
			}
			else
			{
				delay = min(150, delay + 5);
			}
		}
		else if ((::GetAsyncKeyState(VK_UP) & 0x8000) == 0x8000)
		{
			if ((::GetAsyncKeyState(VK_CONTROL) & 0x8000) == 0x8000)
			{
				delay3 = max(5, delay3 - 5);
			}
			else
			{
				delay2 = max(5, delay2 - 5);
			}
		}
		else if ((::GetAsyncKeyState(VK_DOWN) & 0x8000) == 0x8000)
		{
			if ((::GetAsyncKeyState(VK_CONTROL) & 0x8000) == 0x8000)
			{
				delay3 = max(5, delay3 + 5);
			}
			else
			{
				delay2 = max(5, delay2 + 5);
			}
		}
	
		sample1.SetDelay(delay);
		sample2.SetDelay(delay1);
		sample3.SetDelay(delay2);
		sample4.SetDelay(delay3);

		return 0;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hWnd);

		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		sample1.Update(dt);
		sample2.Update(dt);
		sample3.Update(dt);
		sample4.Update(dt);

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
