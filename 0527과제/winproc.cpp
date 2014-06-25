#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT ptHour;
	static POINT ptMinute;
	static POINT ptSecond;
	static LONG thetaHour = 0;
	static LONG thetaMinute = 0;
	static LONG thetaSecond = 0;
	static COLORREF color = RGB(255,255,255);
	static INT count = 0;

	SYSTEMTIME st;
	::GetLocalTime(&st);

	if (uMsg == WM_CREATE)
	{
		::SetTimer(hWnd, 0, 10, NULL);

		if (st.wMinute == 0 && st.wSecond == 0)
		{
			count = st.wHour;
			::SetTimer(hWnd, 1, 1000, NULL);				
		}


		if (count == 0)
		{
			count = st.wHour;	
		}

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

		HBRUSH clockBrush = ::CreateSolidBrush(RGB(255,255,255));
		HBRUSH hBrush = ::CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);
		// TODO.....
		RECT rc;
		::GetClientRect(hWnd, &rc);

		hOldBrush = (HBRUSH)::SelectObject(hdc, clockBrush);

		::Rectangle(hdc, 0, 0, 400, 400);

		hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);
		::Ellipse(hdc, 0, 0, 400, 400);

		hOldBrush = (HBRUSH)::SelectObject(hdc, clockBrush);
		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptHour.x, ptHour.y);

		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptMinute.x, ptMinute.y);

		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptSecond.x, ptSecond.y);

		::SelectObject(hdc, hOldBrush);
		::DeleteObject(clockBrush);
		::DeleteObject(hBrush);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		if (wParam == 0)
		{
			// TODO
			SYSTEMTIME st;

			//::GetSystemTime(&st);
			::GetLocalTime(&st);

			thetaHour = LONG((st.wHour%12)*30
				+ float(st.wMinute)/2 
				+ float(st.wSecond)/120
				+ float(st.wMilliseconds)/120000);

			thetaMinute = LONG(st.wMinute*6 
				+ float(st.wSecond)/10
				+ float(st.wMilliseconds)/10000);

			thetaSecond = LONG(st.wSecond*6
				+ float(st.wMilliseconds)*6/1000);

			LONG LHour = 80;
			LONG LMinute = 100;
			LONG LSecond = 150;

			const float D2R = float(M_PI/180);

			ptHour.x = LONG(200 + LHour*cos((90-thetaHour)*D2R));
			ptHour.y = LONG(200 - LHour*sin((90-thetaHour)*D2R));

			ptMinute.x = LONG(200 + LMinute*cos((90-thetaMinute)*D2R));
			ptMinute.y = LONG(200 - LMinute*sin((90-thetaMinute)*D2R));

			ptSecond.x = LONG(200 + LSecond*cos((90-thetaSecond)*D2R));
			ptSecond.y = LONG(200 - LSecond*sin((90-thetaSecond)*D2R));

			// redraw
			RECT rc;
			::GetClientRect(hWnd, &rc);
			::InvalidateRect(hWnd, &rc, TRUE);

			return 0;
		}
		else if (wParam == 1)
		{	
			if ( count % 2 == 0 )
			{
				color = RGB(255, 0, 0);
			}
			else
			{
				color = RGB(0, 0, 255);
			}
			count --;
			if(count == 0 )
			{
				color = RGB(255,255,255);
				::KillTimer(hWnd, 1);
			}
		}

	}
	else if (uMsg == WM_SIZE)
	{
		DWORD dwStyle = WS_OVERLAPPEDWINDOW;
		dwStyle &= ~WS_MAXIMIZEBOX;
		dwStyle &= ~WS_THICKFRAME;

		RECT rc = {0, 0, 400, 400};
		::AdjustWindowRect(&rc, dwStyle, false);
		::SetWindowPos(hWnd, NULL/*z order (앞 뒤)*/, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
						SWP_NOZORDER | SWP_NOMOVE);
	/*	::SetWindowPlacement();
		::MoveWindow();*/
	}

		return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}