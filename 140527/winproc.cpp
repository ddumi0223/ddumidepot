#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT pthEnd = {200+130,200};
	static POINT ptmEnd = {200+180, 200};
	static POINT ptsEnd = {200+180, 200};
	static LONG htheta = 0;
	static LONG mtheta = 0;
	static LONG stheta = 0;

	if (uMsg == WM_CREATE)
	{
		::SetTimer(hWnd, 0, 100, NULL);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);

		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO.....
		RECT rc;
		::GetClientRect(hWnd, &rc);

		::Rectangle(hdc, 0, 0, 400, 400);
		::Ellipse(hdc, 0, 0, 400, 400);

		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, pthEnd.x, pthEnd.y);
		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptmEnd.x, ptmEnd.y);
		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptsEnd.x, ptsEnd.y);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		SYSTEMTIME st;
		
		//::GetSystemTime(&st);
		::GetLocalTime(&st);

		htheta = LONG((st.wHour%12)*30
			+ float(st.wMinute)/2 
			+ float(st.wSecond)/120
			+ float(st.wMilliseconds)/120000);

		//theta += 6;
		//if (theta >= 360)
		//	theta = 0;

		LONG hL = 130;
		const float D2R = float(M_PI/180);

		pthEnd.x = LONG(200 + hL*cos((90-htheta)*D2R));
		pthEnd.y = LONG(200 - hL*sin((90-htheta)*D2R));

		mtheta = LONG((st.wMinute * 6)
				+ float(st.wSecond)/120
				+ float(st.wMilliseconds)/120000);

		LONG mL = 180;
		
		ptmEnd.x = LONG(200 + mL*cos((90-mtheta)*D2R));
		ptmEnd.y = LONG(200 - mL*sin((90-mtheta)*D2R));

		stheta = LONG((st.wSecond)*6
			+ float(st.wMilliseconds)/120000);

		LONG sL = 180;

		ptsEnd.x = LONG(200 + sL*cos((90-stheta)*D2R));
		ptsEnd.y = LONG(200 - sL*sin((90-stheta)*D2R));

		// redraw
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}