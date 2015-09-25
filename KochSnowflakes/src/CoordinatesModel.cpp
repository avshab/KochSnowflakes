#include "stdafx.h"
#include "CoordinatesModel.h"
#include "CoordinatesPoint.h"


CoordinatesModel::CoordinatesModel()
{
	std::vector<CoordinatesObject*> v;
	obj_map[eModelObjectType::BASE_POINT] = v;
	obj_map[eModelObjectType::BASE_SEGMENT] = v;
    obj_map[eModelObjectType::BASE_POLYGON] = v;
}


CoordinatesModel::~CoordinatesModel()
{
}


bool CoordinatesModel::IsEmpty() const
{
	if (!obj_map.empty())
        return false;

    return true;
}


void CoordinatesModel::Clear( const eModelObjectType& type )
{
    for (int i = 0; i < obj_map.at( type ).size(); i++)
        delete[] obj_map.at( type ).at( i );

    obj_map.at( type ).clear();
    obj_map.at( type ).shrink_to_fit();
}


void CoordinatesModel::SetModelName( const std::string& name_ )
{
    name = name_;
}


std::string CoordinatesModel::GetModelName() const
{
    return name;
}


void CoordinatesModel::AddObjectsVector(const eModelObjectType& type, const std::vector<CoordinatesObject*>& objs)
{
	for (auto it = begin(objs); it != end(objs); it++)
		obj_map.at(type).push_back(*it);
}


void CoordinatesModel::AddObject(const eModelObjectType& type, CoordinatesObject* objs)
{

	obj_map.at(type).push_back(objs);
}


void CoordinatesModel::SetObjectMap(const std::map<eModelObjectType, std::vector<CoordinatesObject*>>& map)
{
	obj_map = map;
}

std::map<eModelObjectType, std::vector<CoordinatesObject*>> CoordinatesModel::GetObjectMap() const
{
	return obj_map;
}



CoordinatesModel CoordinatesModel::GetModel()
{
    return *this;
}



