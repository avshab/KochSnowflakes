#include "stdafx.h"
#include "ProcessMaster.h"
#include "SnowflakesFractal.h"
#include "PainterI.h"
#include "KochCoordModel.h"


ProcessMaster::ProcessMaster()
{
    model = new KochCoordModel();
    model->SetModelName( "Koch Model" );
    fractal = new SnowflakesFractal( model );       
    fractal->SetCenterPoint( BasePoint( 350, 300, 0 ) );
}


ProcessMaster::~ProcessMaster()
{
    model->Clear( eModelObjectType::BASE_POINT );
    model->Clear( eModelObjectType::BASE_SEGMENT );
    model->Clear( eModelObjectType::BASE_POLYGON );
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
    while (true)
    {
     	fractal->Iterate();                        
	    painter->SetModel(&model->GetModel());
	    painter->RedrawWindow();
        Sleep( 4 );
    }

}