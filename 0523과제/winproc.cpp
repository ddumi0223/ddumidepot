#include "Circle.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int count = 10;
	static Point pt[count];
	
	if (uMsg == WM_CREATE)
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		LONG width = rc.right - rc.left;
		LONG height = rc.bottom - rc.top;

		for (int i = 0; i < count; i++)
		{
			pt[i] = Point(rand()%width, rand()%height);
		}

		::SetTimer(hWnd, 0, 100, NULL);

		return 0;
	}
	else if(uMsg == WM_DESTROY)
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
		::GetClientRect(hWnd, &rc);

		for (int i =0; i < count; i++)
		{
			Circle one;
			one.SetRadius(30);
			one.SetCenter(pt[i]);
			one.SetColor(RGB(rand()%256,rand()%256,rand()%256));

			one.Draw(hdc);

			if ((pt[i].x - 30 ) > rc.right)
			{								
				pt[i].x -= rc.right;
				pt[i].y = rand()%(rc.bottom-rc.top);
				one.Draw(hdc);

			}
		}
		

		::EndPaint(hWnd, &ps);
	}
	else if (uMsg == WM_TIMER)
	{
		for (int i = 0; i < count; i++)
		{
			pt[i].x +=10;
		}

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);

}