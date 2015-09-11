#pragma once
#include "Styles.h"  
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
{
public:

    CoordinatesPoint( const PointPos& pos, const std::string& name, bool is_visible );

    CoordinatesPoint();

    void SetPos( const PointPos& pos );

    void SetName( const std::string& name );

    void SetVisible( bool is_visible );

    void SetColor( Color coor );

    bool IsVisible( bool is_visible );

    PointPos GetPos() const;

    std::string GetName() const;

    bool GetVisible() const;

    Color GetColor() const;

private:

    PointPos pos;

    std::string name;

    bool is_visible;

    Color color;
};
