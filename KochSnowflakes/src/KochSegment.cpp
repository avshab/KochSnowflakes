#include "stdafx.h"
#include "KochSegment.h"
#include "RandomAS.h"

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


KochSegment::KochSegment( const BasePoint& p1_, const BasePoint& p2_, int iter_order_ )
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
    iter_order = ++iter_order_;
    was_iterating = false;
}


KochSegment::KochSegment( const BaseSegment& s, int iter_order_ )
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
    iter_order = ++iter_order_;
    was_iterating = false;
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


std::vector<KochSegment> KochSegment::GetChilds( eGrowthDirection dir )
{
    if (!childs.empty())
        return childs;
    
    seg.p3 = KochSegment( seg.p2, seg.p4, 0 ).GetPointIsosTriangle( dir );

    childs.push_back( KochSegment( seg.p1, seg.p2, iter_order ) );
    childs.push_back( KochSegment( seg.p2, seg.p3, iter_order ) );
    childs.push_back( KochSegment( seg.p3, seg.p4, iter_order ) );      
    childs.push_back( KochSegment( seg.p4, seg.p2, iter_order ) );
    childs.push_back( KochSegment( seg.p4, seg.p5, iter_order ) );


    was_iterating = true;
    for (int i = 0; i < childs.size(); i++)
        childs.at( i ).SetColor( color );
    return childs;
}


std::vector<KochSegment> KochSegment::Divide( eGrowthDirection dir )
{   
    if (was_iterating == false)
        return GetChilds();

    std::vector<KochSegment> cur_segs;

    if (iter_order >= 10)
        return cur_segs;

    RandomAS rand;
    for (int i = 0; i < 5; i++)
    {
        std::vector<KochSegment> cur_segs_ = childs.at( i ).Divide();
        if (!cur_segs_.empty())
        {
            for (int j = 0; j < cur_segs_.size(); j++)
                cur_segs.push_back( cur_segs_.at( j ) );
        }
    }
    return  cur_segs;
}


void KochSegment::SetIteration( int order )
{
    iter_order = order;
}


eGrowthDirection KochSegment::GetDirection() const
{
    int y = rand();

    if(y % 2 == 0.0)     
        return eGrowthDirection::INSIDE;
    return eGrowthDirection::OUTSIDE;
}


KochPolygon KochSegment::GetPaintPolygon()
{
    KochPolygon po;
    if (childs.empty())
        return po;

    if (childs.at( 0 ).childs.empty())
        return po;
    if (childs.size() > 5)
        int d = 8;

    for (int i = 1; i < 4; i++)
    {
        std::vector<KochSegment> chl = childs.at( i ).GetChilds( eGrowthDirection::OUTSIDE );
        for (int i = 0; i < chl.size(); i++)
            po.s_pts.push_back( BasePoint( chl.at( i ).GetBasePoints().p1 ) );

    }
    return po;
}
