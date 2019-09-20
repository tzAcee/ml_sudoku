#pragma once
#include "SFML/Graphics.hpp"

class Cell_Object
{

private:
	sf::RenderWindow* _win;

	sf::Vector2f _pos;
	sf::Vector2f _size;
	uint16_t _val;
	uint16_t _rightVal;

	bool is_static = false;
	bool is_marked = false;

	sf::Font* _font;
	sf::Text* _text;

	sf::RectangleShape _backObj;

	void manage_states();
	void set_val(int val);
	void manage_fill_in();

	sf::Vector2f center_text();

	bool _won = false;

public:
	sf::CircleShape _valObj;
	bool is_right();
	void win();
	void toggle_mark(bool val);

	bool remove();

	bool get_static();

	Cell_Object();
	~Cell_Object();

	Cell_Object(sf::RenderWindow* win, sf::Vector2f pos, sf::Vector2f size, uint16_t val, bool stati, sf::Font *font);



	void update();
};
