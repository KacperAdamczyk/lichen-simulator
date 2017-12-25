#include "button.h"

/* deklaracje statycznych pol */
sf::Texture dsp::Button::text_button_;
sf::Texture dsp::Button::next_button_;
sf::Texture dsp::Button::refresh_button_;

dsp::Button::Button(Object * parent, void(*onClickFunction)(void*), bool add_to_list, bool is_clickable, ButtonType button_type, std::string text, bool active, int font_size) :
Object(parent), onClickFunction_(onClickFunction), button_type_(button_type), scale_{0.25f, 0.13f, 0.1f}, active_(active)
{
	button_type_ == ButtonType::TEXT_BUTTON ? texture_ = Button::getTextBtnTexture() :
	button_type_ == ButtonType::NEXT_BUTTON ? texture_ = Button::getNextBtnTexture() :
		                                      texture_ = Button::getRefreshBtnTexture();
	texture_->setSmooth(true);
	button_.setTexture(*texture_);
	button_.setScale(scale_[button_type_], scale_[button_type_]);
	text_.setString(text);
	text_.setFont(Object::font_);
	text_.setCharacterSize(font_size);
	text_.setFillColor(sf::Color::Black);
	setActive(active_);
	if (add_to_list)
		AddToList();
	if (is_clickable)
		AddToClickableList();
}

bool dsp::Button::isClicked(sf::Vector2f mouse_position)
{
	if (button_.getGlobalBounds().contains(mouse_position) && active_)
		onClickFunction_(window_class_);
	return false;
}

void dsp::Button::setText(std::string text, int font_size)
{
	text_.setString(text);
	if(font_size >= 0)
	text_.setCharacterSize(font_size);
}

void dsp::Button::setActive(bool state)
{
	active_ = state;
	if (active_) {
		button_.setColor(sf::Color(255, 255, 255, 255));
	} else {
		button_.setColor(sf::Color(255, 255, 255, 128));
	}
}

void dsp::Button::Assign()
{
	button_.setPosition(getValidPosition(this));
	sf::Vector2f position = button_.getPosition();
	text_.setPosition(position.x + 2 * spacer_, position.y + 1 * spacer_);
}

sf::Vector2f dsp::Button::getSize()
{
	sf::Vector2u size = texture_->getSize();
	return sf::Vector2f(size.x * scale_[button_type_], size.y * scale_[button_type_]);
}

void dsp::Button::AddToList()
{
	dsp::Object::object_list_.push_back(this);
}

void dsp::Button::AddToClickableList()
{
	dsp::Object::clickable_object_list_.push_back(this);
}

sf::Vector2f dsp::Button::getEndPoint() const
{
	sf::Vector2f position = text_.getPosition();
	return sf::Vector2f(position.x, position.y + texture_->getSize().y * scale_[button_type_]);
}

void dsp::Button::Draw()
{
	window_->draw(button_);
	if(button_type_ == ButtonType::TEXT_BUTTON)
	window_->draw(text_);
}

sf::Texture * dsp::Button::getTextBtnTexture()
{
	return &text_button_;
}

sf::Texture * dsp::Button::getNextBtnTexture()
{
	return &next_button_;
}

sf::Texture * dsp::Button::getRefreshBtnTexture()
{
	return &refresh_button_;
}
