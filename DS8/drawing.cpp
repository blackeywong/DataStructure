#include "drawing.h"
#include <thread>
#include <chrono>

void drawLine(HDC dc, int left, int top,  int right, int bottom, COLORREF color) {
	using std::swap;
	if (right != left) {
		double k = (bottom - top) * 1.0 / (right - left);
		double d = bottom * 1.0 - k * right;
		if (left > right) {
			swap(left, right);
			swap(top, bottom);
		}
		for (int x = left; x <= right; ++x) {
			int y = (int)(k * x + d);
			SetPixel(dc, x, y, color);
		}
	}
	else {
		if (top > bottom) {
			swap(top, bottom);
		}
		for (int y = top; y <= bottom; ++y) {
			SetPixel(dc, left, y, color);
		}
	}
}

void drawRectangle(HDC dc, int left, int top, int right, int bottom, COLORREF color) {
	drawLine(dc, left, top, right, top, color);
	drawLine(dc, right, top, right, bottom, color);
	drawLine(dc, left, bottom, right, bottom, color);
	drawLine(dc, left, top, left, bottom, color);
}

void fillRectangle(HDC dc, int left, int top, int right, int bottom, COLORREF color) {
	for (int x = left; x <= right; ++x) {
		drawLine(dc, x, top, x, bottom, color);
	}
}

void erase(HDC dc, int left, int top, int right, int bottom) {
	fillRectangle(dc, left, top, right, bottom, RGB(0,0,0));
}

void drawLine(HDC dc, Point pt1, Point pt2, COLORREF color) {
	drawLine(dc, pt1.x, pt1.y, pt2.x, pt2.y, color);
}

void drawRectangle(HDC dc, MyRectangle rect) {
	drawRectangle(dc, rect.topLeft.x, rect.topLeft.y, rect.bottomRight.x, rect.bottomRight.y, rect.color);
}

void fillRectangle(HDC dc, MyRectangle rect) {
	fillRectangle(dc, rect.topLeft.x, rect.topLeft.y, rect.bottomRight.x, rect.bottomRight.y, rect.color);
}

void erase(HDC dc, MyRectangle rect) {
	erase(dc, rect.topLeft.x, rect.topLeft.y, rect.bottomRight.x, rect.bottomRight.y);
}

void moveRectangle(HDC dc, MyRectangle rect, Point to) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
	erase(dc, rect);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	fillRectangle(dc, to.x, to.y, rect.bottomRight.x+to.x - rect.topLeft.x, rect.bottomRight.y+to.y - rect.topLeft.y, rect.color);
}

void animeMoveRectangle(HDC dc, MyRectangle rect, Point to) {
	double stepX = (to.x * 1.0 - rect.topLeft.x) / 10;
	double stepY = (to.y * 1.0 - rect.topLeft.y) / 10;
	for (int i = 1; i <= 10; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		erase(dc, rect.topLeft.x + (int)(stepX * (i-1)), rect.topLeft.y + (int)(stepY * (i - 1)), rect.bottomRight.x + (int)(stepX * (i - 1)), rect.bottomRight.y + (int)(stepY * (i - 1)));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		fillRectangle(dc, rect.topLeft.x + (int)(stepX * i), rect.topLeft.y + (int)(stepY * i), rect.bottomRight.x + (int)(stepX * i), rect.bottomRight.y + (int)(stepY * i), rect.color);
	}
}

void gotoPos(int x, int y) {
	COORD p = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void drawText(HWND hwnd, HDC dc, int x, int y, const std::string& str) {
	PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);
	//TextOutA(dc, x, y, str.c_str(), str.length());
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + 20;
	rect.bottom = y + 20;
	DrawTextA(dc, str.c_str(), str.length(), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	EndPaint(hwnd, &ps);
}