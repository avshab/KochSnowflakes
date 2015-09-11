#include "stdafx.h"
#include "BasePoint.h"
#include <cmath>


namespace PointConst
{
    const static int MAX_VALUE_MODULO = 20000000;
    const static double MAX_ERROR = 0.0001;
    const static int X_ID = 0;
    const static int Y_ID = 1;
    const static int Z_ID = 2;
}

using namespace PointConst;

BasePoint::BasePoint( double x_, double y_, double z_ )
    : x(x_)
    , y(y_)
    , z(z_)
    , is_visible( false )
{
    is_set[X_ID] = true; is_set[Y_ID] = true; is_set[Z_ID] = true;
}

BasePoint::BasePoint()
    : x( 0.0 )
    , y( 0.0 )
    , z( 0.0 )
    , is_visible( false )
{
    is_set[X_ID] = false; is_set[Y_ID] = false; is_set[Z_ID] = false;
}


bool  BasePoint::IsEqual( const BasePoint& p ) const
{
    if (abs( x - p.x ) > MAX_ERROR)
        return false;
    if (abs( y - p.y ) > MAX_ERROR)
        return false;
    if (abs( z - p.z ) > MAX_ERROR)
        return false;

    return true;
}

bool  BasePoint::IsOnesLine( const BasePoint& p1, const BasePoint& p2 ) const
{
    double d = (p2.GetX() - p1.GetX()) *(y - p1.GetY()) - (x - p1.GetX()) * (p2.GetY() - p1.GetY());
    if (d > 1)
        return false;

    return true;
}

double BasePoint::GetX() const
{
    return x;
}


double BasePoint::GetY() const
{
    return y;
}


double BasePoint::GetZ() const
{
    return z;
}

void BasePoint::SetX( double x_ )
{
    x = x_;
}


void BasePoint::SetY( double y_ )
{
    y = y_;
}


void BasePoint::SetZ( double z_ )
{
    z = z_;
}


bool BasePoint::IsSetX() const
{
    return is_set[X_ID];
}


bool BasePoint::IsSetY() const
{
    return is_set[Y_ID];
}


bool BasePoint::IsSetZ() const
{
    return is_set[Z_ID];
}


bool BasePoint::IsValid() const
{
    if (!is_set)
        return false;

    if (abs( x ) > MAX_VALUE_MODULO)
        return false;

    if (abs( y ) > MAX_VALUE_MODULO)
        return false;

    if (abs( z ) > MAX_VALUE_MODULO)
        return false;

    return true;
}


double BasePoint::GetLength( const BasePoint& p ) const
{
    return sqrt( (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z) );
}

void BasePoint::SetName( const std::string& name_str )
{
    name = name_str;
}

std::string BasePoint::GetName() const
{
    return name;
}

bool BasePoint::IsVisible() const
{
    return is_visible;
}


void BasePoint::SetVisible( bool is_visible_ )
{
    is_visible = is_visible_;
}