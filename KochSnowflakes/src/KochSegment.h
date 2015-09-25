#pragma once
#include "BaseSegment.h"
#include "CoordinatesObject.h"

#include<vector>


enum eGrowthDirection
{
    OUTSIDE,
    INSIDE
};

struct KochUnitPoints
{
    BasePoint p1;
    BasePoint p2;
    BasePoint p3;
    BasePoint p4;
    BasePoint p5;
};


class KochSegment :
    public BaseSegment
{
public:

    KochSegment( const BasePoint& p1, const BasePoint& p2 );

    KochSegment( const BaseSegment& s );

    KochSegment();

    std::vector<KochSegment> Divide( eGrowthDirection = eGrowthDirection::OUTSIDE );

    BasePoint GetPointIsosTriangle( eGrowthDirection = eGrowthDirection::OUTSIDE ) ;

    KochUnitPoints GetUnitPoints() const;    
    
    void SetColor( Color color );

    Color GetColor() const;

private:

    eGrowthDirection GetDirection() const;

    void SetIteration( int order );

private:

    std::string name;

    bool is_visible;

    KochUnitPoints seg;    

    BasePoint opposite_point;

    int order_iteration;

    Color color;
};