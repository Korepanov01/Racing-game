#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <windows.h>

HANDLE HandleCons;
HWND hWnd;
int wid, heg;

class Graphics
{
private:
	static HPEN hPen;
	static HBRUSH hBrush;
public:
	static HDC dc;
	static void CreateGraphics();
	static void DeleteGraphics();
	static void Set_pen(COLORREF, int);
	static void Set_brush(COLORREF, int);
	static void Line(int, int, int, int);
	static void Point(int,int,COLORREF);
};
HPEN Graphics::hPen;
HBRUSH Graphics::hBrush;
HDC Graphics::dc;

void Graphics::CreateGraphics()
{
	dc = GetDC(hWnd);
}
void Graphics::DeleteGraphics()
{
	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(hWnd, dc);
	DeleteDC(dc);
}

void Graphics::Set_pen(COLORREF c, int w)
{
	hPen=CreatePen(PS_INSIDEFRAME, w, c);
	SelectObject(dc, hPen); 
}

void Graphics::Set_brush(COLORREF c, int pr)
{
	if(pr == 0)
		hBrush = ::CreateSolidBrush(HOLLOW_BRUSH);
	else
		hBrush = ::CreateSolidBrush(c);
	::SelectObject(dc, hBrush); 
}

void Graphics::Line(int x1, int y1, int x2, int y2)
{
	MoveToEx(dc, x1, y1, NULL);
	LineTo(dc, x2, y2);
}

void Graphics::Point(int x, int y, COLORREF c)
{
	SetPixel(dc, x, y, c);
}

#endif GRAPHICS_H