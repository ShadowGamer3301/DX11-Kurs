#include <Windows.h>

int main(void)
{
	//Stworzenie i zdefiniowanie klasy okna
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = nullptr;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"BaseWindow";
	wcex.hIconSm = wcex.hIcon;

	//Rejstracja klasy okna
	RegisterClassEx(&wcex);
	
	//Swtórz okno
	HWND wnd = CreateWindow(L"BaseWindow", L"Kurs DirectX", WS_OVERLAPPEDWINDOW, 0, 0, 1280, 720, nullptr, nullptr, nullptr, nullptr);

	//Poka¿ okno
	ShowWindow(wnd, SW_SHOWDEFAULT);

	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}