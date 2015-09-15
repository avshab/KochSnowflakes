#include "stdafx.h"
#include "BaseSegment.h"


BaseSegment::BaseSegment( const BasePoint& p1_, const BasePoint& p2_ )
	: pts(p1_, p2_)
{
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