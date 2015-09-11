#include "stdafx.h"
#include "BasePoint.h"
#include <cmath>


BasePoint::BasePoint( double x_, double y_, double z_ )
    : x(x_)
    , y(y_)
    , z(z_)
    , x_set( true )
    , y_set( true )
    , z_set( true )
    , is_vertix( false )
    , is_visible( false )
{
}

BasePoint::BasePoint()
    : x( 0.0 )
    , y( 0.0 )
    , z( 0.0 )
    , x_set( false )
    , y_set( false )                          
    , z_set( false )
    , is_vertix( false )
    , is_visible( false )
{
}


bool  BasePoint::IsEqual( const BasePoint& p ) const
{
    if (abs(x - p.x) > 0.05)
        return false;
    if (abs(y - p.y) > 0.05)
        return false;
    if (abs(z - p.z) > 0.05)
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
    x_set = true;
}


void BasePoint::SetY( double y_ )
{
    y = y_;
    y_set = true;
}


void BasePoint::SetZ( double z_ )
{
    z = z_;
    z_set = true;
}


bool BasePoint::IsSetX() const
{
    return x_set;
}


bool BasePoint::IsSetY() const
{
    return y_set;
}


bool BasePoint::IsSetZ() const
{
    return z_set;
}


bool BasePoint::IsValid() const
{
    if (!x_set || !y_set || !z_set)
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

int BasePoint::GetIndex()
{
    std::string index_str = name.substr( 1 );
    return atoi( index_str.c_str() );
}


bool BasePoint::IsVisible() const
{
    return is_visible;
}


void BasePoint::SetVisible( bool is_visible_ )
{
    is_visible = is_visible_;
}


bool BasePoint::IsVertix() const
{
    return is_vertix;
}


void BasePoint::SetVertix( bool is_vertix_ )
{
    is_vertix = is_vertix_;
}