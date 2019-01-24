#include <lml/application.hpp>
#include <lml/extension_engine.hpp>

#include <iomanip>
#include <ios>
#include <sstream>
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int show)
{
	if (int errorcode = lml::application::initialize(instance, show); errorcode)
	{
		lml::application::messagebox(nullptr, lml::make_error_message(TEXT("Failed to initialize."), errorcode), MB_OK | MB_ICONERROR);
		return 0;
	}

	lml::extension_engine e;
	e.add_extension(L"./TestExtension.dll");

	return 0;
}