#include "main.h"
#include "program.h"


dsp::Program::Program(sf::RenderWindow& render_window, StartUpParams* start_up_params, Point draw_area_start_point) :
	Window(render_window, start_up_params, draw_area_start_point),
	size_(start_up_params->size),
	max_size_(Point(start_up_params->window_resolution.x - start_up_params_->settings_size.x - 2 * draw_area_start_point_.x,
	                start_up_params->window_resolution.y - 2 * draw_area_start_point_.y)),
	old_size_(size_),
	frames_since_last_tick_(0),
	frames_per_tick_(0),

	text_infection_time_(NULL, true, "Czas trwania infekcji", 29),
	value_infection_time_(NULL, true, true, nullptr),
	arrows_infection_time_(&value_infection_time_, true, true),

	text_immune_time_(NULL, true, "Czas trwania odpornosci", 25),
	value_immune_time_(NULL, true, true, nullptr),
	arrows_immune_time_(&value_immune_time_, true, true),

	text_propability_(NULL, true, "Prawdopodobienstwo zarazenia[%]", 18),
	value_propability_(NULL, true, true, nullptr, 0, 100),
	arrows_propability_(&value_propability_, true, true, nullptr, value_propability_.getMin(), value_propability_.getMax()),

	text_speed_(NULL, true, "Czas trwania jednostki czasu[fpt]", 18),
	value_speed_(NULL, true, true, &frames_per_tick_),
	arrows_speed_(&value_speed_, true, true, &frames_per_tick_),

	text_size_x_(NULL, true, "X: ", 40),
	value_size_x_(&text_size_x_, true, true, &size_.x, 1, max_size_.x, 1.15f),
	arrows_size_x_(&value_size_x_, true, true, &size_.x, value_size_x_.getMin(), value_size_x_.getMax(), 1, 1, 1.2f),
	text_size_y_(NULL, true, "Y: ", 40),
	value_size_y_(&text_size_y_, true, true, &size_.y, 1, max_size_.y, 1.15f),
	arrows_size_y_(&value_size_y_, true, true, &size_.y, value_size_y_.getMin(), value_size_y_.getMax(), 1, 1, 1.2f),

	value_healthy_counter_(NULL, true, false, &healthy_cells_, 0, UINT_MAX, 1, 40, sf::Color::Green),
	value_immune_counter_(NULL, true, false, &immune_cells_, 0, UINT_MAX, 1, 40, sf::Color::Yellow),
	value_infected_counter_(NULL, true, false, &infected_cells_, 0, UINT_MAX, 1, 40, sf::Color::Red),

	button_refresh_(&value_immune_counter_, &onButtonRefreshClick, true, true, dsp::ButtonType::REFRESH_BUTTON),
	button_pause_(NULL, &onButtonPauseClick, true, true, dsp::ButtonType::TEXT_BUTTON, " Pauza", true, 48),
	button_next_(&button_pause_, &onButtonNextClick, true, true, dsp::ButtonType::NEXT_BUTTON, "", false)
{
	dsp::Object::setWindowClass(this);
	Allocate();
	CalculateGcellParams();
	PrepGCells();
	AssignValues();
	initDraw();
	Infect1st();
	action_ = Action::RESUMED;
}

void dsp::Program::Allocate()
{
	field_.resize(size_.getQuantity(), GraphicCell(start_up_params_->infection_time, start_up_params_->immune_time, start_up_params_->infection_propability));
}

Point dsp::Program::get2DPosition(unsigned int _1DPosition)
{
	return Point(_1DPosition%size_.x, _1DPosition/size_.x);
}

bool dsp::Program::Framer(bool inc)
{
	if (action_ == Action::STEPPED) {
		action_ = Action::PAUSED;
		return true;
	}
	 if (frames_per_tick_ <= frames_since_last_tick_ && action_ == Action::RESUMED) {
		frames_since_last_tick_ = 0;
		return true;
	} else {	
		if(action_ == Action::RESUMED && inc)
			frames_since_last_tick_++;
		return false;
	}
}

void dsp::Program::Resize()
{
	std::vector<GraphicCell> nfield;
	nfield.resize(size_.getQuantity(), field_[0].getModel());
	int skipped = 0;

	if (size_.getQuantity() > old_size_.getQuantity()) {
		for (unsigned int i = 0; i < old_size_.getQuantity(); i++) {
			if (i%old_size_.x == 0 && i != 0) 
				skipped += size_.x - old_size_.x;
			nfield[i + skipped] = field_[i];
		} 
	} else if (size_.getQuantity() < old_size_.getQuantity()) {
		for (unsigned int i = 0; i < size_.getQuantity(); i++) {
			if (i%size_.x == 0 && i != 0) 
				skipped += old_size_.x - size_.x;

			nfield[i] = field_[i + skipped];
		}
	} 
	field_ = nfield;
	CalculateGcellParams();
	PrepGCells();
	AssignValues();
}

