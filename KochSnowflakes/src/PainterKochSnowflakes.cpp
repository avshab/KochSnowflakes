#include "stdafx.h"
#include "PainterKochSnowflakes.h"



PainterKochSnowflakes::PainterKochSnowflakes()
{

}



void PainterKochSnowflakes::Paint()
{
	PainterI::RedrawWindow();
}


void PainterKochSnowflakes::SetModel(CoordinatesModel* model)
{

	CoordinatesModel* m = dynamic_cast<CoordinatesModel*>(model);
	PainterI::SetModel(m);
}
