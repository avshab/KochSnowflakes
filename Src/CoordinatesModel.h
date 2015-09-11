#pragma once
#include "Styles.h" 
#include "CoordinatesFace.h"

#include <vector>


class CoordinatesModel
{
public:

    CoordinatesModel();

    virtual ~CoordinatesModel();

public: 

    virtual bool IsEmpty() const;
    
    void SetModelName( const std::string& name );

    void SetBasePoints( const std::vector<CoordinatesPoint>& pts );

    void SetBaseSegments( const std::vector<CoordinatesSegment>& segs );

    std::string GetModelName() const;

    std::vector<CoordinatesPoint> GetBasePoints() const;

    std::vector<CoordinatesSegment> GetBaseSegments() const;

private:

    std::string name;

    std::vector<CoordinatesPoint> base_points;

    std::vector<CoordinatesSegment> base_segs;
};