void dsp::Program::CalcMaxSize()
{
	max_size_ = Point(window_.getSize().x - start_up_params_->settings_size.x - 2 * draw_area_start_point_.x, window_.getSize().y - 2 * draw_area_start_point_.y);
}

void dsp::Program::CalcMinWndSize()
{
	min_window_size_ = Point(size_.x + 2 * draw_area_start_point_.x + start_up_params_->settings_size.x,
		size_.y + 2 * draw_area_start_point_.y > start_up_params_->settings_size.y ? size_.y + 2 * draw_area_start_point_.y : start_up_params_->settings_size.y);
}

void dsp::Program::setFramer(unsigned int frames_per_tick)
{
	frames_per_tick_ = frames_per_tick;
}

void dsp::Program::CalculateGcellParams()
{
	unsigned int gcell_size_x;
	unsigned int gcell_size_y;

	size_.x > 0 ? gcell_size_x = (window_.getSize().x - 2 * draw_area_start_point_.x - start_up_params_->settings_size.x) / size_.x : gcell_size_x = 0;
	size_.y > 0 ? gcell_size_y = (window_.getSize().y - 2 * draw_area_start_point_.y) / size_.y : gcell_size_y = 0;

	gcell_size_x >= gcell_size_y ? gcell_size_ = gcell_size_y : gcell_size_ = gcell_size_x;

	draw_area_size_ = Point(size_.x * gcell_size_, size_.y * gcell_size_);
	CalcMaxSize();
	CalcMinWndSize();
	value_size_x_.setMax(max_size_.x);
	value_size_y_.setMax(max_size_.y);
	arrows_size_x_.setMax(max_size_.x);
	arrows_size_y_.setMax(max_size_.y);
}

void dsp::Program::initDraw()
{	
	std::vector<dsp::Object*> object_list = dsp::Object::getObjectList();
	for (Object* object : object_list)
		object->Assign();
}

void dsp::Program::PrepGCells()
{
	for (unsigned int i = 0; i < size_.getQuantity(); i++) {
		field_[i].rect.setSize(sf::Vector2f(float(gcell_size_), float(gcell_size_)));
		field_[i].rect.setPosition(float(draw_area_start_point_.x + get2DPosition(i).x * gcell_size_), float(draw_area_start_point_.y + get2DPosition(i).y * gcell_size_));
	}
}

void dsp::Program::AssignValues()
{
	value_infection_time_.AssignValue(field_[0].cell.getInfectionTimePtr());
	arrows_infection_time_.AssignValue(field_[0].cell.getInfectionTimePtr());
	value_immune_time_.AssignValue(field_[0].cell.getImmuneTimePtr());
	arrows_immune_time_.AssignValue(field_[0].cell.getImmuneTimePtr());
	value_propability_.AssignValue(field_[0].cell.getInfectionPropabilityPtr());
	arrows_propability_.AssignValue(field_[0].cell.getInfectionPropabilityPtr());
}

void dsp::Program::Draw()
{
	if (Framer())
		Infect();

	healthy_cells_ = 0;
	immune_cells_ = 0;
	infected_cells_ = 0;

	for (unsigned int i = 0; i < size_.getQuantity(); i++) {
			field_[i].rect.setFillColor(field_[i].cell.getColor()); 
			window_.draw(field_[i].rect);
			State cell_state = field_[i].cell.getState();
			cell_state == State::HEALTHY ? healthy_cells_++ : cell_state == State::IMMUNE ? immune_cells_++ : infected_cells_++;
	}
	std::vector<dsp::Object*> object_list = dsp::Object::getObjectList();
	for (Object* object : object_list) 
		object->Draw();
}

void dsp::Program::ResizeWnd()
{
	if (window_.getSize().x < min_window_size_.x)
		window_.setSize(sf::Vector2u(min_window_size_.x, window_.getSize().y));
	if (window_.getSize().y < min_window_size_.y)
		window_.setSize(sf::Vector2u(window_.getSize().x, min_window_size_.y));
	CalculateGcellParams();
	PrepGCells();
	initDraw();
}

void dsp::Program::Infect1st()
{
	if (field_[0].cell.getInfectionTime() == 0)
		return;
	int _1st_pos = int(0.5f * size_.x * (1 + size_.y));
	field_[_1st_pos].cell.Infect();
	field_[_1st_pos].cell.setAge(1);
}
/*
 *	1 2 3
 *	4 x 5
 *	6 7 8
 */
