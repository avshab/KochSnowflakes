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


//bool BaseSegment::HasPoint( const BasePoint& p ) const
//{
//    if (p.IsEqual( p1 ) || p.IsEqual( p2 ))
//        return true;
//
//    if (abs( (p1.GetX() - p.GetX()) - (p2.GetX() - p.GetX()) ) < 0.001 && abs( (p1.GetY() - p.GetY()) - (p2.GetY() - p.GetY())) < 0.001  && abs(p2.GetX() - p.GetX()) < 0.001 && abs(p2.GetY() - p.GetY()) < 0.001 )
//        return true;
//
//    if (abs( (p1.GetX() - p.GetX()) - (p2.GetX() - p.GetX()) ) < 0.001 && abs( (p1.GetZ() - p.GetZ()) - (p2.GetZ() - p.GetZ()) ) < 0.001 && abs( p2.GetX() - p.GetX() ) < 0.001 && abs( p2.GetZ() - p.GetZ() ) < 0.001)
//        return true;
//
//    if (abs( (p1.GetZ() - p.GetZ()) - (p2.GetZ() - p.GetZ()) ) < 0.001 && abs( (p1.GetY() - p.GetY()) - (p2.GetY() - p.GetY()) ) < 0.001 && abs( p2.GetZ() - p.GetZ() ) < 0.001 && abs( p2.GetY() - p.GetY() ) < 0.001)
//        return true;
//
//
//
//    double k1 = (p1.GetX() - p.GetX()) / (p2.GetX() - p.GetX());
//    double k2 = (p1.GetY() - p.GetY()) / (p2.GetY() - p.GetY());
//    double k3 = (p1.GetZ() - p.GetZ()) / (p2.GetZ() - p.GetZ());
//
//    if (abs( k1 - k2 ) < 0.000001 && abs( k1 - k3 ) < 0.000001)
//        return true;
//
//    return false;
//
//}



//
//std::pair<double, double> BaseSegment::GetCoord( ValueP c1, ValueP c2 )
//{
//    double v1 = -1.0;
//    double v2 = -1.0;
//    if (c1.val_cos_2 / c1.val_cos_1 + c2.val_cos_2 / c2.val_cos_1 != 0)
//        v1 = (c2.val_2 - c1.val_2) / (c1.val_cos_2 / c1.val_cos_1 + c2.val_cos_2 / c2.val_cos_1) + c1.val_1;
//
//    if (c2.val_cos_1 == 0.0)
//        v1 = c2.val_1;
//
//    v2 = c1.val_cos_2 * (v1 - c1.val_1) / c1.val_cos_1 + c1.val_2;
//    if (c1.val_cos_1 == 0.0)
//        v2 = c2.val_cos_2 * (v1 - c2.val_1) / c2.val_cos_1 + c2.val_2;
//
//
//    return std::pair<double, double>( v1, v2 );
//}
//


void BaseSegment::SetBasePoints(const SegmentBasePoints& pts_)
{
	pts = pts_;
}


SegmentBasePoints BaseSegment::GetBasePoints() const
{
	return pts;
}