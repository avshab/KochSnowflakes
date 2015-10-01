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

    childs.push_back( KochTriangle( segs.at( 2 ).GetUnitPoints().p4, segs.at( 0 ).GetUnitPoints().p1, segs.at( 0 ).GetUnitPoints().p2, iter_order ));
    childs.push_back( KochTriangle( segs.at( 0 ).GetUnitPoints().p2, segs.at( 0 ).GetUnitPoints().p3, segs.at( 0 ).GetUnitPoints().p4, iter_order ));
    childs.push_back( KochTriangle( segs.at( 0 ).GetUnitPoints().p4, segs.at( 1 ).GetUnitPoints().p1, segs.at( 1 ).GetUnitPoints().p2, iter_order ));
    childs.push_back( KochTriangle( segs.at( 1 ).GetUnitPoints().p2, segs.at( 1 ).GetUnitPoints().p3, segs.at( 1 ).GetUnitPoints().p4, iter_order ));
    childs.push_back( KochTriangle( segs.at( 1 ).GetUnitPoints().p4, segs.at( 2 ).GetUnitPoints().p1, segs.at( 2 ).GetUnitPoints().p2, iter_order ));
    childs.push_back( KochTriangle( segs.at( 2 ).GetUnitPoints().p2, segs.at( 2 ).GetUnitPoints().p3, segs.at( 2 ).GetUnitPoints().p4, iter_order ));
    
    
    
    

   childs.push_back(KochTriangle( segs.at( 0 ).GetUnitPoints().p2, segs.at( 1 ).GetUnitPoints().p2, segs.at( 2 ).GetUnitPoints().p2, iter_order ));
    //childs.push_back(KochTriangle( segs.at( 0 ).GetUnitPoints().p4, segs.at( 1 ).GetUnitPoints().p4, segs.at( 2 ).GetUnitPoints().p4, iter_order ));

    //for (int i = 0; i < 3; i++)
    //{  
    //    KochUnitPoints pts = segs.at( i ).GetUnitPoints();    
    //    childs.push_back( KochTriangle( pts.p2, pts.p3, pts.p4, iter_order ) );
    //}
   
}

std::vector<KochTriangle> KochTriangle::GetIterTriangles()
{   
    
    std::vector<KochTriangle> cur_tris;

    if (was_iterating == false)
    {
        SetChildsTriangles();

        was_iterating = true;
        for (int i = 0; i < 7; i++)
        {   
            childs.at(i).SetColor( rand.GetRandomColor( color, iter_order, i ) );
            if (i != 6)
                cur_tris.push_back( childs.at( i ) );
        }

        return cur_tris;
    }

    

    if (iter_order > 8)
        return cur_tris;

    int counter = 0;
    while (counter < 10)
    {
        int num = rand.GetRandomNumber( 5 );      
        
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