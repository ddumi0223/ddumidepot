﻿#include "Image.h"

Image::Image()
: hBitmap(NULL)
, bUseTransparent(false)
{
}
Image::~Image()
{
	if (hBitmap)
	{
		::DeleteObject(hBitmap);
		hBitmap = NULL;
	}
}

bool Image::Load(LPCTSTR szFileName)
{
	if (!_load_detail(szFileName)) 
		return false;

	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);

	rcSrc = Rect(0, 0, bm.bmWidth, bm.bmHeight);
	rcDest = rcSrc;

	return true;
}
bool Image::Load(LPCTSTR szFileName, const Rect& rc)
{
	if (!_load_detail(szFileName)) 
		return false;

	rcSrc = rc;
	rcDest = rcSrc;

	return true;
}

void Image::Draw(HDC hdc)
{
	if (hBitmap == NULL) return;

	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOld = ::Select(hBitmapDC, hBitmap);

	if (bUseTransparent)
	{
		::GdiTransparentBlt(hdc, rcDest.left, rcDest.top,
			rcDest.width(), rcDest.height(),
			hBitmapDC,
			rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), clrTransparent);
	}
	else
	{
		::StretchBlt(hdc, rcDest.left, rcDest.top,
			rcDest.width(), rcDest.height(),
			hBitmapDC,
			rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), SRCCOPY);
	}

	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);
}

void Image::TileDraw(HDC hdc)
{
	if (hBitmap == NULL) return;
	
	/*HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOld = ::Select(hBitmapDC, hBitmap);*/
		
	INT img_width = rcSrc.width() / rcDest.width();
	INT img_height = rcSrc.height() / rcDest.height();
		
	for(int i = 0; i < rcSrc.width(); i++)
	{
		for(int j = 0; j < rcSrc.height(); j++)
		{
			::StretchBlt(hdc, rcDest.left, rcDest.top, 
				rcDest.width(), rcDest.height(), hBitmapDC, rcSrc.left, rcSrc.top, rcSrc.width(), rcSrc.height(), SRCCOPY);
		}
	}
	

	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);
}

void Image::SetRect(const Rect& rc)
{
	rcDest = rc;
}
void Image::SetTransparent(const COLORREF& clr)
{
	clrTransparent = clr;
	bUseTransparent = true;
}
bool Image::_load_detail(LPCTSTR szFileName)
{
	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);
	if (hBitmap == NULL)
		return false;

	return true;
}
