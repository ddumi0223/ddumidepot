#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LONG theta = 0;
	static LONG r = 120;
	static POINT deadline;
	if (uMsg == WM_CREATE)
	{
		::SetTimer(hWnd, 0, 1000, NULL);
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);

		::PostQuitMessage(0);
		return 0;
	}
	else if(uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);
				
		RECT rc;
		POINT cp;
		
		::GetClientRect(hWnd, &rc);

		cp.x = (rc.right - rc.left)/2;
		cp.y = (rc.bottom - rc.left)/2;		 
				
		const float D2R = float(M_PI
			/180);
		
		LONG dx = LONG (r * cos((180 - theta)*D2R));
		LONG dy = LONG (r * sin((180 - theta)*D2R));
		deadline.x = cp.x - dx;
		deadline.y = cp.y + dy;
		

		::Ellipse(hdc, rc.left, rc.top,
			rc.right, rc.bottom);	

		::MoveToEx(hdc, cp.x, cp.y, NULL);
		::LineTo(hdc, deadline.x, deadline.y);

		::EndPaint(hWnd,&ps);

		return 0;
	}
	else if(uMsg == WM_TIMER)
	{		
		theta -=6;
		RECT rc;
				
		::GetClientRect(hWnd, &rc);
		
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}