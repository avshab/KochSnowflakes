#pragma once
#include "KochSegment.h"
#include "RandomAS.h"
#include <map>


class KochTriangle
{
public:

    KochTriangle( const KochSegment& s1, const KochSegment& s2, const KochSegment& s3, int iter_order );

    KochTriangle( const BasePoint& p1, const BasePoint& p2, const BasePoint& p3, int iter_order );

    KochTriangle(){};

    std::vector<BasePoint> GetPoints() const;

    std::vector<KochSegment> GetSegments() const;

    std::vector<KochTriangle> GetIterTriangles();     

    KochTriangle GetInternalTriangle() const;

    void SetColor( Color color );

    Color GetColor() const;

private:

    void SetChildsTriangles();

    Color color;

    std::vector<BasePoint> versus;

    std::vector<KochSegment> segs;

    std::map<int, KochTriangle> childs;

    bool was_iterating;

    int iter_order;

    RandomAS rand;
};