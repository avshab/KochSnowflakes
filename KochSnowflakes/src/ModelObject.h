#pragma once
#include <string>


class ModelObject
{
public:

	ModelObject();

	virtual ~ModelObject();

    void SetName( const std::string& name_str );

    std::string GetName() const;

    void SetVisible( bool is_visible );

    bool IsVisible() const;

    
protected:

    std::string name; 

	bool is_visible;   
};