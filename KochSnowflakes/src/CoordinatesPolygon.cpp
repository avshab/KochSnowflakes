#include "stdafx.h"
#include "CoordinatesPolygon.h"


CoordinatesPolygon::CoordinatesPolygon()
{

}



CoordinatesPolygon::CoordinatesPolygon( std::vector<CoordinatesPoint>& pts_, const std::string& name_, bool is_visible_ )
    : versus( pts_ )
    , pts_size( pts_.size() )
{
 
}


void CoordinatesPolygon::SetCoordinates( std::vector<CoordinatesPoint>& pts )
{
    versus = pts;
    pts_size = pts.size();
}


std::vector<CoordinatesPoint> CoordinatesPolygon::GetCoordinates() const
{
    return versus;
}