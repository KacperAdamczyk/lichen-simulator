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
	/*!
	*  Definicja struktury graficznej komorki
	*/
struct GraphicCell {
	Cell cell;                /*!< Logiczna czesc komorki typu Cell */
	sf::RectangleShape rect;  /*!< Graficzna reprezentacja komorki */
	GraphicCell() {};         /*!< Konstruktor domyslny */
	/*! Konstruktor 
	*/
	GraphicCell(unsigned int infection_time, unsigned int immune_time, unsigned int infection_propability) : cell(infection_time, immune_time, infection_propability) {}
	GraphicCell getModel();   /*!< Zwroc model komorki ktory bedzie powielony na reszte nowych komorek */
};
/*!
 *  Stany pracy aplikacji
 */
enum Action {
	RESUMED = 0,  /*!< Wznowiona */
	PAUSED = 1,   /*!< Pauza */
	STEPPED = 2   /*!< Praca krokowa */
};

/* Program */
class Program : public Window {
private:
	std::vector<GraphicCell> field_;      /*!< Wektor o dlugosc x*y (size_) typu GraphicCell */
	Point size_;				          /*!< Rozmiar pola */
	Point old_size_;                      /*!< Rozmiar pola przed zmiana rozmiaru */
	Point max_size_;                      /*!< Maksymalny rozmiar pola ktory zmiesci sie w polu o danej rozdzielczosci */
	Point min_window_size_;               /*!< Minimalna rozdzielczosc okna ktora zmiesi pole gdy komorki maja wielkosc 1px x 1px */

	/* Punkty i wymairy graficzne */

	Point draw_area_size_;                 /*!< Rozmiary strefy rysowania pola */
	unsigned int gcell_size_;			   /*!< Rozmiar graficzny komorki */
	unsigned int frames_since_last_tick_;  /*!< Ilosc klatek od ostatniego ticku programu */
	unsigned int frames_per_tick_;		   /*!< Ilosc klatek na tick programu */
	unsigned int healthy_cells_;           /*!< Ilosci zdrowych komorek w danej chwili */
	unsigned int immune_cells_;            /*!< Ilosci odpornych komorek w danej chwili */
	unsigned int infected_cells_;          /*!< Ilosci zainfekowanych komorek w danej chwili */
	Action action_;                        /*!< Aktualny stan pracy programu */

	/* Kolejnosc ustawienia obiektow na ekranie jest ustalona przez kolejnosc ich deklaracji */
	dsp::Caption text_infection_time_;   /*!< Pole teksowe z informacja o czasie infekcji */
	dsp::Value value_infection_time_;    /*!< Wartosc czasu infekcji */
	dsp::Arrows arrows_infection_time_;  /*!< Strzalki do zmiany wartosci czasu infekcji */

	dsp::Caption text_immune_time_;   /*!< Pole teksowe z informacja o czasie odpornosci */
	dsp::Value value_immune_time_;    /*!< Wartosc czasu odpornosci */
	dsp::Arrows arrows_immune_time_;  /*!< Strzalki do zmiany wartosci czasu odpornosci */

	dsp::Caption text_propability_;   /*!< Pole teksowe z informacja o prawdopodobienstwie infekcji */
	dsp::Value value_propability_;    /*!< Wartosc prawdopodobienstwa infekcji */
	dsp::Arrows arrows_propability_;  /*!< Strzalki do zmiany wartosci prawdopodobienstwa infekcji */

	dsp::Caption text_speed_;  /*!< Pole teksowe z informacja o predkosci symulacji */
	dsp::Value value_speed_;   /*!< Wartosc predkosci symulacji */
	dsp::Arrows arrows_speed_; /*!< Strzalki do zmiany wartosci predkosci symulacji */

