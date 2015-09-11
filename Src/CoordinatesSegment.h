#pragma once  
#include "CoordinatesPoint.h" 
#include <vector>


struct SegmentPoints
{
    SegmentPoints( const CoordinatesPoint& c1_, const CoordinatesPoint& c2_ )
        : c1(c1_), c2(c2_){};

    SegmentPoints(){};

    CoordinatesPoint c1;

    CoordinatesPoint c2;
};


class CoordinatesSegment
{
public:

    CoordinatesSegment( const SegmentPoints& pts, const std::string& name, bool is_visible );

    CoordinatesSegment();

    void SetPoints( const SegmentPoints& pts );

    void SetName( const std::string& name );

    void SetVisible( bool is_visible );

    bool IsVisible( bool is_visible );

    SegmentPoints GetPoints() const;

    std::string GetName() const;

    bool GetVisible() const;

private:

    std::string name;

    bool is_visible;

    SegmentPoints pts;
};


