#include "main.h"
#include "common.h"
#include "window.h"
#include "object.h"
#include "arrows.h"
#include "button.h"
#include "resource.h"

/*
 *  Struktura Point
 */
Point::Point()
{
	x = 0;
	y = 0;
}
unsigned int Point::getQuantity()
{
	return x*y;
}
/*
 *
 */
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
/*
 * Struktura StartUpParams
 */
StartUpParams::StartUpParams()
{
	size.x = 100;
	size.y = 100;
	window_resolution.x = 1050;
	window_resolution.y = 750;
	settings_size.x = 300;
	settings_size.y = 750;
	frame_rate = 60;
	frames_per_tick = 3;
	infection_time = 6;
	immune_time = 4;
	infection_propability = 50;
}
/*
 *  Definicje funkcji
 */
void ErrorMsg(std::string error, std::string title)
{
	MessageBoxA(NULL, error.c_str(), title.c_str(), MB_ICONERROR | MB_OK);
}

void getParams(int argc, char** argv, StartUpParams& params)
{
	std::vector<char> prefix = { 'x', 'y', 'f','n', 'i', 'm', 'p'};

	for (int i = 0; i < prefix.size(); i++) {
		for (int j = 1; j < argc; j++) {
			if (argv[j][0] == prefix[i]) {
				switch (i) {
				case 0:
					params.window_resolution.x = atoi((std::string(argv[j]).substr(1)).c_str());
					break;
				case 1:
					params.window_resolution.y = atoi((std::string(argv[j]).substr(1)).c_str());
					break;
				case 2:
					params.frame_rate = atoi((std::string(argv[j]).substr(1)).c_str());
					break;
				case 3:
					params.size.x = atoi((std::string(argv[j]).substr(1)).c_str());
					params.size.y = atoi((std::string(argv[j]).substr(1)).c_str());
					break;
				case 4:
					params.infection_time = atoi((std::string(argv[j]).substr(1)).c_str());
					break;
				case 5:
					params.immune_time = atoi((std::string(argv[j]).substr(1)).c_str());
					break;
				case 6:
					params.infection_propability = atoi((std::string(argv[j]).substr(1)).c_str());
					break;
				}
			}
		}
	}
}
/*
 *
 */
unsigned int rand(unsigned int beginning, unsigned int end)
{
	static bool init = false;
	if (!init) {
		srand(unsigned(time(NULL)));
		init = true;
	}
	return ::rand() % (end - beginning) + beginning;
}

void LoadResources(HINSTANCE &hInstance)
{
	try {
		if (!dsp::Window::getIcon()->loadFromFile("resources\\icon"))
			throw "Blad wczytywania ikony";
		if (!dsp::Object::getFont()->loadFromFile("resources\\font"))
			throw "Blad wczytywania czcionki";
		if (!dsp::Arrows::getTexture()->loadFromFile("resources\\arrow"))
			throw "Nie mozna wczytac grafiki: arrow";
		if (!dsp::Button::getTextBtnTexture()->loadFromFile("resources\\button"))
			throw "Nie mozna wczytac grafiki: button";
		if (!dsp::Button::getNextBtnTexture()->loadFromFile("resources\\next_button"))
			throw "Nie mozna wczytac grafiki: next_button";
		if (!dsp::Button::getRefreshBtnTexture()->loadFromFile("resources\\refresh_button"))
			throw "Nie mozna wczytac grafiki: refresh_button";
	} catch (const char* e) {
		ErrorMsg(e, "Error");
		exit(1);
	}
}


