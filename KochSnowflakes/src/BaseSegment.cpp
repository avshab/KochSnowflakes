#include "stdafx.h"
#include "BaseSegment.h"


BaseSegment::BaseSegment( const BasePoint& p1_, const BasePoint& p2_ )
	: pts(p1_, p2_)
{
    length = pts.p1.GetLength( pts.p2 );
}


BaseSegment::BaseSegment()
{
}

BaseSegment::~BaseSegment()
{
}

bool BaseSegment::IsEqual( const BaseSegment& l ) const
{
	if ((pts.p1.IsEqual(l.pts.p1) && pts.p2.IsEqual(l.pts.p2)))
        return true;

	if ((pts.p1.IsEqual(l.pts.p2) && pts.p2.IsEqual(l.pts.p1)))
        return true;

    return false;
}


void BaseSegment::SetBasePoints(const SegmentBasePoints& pts_)
{
	pts = pts_;
}


SegmentBasePoints BaseSegment::GetBasePoints() const
{
	return pts;
}


BaseSegment BaseSegment::Rotate( double alf_ ) const
{
    double alfa = alf_ * 3.14159265 / 180.0;
    double Bx = cos( alfa ) * length;
    double By = sin( alfa ) * length;
    BasePoint p( pts.p1.GetX() + Bx, pts.p1.GetY() + By, pts.p1.GetZ() );
    return  BaseSegment( pts.p1, p );
}

double BaseSegment::GetLength() const
{
    return length;
}