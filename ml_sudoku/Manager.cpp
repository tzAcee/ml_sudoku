#include "Manager.h"

Manager::Manager()
{
}


Manager::~Manager()
{
}

void Manager::swap_rows(int i, int j)
{
	if (i < j)
	{
		int tmp = i;
		i = j;
		j = tmp;
	}

	if ((i!=j)&& ((i <= 2 && j < 2) ||
		(i <= 5 && j < 5 && (i > 2 && j > 2)) ||
		(i <= 8 && j < 8 && (i > 5 && j > 5))))
	{


		std::vector<int> _tmp(9);
		_tmp = _norm[i];
		_norm[i] = _norm[j];
		_norm[j] = _tmp;
	//	std::cout << "ROW-SHUFFLE SUCCESS [" << i << " | " << j << "]" << std::endl;
	}
}

void Manager::remove(int count)
{
	int succCount = 0;
	do
	{
		if (_field[std::rand() % _field.size()].remove())
		{
			succCount++;
		}
	} while (succCount != count);
}

void Manager::swap_cols(int i, int j)
{
	if(i < j)
	{ 
		int tmp = i;
		i = j;
		j = tmp;
	}

	if ((i <= 2 && j < 2) ||
		(i <= 5 && j < 5 && (i > 2 && j>2)) ||
		(i <= 8 && j < 8 && (i >5 && j >5)))
	{


		for (int k = 0; k < _norm.size(); k++)
		{
			int tmp = _norm[k][i];
			_norm[k][i] = _norm[k][j];
			_norm[k][j] = tmp;
		}

	//	std::cout << "COL-SHUFFLE SUCCESS [" << i << " | " << j << "]" << std::endl;
	}
}

void Manager::init_norm()
{
	_norm.resize(9);
	for (int i = 0; i < _norm.size(); i++)
	{
		_norm[i].resize(9);
	}
	_norm =
	{
		{1,2,3,4,5,6,7,8,9},
		{7,8,9,1,2,3,4,5,6},
		{4,5,6,7,8,9,1,2,3},

		{3,1,2,8,4,5,9,6,7},
		{6,9,7,3,1,2,8,4,5},
		{8,4,5,6,9,7,3,1,2},

		{2,3,1,5,7,4,6,9,8},
		{9,6,8,2,3,1,5,7,4},
		{5,7,4,9,6,8,2,3,1},
	};
	std::srand(time(0));
	int _count = rand() % 5000;
	for (int i = 0; i < _count; i++)
	{
		if (rand() % 100 >= 50)
		{
			swap_rows(rand()%9, rand()%9);
		}
		else
		{
			swap_cols(rand()%9, rand()%9);
		}
	}

	
}

void Manager::make_win()
{
	int win_count = 0;
	for (int i = 0; i < _field.size(); i++)
	{
		if (_field[i].is_right())
			win_count++;
	}
	if(win_count == _field.size())
		_won = true;
}

void Manager::count_mistakes(int i)
{
	if (_field[i].get_mistake() && !_field[i].get_mistake_counted())
	{
		_field[i].mistake_counted_set(true);
		_mistakes++;
		std::cout << "Mistake " << _mistakes << " /3" << std::endl;
		if (_mistakes >= 3)
		{
			_lost = true;
		}
	}
}

void Manager::init_field(sf::Font* font, int row_count)
{
	init_norm();
	for (int i = 0; i < row_count * 3; i++)
	{
		for (int j = 0; j < row_count * 3; j++)
		{

			_field.push_back(Cell_Object(_win, sf::Vector2f(i * (_cellSize.x / 3.f), j * (_cellSize.y / 3.f)), (_cellSize / 3.f), _norm[j][i], true, font));
		}
	}

	if (_dif == EASY)
	{
		remove(40);
	}
	else if (_dif == NORMAL)
	{
		remove(50);
	}
	else if (_dif == HARD)
	{
		remove(60);
	}
}

Manager::Manager(sf::RenderWindow* win, sf::Vector2f& size, int row_count, Difficulty dif, sf::RenderWindow *statWin)
{
	init_values();

	_statWin = statWin;
	_dif = dif;
	_win = win;
	_cellSize = size;

	init_text();

	_font = new sf::Font;

	if (!_font->loadFromFile("futuram.ttf"))
	{

	}
	_rCount = row_count;
	init_field(_font, row_count);
	
}

void Manager::reset_marks()
{
	for (int i = 0; i < _field.size(); i++)
		_field[i].toggle_mark(false);
}

void Manager::check_mouse(int i)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !_field[i].get_static())
	{
		float x = sf::Mouse::getPosition(*_win).x - _field[i]._valObj.getPosition().x;
		x *= x;
		float y = sf::Mouse::getPosition(*_win).y - _field[i]._valObj.getPosition().y;
		y *= y;

		if (sqrt(x + y) <= _field[i]._valObj.getRadius())
		{
			reset_marks();
			_field[i].toggle_mark(true);
		}
	}
}

void Manager::init_text()
{
	_valStat.resize(9);
	_countStat.resize(9);

}

void Manager::play_lil_anim()
{
	static int ind = -1;
	if (ind == -1)
	{	
		if(_won)
		std::cout << "YOU WON!! Press R to restart." << std::endl;
		if(_lost)
		std::cout << "YOU LOST!! Press R to restart." << std::endl;
	}
	if (++ind < _field.size())
	{
		if (_won)
			_field[ind].win();
		if (_lost)
			_field[ind].loose();
	}
	else
		ind = -1;
}

void Manager::check_reset()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		_won = false;
		_lost = false;
		_mistakes = 0;
		_field.clear();
		init_field(_font, _rCount);
	}
}

bool Manager::app_in_focus()
{
	return true;
}

void Manager::init_values()
{
	_values.resize(9);
	for (int i = 0; i < 9; i++)
		_values[i].val = i + 1;
}

void Manager::count_field(int i)
{
	for (int j = 0; j < _values.size(); j++)
	{
		if (_field[i].get_val() == _values[j].val && _field[i].is_right())
		{
			_values[j].count++;
		}
	}
}

void Manager::set_string()
{
	for (int i = 0; i < 9; i++)
	{
		_valStat[i].setFont(*_font);
		_valStat[i].setCharacterSize(20);
		_valStat[i].setPosition(_statWin->getSize().x * 0.1, _statWin->getSize().y / 9 * i + 1);
		_valStat[i].setFillColor(sf::Color(85, 85, 85));
		if(_values[i].count == 9)
			_valStat[i].setFillColor(sf::Color(85, 255, 85));

		_countStat[i].setFont(*_font);
		_countStat[i].setCharacterSize(12);
		_countStat[i].setPosition(_statWin->getSize().x * 0.62, _statWin->getSize().y / 9 * i + 1);
		_countStat[i].setFillColor(sf::Color(169, 169, 169));

		_countStat[i].setString(std::to_string(_values[i].count));
		_valStat[i].setString(std::to_string(_values[i].val));

		_statWin->draw(_countStat[i]);
		_statWin->draw(_valStat[i]);
	}
}

void Manager::update()
{
	_values.clear();
	init_values();
	for (int i = 0; i < _field.size(); i++)
	{
		if (!_won && !_lost)
		{
			check_mouse(i);
			count_mistakes(i);
			count_field(i);
		}
		if(app_in_focus())
		_field[i].update();
	}
	make_win();

	set_string();

	//_statWin->draw(sf::CircleShape(15));

	if (_won||_lost)
	{
		play_lil_anim();
		check_reset();
	}
}
