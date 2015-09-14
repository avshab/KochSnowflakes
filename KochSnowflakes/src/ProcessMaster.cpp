#include "stdafx.h"
#include "ProcessMaster.h"
#include "SnowflakesFractal.h"
#include "PainterI.h"
#include "KochCoordModel.h"


ProcessMaster::ProcessMaster()
{
	model = new KochCoordModel();
	model->SetModelName("Koch Model");
	KochSegment k( BasePoint(50, 50, 0), BasePoint(200, 200, 0) );
	model->SetKochSegment( k );
}


ProcessMaster::~ProcessMaster()
{
    delete model;
}

void ProcessMaster::SetPainter(PainterI *p)
{
	painter = p;
}

void ProcessMaster::Process()
{
	SnowflakesFractal fractal;
	fractal.SetKochSegments(model->GetKochSegments());
	fractal.Iterate();
	model->SetKochSegments(fractal.GetKochSegments());
	painter->SetModel(model);
	painter->RedrawWindow();
}
