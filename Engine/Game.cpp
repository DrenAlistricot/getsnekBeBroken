/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Board.h"
#include "SpriteCodex.h"
#include "Obstacle.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	rng2(std::random_device()()),
	snek({2,2}),
	goal(rng,brd,snek),
	obstacle(rng2,brd,snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (gameIsStarted) {
		if (!GameIsOver)
		{
			/////Fix snake from eating itself on vertical to vertical pivot or horizontal to horizontal pivot
			/////(head to ass death on one axis ... can't go backwards only forwards)
			//figure out which direction snek is going on y
			int y = delta_loc.y;
			///figure out which direction snek is going on x
			int x = delta_loc.x;
			////////////////////////////////
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				///all of these if statements check to make sure that you can't just turn into yourself
				if (y != 1) {
					delta_loc = { 0,-1 };
				}
			}


			if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				if (y != -1) {
					delta_loc = { 0,1 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				if (x != 1) {
					delta_loc = { -1, 0 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				if (x != -1) {
					delta_loc = { 1, 0 };
				}
			}

			// the counter lags the game to slow the snek down by making UpdateModel cycle 20 times (snekMovePeriod) before running conditions ... leads to input lag
			snekMoveCounter++;
			if (snekMoveCounter >= snekMovePeriod)
			{
				snekMoveCounter = 0;
				const Location next = snek.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(next) ||
					snek.IsInTileExceptEnd(next))
				{
					GameIsOver = true;

				}
				else
				{
					const bool eating = next == goal.GetLocation();
					if (eating)
					{
						snek.Grow();
						snekMovePeriod--;
					}

					snek.MoveBy(delta_loc);
					if (eating)
					{
						goal.Respawn(rng, brd, snek);
						obstacle.howMany++;
					}
				}
			}
			snekSpeedUpcounter++;
			if (snekSpeedUpcounter >= snekSpeedUpPeriod)
			{
				snekSpeedUpcounter = 0;
				// std::max ... returns biggest of snekMovePeriod -1, or snekMovePeriodMin
				snekMovePeriod = std::max(snekMovePeriod - 1, snekMovePeriodMin);
				/*
				// snekMovePeriod --; increases speed and resetting to 0 makes sure that you have a minimum speed
				snekMovePeriod--;
				if (snekMovePeriod < 0)
				{
					snekMovePeriod = 0;
				}*/
			}

		}
	}
	else
	{
		gameIsStarted = wnd.kbd.KeyIsPressed(VK_RETURN);

	}

}


void Game::ComposeFrame()
{
	if (gameIsStarted)
	{
		/*for (int i = 0; i < obstacle.howMany; i++)
		{
			obstacle.Draw(brd);
		}*/
		snek.Draw(brd);
		goal.Draw(brd);
		if (GameIsOver)
		{
			SpriteCodex::DrawGameOver(350, 265, gfx);
		}
		brd.DrawBorder();
	}
	else
	{
		SpriteCodex::DrawTitle(290, 225, gfx);
	}
}
