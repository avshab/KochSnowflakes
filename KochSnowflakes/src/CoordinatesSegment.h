#pragma once  
#include "CoordinatesPoint.h" 
#include <vector>


struct SegmentCoordPoints
{
    SegmentCoordPoints( const CoordinatesPoint& c1_, const CoordinatesPoint& c2_ )
        : c1(c1_), c2(c2_){};

    SegmentCoordPoints(){};

    CoordinatesPoint c1;

    CoordinatesPoint c2;
};


class CoordinatesSegment
	: public ModelObject
{
public:

    CoordinatesSegment( const SegmentCoordPoints& pts, const std::string& name, bool is_visible );

    CoordinatesSegment();

    void SetPoints( const SegmentCoordPoints& pts );

    SegmentCoordPoints GetPoints() const;

private:

    std::string name;

    bool is_visible;

    SegmentCoordPoints pts;
};


