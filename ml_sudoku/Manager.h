#pragma once
#include "SFML/Graphics.hpp"
#include "Cell_Object.h"
#include <iostream>
#include <Windows.h>

struct Values
{
	int val;
	int count;
};

enum Difficulty
{
	EASY,
	NORMAL,
	HARD
};

class Manager
{
private:

	std::vector<Values> _values;
	void init_values();
	void count_field(int i);
	bool _won = false;
	bool _lost = false;

	bool app_in_focus();

	void check_reset();

	sf::Font* _font;

	int _rCount;

	void count_mistakes(int i);
	int _mistakes = 0;

	void play_lil_anim();

	sf::RenderWindow* _win;
	sf::RenderWindow* _statWin;
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

	std::vector<sf::Text> _valStat;
	std::vector<sf::Text> _countStat;

	void init_text();
	void set_string();

public:
	Manager();
	~Manager();
	Manager(sf::RenderWindow* win, sf::Vector2f& size, int row_count, Difficulty dif, sf::RenderWindow *statWin);

	void update();
};

