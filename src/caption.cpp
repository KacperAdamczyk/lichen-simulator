#include "caption.h"

/*
 * Caption
 */
dsp::Caption::Caption(dsp::Object* parent, bool add_to_list, std::string text, int font_size) : dsp::Object(parent)
{
	text_.setString(text);
	text_.setCharacterSize(font_size);
	text_.setFont(dsp::Object::font_);
	text_.setFillColor(sf::Color::Black);
	if (add_to_list)
		AddToList();
}

void dsp::Caption::Assign()
{
	text_.setPosition(getValidPosition(this));
}

sf::Vector2f dsp::Caption::getSize()
{
	return sf::Vector2f(float(text_.getString().getSize() * text_.getCharacterSize() * FONT_PROP), float(text_.getCharacterSize()));
}

void dsp::Caption::AddToList()
{
	dsp::Object::object_list_.push_back(this);
}

sf::Vector2f dsp::Caption::getEndPoint() const
{
	sf::Vector2f position = text_.getPosition();
	return sf::Vector2f(position.x, position.y + text_.getCharacterSize() + spacer_);
}

void dsp::Caption::Draw()
{
	window_->draw(text_);
}
