#pragma once
#include "Styles.h" 
#include "CoordinatesModel.h"
#include "KochSegment.h"


class KochCoordModel
	: public CoordinatesModel
{
public:

	KochCoordModel();

	virtual ~KochCoordModel();

	std::vector<KochSegment> GetKochSegments() const;

	void SetKochSegments( const std::vector<KochSegment>& segs );

	void SetKochSegment(const KochSegment& seg);  
    
    void SetCenterPoint( const BasePoint& p );

private:

	std::vector<KochSegment> segments;

    BasePoint  base_point;

};