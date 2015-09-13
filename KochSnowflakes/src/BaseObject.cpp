#include "stdafx.h"
#include "BaseObject.h"


BaseObject::BaseObject()
    : is_visible( false )
{
}


BaseObject::~BaseObject()
{
}


void BaseObject::SetName( const std::string& name_str )
{
    name = name_str;
}


std::string BaseObject::GetName() const
{
    return name;
}


void BaseObject::SetVisible( bool is_visible_)
{
    is_visible = is_visible_;
}

bool BaseObject::IsVisible() const
{
    return  is_visible;
}