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


void CoordinatesPoint::SetColor( Color color_ )
{
    color = color_;
}


PointPos CoordinatesPoint::GetPos() const
{
    return pos;
}


Color CoordinatesPoint::GetColor() const
{
    return color;
}