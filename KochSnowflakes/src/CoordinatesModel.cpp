#include "stdafx.h"
#include "CoordinatesModel.h"
#include "CoordinatesPoint.h"


CoordinatesModel::CoordinatesModel()
{
	std::vector<CoordinatesObject*> v;
	obj_map[eModelObjectType::BASE_POINT] = v;
	obj_map[eModelObjectType::BASE_SEGMENT] = v;
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


void CoordinatesModel::Clear()
{
    for (int i = 0; i < obj_map.at( eModelObjectType::BASE_POINT ).size(); i++)
        delete[] obj_map.at( eModelObjectType::BASE_POINT ).at( i );
    for (int i = 0; i < obj_map.at( eModelObjectType::BASE_SEGMENT ).size(); i++)
		delete[] obj_map.at(eModelObjectType::BASE_SEGMENT).at(i);


    obj_map.at( eModelObjectType::BASE_SEGMENT ).clear();
	obj_map.at(eModelObjectType::BASE_SEGMENT).shrink_to_fit();
	obj_map.at( eModelObjectType::BASE_POINT ).clear();
	obj_map.at(eModelObjectType::BASE_POINT).shrink_to_fit();
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



