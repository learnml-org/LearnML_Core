#include <Windows.h>

#include <lml/matrix.hpp>

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int show)
{
	lml::matrix a({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 3);
	lml::matrix b({ 1, 2, 3, 4, 5, 6 }, 3);
	lml::matrix c = lml::dot(a, b);

	return 0;
}