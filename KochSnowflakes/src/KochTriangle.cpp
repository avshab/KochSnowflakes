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
    if (segs.at( 0 ).GetLength() < 2)
        iter_order = 15;
    SetCentralPoint();
}


KochTriangle::KochTriangle( const BasePoint& p1, const BasePoint& p2, const BasePoint& p3, int iter_order_ )
{
    versus.push_back( p1 );
    versus.push_back( p2 );
    versus.push_back( p3 );


    segs.push_back( KochSegment( p1, p2, 0 ) );
    segs.push_back( KochSegment( p2, p3, 0 ) );
    segs.push_back( KochSegment( p3, p1, 0 ) );
    for (int i = 0; i < 3; i++)
        segs.at( i ).Divide();

    was_iterating = false;
    iter_order = ++iter_order_;
    if (segs.at( 0 ).GetLength() < 2)
        iter_order = 15;

    SetCentralPoint();
}

BasePoint GetPointIntoSeg( BasePoint p1, BasePoint p2, double k )
{
    return BasePoint( p1.GetX() + (p2.GetX() - p1.GetX()) * k, p1.GetY() + (p2.GetY() - p1.GetY()) * k, p1.GetZ() + (p2.GetZ() - p1.GetZ()) * k );
}

void KochTriangle::SetCentralPoint()
{
    BasePoint pc = GetPointIntoSeg( segs.at( 0 ).GetUnitPoints().p5, segs.at( 0 ).GetUnitPoints().p1, 0.5 );
    central_point = GetPointIntoSeg( segs.at( 2 ).GetUnitPoints().p1, pc, 2.0/3.0 );
}

void KochTriangle::SetChildsTriangles()
{
    std::vector<KochTriangle> cur_tri;
    cur_tri.push_back( KochTriangle( segs.at( 2 ).GetUnitPoints().p4, segs.at( 0 ).GetUnitPoints().p1, segs.at( 0 ).GetUnitPoints().p2, iter_order ) );
    cur_tri.push_back( KochTriangle( segs.at( 0 ).GetUnitPoints().p2, segs.at( 0 ).GetUnitPoints().p3, segs.at( 0 ).GetUnitPoints().p4, iter_order ) );
    cur_tri.push_back( KochTriangle( segs.at( 0 ).GetUnitPoints().p4, segs.at( 1 ).GetUnitPoints().p1, segs.at( 1 ).GetUnitPoints().p2, iter_order ) );
    cur_tri.push_back( KochTriangle( segs.at( 1 ).GetUnitPoints().p2, segs.at( 1 ).GetUnitPoints().p3, segs.at( 1 ).GetUnitPoints().p4, iter_order ) );
    cur_tri.push_back( KochTriangle( segs.at( 1 ).GetUnitPoints().p4, segs.at( 2 ).GetUnitPoints().p1, segs.at( 2 ).GetUnitPoints().p2, iter_order ) );
    cur_tri.push_back( KochTriangle( segs.at( 2 ).GetUnitPoints().p2, segs.at( 2 ).GetUnitPoints().p3, segs.at( 2 ).GetUnitPoints().p4, iter_order ) );
    
    int j = rand.GetRandomNumber( 6 );
    for (int i = 0; i < 6; i++, j++)
    { 
        if (j == 6)
            j = 0;
        childs.push_back( cur_tri.at( j ) );
    }

    int variable = 1;
    if ( variable == 0 )
    { 
        j = rand.GetRandomNumber( 2 );
        if (j == 0)
            childs.push_back( KochTriangle( segs.at( 0 ).GetUnitPoints().p2, segs.at( 1 ).GetUnitPoints().p2, segs.at( 2 ).GetUnitPoints().p2, iter_order ) );
        else if (j == 1)
            childs.push_back( KochTriangle( segs.at( 0 ).GetUnitPoints().p4, segs.at( 1 ).GetUnitPoints().p4, segs.at( 2 ).GetUnitPoints().p4, iter_order ) );  
    }
    
    if (variable == 1)
    {
        childs.push_back( KochTriangle( segs.at( 0 ).GetUnitPoints().p4, segs.at( 1 ).GetUnitPoints().p2, central_point, iter_order ) );
        childs.push_back( KochTriangle( segs.at( 1 ).GetUnitPoints().p4, segs.at( 2 ).GetUnitPoints().p2, central_point, iter_order ) );
        childs.push_back( KochTriangle( segs.at( 2 ).GetUnitPoints().p4, segs.at( 0 ).GetUnitPoints().p2, central_point, iter_order ) );
    }
}


std::vector<KochTriangle> KochTriangle::GetIterTriangles()
{   
    
    std::vector<KochTriangle> cur_tris;

    if (was_iterating == false)
    {
        SetChildsTriangles();

        was_iterating = true;
        for (int i = 0; i < childs.size(); i++)
        {   
            childs.at(i).SetColor( rand.GetRandomColor( color, iter_order, i ) );
            if (i != 6)
                cur_tris.push_back( childs.at( i ) );
        }

        return childs;
    }

    

    if (iter_order >= 15)
        return cur_tris;

    int counter = 0;
    while (counter < 10)
    {
        int num = rand.GetRandomNumber( 2 );      
        if (iter_order > 2)
            num += 5;

        cur_tris = childs.at( num ).GetIterTriangles();
        KochTriangle tri = childs.at( num );
        if (!cur_tris.empty())
        { 
            childs.erase( childs.begin() + num );
            childs.push_back( tri );
            return  cur_tris;
        }

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
    if (was_iterating == false)
        return versus;
    if (was_iterating != false)
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