#include "stdafx.h"
#include "KochSegment.h"

#include <cmath>

namespace
{
    const static double COEF = 1.0 / 3.0;
    const static double ALFA = 60.0 * 3.14159265 / 180.0;

    BasePoint GetThirdPoint( BaseSegment* s, eGrowthDirection dir = eGrowthDirection::OUTSIDE )
    {
        double alfa;

        if (dir == eGrowthDirection::INSIDE)
            alfa = ALFA;

        if (dir == eGrowthDirection::OUTSIDE)
            alfa = -ALFA;

        SegmentBasePoints bp = s->GetBasePoints();

        double Bx = cos( alfa ) * (bp.p2.GetX() - bp.p1.GetX()) - sin( alfa ) * (bp.p2.GetY() - bp.p1.GetY());
        double By = sin( alfa ) * (bp.p2.GetX() - bp.p1.GetX()) + cos( alfa ) * (bp.p2.GetY() - bp.p1.GetY());

        return  BasePoint( bp.p1.GetX() + Bx, bp.p1.GetY() + By, bp.p1.GetZ() );
    }

}



KochSegment::KochSegment( const BasePoint& p1_, const BasePoint& p2_ )
	: BaseSegment(p1_,p2_)
{
    BaseSegment sn( p1_, p2_ );
    seg.p1 = p1_;
    seg.p1.SetZ( 0.0 );
    seg.p5 = p2_; 
    seg.p5.SetZ( 0.0 );
    double k = 1.0 / 3.0;
    seg.p2 = GetMiddlePoint( seg.p1, seg.p5, k );
    seg.p4 = GetMiddlePoint( seg.p5, seg.p1, k );
    opposite_point = GetThirdPoint( &sn, eGrowthDirection::INSIDE );
    order_iteration = 0;
}

KochSegment::KochSegment( const BaseSegment& s )
    : BaseSegment( s )
{
    SegmentBasePoints bp = GetBasePoints();
    BaseSegment sn = s;
    seg.p1 = bp.p1;
    seg.p1.SetZ( 0.0 );
    seg.p5 = bp.p2;
    seg.p5.SetZ( 0.0 );
    double k = 1.0 / 3.0;
    seg.p2 = GetMiddlePoint( seg.p1, seg.p5, k );
    seg.p4 = GetMiddlePoint( seg.p5, seg.p1, k );
    opposite_point = GetThirdPoint( &sn, eGrowthDirection::INSIDE );
    order_iteration = 0;
}
 

KochSegment::KochSegment()
{
  
}



KochUnitPoints KochSegment::GetUnitPoints() const
{
    return seg;

}


void KochSegment::SetColor( Color c )
{
    color = c;
}


Color KochSegment::GetColor() const
{
    return color;
}


BasePoint KochSegment::GetPointIsosTriangle( eGrowthDirection dir )
{
    return  GetThirdPoint( this, dir );
}

std::vector<KochSegment> KochSegment::Divide( eGrowthDirection dir )
{   
    std::vector<KochSegment> segs;

    seg.p3 = KochSegment( seg.p2, seg.p4 ).GetPointIsosTriangle( dir );
    BasePoint  ff = KochSegment( seg.p2, seg.p4 ).GetPointIsosTriangle( eGrowthDirection::INSIDE );

    order_iteration++;
    segs.push_back( KochSegment( seg.p1, seg.p2 ) );
    segs.push_back( KochSegment( seg.p2, seg.p3 ) );
    segs.push_back( KochSegment( seg.p3, seg.p4 ) );
    segs.push_back( KochSegment( seg.p4, seg.p5 ) );
    //segs.push_back( KochSegment( seg.p4, seg.p2 ) );  

    for (auto it = begin( segs ); it != end( segs ); it++)
    {
        it->SetColor( GetColor() );   
    }

    return segs;
}


void KochSegment::SetIteration( int order )
{
    order_iteration = order;
}


eGrowthDirection KochSegment::GetDirection() const
{
    int y = rand();

    if(y % 2 == 0.0)     
        return eGrowthDirection::INSIDE;
    return eGrowthDirection::OUTSIDE;
}

