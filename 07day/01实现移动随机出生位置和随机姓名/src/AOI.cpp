#include "../inc/AOI.h"
#include <iostream>
using namespace std;

AOIGrid::AOIGrid(const int& x, const int& y) : x(x), y(y)
{
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


