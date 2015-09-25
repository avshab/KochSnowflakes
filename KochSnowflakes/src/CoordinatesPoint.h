#pragma once 
#include "CoordinatesObject.h"  
#include <vector>


struct PointPos
{
    PointPos( int x_, int y_ )
        : x( x_ ), y( y_ ){};

    PointPos(){};

    int x;

    int y;
};


class CoordinatesPoint
	: public CoordinatesObject
{
public:

    CoordinatesPoint( const PointPos& pos, const std::string& name, bool is_visible );

    CoordinatesPoint();

    void SetPos( const PointPos& pos );

    PointPos GetPos() const;

private:

    PointPos pos;

    std::string name;

    bool is_visible;

};
