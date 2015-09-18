#include "stdafx.h"
#include "ProcessMaster.h"
#include "SnowflakesFractal.h"
#include "PainterI.h"
#include "KochCoordModel.h"


ProcessMaster::ProcessMaster()
{
	model = new KochCoordModel();
	model->SetModelName("Koch Model");
	KochSegment k1( BasePoint( 200, 200, 0 ), BasePoint( 500, 200, 0 ) );
    BasePoint pc = k1.GetPointIsosTriangle( eGrowthDirection::INSIDE );
	model->SetKochSegment( k1 );
    model->SetKochSegment( KochSegment( BasePoint( 500, 200, 0 ), pc ) );
    model->SetKochSegment( KochSegment( pc, BasePoint( 200, 200, 0 ) ) );

    fractal = new SnowflakesFractal();   
    fractal->SetKochSegments(model->GetKochSegments());
}


ProcessMaster::~ProcessMaster()
{
    model->Clear();
    delete model;
    delete fractal;
}

void ProcessMaster::SetPainter(PainterI *p)
{
	painter = p;   
    painter->SetModel( &model->GetModel() );
    painter->RedrawWindow();
}

void ProcessMaster::Process()
{
	fractal->Iterate();
   
	model->SetKochSegments(fractal->GetKochSegments());
	painter->SetModel(&model->GetModel());
	painter->RedrawWindow();
}
