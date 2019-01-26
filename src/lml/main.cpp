#include <lml/application.hpp>
#include <lml/layer.hpp>
#include <lml/layers/fully_connected_layer.hpp>
#include <lml/layers/sigmoid_layer.hpp>
#include <lml/network.hpp>

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int show)
{
	if (int errorcode = lml::application::initialize(instance, show); errorcode)
	{
		lml::application::messagebox(nullptr, lml::make_error_message(TEXT("Failed to initialize."), errorcode), MB_OK | MB_ICONERROR);
		return 0;
	}

	lml::network net;
	net.add_layer(std::make_shared<lml::layers::fully_connected_layer>(2, 2));
	net.add_layer(std::make_shared<lml::layers::sigmoid_layer>());
	net.add_layer(std::make_shared<lml::layers::fully_connected_layer>(2, 1));
	
	const lml_edk::matrix input({ 0, 1, 0, 1, 0, 0, 1, 1 }, 2);
	const lml_edk::matrix output({ 0, 1, 1, 0 }, 1);

	const auto mse = [&output](const lml_edk::matrix& y)
	{
		lml_edk::matrix temp = y - output;
		double res = 0.;
		for (std::size_t i = 0; i < 4; ++i)
		{
			res += temp[{ 0, i }] * temp[{ 0, i }];
		}
		res /= 4;
		return res;
	};

	const auto test1 = mse(output);
	double te = 0;

	for (int i = 0; i < 5000; ++i)
	{
		lml_edk::matrix y = net.forward(input);
		lml_edk::matrix g = y - output;
		net.backward(g);
		net.update(0.1);

		if (i == 2500)
		{
			te = mse(y);
		}
	}

	lml_edk::matrix y = net.forward(input);
	auto test2 = mse(y);

	return 0;
}