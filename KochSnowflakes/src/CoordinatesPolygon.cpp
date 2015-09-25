#include "stdafx.h"
#include "CoordinatesPolygon.h"


CoordinatesPolygon::CoordinatesPolygon()
{

}


void CoordinatesPolygon::SetName( const std::string& name_ )
{
    name = name_;
}


void CoordinatesPolygon::SetVisible( bool is_visible_ )
{
    is_visible = is_visible_;
}


std::string CoordinatesPolygon::GetName() const
{
    return name;
}


bool CoordinatesPolygon::GetVisible() const
{
    return is_visible;
}