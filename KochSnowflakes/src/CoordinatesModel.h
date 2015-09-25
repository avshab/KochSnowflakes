#pragma once
#include "Styles.h" 
#include "CoordinatesObject.h" 
#include <map>
#include <vector>


enum eModelObjectType
{
	BASE_POINT,
	BASE_SEGMENT,
    BASE_POLYGON
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

	void AddObjectsVector(const eModelObjectType& type, const std::vector<CoordinatesObject*>& objs);

	void AddObject(const eModelObjectType& type, CoordinatesObject* objs);

	void SetObjectMap(const std::map<eModelObjectType, std::vector<CoordinatesObject*>>& map);

	std::map<eModelObjectType, std::vector<CoordinatesObject*>> GetObjectMap() const;

    CoordinatesModel GetModel();

    void Clear( const eModelObjectType& type );

protected:

	std::string name;

	std::map<eModelObjectType, std::vector<CoordinatesObject*>> obj_map;
};