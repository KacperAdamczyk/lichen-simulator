#include "arrows.h"
/// \file arrows.cpp
/* deklaracje statycznych pol */
sf::Texture dsp::Arrows::texture_;

dsp::Arrows::Arrows(Object* parent, bool add_to_list, bool is_clickable, unsigned int* value, unsigned int min, unsigned int max,
	                int step, float fractionR, float fractionL, float scale) :
	 Object(parent), value_(value), step_(step), scale_(scale), min_(min), max_(max), fractionR_(fractionR), fractionL_(fractionL)
{
	right_.setTexture(texture_);
	right_.setScale(scale_, scale_);
	
	left_.setTexture(texture_);
	left_.rotate(180);
	left_.setScale(scale_, scale_);

	if (add_to_list)
		AddToList();
	if (is_clickable)
		AddToClickableList();
}

void dsp::Arrows::Assign()
{
	sf::Vector2f position = getValidPosition(this);
	right_.setPosition(dsp::Object::point_of_reference_start_.x + 
		               dsp::Object::point_of_reference_size_.x / fractionR_ - dsp::Arrows::texture_.getSize().x * scale_, position.y);
	left_.setPosition(right_.getPosition().x - dsp::Object::point_of_reference_size_.x / fractionL_ + 2*dsp::Arrows::texture_.getSize().x * scale_,
		              right_.getPosition().y + dsp::Arrows::texture_.getSize().y * scale_);
}

sf::Vector2f dsp::Arrows::getSize()
{
	sf::Vector2f position = left_.getPosition();
	return sf::Vector2f(position.x, position.y - dsp::Arrows::texture_.getSize().y * scale_);
}

void dsp::Arrows::AddToList()
{
	dsp::Object::object_list_.push_back(this);
}

void dsp::Arrows::AddToClickableList()
{
	dsp::Object::clickable_object_list_.push_back(this);
}

sf::Vector2f dsp::Arrows::getEndPoint() const
{
	sf::Vector2f position = right_.getPosition();
	return sf::Vector2f(position.x - dsp::Object::point_of_reference_size_.x + dsp::Arrows::texture_.getSize().x * scale_,
		                position.y + scale_*texture_.getSize().y + spacer_);
}

void dsp::Arrows::Draw()
{
	window_->draw(right_);
	window_->draw(left_);
}

bool dsp::Arrows::isClicked(sf::Vector2f mouse_position)
{
	if (right_.getGlobalBounds().contains(mouse_position) && signed(*value_ + step_) <= max_) {
		*value_ += step_;
		return true;
	}	else if (left_.getGlobalBounds().contains(mouse_position) && signed(*value_ - step_) >= signed(min_)) {
		*value_ -= step_;
		return true;
	}
	return false;
}

void dsp::Arrows::setMin(unsigned int min)
{
	min_ = min;
}

void dsp::Arrows::setMax(unsigned int max)
{
	max_ = max;
}

void dsp::Arrows::AssignValue(unsigned int * value)
{
	value_ = value;
}

sf::Texture * dsp::Arrows::getTexture()
{
	return &texture_;
}
