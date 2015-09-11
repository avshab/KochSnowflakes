#include "stdafx.h"
#include "CoordinatesFace.h"


CoordinatesFace::CoordinatesFace()
{

}


void CoordinatesFace::SetName( const std::string& name_ )
{
    name = name_;
}


void CoordinatesFace::SetVisible( bool is_visible_ )
{
    is_visible = is_visible_;
}


std::string CoordinatesFace::GetName() const
{
    return name;
}


bool CoordinatesFace::GetVisible() const
{
    return is_visible;
}