#include <iostream>
#include "../inc/test.h"

using namespace std;





int main()
{
	AOI world;

	player p1(60.2, 107.2);
	player p2(91.5, 118.3);
	player p3(147.6, 133.6);
	
	cout << "(" << p1.getX() << ", " << p1.getY() << ")" << endl;
	cout << "(" << p2.getX() << ", " << p2.getY() << ")" << endl;
	cout << "(" << p3.getX() << ", " << p3.getY() << ")" << endl;

	world.addPlyr(p1);
	world.addPlyr(p2);
	world.addPlyr(p3);
	
	cout << "-----------------" << endl;

	list<AOIGrid*> gridList = world.getSrdPlyrs(p1);
	for (AOIGrid*& p_g : gridList)
	{
		for (AOIObj* const & p : *p_g)
		{
			cout << "(" << p->getX() << ", " << p->getY() << ")" << endl;
		}
	}

	return 0;
}