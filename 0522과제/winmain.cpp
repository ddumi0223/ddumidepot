#include "windefine.h"

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPTSTR lpCmdLine, INT nCmdShow)
{
	LPCTSTR szClassName = _T("MyWindowClass");
	
	WNDCLASSEX wcex;

	::memset(&wcex, 0, sizeof(wcex));

	 wcex.cbSize = sizeof(wcex);
     wcex.style = CS_VREDRAW | CS_HREDRAW;
     wcex.lpfnWndProc = &WndProc;
     wcex.cbClsExtra = 0;
     wcex.cbWndExtra = 0;
     wcex.hInstance = hInstance;
	 wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	 wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	 wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
     wcex.lpszMenuName = NULL;
     wcex.lpszClassName = szClassName;
	 wcex.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);

	 if(!::RegisterClassEx(&wcex))
	 {
		return 1;
	 }
	
	 int nWidth = 600;
	 int nHeight = 300;

	 int cx = ::GetSystemMetrics(SM_CXSCREEN);
	 int cy = ::GetSystemMetrics(SM_CYSCREEN);

	 int x = (cx - nWidth)/2;
	 int y = (cy - nHeight)/2;

	 DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	 dwStyle &= ~WS_MAXIMIZEBOX;
	 dwStyle &= ~WS_THICKFRAME;

	 HWND hWnd = ::CreateWindowEx(0, szClassName, _T("Circle and Square"), dwStyle,
		 x, y, nWidth, nHeight, NULL, NULL, hInstance, NULL);

	 if(hWnd == NULL)
	 {
		return 2;
	 }
	 ::ShowWindow(hWnd, SW_NORMAL);
	 ::UpdateWindow(hWnd);

	 MSG msg;

	 while(true)
	 {
		 if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		 {
			 ::TranslateMessage(&msg);
			 ::DispatchMessage(&msg);
		 }
		 if(msg.message == WM_QUIT)
			 break;
	 }
}

