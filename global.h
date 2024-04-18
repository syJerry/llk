#pragma once

class Vex
{
public:
	Vex()
	{

	}
	Vex(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int x;
	int y;
	
};
enum PARAM{
nRow = 8,
nCol = 8,
sizeElem = 40
};

static int level = 1;
