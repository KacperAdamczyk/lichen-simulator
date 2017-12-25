#pragma once

#include "main.h"
#include "window.h"
#include "common.h"

#define FONT_PROP 0.3f /*<! Wspolczynnik proporcjonalnosci czcionki */

namespace dsp {
	/* Object */
class Object {
protected:
	Object* parent_;       /*<! Wskaznik na obiekt obok ktorego ma zostac umieszczony ten obiekt */
	unsigned int spacer_;  /*<! Dlugosc odstepu miedzy obiektami */

	static std::vector<Object*> object_list_;            /*<! Lista obiektow */
	static std::vector<Object*> clickable_object_list_;  /*<! Lista obiektow ktore mozna nacisnac */
	static Point point_of_reference_start_;              /*<! Punkt odniesienia do pozycjonowania obiektow */
	static Point point_of_reference_size_;               /*<! Wielkosc pola w ktorym sa rozmieszczane obiekty */
	static sf::RenderWindow* window_;                    /*<! Wskaznik na okno na ktorym sa renderowane obiekty */
	static Window* window_class_;                        /*<! Klasa okna ktora posiada ten obiekt */
	static sf::Font font_;                               /*<! Czcionka */
public:
	/*! Konstruktor
	*/
	Object(Object* = NULL);

	static std::vector<Object*> getObjectList();           /*<! Zwraca liste obiektow */
	static std::vector<Object*> getClickableObjectList();  /*<! Zwraca liste obiektow ktore mozna nacisnac */
	static void ResetObjectList();                         /*<! Wyczysc liste obiektow */
	static void ResetClickableObjectList();                /*<! Wyczysc liste obiektow ktore mozna nacisnac */
	static void setRenderWindow(sf::RenderWindow*);        /*<! Ustaia wskaznik na okno */
	static void setWindowClass(Window*);                   /*<! Ustawia klase okna ktora posiada ten obiekt */
	static void setPointOfReference(Point, Point);         /*<! Ustawia punkt odniesienia do pozycjonowania obiektow */
	static sf::Font* getFont();                            /*<! Zwraca czcionke */
	static int FindInObjectList(Object*);                  /*<! Zwraca pozycje obiektu w liscie obiektow */

	sf::Vector2f getValidPosition(Object*) const;/*<! Zwraca poprawna pozycje obiektu */

	/* Metody czysto abstrakcyjne */
	virtual void Assign() = 0;                               /*<! Przypisz pozycje obiektu */
	virtual sf::Vector2f getSize() = 0;                      /*<! Zwraca rozmiar obiektu */
	virtual void AddToList() = 0;                            /*<! Dodaj obiekt do listy obiektow */
	virtual sf::Vector2f getEndPoint() const = 0;	         /*<! Zwraca punkt konczacy obiekt */
	virtual void Draw() = 0;                                 /*<! Rysuj obiekt */
	virtual bool isClicked(sf::Vector2f) { return false; };  /*<! Obsluga klikniecia obiektu */
};	
}