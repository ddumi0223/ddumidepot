#pragma once

#include <windows.h>
#include <tchar.h>
#include "BaseType.h"
#include "Utility.hpp"

class Image
{
public :
	Image();
	virtual ~Image();

	bool Load(LPCTSTR szFileName);
	bool Load(LPCTSTR szFileName, const Rect& rc);

	void Draw(HDC hdc);
	void TileDraw(HDC hdc);
	void SetRect(const Rect& rc);

	void SetTransparent(const COLORREF& clr);

private :
	bool _load_detail(LPCTSTR szFileName);
private :
	HBITMAP hBitmap;
	Rect rcSrc;
	Rect rcDest;

	COLORREF clrTransparent;
	bool bUseTransparent;
};