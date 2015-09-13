#pragma once
#include "PainterI.h"
#include <vector>



class PainterKochSnowflakes 
	: public PainterI
{
public:

	PainterKochSnowflakes();

    void Paint();

	void SetModel(CoordinatesModel* model);

private:


};

