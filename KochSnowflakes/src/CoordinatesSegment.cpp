#include "stdafx.h"
#include "CoordinatesSegment.h"


CoordinatesSegment::CoordinatesSegment( const SegmentCoordPoints& pts_, const std::string& name_, bool is_visible_ )
    : pts( pts_ )

{
	SetColor(Gdiplus::Color::Green);
};


CoordinatesSegment::CoordinatesSegment()
{
}


void CoordinatesSegment::SetPoints( const SegmentCoordPoints& pts_ )
{
    pts = pts_;
}


SegmentCoordPoints CoordinatesSegment::GetUnitPoints() const
{
    return pts;
}
