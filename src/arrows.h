#pragma once

#include "object.h"
#include "value.h"
/* Arrows */
namespace dsp {
class Arrows : public Object {
private: 
	static sf::Texture texture_;   /*!< Tekstura strzalki (taka sama dla wszystkich obiektow) */
	sf::Sprite left_;              /*!< Sprite lewej strzalki */
	sf::Sprite right_;             /*!< Sprite prawej strzalki */
	float scale_;                  /*!< Skala sprite wzgledem tekstury */
	int step_;                     /*!< Wartosc o jaka jest zmieniana zmienna */
	float fractionR_;              /*!< Wspolczynnik wypelnienia przestrzeni w ktorej jest wyswietlana prawa strzalka */
	float fractionL_;              /*!< Wspolczynnik wypelnienia przestrzeni w ktorej jest wyswietlana lewa strzalka */
	unsigned int* value_;          /*!< Modyfikowana zmienna */	
	unsigned int min_;             /*!< Minimalna wartosc zmiennej */
	unsigned int max_;             /*!< Maksymalna wartosc zmiennej */

public:
	/*! Konstruktor
	 */
	Arrows(Object*, bool, bool, unsigned int* = nullptr, unsigned int = 0, unsigned int = UINT_MAX, int = 1, float = 1, float = 1, float = 0.1);

	void Assign();                     /*!< Ustawienie sprite'ow na odpowiednich pozycjach */
	sf::Vector2f getSize();            /*!< Zwraca rozmiar sprite'a */
	void AddToList();                  /*!< Dodaj do listy objektow */
	void AddToClickableList();         /*!< Dodaj do listy obiektow ktore moga byc nacisniete */
	sf::Vector2f getEndPoint() const;  /*!< Zwraca punkt konca sprite'a prawej strzalki */
	void Draw();                       /*!< Wyswietl sprite'y */
	bool isClicked(sf::Vector2f);      /*!< Sprawdz czy nastapilo klikniecie */
	void setMin(unsigned int);         /*!< Ustawia minimum */
	void setMax(unsigned int);         /*!< Ustawia maksimum */
	void AssignValue(unsigned int*);   /*!< Ustawia adres modyfikowanej zmiennej */

	static sf::Texture* getTexture();  /*!< Zwraca wskaznik na teksture */
};
}
