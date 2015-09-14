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
    KochSegment k2( BasePoint( 500, 200, 0 ), BasePoint( 350, 459.80762113533160, 0 ) );
    KochSegment k3( BasePoint( 350, 459.80762113533160, 0 ), BasePoint( 200, 200, 0 ) );
	model->SetKochSegment( k1 );
    model->SetKochSegment( k2 );
    model->SetKochSegment( k3 );
    fractal = new SnowflakesFractal();   
    fractal->SetKochSegments(model->GetKochSegments());
}


ProcessMaster::~ProcessMaster()
{
    model->Clear();
    delete model;
}

void ProcessMaster::SetPainter(PainterI *p)
{
	painter = p;   
    painter->SetModel( model->GetModel() );
    painter->RedrawWindow();
}

void ProcessMaster::Process()
{

	fractal->Iterate();
    model->Clear();
	model->SetKochSegments(fractal->GetKochSegments());
	painter->SetModel(model->GetModel());
	painter->RedrawWindow();
}
