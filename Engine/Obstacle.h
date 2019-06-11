#pragma once
#include "Board.h"
#include "Graphics.h"
#include "Location.h"
#include <random>
#include "Snake.h"

class Obstacle
{
public:
	Obstacle(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;
	int howMany = 0;

	bool isHit(const Snake& snake);

private:
	Location loc;
	static constexpr Color c = Colors::Blue;

};