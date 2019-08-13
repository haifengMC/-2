#include "../inc/AOI.h"
#include <iostream>
using namespace std;

AOIGrid::AOIGrid(const int& x, const int& y) : x(x), y(y)
{
}

int & AOIGrid::getX()
{
	return x;
}

int & AOIGrid::getY()
{
	return y;
}

void AOIGrid::addObj(AOIObj * const & p_obj) const
{
	obj_list.push_back(p_obj);
}

void AOIGrid::delObj(AOIObj * const & p_obj) const
{
	obj_list.remove(p_obj);
}

list<AOIObj*>::iterator AOIGrid::begin()
{
	return obj_list.begin();
}

list<AOIObj*>::iterator AOIGrid::end()
{
	return obj_list.end();
}

list<AOIObj*>::const_iterator AOIGrid::cbegin() const
{
	return obj_list.cbegin();
}

list<AOIObj*>::const_iterator AOIGrid::cend() const
{
	return obj_list.cend();
}

bool AOIGrid::operator==(const AOIGrid & grid) const
{
	if (this->x == grid.x && this->y == grid.y)	return true;

	return false;
}

bool AOIGrid::operator<(const AOIGrid & grid) const
{
	if (this->x < grid.x) return true;
	else if (this->x == grid.x && this->y < grid.y) return true;

	return false;
}

bool AOIGrid::operator>(const AOIGrid & grid) const
{
	if (grid < *this) return true;

	return false;
}


AOI::AOI(int x, int y, size_t gridSize) :
	x(x), y(y), gridSize(gridSize)
{
}

AOI::~AOI()
{
}

set<AOIGrid>::iterator AOI::begin()
{
	return grid_set.begin();
}

set<AOIGrid>::iterator AOI::end()
{
	return grid_set.end();
}

set<AOIGrid>::const_iterator AOI::cbegin() const
{
	return grid_set.cbegin();
}

set<AOIGrid>::const_iterator AOI::cend() const
{
	return grid_set.cend();
}

list<AOIGrid*> AOI::getSrdPlyrs(const AOIObj & plyr)
{
	list<AOIGrid*> ret;

	int x = getGridPosX(plyr.getX());
	int y = getGridPosY(plyr.getY());

	AOIGrid gridTemp(x, y);
	AOIGrid gridTopTemp(x, y - 1);
	AOIGrid gridBottomTemp(x, y + 1);
	AOIGrid gridLeftTemp(x - 1, y);
	AOIGrid gridRightTemp(x + 1, y);
	AOIGrid gridTopLeftTemp(x - 1, y - 1);
	AOIGrid gridTopRightTemp(x + 1, y - 1);
	AOIGrid gridBottomLeftTemp(x - 1, y + 1);
	AOIGrid gridBottomRightTemp(x + 1, y + 1);

	set<AOIGrid>::iterator grid_it;
	if (grid_set.end() != (grid_it = grid_set.find(gridTemp)))ret.push_back((AOIGrid*)&*grid_it);
	if (grid_set.end() != (grid_it = grid_set.find(gridTopTemp)))ret.push_back((AOIGrid*)&*grid_it);
	if (grid_set.end() != (grid_it = grid_set.find(gridBottomTemp)))ret.push_back((AOIGrid*)&*grid_it);
	if (grid_set.end() != (grid_it = grid_set.find(gridLeftTemp)))ret.push_back((AOIGrid*)&*grid_it);
	if (grid_set.end() != (grid_it = grid_set.find(gridRightTemp)))ret.push_back((AOIGrid*)&*grid_it);
	if (grid_set.end() != (grid_it = grid_set.find(gridTopLeftTemp)))ret.push_back((AOIGrid*)&*grid_it);
	if (grid_set.end() != (grid_it = grid_set.find(gridTopRightTemp)))ret.push_back((AOIGrid*)&*grid_it);
	if (grid_set.end() != (grid_it = grid_set.find(gridBottomLeftTemp)))ret.push_back((AOIGrid*)&*grid_it);
	if (grid_set.end() != (grid_it = grid_set.find(gridBottomRightTemp)))ret.push_back((AOIGrid*)&*grid_it);

	return ret;
}

