#include "Obstacle.h"

void Obstacle::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Obstacle::GetLocation() const
{
	return loc;
}




