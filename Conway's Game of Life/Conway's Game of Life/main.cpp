#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <array>
#include <vector>
#include <algorithm>

#include "Renderer.h"

const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

bool isAlive(
	std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH>& game,
	const int x,
	const int y)
{

	int alive = 0;

	if (x > 0 && game[x - 1][y] == 1) alive += 1;
	if (x < GAME_WIDTH - 1 && game[x + 1][y] == 1) alive += 1;
	if (y > 0 && game[x][y - 1] == 1) alive += 1;
	if (y < GAME_HEIGHT - 1 && game[x][y + 1] == 1) alive += 1;


	if (y > 0 && x > 0 && game[x - 1][y - 1] == 1) alive += 1;
	if (y > 0 && x < GAME_WIDTH - 1 && game[x + 1][y - 1] == 1) alive += 1;
	if (y < GAME_HEIGHT - 1 && x > 0 && game[x - 1][y + 1] == 1) alive += 1;
	if (y < GAME_HEIGHT - 1 && x < GAME_WIDTH - 1 && game[x + 1][y + 1] == 1) alive += 1;

	if (game[x][y] == 1 && alive < 2) return false;
	if (game[x][y] == 1 && (alive == 2 || alive == 3)) return true;
	if (alive > 3) return false;
	if (game[x][y] == 0 && alive == 3) return true;

	return false;

}

int main()
{
	G screen;
	std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> display{};
	std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> swap{};

	for (auto& row : display)
		std::generate(row.begin(), row.end(), []() { return rand() % 10 == 0 ? 1 : 0; });


	while (true)
	{
	
		for (int i = 0; i < GAME_WIDTH; ++i)
		{
			for (int k = 0; k < GAME_HEIGHT; ++k)
			{
				swap[i][k] = isAlive(display, i, k) ? 1 : 0;
			}
		}

		for (int i = 0; i < GAME_WIDTH; ++i)
		{
			for (int k = 0; k < GAME_HEIGHT; ++k)
			{
				if (swap[i][k])
				{
					screen.drawpixel(i, k);
				}
			}
		}

		std::copy(swap.begin(), swap.end(), display.begin());

		screen.update();
		SDL_Delay(20);
		screen.input();
		screen.clearpixels();

	}
}