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

    void AddKochSegments( const std::vector<KochSegment>& segs );

	void SetKochSegment( const KochSegment& seg );  
    
    void SetCenterPoint( const BasePoint& p );

    void SetKochTriangles( const std::vector<KochTriangle>& tris );

    void AddKochTriangles( const std::vector<KochTriangle>& tris );

    void AddKochPolygon( const KochPolygon& p );

    void SetKochPolygons( const std::vector<KochPolygon>& pols );

    void SetBasePolygons( const std::vector<KochPolygon>& pols );

    void SetKochTriangle( const KochTriangle& tri );

private:

    BasePoint  base_point;

    std::vector<KochPolygon> pols;

};