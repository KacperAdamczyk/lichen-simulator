#pragma once

#include "main.h"
#include "object.h"

namespace dsp {
	/* Caption */
class Caption : public Object {
private:
	sf::Text text_; /*!< Tekst ktory jest wyswietlany */
public:
	/*! Konstruktor
	*/
	Caption(dsp::Object*, bool, std::string = "", int = 30);

	void Assign();                     /*!< Ustawienie pola tekstowego na odpowiedniej pozycji */
	sf::Vector2f getSize();            /*!< Zwraca rozmiar pola tekstowego */
	void AddToList();                  /*!< Dodaj do listy objektow */
	sf::Vector2f getEndPoint() const;  /*!< Zwraca punkt konca pola tekstowego */
	void Draw();                       /*!< Wyswietl pole tekstowe */
};
}