	dsp::Caption text_size_x_;   /*!< Pole teksowe z informacja o rozmiarze pola x */
	dsp::Value value_size_x_;    /*!< Wartosc rozmiaru pola x */
	dsp::Arrows arrows_size_x_;  /*!< Strzalki do zmiany wartosci rozmiaru pola x */
	dsp::Caption text_size_y_;   /*!< Pole teksowe z informacja o rozmiarze pola y */
	dsp::Value value_size_y_;    /*!< Wartosc rozmiaru pola y */
	dsp::Arrows arrows_size_y_;  /*!< Strzalki do zmiany wartosci rozmiaru pola y */

	dsp::Value value_healthy_counter_;   /*!< Wartosci z iloscia zdrowych komorek */
	dsp::Value value_immune_counter_;    /*!< Wartosci z iloscia odpornych komorek */
	dsp::Button button_refresh_;         /*!< Przycisk do czyszczenia pola komorek */
	dsp::Value value_infected_counter_;  /*!< Wartosci z iloscia zainfekowanych komorek */

	dsp::Button button_pause_;  /*!< Przycisk do pauzaowania/wznawiania symulacji */
	dsp::Button button_next_;   /*!< Przycisk do pracy krokowej podczas pauzy */
public:
	/*! Konstruktor
	(sf::RenderWindow& render_window, StartUpParams* start_up_params, Point draw_area_start_point)
	*/
	 Program(sf::RenderWindow&, StartUpParams*, Point); /* konstruktor */

private:
	 void Allocate();                    /*!< Ustawia rozmiar wektora */
	 Point get2DPosition(unsigned int);  /*!< Konwertuje pozycje 1D na pozycje 2D */
	 bool Framer(bool = true);           /*!< Ustala moment ticku */
	 void Resize();                      /*!< Zmien rozmiar pola */
	 void CalcMaxSize();                 /*!< Oblicz maksymalny rozmiar pola */
	 void CalcMinWndSize();              /*!< Oblicz minimalny rozmiar okna */
public:
	 void setFramer(unsigned int);  /*!< Ustawia ilosc klatek na jednostke czasu */
private:
	 void CalculateGcellParams();  /*!< Oblicza rozmiar graficzny komorki */
	 void initDraw();              /*!< Inicjalizacja grafik */
	 void PrepGCells();            /*!< Przygotowanie graficznej czesci komorek */
	 void AssignValues();          /*!< Przypisanie wskaznikow wartosci do pol z wartosciami */
public:
	 void Draw();       /*!< Rysowanie grafik */
	 void ResizeWnd();  /*!< Zmien rozmiar okna */
private:
	 void Infect1st();  /*!< Infekuj pierwsza komorke znajdujaca sie na srodku */
	 void Infect();     /*!< Infekcja sasiednich komorek zarazonej komorki */
public:
	 void isButtonClicked(); /*!< Obsluga przyciskow */
private:
	 friend void onButtonRefreshClick(void* _this);  /*!< Zaprzyjaznienie funkcji obslugi klikniecia przycisku ButtonRefresh */
	 friend void onButtonPauseClick(void* _this);    /*!< Zaprzyjaznienie funkcji obslugi klikniecia przycisku ButtonPause */
	 friend void onButtonNextClick(void* _this);     /*!< Zaprzyjaznienie funkcji obslugi klikniecia przycisku ButtonNext */
public:
	 void ClickedKey(sf::Keyboard::Key);  /*!< Zmiana wartosci edytowanych pol tekstowych wartosciami z klawiatury */
private:
	 void InfectByClick(sf::Vector2f);  /*!< Obsluga infekcji przez klikniecie komorki */
	 void Look4ParamChanges();          /*!< Zastosowanie zmian parametrow na wszystkie komorki */
     void ChangeFramesPerTick(float);     /*!< Zmiana wartosci trwania ticku programu */
};
void onButtonRefreshClick(void* _this);/*!< Funkcja obslugi przycisku ButtonRefresh */
void onButtonPauseClick(void* _this);/*!< Funkcja obslugi przycisku ButtonPause */
void onButtonNextClick(void* _this);/*!< Funkcja obslugi przycisku ButtonNext */
}