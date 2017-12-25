#pragma once
/*
 * Struktura Punkt
 */
struct Point {
	unsigned int x; /*!< Wspolrzedna x */
	unsigned int y; /*!< Wspolrzedna y */

	Point(); /*!< Konstruktor domyslny */
	/*!
	(int x, int y)
	*/
	Point(int, int); 
	
    unsigned int getQuantity(); /*!< Zwraca iloczyn x i y */
};
/*
 * Struktura StartUpParams
 */
struct StartUpParams {
	Point size;                          /*!< Rozmiar pola */
	Point window_resolution;             /*!< Rozdzielczosc okna */
	Point settings_size;                 /*!< Rozmiar pola ustawien */
	unsigned int frame_rate;             /*!< Ilosc FPS */
	unsigned int frames_per_tick;        /*!< Ilosc klatek na klatke logiczna */
	unsigned int infection_time;         /*!< Czas trwania infekcji */
	unsigned int immune_time;            /*!< Czas trwania odpornosci */
	unsigned int infection_propability;  /*!< Prawdopodobinenstwo infekcji */

	StartUpParams();
};
/*
 * Funkcje gloalne 
 */
void ErrorMsg(std::string error, std::string title); /* Message box z komunikatem bledu */
/*!
 * x - szerokosc okna
 * y - wysokosc okna
 * f - ramerate okna
 * n - rozmiar okna
 * i - czas trwania infekcji
 * m - czas trwania odpornosci
 * p - prawdopodobienstwo infekcji
 */
void getParams(int, char**, StartUpParams&);    /*!< Wczytywanie parametrow startowych */
unsigned int rand(unsigned int, unsigned int);  /*!< Zwraca losowa wartosc z danego przedzialu */
void LoadResources(HINSTANCE&);                 /*!< Wczytuje zasoby z plikow */

/*! Konwertuje wskaznik generyczny na wskaznik danego typu */
template <class T>
inline bool ConvertPtr(void* void_ptr, T** type_ptr) {
	if (void_ptr == nullptr) {
		*type_ptr = nullptr;
		return false;
	}
	*type_ptr = static_cast<T*>(void_ptr);
	return true;
}