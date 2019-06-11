#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>

//DumbNameBranchHistoryChecking
class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();

private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr int cellPadding = 1;
	static constexpr int dimension = 20;
	static constexpr int innerDimension = 18;
	static constexpr int width =32;
	static constexpr int height=24;
	static constexpr int x = 70;
	static constexpr int y = 50;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;


	//graphics cache for convenience (or performance in this case convenience)
	Graphics& gfx;
};