void AOI::upDateSrdPlyrs(AOIObj& plyr, 
	const float& x, const float& y,
	list<AOIGrid*> &oldGridList,
	list<AOIGrid*> &unaltGridList,
	list<AOIGrid*> &newGridList)
{
	int oldX = getGridPosX(plyr.getX());
	int oldY = getGridPosY(plyr.getY());
	int newX = getGridPosX(x);
	int newY = getGridPosY(y);
	//cout << "old(" <<
	//	plyr.getX() << "[" << oldX << "], " <<
	//	plyr.getY() << "[" << oldY << "])" << endl;
	//cout << "new(" <<
	//	x << "[" << newX << "], " <<
	//	y << "[" << newY << "])" << endl;

	oldGridList.clear();
	unaltGridList.clear();
	newGridList.clear();
	
	if (oldX == newX && oldY == newY)
	{
		//cout << "oldX == newX && oldY == newY" << endl;
		//cout << "old(" <<
		//	plyr.getX() << "[" << oldX << "], " <<
		//	plyr.getY() << "[" << oldY << "])" << endl;
		//cout << "new(" <<
		//	x << "[" << newX << "], " <<
		//	y << "[" << newY << "])" << endl;
		plyr.setXY(x, y);
		unaltGridList = getSrdPlyrs(plyr);

		return;
	}

	if (getAbs(newX - oldX) > 2 || getAbs(newY - oldY) > 2)
	{
		oldGridList = getSrdPlyrs(plyr);
		delPlyr(plyr);
		plyr.setXY(x, y);
		addPlyr(plyr);
		newGridList = getSrdPlyrs(plyr);

		return;
	}

	/*
			AOIGrid oldGridTemp(oldX, oldY);
			AOIGrid oldGridTopTemp(oldX, oldY - 1);
			AOIGrid oldGridBottomTemp(oldX, oldY + 1);
			AOIGrid oldGridLeftTemp(oldX - 1, oldY);
			AOIGrid oldGridRightTemp(oldX + 1, oldY);
			AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
			AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
			AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
			AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

			if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

			AOIGrid newGridTemp(newX, newY);
			AOIGrid newGridTopTemp(newX, newY - 1);
			AOIGrid newGridBottomTemp(newX, newY + 1);
			AOIGrid newGridLeftTemp(newX - 1, newY);
			AOIGrid newGridRightTemp(newX + 1, newY);
			AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
			AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
			AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
			AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

			if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
			if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
	
	*/
	delPlyr(plyr);
	plyr.setXY(x, y);
	addPlyr(plyr);
	set<AOIGrid>::iterator grid_it;
	switch (newX - oldX)
	{
	case -2:
		{
			switch (newY - oldY)
			{
			case -2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				
					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
				}
				break;
			case -1:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
				}
				break;
			case 0:
				{
				AOIGrid oldGridTemp(oldX, oldY);
				AOIGrid oldGridTopTemp(oldX, oldY - 1);
				AOIGrid oldGridBottomTemp(oldX, oldY + 1);
				AOIGrid oldGridRightTemp(oldX + 1, oldY);
				AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
				AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

				if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

				AOIGrid newGridTemp(newX, newY);
				AOIGrid newGridTopTemp(newX, newY - 1);
				AOIGrid newGridBottomTemp(newX, newY + 1);
				AOIGrid newGridLeftTemp(newX - 1, newY);
				AOIGrid newGridRightTemp(newX + 1, newY);
				AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
				AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
				AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
				AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

				if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 1:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				}
				break;
			case 2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				}
				break;
			default:
				//cout << "error : " << newX - oldX << newY - oldY << endl;
				break;
			}
		}
		break;
	case -1:
		{
			switch (newY - oldY)
			{
			case -2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case -1:
				{
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 0:
				{
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
				}
				break;
			case 1:
				{
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			default:
				cout << "error" << endl;
				break;
			}
		}
		break;
	case 0:
		{
			switch (newY - oldY)
			{
			case -2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case -1:
				{
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 1:
				{
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			default:
				cout << "error" << endl;
				break;
			}
		}
		break;
	case 1:
		{
			switch (newY - oldY)
			{
			case -2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case -1:
				{
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 0:
				{
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 1:
				{
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 2:
				{
				AOIGrid oldGridTemp(oldX, oldY);
				AOIGrid oldGridTopTemp(oldX, oldY - 1);
				AOIGrid oldGridLeftTemp(oldX - 1, oldY);
				AOIGrid oldGridRightTemp(oldX + 1, oldY);
				AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
				AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
				AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);

				if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

				AOIGrid newGridTemp(newX, newY);
				AOIGrid newGridTopTemp(newX, newY - 1);
				AOIGrid newGridBottomTemp(newX, newY + 1);
				AOIGrid newGridLeftTemp(newX - 1, newY);
				AOIGrid newGridRightTemp(newX + 1, newY);
				AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
				AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
				AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
				AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

				if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
				if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			default:
				cout << "error" << endl;
				break;
			}
		}
		break;
	case 2:
		{
			switch (newY - oldY)
			{
			case -2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case -1:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);
					AOIGrid oldGridBottomRightTemp(oldX + 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 0:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 1:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			case 2:
				{
					AOIGrid oldGridTemp(oldX, oldY);
					AOIGrid oldGridTopTemp(oldX, oldY - 1);
					AOIGrid oldGridBottomTemp(oldX, oldY + 1);
					AOIGrid oldGridLeftTemp(oldX - 1, oldY);
					AOIGrid oldGridRightTemp(oldX + 1, oldY);
					AOIGrid oldGridTopLeftTemp(oldX - 1, oldY - 1);
					AOIGrid oldGridTopRightTemp(oldX + 1, oldY - 1);
					AOIGrid oldGridBottomLeftTemp(oldX - 1, oldY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(oldGridTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridTopRightTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(oldGridBottomLeftTemp)))oldGridList.push_back((AOIGrid*)&*grid_it);

					AOIGrid newGridTemp(newX, newY);
					AOIGrid newGridTopTemp(newX, newY - 1);
					AOIGrid newGridBottomTemp(newX, newY + 1);
					AOIGrid newGridLeftTemp(newX - 1, newY);
					AOIGrid newGridRightTemp(newX + 1, newY);
					AOIGrid newGridTopLeftTemp(newX - 1, newY - 1);
					AOIGrid newGridTopRightTemp(newX + 1, newY - 1);
					AOIGrid newGridBottomLeftTemp(newX - 1, newY + 1);
					AOIGrid newGridBottomRightTemp(newX + 1, newY + 1);

					if (grid_set.end() != (grid_it = grid_set.find(newGridTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopLeftTemp)))unaltGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridTopRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomLeftTemp)))newGridList.push_back((AOIGrid*)&*grid_it);
					if (grid_set.end() != (grid_it = grid_set.find(newGridBottomRightTemp)))newGridList.push_back((AOIGrid*)&*grid_it);

				}
				break;
			default:
				cout << "error" << endl;
				break;
			}
		}
		break;
	default:
		cout << "error" << endl;
		break;
	}
}

void AOI::addPlyr(AOIObj & plyr)
{
	AOIGrid gridTemp(getGridPosX(plyr.getX()), getGridPosY(plyr.getY()));
	set<AOIGrid>::iterator grid_it;
	if (grid_set.end() == (grid_it = grid_set.find(gridTemp)))
	{
		gridTemp.addObj(&plyr);
		grid_set.insert(gridTemp);
	}
	else
	{
		grid_it->addObj(&plyr);
	}
}

void AOI::delPlyr(AOIObj & plyr)
{
	AOIGrid gridTemp(getGridPosX(plyr.getX()), getGridPosY(plyr.getY()));
	set<AOIGrid>::iterator grid_it;
	if (grid_set.end() != (grid_it = grid_set.find(gridTemp)))
	{
		grid_it->delObj(&plyr);
	}
}

int AOI::getGridPosX(const float & x)
{
	if (x < 0) return x / gridSize - 1;
	return x / gridSize;
}

int AOI::getGridPosY(const float & y)
{
	if (y < 0) return y / gridSize - 1;
	return y / gridSize;
}

int AOI::getAbs(const int & n)
{
	return n > 0 ? n : -n;
}
