#include "Window.h"
#include "loguru.hpp"
#include "DxBase.h"

int main(int argc, char** argv)
{
	try
	{
		loguru::init(argc, argv);
		loguru::add_file("Log.txt", loguru::Append, loguru::Verbosity_MAX);

		Window wnd;
		DxBase gfx(wnd.GetWindowHandler());

		MSG msg = {};

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			gfx.Render(0, 0.4, 0.7, 1.0);
		}

		return msg.wParam;
	}
	catch (const std::runtime_error& e)
	{
		LOG_F(ERROR, "Exception caught: %s", e.what());
		return 1;
	}

}

