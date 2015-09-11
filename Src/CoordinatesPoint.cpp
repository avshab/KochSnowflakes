#include "stdafx.h"
#include "CoordinatesPoint.h"


CoordinatesPoint::CoordinatesPoint( const PointPos& pos_, const std::string& name_, bool is_visible_ )
    : pos( pos_ )
    , name( name_ )
    , is_visible( is_visible_ )
{

}


CoordinatesPoint::CoordinatesPoint()
{

}


void CoordinatesPoint::SetPos( const PointPos& pos_ )
{
    pos = pos_;
}


void CoordinatesPoint::SetName( const std::string& name_ )
{
    name = name_;
}


void CoordinatesPoint::SetVisible( bool is_visible_ )
{
    is_visible = is_visible_;
}


PointPos CoordinatesPoint::GetPos() const
{
    return pos;
}


std::string CoordinatesPoint::GetName() const
{
    return name;
}


bool CoordinatesPoint::GetVisible() const
{
    return is_visible;
}