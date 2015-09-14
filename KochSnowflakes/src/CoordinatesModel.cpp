#include "stdafx.h"
#include "CoordinatesModel.h"
#include "CoordinatesPoint.h"


CoordinatesModel::CoordinatesModel()
{
	std::vector<ModelObject*> v;
	obj_map[eModelObjectType::BASE_POINT] = v;
	obj_map[eModelObjectType::BASE_SEGMENT] = v;
}


CoordinatesModel::~CoordinatesModel()
{
    Clear();
}


bool CoordinatesModel::IsEmpty() const
{
	if (!obj_map.empty())
        return false;

    return true;
}


void CoordinatesModel::Clear()
{
    for (auto it = begin( obj_map.at( eModelObjectType::BASE_POINT ) ); it != end( obj_map.at( eModelObjectType::BASE_POINT ) ); it++)
        delete *it;
    obj_map.at( eModelObjectType::BASE_POINT ).clear();
    obj_map.at( eModelObjectType::BASE_SEGMENT ).clear();
}


void CoordinatesModel::SetModelName( const std::string& name_ )
{
    name = name_;
}


std::string CoordinatesModel::GetModelName() const
{
    return name;
}


void CoordinatesModel::AddObjectsVector(const eModelObjectType& type, const std::vector<ModelObject*>& objs)
{
	for (auto it = begin(objs); it != end(objs); it++)
		obj_map.at(type).push_back(*it);
}


void CoordinatesModel::AddObject(const eModelObjectType& type, ModelObject* objs)
{

	obj_map.at(type).push_back(objs);
}


void CoordinatesModel::SetObjectMap(const std::map<eModelObjectType, std::vector<ModelObject*>>& map)
{
	obj_map = map;
}

std::map<eModelObjectType, std::vector<ModelObject*>> CoordinatesModel::GetObjectMap() const
{
	return obj_map;
}



CoordinatesModel CoordinatesModel::GetModel()
{
    return *this;
}



