#pragma once

#include "main.h"

/*!
 *	Staty komorek
 */
enum State 
{
	HEALTHY,	  /*!< Zdrowa   */
	IMMUNE,		  /*!< Odporna  */
	INFECTED	  /*!< Zarazona */
}; 
/* Cell */
class Cell
{
private:
	State state_;					      /*!< Stan komorki */
	unsigned int age_;				      /*!< Ilosc cykli komorki */ 
	unsigned int infection_time_;	      /*!< Ilosc cylki jaka musi uplynac do zmiany stanu z zarazonej na odporna */
	unsigned int immune_time_;		      /*!< Ilosc cykli jaka musi uplynac do zmiany stanu z opronej na zdrowa */
	unsigned int infection_propabitity_;  /*!< Szansa na infekcje sasiednich komorek w % */

public:
	/*! Konstruktor 
	*/
	Cell(unsigned int = 6, unsigned int = 4, unsigned int = 50);
	sf::Color getColor() const;        	                /*!< Zwraca kolor */
	State getState() const;				                /*!< Zwraca stan komorki */
	void setState(State);                               /*!< Ustawia stan komorki*/
	unsigned int getAge() const;			            /*!< Zwraca wiek */
	unsigned int getInfectionTime() const;              /*!< Zwraca czas infekcji */
	unsigned int* getInfectionTimePtr();                /*!< Zwraca wskaznik do zmiennej 'infection_time_' */
	unsigned int getImmuneTime() const;                 /*!< Zwraca czas odpornosci */
	unsigned int* getImmuneTimePtr();                   /*!< Zwraca wskaznik do zmiennej 'immune_time_' */
	unsigned int getInfectionPropability() const;       /*!< Zwraca prawdopodobienstwo infekcji */
	unsigned int* getInfectionPropabilityPtr();         /*!< Zwraca wskaznik do zmiennej 'infection_propabitity_' */ 
	void setInfectionTime(unsigned int);                /*!< Ustawia czas trwania infekcji */
	void setImmuneTime(unsigned int);                   /*!< Ustawia czas trwania odpornosci */
	void setInfectionPropability(unsigned int);         /*!< Ustawia prawdopodobienstwo zarazenia */
	void setAge(unsigned int);		                    /*!< Ustawia wiek */
	void Life();				                        /*!< Obsluga zycia komorki */
	void beInfected();				                    /*!< Infekowanie sasiednich komorek */
	void Infect();					                    /*!< Infekuje komorke */
};





