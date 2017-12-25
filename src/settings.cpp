#include "settings.h"

dsp::Settings::Settings(sf::RenderWindow& render_window, StartUpParams* start_up_params, Point draw_area_start_point) :
	Window(render_window, start_up_params, draw_area_start_point),
	
	text_resolution_(NULL, true, "Rozdzielczosc ekranu: ", 29),
	text_resolution_x_(NULL, true, "X: ", 40),
	value_resolution_x_(&text_resolution_x_, true, true, &start_up_params_->window_resolution.x, start_up_params_->settings_size.x, 1920, 1.15f),
	arrows_resolution_x_(&value_resolution_x_, true, true, &start_up_params_->window_resolution.x, value_resolution_x_.getMin(), value_resolution_x_.getMax(), 1, 1, 1.2f),
	text_resolution_y_(NULL, true, "Y: ", 40),
	value_resolution_y_(&text_resolution_y_, true, true, &start_up_params_->window_resolution.y, start_up_params_->settings_size.y, 1080, 1.15f),
	arrows_resolution_y_(&value_resolution_y_, true, true, &start_up_params_->window_resolution.y, value_resolution_y_.getMin(), value_resolution_y_.getMax(), 1, 1, 1.2f),

	text_size_(NULL, true, "Wielkosc pola: ", 29),
	text_size_x_(NULL, true, "X: ", 40),
	value_size_x_(&text_size_x_, true, true, &start_up_params_->size.x, 1, sf::VideoMode::getDesktopMode().width, 1.15f),
	arrows_size_x_(&value_size_x_, true, true, &start_up_params_->size.x, value_size_x_.getMin(), value_size_x_.getMax(), 1, 1, 1.2f),
	text_size_y_(NULL, true, "Y: ", 40),
	value_size_y_(&text_size_y_, true, true, &start_up_params_->size.y, 1, sf::VideoMode::getDesktopMode().height, 1.15f),
	arrows_size_y_(&value_size_y_, true, true, &start_up_params_->size.y, value_size_y_.getMin(), value_size_y_.getMax(), 1, 1, 1.2f),

	text_speed_(NULL, true, "Czas trwania jednostki czasu[fpt]", 18),
	value_speed_(NULL, true, true, &start_up_params_->frames_per_tick),
	arrows_speed_(&value_speed_, true, true, &start_up_params_->frames_per_tick),

	text_infection_time_(NULL, true, "Czas trwania infekcji", 29),
	value_infection_time_(NULL, true, true, &start_up_params_->infection_time),
	arrows_infection_time_(&value_infection_time_, true, true, &start_up_params_->infection_time),

	text_immune_time_(NULL, true, "Czas trwania odpornosci", 25),
	value_immune_time_(NULL, true, true, &start_up_params_->immune_time),
	arrows_immune_time_(&value_immune_time_, true, true, &start_up_params_->immune_time),

	text_propability_(NULL, true, "Prawdopodobienstwo zarazenia[%]", 18),
	value_propability_(NULL, true, true, &start_up_params_->infection_propability, 0, 100),
	arrows_propability_(&value_propability_, true, true, &start_up_params_->infection_propability, value_propability_.getMin(), value_propability_.getMax()),

	_SPACER_button_start_(NULL, true, "     "),
	button_start_(&_SPACER_button_start_, &onButtonStartClick, true, true, dsp::ButtonType::TEXT_BUTTON, "Start!", true, 52)
{
	dsp::Object::setWindowClass(this);
	initDraw();
}

void dsp::Settings::initDraw()
{
	std::vector<dsp::Object*> object_list = dsp::Object::getObjectList();
	for (Object* object :object_list)
		object->Assign();
}

void dsp::Settings::CalcMaxSize()
{
	max_size_ = Point(start_up_params_->window_resolution.x - start_up_params_->settings_size.x - 2 * draw_area_start_point_.x,
		              start_up_params_->window_resolution.y - 2 * draw_area_start_point_.y);
}

void dsp::Settings::Draw()
{
	CalcMaxSize();
	value_size_x_.setMax(max_size_.x);
	value_size_y_.setMax(max_size_.y);
	std::vector<dsp::Object*> object_list = dsp::Object::getObjectList();
	for (Object* object : object_list)
		object->Draw();
}

void dsp::Settings::isButtonClicked()
{
	sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window_));
	std::vector<dsp::Object*> clickable_object_list = dsp::Object::getClickableObjectList();
	for (Object* object : clickable_object_list)
		object->isClicked(mouse_position);
}

void dsp::Settings::ClickedKey(sf::Keyboard::Key key)
{
	dsp::Value::EditFromKeyboard(key);
}

void dsp::onButtonStartClick(void* _this)
{
	dsp::Settings* this_ = nullptr;
	if (!ConvertPtr<Settings>(_this, &this_))
		return;

	this_->window_.close();
}