void dsp::Program::Infect()
{
	for (unsigned int i = 0; i < size_.getQuantity(); i++) {
		if (field_[i].cell.getState() == State::INFECTED && (field_[i].cell.getAge() > 0)) {
			Point position = get2DPosition(i);
			/* narozniki */
			if (int(position.x) - 1 >= 0 && int(position.y) - 1 >= 0) /* 1 */
			field_[i - size_.x - 1].cell.beInfected();
			if ((int(position.x) + 1) < int(size_.x) && (int(position.y) - 1) >= 0) /* 3 */
			field_[i - size_.x + 1].cell.beInfected();
			if (int(position.x) - 1 >= 0 && int(position.y) + 1 < int(size_.y)) /* 6 */
			field_[i + size_.x - 1].cell.beInfected();
			if (int(position.x) + 1 < int(size_.x) && int(position.y) + 1 < int(size_.y)) /* 8 */
			field_[i + size_.x + 1].cell.beInfected();
			/* krawedzie */
			if (int(position.y) - 1 >= 0) /* 2 */
				field_[i - size_.x].cell.beInfected();
			if (int(position.x) - 1 >= 0) /* 4 */
				field_[i - 1].cell.beInfected();
			if (int(position.y) + 1 < int(size_.y)) /* 7 */
				field_[i + size_.x].cell.beInfected();
			if (int(position.x) + 1 < int(size_.x)) /* 5 */
				field_[i + 1].cell.beInfected();
		}
	}
	for (unsigned int i = 0; i < size_.getQuantity(); i++)
		field_[i].cell.Life();
}

void dsp::Program::isButtonClicked()
{
	old_size_ = size_;
	sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window_));
	/* sprawdzaj czy zostala kliknieta komorka <=> gdy kursor znajduje sie w obrebie pola */
	if (sf::FloatRect(float(draw_area_start_point_.x), float(draw_area_start_point_.y), float(draw_area_size_.x), float(draw_area_size_.y)).contains(mouse_position))
		InfectByClick(mouse_position);
	/* obsluga elementow ktore mozna kliknac */
	std::vector<dsp::Object*> clickable_object_list = dsp::Object::getClickableObjectList();
	for (Object* object : clickable_object_list)
		object->isClicked(mouse_position);
	Look4ParamChanges();
}

void dsp::Program::ClickedKey(sf::Keyboard::Key key)
{
	dsp::Value::EditFromKeyboard(key);
	Look4ParamChanges();
}

void dsp::Program::InfectByClick(sf::Vector2f mouse_position)
{
	if (field_[0].cell.getInfectionTime() == 0)
		return;
	for (unsigned int i = 0; i < size_.getQuantity(); i++) {
		if (field_[i].rect.getGlobalBounds().contains(mouse_position)) {
			field_[i].cell.Infect();
			field_[i].cell.setAge(1);
			break;
		}
	}
}

void dsp::Program::Look4ParamChanges()
{
	if (size_.getQuantity() != field_.size())
		Resize();
	if (field_.size() <= 1)
		return;
	bool c_infection_time = false;
	bool c_immune_time = false;
	bool c_propability_time = false;
	if (field_[0].cell.getInfectionTime() != field_[1].cell.getInfectionTime())
		c_infection_time = true;
	if (field_[0].cell.getImmuneTime() != field_[1].cell.getImmuneTime())
		c_immune_time = true;
	if (field_[0].cell.getInfectionPropability() != field_[1].cell.getInfectionPropability())
		c_propability_time = true;

	if (c_infection_time || c_immune_time || c_propability_time) {
		for (unsigned int i = 1; i < size_.getQuantity(); i++) {
			if (c_infection_time)
				field_[i].cell.setInfectionTime(field_[0].cell.getInfectionTime());
			if (c_immune_time) 
				field_[i].cell.setImmuneTime(field_[0].cell.getImmuneTime());
			if (c_propability_time) 
				field_[i].cell.setInfectionPropability(field_[0].cell.getInfectionPropability());
		}
	}
}

void dsp::Program::ChangeFramesPerTick(float difference)
{
	if (difference == 0)
		return;
	if (difference > 0)
		frames_per_tick_ += signed (difference * start_up_params_->frame_rate);
	else if (difference < 0 && signed (frames_per_tick_) + difference * start_up_params_->frame_rate >= 0)
		frames_per_tick_ += signed (difference * start_up_params_->frame_rate);
}

dsp::GraphicCell dsp::GraphicCell::getModel()
{
	dsp::GraphicCell model = *this;
	model.cell.setAge(1);
	model.cell.setState(State::HEALTHY);
	return model;
}

void dsp::onButtonRefreshClick(void* _this)
{
	dsp::Program* this_ = nullptr;
	if (!ConvertPtr<Program>(_this, &this_))
		return;

	this_->Resize();
}

void dsp::onButtonPauseClick(void* _this)
{
	dsp::Program* this_ = nullptr;
	if (!ConvertPtr<Program>(_this, &this_))
		return;

	if (this_->action_ == Action::RESUMED) {
		this_->action_ = Action::PAUSED;
		this_->button_pause_.setText("Wznow");
		this_->button_next_.setActive(true);
	}
	else if (this_->action_ = Action::PAUSED) {
		this_->action_ = Action::RESUMED;
		this_->button_pause_.setText(" Pauza");
		this_->button_next_.setActive(false);
	}
}

void dsp::onButtonNextClick(void* _this)
{
	dsp::Program* this_ = nullptr;
	if (!ConvertPtr<Program>(_this, &this_))
		return;

	this_->action_ = Action::STEPPED;
}
