#pragma once
#include "main.h"
#include "window.h"
#include "cell.h"
#include "common.h"
#include "object.h"
#include "caption.h"
#include "value.h"
#include "arrows.h"
#include "button.h"

namespace dsp {
/* Settings */
class Settings : public Window {
private:
	Point max_size_;         /*!< Maksymalny rozmiar pola wzgledem rozdzielczosci okna */
	Point min_window_size_;  /*!< Minimalna rozdzielczosc ekranu wzgledem wielkosci pola */

	dsp::Caption text_resolution_;     /*!< Pole teksowe z informacja o rozdzielczosc okna */
	dsp::Caption text_resolution_x_;   /*!< Pole teksowe z informacja o rozdzielczosc okna x */
	dsp::Value value_resolution_x_;    /*!< Wartosc rozdzielczosci okna x */
	dsp::Arrows arrows_resolution_x_;  /*!< Strzalki do zmiany wartosci rozdzielczosci okna x */
	dsp::Caption text_resolution_y_;   /*!< Pole teksowe z informacja o rozdzielczosc okna y */
	dsp::Value value_resolution_y_;    /*!< Wartosc rozdzielczosci okna y */
	dsp::Arrows arrows_resolution_y_;  /*!< Strzalki do zmiany wartosci rozdzielczosci okna y */

	dsp::Caption text_size_;     /*!< Pole teksowe z informacja o wielkosci pola */
	dsp::Caption text_size_x_;   /*!< Pole teksowe z informacja o wielkosci pola x */
	dsp::Value value_size_x_;    /*!< Wartosci wielkosci pola x */
	dsp::Arrows arrows_size_x_;  /*!< Strzalki do zmiany wartosci wielkosci pola x */
	dsp::Caption text_size_y_;   /*!< Pole teksowe z informacja o wielkosci pola y */
	dsp::Value value_size_y_;    /*!< Wartosci wielkosci pola y */
	dsp::Arrows arrows_size_y_;  /*!< Strzalki do zmiany wartosci wielkosci pola y */

	dsp::Caption text_speed_;   /*!< Pole teksowe z informacja o predkosci symulacji */
	dsp::Value value_speed_;    /*!< Wartosc predkosci symulacji */
	dsp::Arrows arrows_speed_;  /*!< Strzalki do zmiany wartosci predkosci symulacji */

	dsp::Caption text_infection_time_;   /*!< Pole teksowe z informacja o czasie infekcji */
	dsp::Value value_infection_time_;    /*!< Wartosc czasu infekcji */
	dsp::Arrows arrows_infection_time_;  /*!< Strzalki do zmiany wartosci czasu infekcji */

	dsp::Caption text_immune_time_;   /*!< Pole teksowe z informacja o czasie odpornosci */
	dsp::Value value_immune_time_;    /*!< Wartosc czasu odpornosci */
	dsp::Arrows arrows_immune_time_;  /*!< Strzalki do zmiany wartosci czasu odpornosci */

	dsp::Caption text_propability_;   /*!< Pole teksowe z informacja o prawdopodobienstwie infekcji */
	dsp::Value value_propability_;    /*!< Wartosc prawdopodobienstwa infekcji */
	dsp::Arrows arrows_propability_;  /*!< Strzalki do zmiany wartosci prawdopodobienstwa infekcji */

	dsp::Caption _SPACER_button_start_;  /*!< Pole tekstowe pelniace role wysrodkowania przycisku */
	dsp::Button button_start_;           /*!< Przycisk do rozpoczecia symulacji */
public:
	/*! Konstruktor
	*/
	Settings(sf::RenderWindow&, StartUpParams*, Point = Point(10, 10));
private:
	void initDraw();     /*!< Inicjalizacja grafik */
	void CalcMaxSize();  /*!< Oblicz maksymalny rozmiar pola */
public:
	void Draw();             /*!< Rysowanie grafik */
	void isButtonClicked();  /*!< Obsluga przyciskow */

	friend void onButtonStartClick(void*);  /*!< Zaprzyjaznienie funkcji obslugi klikniecia przycisku ButtonStart */

	void ClickedKey(sf::Keyboard::Key);  /*!< Zmiana wartosci edytowanych pol tekstowych wartosciami z klawiatury */
};
void onButtonStartClick(void*);  /*!< Funkcja obslugi przycisku ButtonStart */
}