#pragma once
#include "object.h"

namespace dsp {
/*!
 * Typy przyciskow 	
 */
enum ButtonType {
	TEXT_BUTTON,     /*!< Przycisk z tekstem */
	NEXT_BUTTON,     /*!< Przycisk next */
	REFRESH_BUTTON   /*!< Przycisk refresh */
};
/* Button */
class Button : public Object {
private:
	static sf::Texture text_button_;    /*!< Tekstura dla przycisku z tekstem */
	static sf::Texture next_button_;    /*!< Tekstura dla przycisku next */
	static sf::Texture refresh_button_; /*!< Tekstura dla przycisku refresh */

	void(*onClickFunction_)(void*); /*!< Wskaznik na funkcje obslugujaca klikniecie */
	sf::Texture* texture_;          /*!< Aktualna tekstura przycisku */
	sf::Sprite button_;             /*!< Aktualny sprite przycisku */
	sf::Text text_;                 /*!< Tekst ktory jest wyswietlany na przycisku, jesli jego typ to TEXT_BUTTON */
	ButtonType button_type_;        /*!< Tym przycisku */
	bool active_;                   /*!< Informacja o tym czy przycisk jest aktywny */
	const float scale_[3];          /*!< Tablica ze skala tekstur dla wszystkich typow przyciskow */

public:
	/*! Konstruktor
	*/
	Button(Object*, void(*)(void*), bool, bool, ButtonType, std::string = "", bool = true, int = 30);
	bool isClicked(sf::Vector2f);          /*!< Sprawdz czy nastapilo klikniecie */
	void setText(std::string, int = -1);   /*!< Ustawia tekst przycisku */
	void setActive(bool);                  /*!< Aktywuj przycisk */
	void Assign();                         /*!< Ustawienie sprite'a i pola tekstowego na odpowiednich pozycjach */
	sf::Vector2f getSize();                /*!< Zwraca rozmiar sprite'a */
	void AddToList();                      /*!< Dodaj do listy objektow */
	void AddToClickableList();             /*!< Dodaj do listy obiektow ktore moga byc nacisniete */
	sf::Vector2f getEndPoint() const;      /*!< Zwraca punkt konca sprite'a */
	void Draw();                           /*!< Wyswietl sprite i pole tekstowe */

	static sf::Texture* getTextBtnTexture();    /*!< Zwraca wskaznik na teksture przycisku TEXT_BUTTON */
	static sf::Texture* getNextBtnTexture();    /*!< Zwraca wskaznik na teksture przycisku NEXT_BUTTON */
	static sf::Texture* getRefreshBtnTexture(); /*!< Zwraca wskaznik na teksture przycisku REFRESH_BUTTON */
};
}
