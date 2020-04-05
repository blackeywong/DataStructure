#pragma once
#ifndef _DRAWING_H
#define _DRAWING_H
#include <Windows.h>
#include <string>

struct Point {
	Point(int x, int y) : x(x), y(y) {}
	Point() = default;
	int x;
	int y;
};

struct MyRectangle {
	MyRectangle(Point p1, Point p2, COLORREF color) :topLeft(p1), bottomRight(p2), color(color) {}
	MyRectangle() = default;
	Point topLeft;
	Point bottomRight;
	COLORREF color;
};

void drawLine(HDC dc, int left, int top, int right, int bottom, COLORREF color);
void drawRectangle(HDC dc, int left, int top, int right, int bottom, COLORREF color);
void fillRectangle(HDC dc, int left, int top, int right, int bottom, COLORREF color);
void erase(HDC dc, int left, int top, int right, int bottom);

void drawLine(HDC dc, Point pt1, Point pt2, COLORREF color);
void drawRectangle(HDC dc, MyRectangle rect);
void fillRectangle(HDC dc, MyRectangle rect);
void erase(HDC dc, MyRectangle rect);

void moveRectangle(HDC dc, MyRectangle rect, Point to);
void animeMoveRectangle(HDC dc, MyRectangle rect, Point to);

void gotoPos(int x, int y);
void drawText(HWND hwnd, HDC dc, int x, int y, const std::string& str);

#endif
