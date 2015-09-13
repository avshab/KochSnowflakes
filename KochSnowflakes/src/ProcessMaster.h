#pragma once
#include <vector>

class PainterI;
class KochCoordModel;


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
};

