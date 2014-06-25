#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static const int count = 50;
	static star sr[count];
	static HBITMAP hStar = NULL;
	static Point ptMouse;
	
	if (uMsg == WM_CREATE)
	{	
		Rect rc;
		::GetClientRect(hWnd, &rc);

		LONG width = rc.right - rc.left;
		LONG height = rc.bottom - rc.top;

	/*	for (int i = 0; i < count; i++)
		{
			pt[i] = Point(rand()%width, rand()%height);
		}*/
		for (int i = 0; i < count; i++)
		{
			sr[i].SetSpeed(10);
			sr[i].SetAngle(rand()%361);
			sr[i].SetCenPos(Point(-5,-5));
		}

		hStar = (HBITMAP)::LoadImage(NULL, _T("star.bmp"),
			IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);
		
		//st = ::GetTickCount();
		::SetTimer(hWnd, 0, 40, NULL);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);

		::DeleteObject(hStar);

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

		BITMAP bm;

		::GetObject(hStar, sizeof(BITMAP), &bm);
		int width = bm.bmWidth;
		int height = bm.bmHeight;

		// draw image...
		HDC hBitmapDC = ::CreateCompatibleDC(hdc);
		HBITMAP hOldStar = ::Select(hBitmapDC, hStar);
		
	/*	for (int i = 0; i < count; i++)
		{
			::GdiTransparentBlt(hdc, ptMouse[i].x,
				ptMouse[i].y, width, height, 
				hBitmapDC, 0, 0,
				width, height,
				RGB(255,255,255));			
		}*/
		for (int i = 0; i < count; i++)
		{
			::GdiTransparentBlt(hdc, sr[i].GetPos().x, sr[i].GetPos().y,
				width, height, hBitmapDC, 0, 0,
				width, height, RGB(255,255,255));
		}
		//::BitBlt(hdc, ptMouse.x - width/2,
		//	ptMouse.y - height/2, width, height, hBitmapDC, 0, 0, SRCCOPY);

		::Select(hBitmapDC, hOldStar);
		::DeleteDC(hBitmapDC);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hWnd);

		// redraw
		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);		
		
		// TODO
		for (int i = 0; i < count; i++)
		{
			sr[i].Update(rc, ptMouse);
		}

		/*dt = ::GetTickCount() - st;
		st = ::GetTickCount();*/

		// redraw
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

