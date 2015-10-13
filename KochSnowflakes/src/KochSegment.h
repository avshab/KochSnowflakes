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

struct KochPolygon
{
    std::vector<BasePoint> s_pts;
    Color s_color;
};

class KochSegment :
    public BaseSegment
{
public:

    KochSegment( const BasePoint& p1, const BasePoint& p2, int iter_rder );

    KochSegment( const BaseSegment& s, int iter_rder );

    KochSegment();

    std::vector<KochSegment> Divide( eGrowthDirection = eGrowthDirection::OUTSIDE );

    std::vector<KochSegment> GetChilds( eGrowthDirection = eGrowthDirection::OUTSIDE );

    BasePoint GetPointIsosTriangle( eGrowthDirection = eGrowthDirection::OUTSIDE ) ;

    KochUnitPoints GetUnitPoints() const;    
    
    void SetColor( Color color );

    Color GetColor() const;

    KochPolygon GetPaintPolygon();


private:

    eGrowthDirection GetDirection() const;

    void SetIteration( int order );

private:

    std::string name;

    bool is_visible;

    KochUnitPoints seg;    

    BasePoint opposite_point;

    int iter_order;

    bool was_iterating;

    std::vector<KochSegment> childs;

    Color color;

    KochPolygon paint_pols;
};