#include "stdafx.h"
#include "KochSegment.h"

#include <cmath>

namespace
{
    const static double COEF = 1.0 / 3.0;
    const static double ALFA = 60.0 * 3.14159265 / 180.0;
}



KochSegment::KochSegment( const BasePoint& p1_, const BasePoint& p2_ )
	: BaseSegment(p1_,p2_)
{
    seg.p1 = p1_;
    seg.p1.SetZ( 0.0 );
    seg.p5 = p2_; 
    seg.p5.SetZ( 0.0 );
    double k = 1.0 / 3.0;
    seg.p2 = GetMiddlePoint( seg.p1, seg.p5, k );
    seg.p4 = GetMiddlePoint( seg.p5, seg.p1, k );
    l = seg.p1.GetLength( seg.p5 );
}
 

KochSegment::KochSegment()
{
  
}


double KochSegment::GetLength() const
{
    return l;
}


BasePoint KochSegment::GetMiddlePoint( const BasePoint& p1_, const BasePoint& p2_, double k ) const
{
    BasePoint pad( p1_.GetX() + (p2_.GetX() - p1_.GetX()) * k, p1_.GetY() + (p2_.GetY() - p1_.GetY()) * k, p1_.GetZ() + (p2_.GetZ() - p1_.GetZ())  * k );
    return BasePoint( p1_.GetX() + (p2_.GetX() - p1_.GetX()) * k, p1_.GetY() + ( p2_.GetY() - p1_.GetY() ) * k, p1_.GetZ() + ( p2_.GetZ() - p1_.GetZ() )  * k);
}


std::vector<KochSegment> KochSegment::Divide()
{
    double R = seg.p2.GetLength( seg.p4 );

    eGrowthDirection dir = GetDirection();

    BasePoint b = GetMiddlePoint( seg.p2, seg.p4, 0.5 );

    double alfa; 

     if (dir == eGrowthDirection::INSIDE)
         alfa = ALFA;

    if (dir == eGrowthDirection::OUTSIDE)
        alfa = -ALFA;

    double Bx = cos( alfa ) * (seg.p4.GetX() - seg.p2.GetX()) - sin( alfa ) * (seg.p4.GetY() - seg.p2.GetY());
    double By = sin( alfa ) * (seg.p4.GetX() - seg.p2.GetX()) + cos( alfa ) * (seg.p4.GetY() - seg.p2.GetY());
   
    seg.p3 = BasePoint( seg.p2.GetX() + Bx, seg.p2.GetY() + By, seg.p1.GetZ() );

    std::vector<KochSegment> segs;

    segs.push_back( KochSegment( seg.p1, seg.p2 ) );
    segs.push_back( KochSegment( seg.p2, seg.p3 ) );
    segs.push_back( KochSegment( seg.p3, seg.p4 ) );
    segs.push_back( KochSegment( seg.p4, seg.p5 ) );

    return segs;
}


eGrowthDirection KochSegment::GetDirection() const
{
    int y = rand();

    if(y % 2 == 0.0)     
        return eGrowthDirection::INSIDE;
    return eGrowthDirection::OUTSIDE;
}