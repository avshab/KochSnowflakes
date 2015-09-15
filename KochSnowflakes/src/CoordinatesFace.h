#pragma once
#include "BaseObject.h"
#include "CoordinatesSegment.h"
#include <vector>


class CoordinatesFace 
	: public BaseObject
{
public:

    CoordinatesFace();

	virtual ~CoordinatesFace(){};

    void SetName( const std::string& name );

    void SetVisible( bool is_visible );

    bool IsVisible( bool is_visible );

    std::string GetName() const;

    bool GetVisible() const;

private:

    std::string name;

    bool is_visible;
};
