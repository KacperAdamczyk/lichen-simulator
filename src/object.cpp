#include "main.h"
#include "object.h"

/*
 * Object
 */

/* deklaracje statycznych pol */
std::vector<dsp::Object*> dsp::Object::object_list_;
std::vector<dsp::Object*> dsp::Object::clickable_object_list_;
sf::RenderWindow* dsp::Object::window_ = nullptr;
dsp::Window* dsp::Object::window_class_ = nullptr;
sf::Font dsp::Object::font_;
Point dsp::Object::point_of_reference_start_;
Point dsp::Object::point_of_reference_size_;

dsp::Object::Object(dsp::Object* parent) : parent_(parent), spacer_(10)
{
}

std::vector<dsp::Object*> dsp::Object::getObjectList()
{
	return object_list_;
}

std::vector<dsp::Object*> dsp::Object::getClickableObjectList()
{
	return clickable_object_list_;
}
void dsp::Object::ResetObjectList()
{
	object_list_.clear();
}

void dsp::Object::ResetClickableObjectList()
{
	clickable_object_list_.clear();
}

void dsp::Object::setRenderWindow(sf::RenderWindow* window)
{
		window_ = window;
}

void dsp::Object::setWindowClass(dsp::Window * window_class)
{
	window_class_ = window_class;
}

void dsp::Object::setPointOfReference(Point start, Point size)
{
		point_of_reference_start_ = start;
		point_of_reference_size_ = size;
}

sf::Font* dsp::Object::getFont()
{
		return &font_;
}
int dsp::Object::FindInObjectList(Object* object)
{
	for (int i = 0; i < object_list_.size(); i++) {
		if (object_list_[i] == object) {
			return i;
		}
	}
	return -1;
}
sf::Vector2f dsp::Object::getValidPosition(dsp::Object* object) const
{
	if (parent_ == NULL) {
		int position = dsp::Object::FindInObjectList(object);
		if (position <= 0)
		{
			return sf::Vector2f(float(point_of_reference_start_.x), float(point_of_reference_start_.y));
		} else {
			for (int i = position - 1; i >= 0; i--)
				if (object_list_[i]->parent_ == NULL)
					return object_list_[i]->getEndPoint();
			return sf::Vector2f(0.f, 0.f);
		}
	} else {
		return parent_->getValidPosition(parent_) + sf::Vector2f(parent_->getSize().x + spacer_, 0);
	}
}

