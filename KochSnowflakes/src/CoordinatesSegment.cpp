#include "stdafx.h"
#include "CoordinatesSegment.h"


CoordinatesSegment::CoordinatesSegment( const SegmentCoordPoints& pts_, const std::string& name_, bool is_visible_ )
    : pts( pts_ )
    , name( name_ )
    , is_visible( is_visible_ )
{
};


CoordinatesSegment::CoordinatesSegment()
    : is_visible(false)
{
}


void CoordinatesSegment::SetPoints( const SegmentCoordPoints& pts_ )
{
    pts = pts_;
}


void CoordinatesSegment::SetColor( Color color_ )
{
    color = color_;
}


SegmentCoordPoints CoordinatesSegment::GetPoints() const
{
    return pts;
}


Color CoordinatesSegment::GetColor() const
{
    return color;
}