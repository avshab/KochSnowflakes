#include "stdafx.h"
#include "CoordinatesSegment.h"


CoordinatesSegment::CoordinatesSegment( const SegmentPoints& pts_, const std::string& name_, bool is_visible_ )
    : pts( pts_ )
    , name( name_ )
    , is_visible( is_visible_ )
{
};


CoordinatesSegment::CoordinatesSegment()
    : is_visible(false)
{
}


void CoordinatesSegment::SetPoints( const SegmentPoints& pts_ )
{
    pts = pts_;
}


void CoordinatesSegment::SetName( const std::string& name_ )
{
    name = name_;
}


void CoordinatesSegment::SetVisible( bool is_visible_ )
{
    is_visible = is_visible_;
}


void CoordinatesSegment::SetColor( Color color_ )
{
    color = color_;
}


SegmentPoints CoordinatesSegment::GetPoints() const
{
    return pts;
}

std::string CoordinatesSegment::GetName() const
{
    return name;
}

bool CoordinatesSegment::GetVisible() const
{
    return is_visible;
}


Color CoordinatesSegment::GetColor() const
{
    return color;
}