#pragma once
#include "SFML/Graphics.hpp"
#include "Cell_Object.h"
#include <iostream>

enum Difficulty
{
	EASY,
	NORMAL,
	HARD
};

class Manager
{
private:
	bool _won = false;

	void check_reset();

	sf::Font* _font;

	int _rCount;

	void play_lil_anim();

	sf::RenderWindow* _win;
	sf::Vector2f _cellSize;

	std::vector<Cell_Object> _field;

	void check_mouse(int i);
	void reset_marks();

	std::vector<std::vector<int> > _norm;
	void init_norm();

	void swap_rows(int i, int j);
	void swap_cols(int i, int j);

	void init_field(sf::Font* font, int row_count);

	void remove(int count);

	void make_win();

	Difficulty _dif;

public:
	Manager();
	~Manager();
	Manager(sf::RenderWindow* win, sf::Vector2f& size, int row_count, Difficulty dif);

	void update();
};

