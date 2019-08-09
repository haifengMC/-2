#pragma once

#include "AOI.h"

class player : public AOIObj
{
public:
	player(float x, float y);
	virtual ~player();



	// ͨ�� AOIObj �̳�
	virtual float & getX() const override
	{
		return x;
	}

	virtual float & getY() const override
	{
		return y;
	}
private:
	mutable float x, y;

};