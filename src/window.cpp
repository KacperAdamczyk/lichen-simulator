#include "window.h"


sf::Image dsp::Window::icon_;

dsp::Window::Window(sf::RenderWindow& window, StartUpParams* start_up_params, Point draw_area_start_point) :
	window_(window), start_up_params_(start_up_params), draw_area_start_point_(draw_area_start_point)
{
	if (&window_ != nullptr)
		window_.setIcon(icon_.getSize().x, icon_.getSize().y, icon_.getPixelsPtr());
}

sf::Image * dsp::Window::getIcon()
{
	return &icon_;
}
