#include "main.h"
#include "window.h"
#include "program.h"
#include "settings.h"
#include "value.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LoadResources(hInstance);              /* wczytanie zasobow graficznych */
	StartUpParams params;                  /* struktura parametrow startowych */
	if (__argc > 1)
		getParams(__argc, __argv, params); /* wczytanie parametrow z ktorymi zostal wlaczony program (jesli wystepuja) */

	/* Okno ustawien */
	sf::RenderWindow settings_window(sf::VideoMode(330, 750), "Launcher", sf::Style::Titlebar | sf::Style::Close);
	/* Ustawienie parametrow renderowania */
	dsp::Object::setRenderWindow(&settings_window);
	dsp::Object::setPointOfReference(Point(10, 0), Point(settings_window.getSize().x - 20, settings_window.getSize().y - 10));
	/* Klasa okna ustawien */
	dsp::Settings settings(settings_window, &params);
	/* Petla wydarzen dla okna ustawien */
	while (settings_window.isOpen()) {
		sf::Event event;
		while (settings_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				settings_window.close();
				return 0;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				settings.isButtonClicked();
			}
			if (event.type == sf::Event::KeyPressed) {
				settings.ClickedKey(event.key.code);
			}
		}
		settings_window.clear(sf::Color(200, 200, 255, 255));
		settings.Draw();
		settings_window.display();
	}
	/* Okno glowne programu */
	sf::RenderWindow program_window(sf::VideoMode(params.window_resolution.x, params.window_resolution.y), "Symulator Liszaja - wykonal Kacper Adamczyk", sf::Style::Default);
	/* Ustawienie parametrow renderowania */
	program_window.setFramerateLimit(params.frame_rate);
	dsp::Object::setRenderWindow(&program_window);
	dsp::Object::setPointOfReference(Point(program_window.getSize().x - params.settings_size.x, 0),
		                             Point(params.settings_size.x - 10, params.settings_size.y));
	dsp::Object::ResetObjectList();           // Resetowanie list objektow
	dsp::Object::ResetClickableObjectList();
	/* Klasa glowna programu */
	dsp::Program program(program_window, &params, Point(10, 10));
	program.setFramer(params.frames_per_tick);
	/* Petla wydarzen dla okna glownego */
	while (program_window.isOpen()) {
		sf::Event event;
		while (program_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				program_window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				program.isButtonClicked();
			}
			if (event.type == sf::Event::KeyPressed) {
				program.ClickedKey(event.key.code);
			}
			if (event.type == sf::Event::Resized) {
				dsp::Object::setPointOfReference(Point(program_window.getSize().x - params.settings_size.x, 0),
					                             Point(params.settings_size.x - 10, params.settings_size.y));
				program.ResizeWnd();
				program_window.setView(sf::View(sf::FloatRect(0.f, 0.f, float(event.size.width), float(event.size.height))));
			}
		}
		program_window.clear(sf::Color(200, 200, 200, 255));
		program.Draw();
		program_window.display();
	}
	return 0;
}