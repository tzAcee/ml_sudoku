#include "Cell_Object.h"
#include <iostream>

Cell_Object::Cell_Object()
{
}


Cell_Object::~Cell_Object()
{
}

sf::Vector2f Cell_Object::center_text()
{
	return sf::Vector2f(_pos.x + _backObj.getSize().x * 0.5, _pos.y + _backObj.getSize().y * 0.30f);
}

Cell_Object::Cell_Object(sf::RenderWindow* win, sf::Vector2f pos, sf::Vector2f size, uint16_t val, bool stati, sf::Font* font)
{
	_win = win;
	_pos = pos;
	_size = size;
	_val = val;
	is_static = stati;
	_font = font;

	_backObj.setSize(size);
	_backObj.setFillColor(sf::Color(112, 128, 144));
	_backObj.setOutlineThickness(1.0f);
	_backObj.setOutlineColor(sf::Color(176, 196, 222));
	_backObj.setPosition(pos);

	_text = new sf::Text;

	_text->setFont(*_font);
	_text->setOrigin(sf::Vector2f(float(_text->getCharacterSize()) / 2.f, float(_text->getCharacterSize()) / 2.f));
	_text->setPosition(center_text());
	_text->setString(std::to_string(_val));
	_text->setCharacterSize(50);
	_text->setFillColor(sf::Color::Black);

	_rightVal = _val;

	_valObj.setFillColor(sf::Color(230, 230, 250, 80));
	_valObj.setRadius(_backObj.getSize().x / 2.f -5.f);
	_valObj.setOrigin(_valObj.getRadius(), _valObj.getRadius());
	_valObj.setPosition(_pos.x+_backObj.getSize().x/2.f, _pos.y+_backObj.getSize().y/2.f);
}

void Cell_Object::toggle_mark(bool val)
{
	is_marked = val;
}

bool Cell_Object::is_right()
{
	return (_val == _rightVal);
}

void Cell_Object::win()
{
	_won = true;
}

void Cell_Object::loose()
{
	_lost = true;
}

bool Cell_Object::remove()
{
	if (is_static)
	{
		set_val(-1);
		is_static = false; 
			return true;
	}
	else
	{
		return false;
	}
}

void Cell_Object::set_val(int val)
{
	_val = val;
	if (val != 10)
	{
		if (val != -1)
		{
			_text->setString(std::to_string(_val));
			mistake_set = false;
		}
		else
		{
			_text->setString("");
		}
	}
	else
	{
		_text->setString(":(");
	}
}

bool Cell_Object::get_mistake()
{
	return made_mistake;
}

void Cell_Object::mistake_counted_set(bool val)
{
	mistake_set = val;
}

bool Cell_Object::get_mistake_counted()
{
	return mistake_set;
}

void Cell_Object::manage_states()
{
	if (!_won && !_lost)
	{
		if (is_marked)
		{
			_valObj.setFillColor(sf::Color(150, 210, 210, 100));
		}
		else if (!is_right() && _val != 65535)
		{
			made_mistake = true;
			_valObj.setFillColor(sf::Color(250, 100, 150, 100));
		}
		else
		{
			_text->setFillColor(sf::Color::Black);
			_valObj.setFillColor(sf::Color(230, 230, 250, 80));
		}

		if (is_static)
		{
			_text->setFillColor(sf::Color::White);
		}
	} 
	else if(_won)
	{
		set_val(0);
		is_marked = false;
		_valObj.setFillColor(sf::Color(230, 150, 250, 80));
	}
	else if(_lost)
	{
		set_val(10);
		is_marked = false;
		_valObj.setFillColor(sf::Color(250, 150, 50, 80));
	}
}

bool Cell_Object::get_static()
{
	return is_static;
}

void Cell_Object::manage_fill_in()
{
	if (is_marked)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(1);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(2);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(3);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(4);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(5);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(6);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(7);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(8);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(9);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!_clicked)
			{
				_clicked = true;
				set_val(-1);
			}
		}
		else
			_clicked = false;
	}
}

void Cell_Object::update()
{
	manage_states();
	manage_fill_in();

	_win->draw(_backObj);
	_win->draw(_valObj);
	_win->draw(*_text);
}
