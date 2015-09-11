#include "stdafx.h"
#include "CoordinatesModel.h"


CoordinatesModel::CoordinatesModel()
{

}


CoordinatesModel::~CoordinatesModel()
{
}


bool CoordinatesModel::IsEmpty() const
{
    if (!base_points.empty())
        return false;

    if (!base_segs.empty())
        return false;

    return true;
}

void CoordinatesModel::SetModelName( const std::string& name_ )
{
    name = name_;
}


void CoordinatesModel::SetBasePoints( const std::vector<CoordinatesPoint>& pts )
{
    base_points = pts;
}

void CoordinatesModel::SetBaseSegments( const std::vector<CoordinatesSegment>& segs )
{
    base_segs = segs;
}


std::string CoordinatesModel::GetModelName() const
{
    return name;
}


std::vector<CoordinatesPoint> CoordinatesModel::GetBasePoints() const
{
    return base_points;
}


std::vector<CoordinatesSegment> CoordinatesModel::GetBaseSegments() const
{
    return base_segs;
}