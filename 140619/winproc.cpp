#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	static Image sample1;
	static Image sample2;
	static Image sample3;
	static Image sample4;

	static Point ptMouse;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		backbuffer.Attach(hWnd);

		// TODO
		sample1.Load(_T("ryu_normal.bmp"), Rect(0,0,170,170));
		sample2.Load(_T("ryu_normal.bmp"), Rect(170,0,340,170));
		sample3.Load(_T("ryu_normal.bmp"), Rect(340,0,510,170));
		sample4.Load(_T("ryu_normal.bmp"), Rect(510,0,680,170));

		sample1.SetTransparent(RGB(255,0,255));
		sample2.SetTransparent(RGB(255,0,255));
		sample3.SetTransparent(RGB(255,0,255));
		sample4.SetTransparent(RGB(255,0,255));

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
		sample1.SetRect(Rect(Point(rc.left + 100, rc.top + 50), Size(170,170)));
		sample2.SetRect(Rect(Point(rc.left + 200, rc.top + 50), Size(170,170)));
		sample3.SetRect(Rect(Point(rc.left + 300, rc.top + 50), Size(170,170)));
		sample4.SetRect(Rect(Point(rc.left + 400, rc.top + 50), Size(170,170)));
		
		sample1.Draw(backbuffer);
		sample2.Draw(backbuffer);
		sample3.Draw(backbuffer);
		sample4.Draw(backbuffer);
		
		backbuffer.Draw();

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
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

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
