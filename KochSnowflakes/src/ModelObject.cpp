#include "stdafx.h"
#include "ModelObject.h"


ModelObject::ModelObject()
    : is_visible( false )
{
}


ModelObject::~ModelObject()
{
}


void ModelObject::SetName(const std::string& name_str)
{
    name = name_str;
}


std::string ModelObject::GetName() const
{
    return name;
}


void ModelObject::SetVisible(bool is_visible_)
{
    is_visible = is_visible_;
}


bool ModelObject::IsVisible() const
{
    return  is_visible;
}