#pragma once
#include "KochSegment.h"


class KochTriangle
{
public:

    KochTriangle( const KochSegment& s1, const KochSegment& s2, const KochSegment& s3 );

    KochTriangle( const BasePoint& p1, const BasePoint& p2, const BasePoint& p3 );

    std::vector<KochSegment> GetSegments() const;

    std::vector<KochTriangle> GetIterTriangles();

private:
    std::vector<KochTriangle> GetCornerTriangles() const;

    std::vector<BasePoint> versus;

    std::vector<KochSegment> segs;

    int order_iteration;
};