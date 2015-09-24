#include "stdafx.h"
#include "KochTriangle.h"



KochTriangle::KochTriangle( const KochSegment& s1, const KochSegment& s2, const KochSegment& s3 )
{
    versus.push_back( s1.GetBasePoints().p1 );
    versus.push_back( s2.GetBasePoints().p1 );
    versus.push_back( s3.GetBasePoints().p1 );

    segs.push_back( s1 );
    segs.push_back( s2 );
    segs.push_back( s3 );
    for (int i = 0; i < 3; i++)
        segs.at( i ).Divide();

    order_iteration = 0;
}


KochTriangle::KochTriangle( const BasePoint& p1, const BasePoint& p2, const BasePoint& p3 )
{
    versus.push_back( p1 );
    versus.push_back( p2 );
    versus.push_back( p3 );


    segs.push_back( KochSegment( p1, p2 ) );
    segs.push_back( KochSegment( p2, p3 ) );
    segs.push_back( KochSegment( p3, p1 ) );
    for (int i = 0; i < 3; i++)
        segs.at( i ).Divide();

    order_iteration = 0;
}
 

std::vector<KochTriangle> KochTriangle::GetCornerTriangles() const
{
    std::vector<KochTriangle> corner_segs;
    corner_segs.push_back( KochTriangle( segs.at( 0 ).GetUnitPoints().p4, segs.at( 1 ).GetUnitPoints().p1, segs.at( 1 ).GetUnitPoints().p2 ) );
    corner_segs.push_back( KochTriangle( segs.at( 1 ).GetUnitPoints().p4, segs.at( 2 ).GetUnitPoints().p1, segs.at( 2 ).GetUnitPoints().p2 ) );
    corner_segs.push_back( KochTriangle( segs.at( 2 ).GetUnitPoints().p4, segs.at( 0 ).GetUnitPoints().p1, segs.at( 0 ).GetUnitPoints().p2 ) );
    return corner_segs;
}

std::vector<KochTriangle> KochTriangle::GetIterTriangles()
{

    std::vector<KochTriangle> d_s = GetCornerTriangles();

    for (int i = 0; i < 3; i++)
    {
        KochUnitPoints pts = segs.at( i ).GetUnitPoints();
        d_s.push_back( KochTriangle( pts.p2, pts.p3, pts.p4 ) );
    }
    
    return d_s;
}

std::vector<KochSegment> KochTriangle::GetSegments() const
{
    return segs;
}