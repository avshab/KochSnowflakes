#include "stdafx.h"
#include "CoordinatesSegment.h"


CoordinatesSegment::CoordinatesSegment( const SegmentCoordPoints& pts_, const std::string& name_, bool is_visible_ )
    : pts( pts_ )
    , name( name_ )
    , is_visible( is_visible_ )
{
	SetColor(Gdiplus::Color::DarkSeaGreen);
};


CoordinatesSegment::CoordinatesSegment()
    : is_visible(false)
{
}


void CoordinatesSegment::SetPoints( const SegmentCoordPoints& pts_ )
{
    pts = pts_;
}


SegmentCoordPoints CoordinatesSegment::GetPoints() const
{
    return pts;
}
