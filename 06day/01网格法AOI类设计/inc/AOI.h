#pragma once

#include "list"
#include "set"

using namespace std;

#define GRID_SIZE_DEFAULT 30

struct AOIObj
{
	virtual float& getX() const = 0;
	virtual float& getY() const = 0;
};

class AOIGrid
{
	int x, y;
public:
	AOIGrid(const int& x, const int& y);

	void addObj(AOIObj* const& obj) const;
	void delObj(AOIObj* const& obj) const;

	list<AOIObj*>::iterator begin();
	list<AOIObj*>::iterator end();
	list<AOIObj*>::const_iterator cbegin() const;
	list<AOIObj*>::const_iterator cend() const;

	bool operator==(const AOIGrid& grid) const;
	bool operator<(const AOIGrid& grid) const;
	bool operator>(const AOIGrid& grid) const;
private:
	mutable list<AOIObj*> obj_list;
};

class AOI
{
	//���ӵĳߴ磨�߳���
	size_t gridSize;
	//ԭ��
	int x, y;

	set<AOIGrid> grid_set;
public:
	AOI(int x = 0, int y = 0, size_t gridSize = GRID_SIZE_DEFAULT);
	virtual ~AOI();

	//��ȡ��Χ���
	list<AOIGrid*> getSrdPlyrs(const AOIObj& plyr);
	//������
	void addPlyr(AOIObj& plyr);
	//ɾ�����
	void delPlyr(AOIObj& plyr);
private:
	int getGridPosX(const float& x);
	int getGridPosY(const float& y);
};

