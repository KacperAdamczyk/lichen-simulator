#include "main.h"
#include "cell.h"
#include "common.h"


Cell::Cell(unsigned int infection_time, unsigned int immune_time, unsigned int infection_propability) : 
	state_(HEALTHY), 
	age_(0), 
	infection_time_(infection_time),
	immune_time_(immune_time),
	infection_propabitity_(infection_propability)
{}

sf::Color Cell::getColor() const
{
	static int Y_max_step = 175;
	static int R_max_step = 175;
	int Y_divider = 1;
	int R_divider = 1;

    while (int(Y_max_step - immune_time_/Y_divider) <= 0) Y_divider++;
	while (int(R_max_step - infection_time_ / R_divider) <= 0) R_divider++;

	switch (state_) {
	case State::HEALTHY:
		return sf::Color::Green;
	case State::IMMUNE:
		return sf::Color(255, immune_time_ > 0 ?  255 - (Y_max_step / (immune_time_ / Y_divider) ) * ((age_ - 1) / Y_divider) : 255, 0);
	case State::INFECTED:
		return sf::Color(infection_time_ > 0 ? 255 - (R_max_step / (infection_time_ / R_divider) ) * ((age_ - 1) / R_divider) : 255, 0, 0);
	default:
		return sf::Color(255, 255, 255, 255);
	}
}

State Cell::getState() const
{
	return state_;
}
void Cell::setState(State state)
{
	state_ = state;
}

unsigned int Cell::getAge() const
{
	return age_;
}

unsigned int Cell::getInfectionTime() const
{
	return infection_time_;
}
unsigned int * Cell::getInfectionTimePtr()
{
	return &infection_time_;
}

unsigned int Cell::getImmuneTime() const
{
	return immune_time_;
}
unsigned int * Cell::getImmuneTimePtr()
{
	return &immune_time_;
}

unsigned int Cell::getInfectionPropability() const
{
	return infection_propabitity_;
}
 unsigned int * Cell::getInfectionPropabilityPtr()
 {
	 return &infection_propabitity_;
 }

void Cell::setInfectionTime(unsigned int infection_time)
{
	infection_time_ = infection_time;
}

void Cell::setImmuneTime(unsigned int immune_time)
{
	immune_time_ = immune_time;
}

void Cell::setInfectionPropability(unsigned int infection_propability)
{
	infection_propabitity_ = infection_propability;
}

void Cell::setAge(unsigned int age)
{
	age_ = age;
}

void Cell::Life()
{
	if (age_ >= infection_time_ && state_ == State::INFECTED && immune_time_ > 0) {
		state_ = State::IMMUNE;
		age_ = 0;
	} else if (age_ >= immune_time_ && state_ == State::IMMUNE) {
		state_ = State::HEALTHY;
		age_ = 0;
	}
	if(state_ == State::INFECTED || state_ == State::IMMUNE)
	age_++;
}

void Cell::beInfected()
{
	if (rand(1, 100) > infection_propabitity_)
		return;

	if (state_ == State::HEALTHY && infection_time_ > 0) {
		state_ = State::INFECTED;
		age_ = 0;
	}
}

void Cell::Infect()
{
	state_ = State::INFECTED;
}