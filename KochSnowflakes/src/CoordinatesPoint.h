#pragma once
#include "Styles.h"  
#include "ModelObject.h"  
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
	: public ModelObject
{
public:

    CoordinatesPoint( const PointPos& pos, const std::string& name, bool is_visible );

    CoordinatesPoint();

    void SetPos( const PointPos& pos );

    void SetColor( Color coor );

    PointPos GetPos() const;

    Color GetColor() const;

private:

    PointPos pos;

    std::string name;

    bool is_visible;

    Color color;
};
