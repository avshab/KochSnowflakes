#include "stdafx.h"
#include "BaseSegment.h"


BaseSegment::BaseSegment( const BasePoint& p1_, const BasePoint& p2_ )
    : p1( p1_ )
    , p2( p2_ )
    , is_visible( false )
{
}


BaseSegment::BaseSegment()
    : p1( BasePoint() )
    , p2( BasePoint() )
    , is_visible( false )
{
}

BaseSegment::~BaseSegment()
{
}

void BaseSegment::SetName( const std::string& name_str )
{
    name = name_str;
}

bool BaseSegment::IsEqual( const BaseSegment& l ) const
{
    if ((p1.IsEqual( l.p1 ) && p2.IsEqual( l.p2 )))
        return true;

    if ((p1.IsEqual( l.p2 ) && p2.IsEqual( l.p1 )))
        return true;

    return false;
}

std::string BaseSegment::GetName() const
{
    return name;
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

void BaseSegment::SetVisible( bool is_visible_)
{
    is_visible = is_visible_;
}

bool BaseSegment::IsVisible() const
{
    return  is_visible;
}


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