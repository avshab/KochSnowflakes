#pragma once
#include <vector>

class PainterI;
class KochCoordModel;
class SnowflakesFractal;


class ProcessMaster
{
public:

	ProcessMaster();

    ~ProcessMaster();

	void Process();

	void SetPainter(PainterI *p);





private:

	PainterI *painter;

	KochCoordModel* model;

    SnowflakesFractal *fractal;


};

