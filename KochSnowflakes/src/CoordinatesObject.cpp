#include "stdafx.h"
#include "CoordinatesObject.h"


CoordinatesObject::CoordinatesObject()
    : is_visible( false )
{
}


CoordinatesObject::~CoordinatesObject()
{
}


void CoordinatesObject::SetName(const std::string& name_str)
{
    name = name_str;
}


std::string CoordinatesObject::GetName() const
{
    return name;
}


void CoordinatesObject::SetVisible(bool is_visible_)
{
    is_visible = is_visible_;
}


bool CoordinatesObject::IsVisible() const
{
    return  is_visible;
}


void CoordinatesObject::SetColor( Color color_ )
{
    color = color_;
}


Color CoordinatesObject::GetColor() const
{
    return color;
}