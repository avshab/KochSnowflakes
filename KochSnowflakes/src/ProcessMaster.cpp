#include "stdafx.h"
#include "ProcessMaster.h"
#include "SnowflakesFractal.h"
#include "PainterI.h"
#include "KochCoordModel.h"


ProcessMaster::ProcessMaster()
{
	//model = new KochCoordModel();
	//model->SetModelName("Koch Model");
    //std::vector<KochSegment> vect;
    //vect.push_back(KochSegment( BasePoint( 200, 200, 0 ), BasePoint( 500, 200, 0 ) ));
    //BasePoint pc = vect.at(0).GetPointIsosTriangle( eGrowthDirection::INSIDE );
    //vect.push_back( KochSegment( BasePoint( 500, 200, 0 ), pc ) );
    //vect.push_back( KochSegment( pc, BasePoint( 200, 200, 0 ) ) );

    //for (auto it = begin( vect ); it != end( vect ); it++)
    //    it->SetColor( Color::Purple );


    //model->SetKochSegments( vect );
    //
    //fractal = new SnowflakesFractal();   
    //fractal->SetKochSegments(model->GetKochSegments());

    model = new KochCoordModel();
    model->SetModelName( "Koch Model" );
    model->SetCenterPoint( BasePoint( 350, 300, 0 ) );
    fractal = new SnowflakesFractal();
    fractal->SetKochSegments( model->GetKochSegments() );
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
    model = new KochCoordModel();
    model->SetModelName( "Koch Model" );
    model->SetCenterPoint( BasePoint(300, 300, 0) );
    fractal = new SnowflakesFractal();
    fractal->SetKochSegments( model->GetKochSegments() );
    fractal->SetCenterPoint( BasePoint( 300, 300, 0 ) );
    while (true)
    {
     	fractal->Iterate();                        
        model->SetKochSegments(fractal->GetKochSegments());
	    painter->SetModel(&model->GetModel());
	    painter->RedrawWindow();
        Sleep( 100 );
    }

}