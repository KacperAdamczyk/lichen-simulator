#include "main.h"
#include "value.h"

/* Inicjalizacja pol statycznych */
dsp::Value* dsp::Value::edited_ = nullptr;
/*
 *  Value
 */
dsp::Value::Value(Object* parent, bool add_to_list, bool is_clickable, unsigned int* value, unsigned int min, unsigned int max,
	              float fraction, int font_size, sf::Color background_color) :
	dsp::Object(parent), value_(value), min_(min), max_(max), fraction_(fraction), is_edited_(false)
{
	if (value_ != nullptr) {
		CheckValue();
		text_value_.setString(std::to_string(*value_));
	} else {
		text_value_.setString("");
	}
	text_value_.setCharacterSize(font_size);
	text_value_.setFont(dsp::Object::font_);
	text_value_.setFillColor(sf::Color::Black);
	rectangle_.setFillColor(background_color);
	if (add_to_list)
		AddToList();
	if (is_clickable)
		AddToClickableList();
}

inline void dsp::Value::ChangeValue(int step)
{
	*value_ += step;
}

void dsp::Value::Assign()
{
	sf::Vector2f vector = getValidPosition(this);
	text_value_.setPosition(vector.x + point_of_reference_size_.x / (2*fraction_) -
		FONT_PROP * text_value_.getCharacterSize() * text_value_.getString().getSize(), vector.y);
	vector = text_value_.getPosition();
	rectangle_.setPosition(vector.x - 0.5f * spacer_, vector.y);
	rectangle_.setSize(sf::Vector2f(float(2 * FONT_PROP * text_value_.getCharacterSize() * text_value_.getString().getSize() + spacer_),
																										float(text_value_.getCharacterSize() + spacer_)));
}

sf::Vector2f dsp::Value::getSize()
{
	int max_nr_cnt = 7;
	sf::Vector2f position = rectangle_.getPosition();
	sf::Vector2f size = rectangle_.getSize();
	return sf::Vector2f(position.x - Object::point_of_reference_start_.x + FONT_PROP * text_value_.getCharacterSize() * (max_nr_cnt + text_value_.getString().getSize()),
		               size.y);
}

void dsp::Value::AddToList()
{
	dsp::Object::object_list_.push_back(this);
}

void dsp::Value::AddToClickableList()
{
	dsp::Object::clickable_object_list_.push_back(this);
}

sf::Vector2f dsp::Value::getEndPoint() const
{
	sf::Vector2f position = text_value_.getPosition();
	return sf::Vector2f(position.x - point_of_reference_size_.x / (2*fraction_) + 0.3f * text_value_.getCharacterSize() * text_value_.getString().getSize(),
		                                                                                     position.y + text_value_.getCharacterSize() + 2 * spacer_);
}

void dsp::Value::Draw()
{
	if (value_ != nullptr && !isEdited(this)) {
		CheckValue();
		text_value_.setString(std::to_string(*value_));
	}
	Assign();
	window_->draw(rectangle_);
	window_->draw(text_value_);
	
}

void dsp::Value::AssignValue(unsigned int* value)
{
	value_ = value;
}

unsigned int dsp::Value::getMin() const
{
	return min_;
}

unsigned int dsp::Value::getMax() const
{
	return max_;
}

void dsp::Value::setMin(unsigned int min)
{
	min_ = min;
}

void dsp::Value::setMax(unsigned int max)
{
	max_ = max;
}

void dsp::Value::CheckValue()
{
	if (value_ == NULL)
		return;
	if (signed(*value_) < min_)
		*value_ = min_;
	else if (*value_ > max_)
		*value_ = max_;
}

bool dsp::Value::isClicked(sf::Vector2f mouse_position)
{
	if (text_value_.getGlobalBounds().contains(mouse_position)) {
		edited_ = this;
		is_edited_ = true;
		text_value_.setOutlineColor(sf::Color::Green);
		text_value_.setOutlineThickness(4);
		return true;
	} else {
		is_edited_ = false;
		text_value_.setOutlineThickness(0);
		return false;
	}
}

bool dsp::Value::isEdited(Value * ptr)
{
	if (edited_ == ptr && ptr->is_edited_)
		return true;
	return false;
}

void dsp::Value::EditFromKeyboard(sf::Keyboard::Key key)
{
	if (edited_ == NULL || !edited_->is_edited_)
		return;

	if (key == sf::Keyboard::Key::Num0)
		edited_->text_value_.setString(edited_->text_value_.getString() + "0");
	else if (key == sf::Keyboard::Key::Num1)
		edited_->text_value_.setString(edited_->text_value_.getString() + "1");
	else if (key == sf::Keyboard::Key::Num2)
		edited_->text_value_.setString(edited_->text_value_.getString() + "2");
	else if (key == sf::Keyboard::Key::Num3)
		edited_->text_value_.setString(edited_->text_value_.getString() + "3");
	else if (key == sf::Keyboard::Key::Num4)
		edited_->text_value_.setString(edited_->text_value_.getString() + "4");
	else if (key == sf::Keyboard::Key::Num5)
		edited_->text_value_.setString(edited_->text_value_.getString() + "5");
	else if (key == sf::Keyboard::Key::Num6)
		edited_->text_value_.setString(edited_->text_value_.getString() + "6");
	else if (key == sf::Keyboard::Key::Num7)
		edited_->text_value_.setString(edited_->text_value_.getString() + "7");
	else if (key == sf::Keyboard::Key::Num8)
		edited_->text_value_.setString(edited_->text_value_.getString() + "8");
	else if (key == sf::Keyboard::Key::Num9)
		edited_->text_value_.setString(edited_->text_value_.getString() + "9");
	else if (key == sf::Keyboard::Key::BackSpace)
		edited_->text_value_.setString(edited_->text_value_.getString().toAnsiString().substr(0, edited_->text_value_.getString().toAnsiString().length() - 1));
	else if (key == sf::Keyboard::Key::Return) {
		*(edited_->value_) = atoi(edited_->text_value_.getString().toAnsiString().c_str());
		edited_->CheckValue();
		edited_->is_edited_ = false;
		edited_->text_value_.setOutlineThickness(0);
		edited_ = nullptr;
	}	
}
