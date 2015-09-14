#pragma once
#include "BaseSegment.h"

#include<vector>


enum eGrowthDirection
{
    OUTSIDE,
    INSIDE
};

struct KochUnitSegment
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

    KochSegment();

    std::vector<KochSegment> Divide();

private:

    eGrowthDirection GetDirection() const;

private:

    std::string name;

    bool is_visible;

    KochUnitSegment seg;

    BasePoint GetMiddlePoint( const BasePoint& p1, const BasePoint& p2, double k ) const;
};