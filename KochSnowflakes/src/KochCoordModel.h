#pragma once
#include "Styles.h" 
#include "CoordinatesModel.h"
#include "KochTriangle.h"


class KochCoordModel
	: public CoordinatesModel
{
public:

	KochCoordModel();

	virtual ~KochCoordModel();

	std::vector<KochSegment> GetKochSegments() const;

	void SetKochSegments( const std::vector<KochSegment>& segs );

	void SetKochSegment( const KochSegment& seg );  
    
    void SetCenterPoint( const BasePoint& p );

    void SetKochTriangles( const std::vector<KochTriangle>& tris );

    void AddKochTriangles( const std::vector<KochTriangle>& tris );

    void SetKochTriangle( const KochTriangle& tri );

private:


    BasePoint  base_point;

};