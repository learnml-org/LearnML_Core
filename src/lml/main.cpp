#include <lml/application.hpp>

#include <cstdint>
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int show)
{
	if (int errorcode = lml::application::initialize(instance, show); errorcode)
	{
		lml::application::messagebox(nullptr, lml::make_error_message(errorcode), MB_OK | MB_ICONERROR);
		return 0;
	}

	lml::application::run();

	return 0;
}