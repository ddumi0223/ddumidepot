#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;
		
	static Image tile;
	static std::list<Rect> TileRc;
	static INT tileW;
	static INT tileH;

	static Point ptMouse;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		backbuffer.Attach(hWnd);

		// TODO
		
		tile.Load(_T("bg_ingame.bmp"), Rect(0, 0, 100, 100));
			
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
	else if (uMsg == WM_SIZE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		BITMAP bm;
		::GetObject(tile.GetBitMap(), sizeof(BITMAP), &bm);

		tileW = rc.width() / bm.bmWidth + 2;
		tileH = rc.height() / bm.bmHeight + 1;		
		for (int i = 0; i < tileH; i++)
		{
			for(int j = 0; j < tileW; j++)
			{
				TileRc.push_back(Rect(j * bm.bmWidth, i * bm.bmHeight, (j + 1) * bm.bmWidth, (i + 1) * bm.bmHeight));	
			}
		}

		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);
				
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);
		
		//backbuffer << RGB(255,200,200);		
		
		// TODO
		std::list<Rect>::iterator itor;

		for(itor = TileRc.begin(); itor != TileRc.end(); itor++)
		{
			tile.SetRect((*itor));
			tile.Draw(hdc);
		}
		
		//backbuffer.Draw();

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}	
	else if (uMsg == WM_TIMER)
	{
		// TODO

	
		Rect rc;
		::GetClientRect(hWnd, &rc);

		std::list<Rect>::iterator itor;

		BITMAP bm;
		::GetObject(tile.GetBitMap(), sizeof(BITMAP), &bm);

		for(itor = TileRc.begin(); itor != TileRc.end(); itor++)
		{
			(*itor).left -= 5;
			(*itor).right -= 5;
			if((*itor).right < rc.left)
			{
				(*itor).left += tileW * bm.bmWidth;
				(*itor).right += tileW * bm.bmWidth;
			}
		}

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();
		
		::InvalidateRect(hWnd, &rc, TRUE);


		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
