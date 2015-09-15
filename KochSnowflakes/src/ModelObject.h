#pragma once
#include <string>
//#include "Styles.h"


class ModelObject
{
public:

	ModelObject();

	virtual ~ModelObject();

    void SetName( const std::string& name_str );

    std::string GetName() const;

    void SetVisible( bool is_visible );

    bool IsVisible() const;

    void SetColor( Color color );

    Color GetColor() const;

    
protected:

    Color color;

    std::string name; 

	bool is_visible;   
};