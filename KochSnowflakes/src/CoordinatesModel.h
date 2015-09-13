#pragma once
#include "Styles.h" 
#include "ModelObject.h" 
#include <map>
#include <vector>


enum eModelObjectType
{
	BASE_POINT,
	BASE_SEGMENT
};

class CoordinatesModel
{
public:

	CoordinatesModel();

	virtual ~CoordinatesModel();

public:

	virtual bool IsEmpty() const;

	void SetModelName(const std::string& name);

	std::string GetModelName() const;

	void AddObjectsVector(const eModelObjectType& type, const std::vector<ModelObject*>& objs);

	void AddObject(const eModelObjectType& type, ModelObject* objs);

	void SetObjectMap(const std::map<eModelObjectType, std::vector<ModelObject*>>& map);

	std::map<eModelObjectType, std::vector<ModelObject*>> GetObjectMap() const;

protected:

	std::string name;

	std::map<eModelObjectType, std::vector<ModelObject*>> obj_map;
};