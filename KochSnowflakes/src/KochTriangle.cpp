#include "stdafx.h"
#include "KochTriangle.h"
#include "RandomAS.h"


KochTriangle::KochTriangle( const KochSegment& s1, const KochSegment& s2, const KochSegment& s3, int iter_order_ )
{
    versus.push_back( s1.GetBasePoints().p1 );
    versus.push_back( s2.GetBasePoints().p1 );
    versus.push_back( s3.GetBasePoints().p1 );

    segs.push_back( s1 );
    segs.push_back( s2 );
    segs.push_back( s3 );
    for (int i = 0; i < 3; i++)
        segs.at( i ).Divide();

    was_iterating = false;
    iter_order = ++iter_order_;
    if (segs.at( 0 ).GetLength() < 1)
        iter_order = 10;
}


KochTriangle::KochTriangle( const BasePoint& p1, const BasePoint& p2, const BasePoint& p3, int iter_order_ )
{
    versus.push_back( p1 );
    versus.push_back( p2 );
    versus.push_back( p3 );


    segs.push_back( KochSegment( p1, p2 ) );
    segs.push_back( KochSegment( p2, p3 ) );
    segs.push_back( KochSegment( p3, p1 ) );
    for (int i = 0; i < 3; i++)
        segs.at( i ).Divide();

    was_iterating = false;
    iter_order = ++iter_order_;
    if (segs.at( 0 ).GetLength() < 1)
        iter_order = 10;
}
 

void KochTriangle::SetChildsTriangles()
{

    childs[0] = KochTriangle( segs.at( 0 ).GetUnitPoints().p4, segs.at( 1 ).GetUnitPoints().p1, segs.at( 1 ).GetUnitPoints().p2, iter_order );
    childs[1] = KochTriangle( segs.at( 1 ).GetUnitPoints().p4, segs.at( 2 ).GetUnitPoints().p1, segs.at( 2 ).GetUnitPoints().p2, iter_order );
    childs[2] = KochTriangle( segs.at( 2 ).GetUnitPoints().p4, segs.at( 0 ).GetUnitPoints().p1, segs.at( 0 ).GetUnitPoints().p2, iter_order );
                                                                                                                                         
    childs[3] = KochTriangle( segs.at( 0 ).GetUnitPoints().p2, segs.at( 1 ).GetUnitPoints().p2, segs.at( 2 ).GetUnitPoints().p2, iter_order );
    childs[4] = KochTriangle( segs.at( 0 ).GetUnitPoints().p4, segs.at( 1 ).GetUnitPoints().p4, segs.at( 2 ).GetUnitPoints().p4, iter_order );

    for (int i = 0; i < 3; i++)
    {  
        KochUnitPoints pts = segs.at( i ).GetUnitPoints();                                                                
        childs[i + 5] = KochTriangle( pts.p2, pts.p3, pts.p4, iter_order );
    }
   
}

std::vector<KochTriangle> KochTriangle::GetIterTriangles()
{   
    
    std::vector<KochTriangle> cur_tris;

    if (was_iterating == false)
    {
        SetChildsTriangles();

        was_iterating = true;
        for (auto it = begin( childs ); it != end( childs ); it++)
        {   
            it->second.SetColor( rand.GetRandomColor( color ) );
            cur_tris.push_back( it->second );
        }

        return cur_tris;
    }

    

    if (iter_order > 7)
        return cur_tris;

    int counter = 0;
    while (cur_tris.empty())
    {
        int num = rand.GetRandomNumber( 5 );      
        KochTriangle tri = childs.at( num );
        cur_tris = childs.at( num ).GetIterTriangles();
        
       
        if (counter > 10)
            break;
        counter++;
    }
    
    return  cur_tris;
}

std::vector<KochSegment> KochTriangle::GetSegments() const
{
    return segs;
}

KochTriangle KochTriangle::GetInternalTriangle() const
{
    return KochTriangle( segs.at( 0 ).GetUnitPoints().p2, segs.at( 1 ).GetUnitPoints().p2, segs.at( 2 ).GetUnitPoints().p2, iter_order );
}


std::vector<BasePoint> KochTriangle::GetPoints() const
{
    return versus;
}

void KochTriangle::SetColor( Color c )
{
    color = c;
}

Color KochTriangle::GetColor() const
{
    return color;
}