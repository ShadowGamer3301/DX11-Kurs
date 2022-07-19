#pragma once
#include <Windows.h>
#include <stdexcept>

class Window
{
public:
	Window();
	~Window();

	inline HWND GetWindowHandler() const noexcept { return m_hWnd; }

private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};

