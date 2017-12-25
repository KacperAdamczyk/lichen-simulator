#pragma once

#include "object.h"

namespace dsp {
	/* Value */
class Value : public Object {
private:
	sf::Text text_value_;           /*!< Pole tekstowe ktore wyswietla wartosc zmiennej */
	sf::RectangleShape rectangle_;  /*!< Prostokat bedacy tlem */
	unsigned int* value_;           /*!< Wskaznik na zmienna */
	unsigned int min_;              /*!< Minimalna wartosc zmiennej */
	unsigned int max_;              /*!< Maksymalna wartosc zmiennej */
	float fraction_;                /*!< Wspolczynnik wypelnienia przestrzeni w ktorej jest wyswietlane pole tekstowe */
	static Value* edited_;          /*!< Wskaznik na pole z wartoscia ktore jest edytowane z klawiatury */
	bool is_edited_;                /*!< Informacja o tym czy pole jest aktualnie edytowane */
public:
	/*! Konstruktor
	*/
	Value(Object*, bool, bool, unsigned int*, unsigned int = 0, unsigned int = UINT_MAX, float = 1, int = 40, sf::Color = sf::Color::Transparent);
	
	void ChangeValue(int);                                /*!< Zmien wartosc zmiennej */
	void Assign();                                        /*!< Ustawienie pola tekstowego i tla na odpowiednich pozycjach */
	sf::Vector2f getSize();                               /*!< Zwraca rozmiar tla */
	void AddToList();                                     /*!< Dodaj do listy objektow */
	void AddToClickableList();                            /*!< Dodaj do listy obiektow ktore moga byc nacisniete */
	sf::Vector2f getEndPoint() const;                     /*!< Zwraca punkt konca pola tekstowego z wartoscia */
	void Draw();                                          /*!< Wyswietl pole tekstowe i tlo */
	void AssignValue(unsigned int*);                      /*!< Ustawia adres modyfikowanej zmiennej */
	unsigned int getMin() const;                          /*!< Zwraca minimum wartosci */
	unsigned int getMax() const;                          /*!< Zwraca maksimum wartosci */
	void setMin(unsigned int);                            /*!< Ustawia munimum wartosci */
	void setMax(unsigned int);                            /*!< Ustawia maksimum wartosci */
	void CheckValue();                                    /*!< Sprawdz czy wartosc nalezy do dozwolonego przedzialu */
	bool isClicked(sf::Vector2f);                         /*!< Sprawdz czy nastapilo klikniecie */
	static bool isEdited(Value*);                         /*!< Zwraca czy aktualny obiekt jest edytowany */
	static void EditFromKeyboard(sf::Keyboard::Key key);  /*!< Zmien wartosc edytowanego pola wartosciami wprowadzanymi z klawiatury */
};
}

