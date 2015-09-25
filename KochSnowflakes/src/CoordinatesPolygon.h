#pragma once
#include "CoordinatesSegment.h"
#include <vector>


class CoordinatesPolygon 
    : public CoordinatesObject
{
public:

    CoordinatesPolygon();

    CoordinatesPolygon( std::vector<CoordinatesPoint>& pts, const std::string& name_, bool is_visible_ );

	virtual ~CoordinatesPolygon(){};

    void SetCoordinates( std::vector<CoordinatesPoint>& pts );

    std::vector<CoordinatesPoint> GetCoordinates() const;

    int pts_size;

private:

    std::vector<CoordinatesPoint> versus;
};
