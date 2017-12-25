#pragma once
#include "main.h"
#include "common.h"

namespace dsp {
class Window {
protected:
	static sf::Image icon_;           /*!< Ikona okna */
	sf::RenderWindow& window_;        /*!< Referencja do glownego okna */
	StartUpParams* start_up_params_;  /*!< Wskaznik na parametry startowe */
	Point draw_area_start_point_;     /*!< Poczatek strefy rysowania okna glownego */
public:
	/*!
	*/
	Window(sf::RenderWindow&, StartUpParams*, Point = Point(0, 0));
	static sf::Image* getIcon();  /*!< Zwraca ikone */
private:
	virtual void initDraw() = 0;  /*!< Inicjalizacja grafik */
	/* Metody czysto wirtualne */
public:
	virtual void Draw() = 0;                         /*!< Wyswietl grafiki */
	virtual void isButtonClicked() = 0;              /*!< Obsluga klikniecia */
	virtual void ClickedKey(sf::Keyboard::Key) = 0;  /*!< Obsluga klawiatury */
};
}