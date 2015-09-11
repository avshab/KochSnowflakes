#include "stdafx.h"
#include "KochSegment.h"

namespace
{
    const static double COEF = 1 / 3;
    const static double ALFA = 60 * 3.14159265 / 180;
}


double GetThird( double l ) { return COEF * l;  }


KochSegment::KochSegment( const BasePoint& p1_, const BasePoint& p2_ )
{
    seg.p1 = p1_;
    seg.p1.SetZ( 0.0 );
    seg.p5 = p2_; 
    seg.p5.SetZ( 0.0 );
    seg.p2 = BasePoint( GetThird( seg.p5.GetX() - seg.p1.GetX() ), GetThird( seg.p5.GetY() - seg.p1.GetY() ), GetThird( seg.p5.GetZ() - seg.p1.GetZ() ) );
    seg.p4 = BasePoint( GetThird( seg.p1.GetX() - seg.p5.GetX() ), GetThird( seg.p1.GetY() - seg.p5.GetY() ), GetThird( seg.p1.GetZ() - seg.p5.GetZ() ) );
}


KochSegment::KochSegment()
{
}


std::vector<KochSegment> KochSegment::Divide()
{
    double R = seg.p5.GetLength( seg.p2 );

    eGrowthDirection dir = GetDirection();

    if (dir == eGrowthDirection::INSIDE)
        seg.p4 = BasePoint( cos( ALFA ) * R, sin( ALFA ) * R, seg.p1.GetZ() ); 

    if (dir == eGrowthDirection::OUTSIDE)
        seg.p4 = BasePoint( cos( - ALFA ) * R, sin( - ALFA ) * R, seg.p1.GetZ() );

    std::vector<KochSegment> segs;

    segs.push_back( KochSegment( seg.p1, seg.p2 ) );
    segs.push_back( KochSegment( seg.p2, seg.p3 ) );
    segs.push_back( KochSegment( seg.p3, seg.p4 ) );
    segs.push_back( KochSegment( seg.p4, seg.p5 ) );

    return segs;
}


eGrowthDirection KochSegment::GetDirection() const
{
    return eGrowthDirection::INSIDE;
}