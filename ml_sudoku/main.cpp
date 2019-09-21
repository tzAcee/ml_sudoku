#include <iostream>
#include "SFML/Graphics.hpp"
#include "Manager.h"


sf::Vector2f draw_seperation_line(sf::RenderWindow& win, int count)
{
	std::vector<sf::RectangleShape> _lines(count * 2);
	for (int i = 1; i <= count; i++)
	{
		//// line: ____
		_lines[i - 1].setFillColor(sf::Color::White);
		_lines[i - 1].setSize(sf::Vector2f(win.getSize().x, 1));
		_lines[i - 1].setPosition(sf::Vector2f(0, i * win.getSize().y / (count + 1)));

		//// line: |
		_lines[i + 1].setFillColor(sf::Color::White);
		_lines[i + 1].setSize(sf::Vector2f(1, win.getSize().y));
		_lines[i + 1].setPosition(sf::Vector2f(i * win.getSize().x / (count + 1), 0));

		win.draw(_lines[i - 1]);
		win.draw(_lines[i + 1]);
	}

	return sf::Vector2f(win.getSize().x / (count + 1), win.getSize().y / (count + 1));
}

void adjust_pos(sf::RenderWindow& win, sf::RenderWindow& to_win)
{
	to_win.setPosition(sf::Vector2i(win.getPosition().x + win.getSize().x+8, win.getPosition().y + 0.7 * win.getSize().y));
}

int main()
{
	std::cout << "DIFFICULTIES:" << std::endl;
	std::cout << "EASY   - 0" << std::endl;
	std::cout << "NORMAL - 1" << std::endl;
	std::cout << "HARD   - 2" << std::endl;

	bool success = false;
	std::string inp;
	do
	{
		std::cout << "*********************************" << std::endl << "_: ";
		std::cin >> inp;
		if (inp == "0" || inp == "EASY" ||
			inp == "1" || inp == "NORMAL" ||
			inp == "2" || inp == "HARD")
		{
			success = true;
			std::cout << "You selected " << inp <<" || HAVE FUN!" << std::endl;
		}
		else
		{
			std::cout << "Oof, try again..." << std::endl;
		}
		} while (!success);

		if (inp == "EASY")
			inp = "0";
		if (inp == "NORMAL")
			inp = "2";
		if (inp == "HARD")
			inp = "3";

	sf::RenderWindow win(sf::VideoMode(800, 800, 64), "Sudoku_FLEX", sf::Style::Titlebar | sf::Style::Close);
	sf::RenderWindow stat_win(sf::VideoMode(50, 170), "stats", sf::Style::None);

	sf::Vector2f size = draw_seperation_line(win, 2);
	Manager manager(&win, size, 3, (Difficulty)std::stoi(inp), &stat_win);


	while (win.isOpen())
	{
		sf::Event _ev;
		while (win.pollEvent(_ev))
		{
			adjust_pos(win, stat_win);
			if (_ev.type == sf::Event::Closed)
			{
				win.close();
				stat_win.close();
			}
		}

		adjust_pos(win, stat_win);

		win.clear();
		stat_win.clear(sf::Color(112, 128, 144));

		manager.update();

		draw_seperation_line(win, 2);
		win.display();
		stat_win.display();
	}

	return 0;
}