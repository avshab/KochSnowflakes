#pragma once
#include "KochSegment.h"
#include "KochCoordModel.h"
#include "RandomAS.h"
#include "KochTriangle.h"


class SnowflakesFractal
{
public:

    SnowflakesFractal( KochCoordModel* model );
    
    void Iterate();
    
    void SetKochSegments( const std::vector<KochSegment>& segs );

    std::vector<KochSegment> GetKochSegments() const;

    std::vector<KochSegment> GetKochTris() const;

    void SetCenterPoint( const BasePoint& p );

private:

    RandomAS r_as;

    std::vector<KochSegment> segs;

    std::vector<KochTriangle> tris;

	int random_status;

    double min_w;

    int rand_size;

    double iter;

    BasePoint center_point;

    KochCoordModel* model;

private:

    void DivideAll();    

    void DoubleDivideAll();

    void SimpleRandom();

	void DoubleSimpleRandom();

    void NewRandom();

    void CenterRandom();

    void DivideTriangles();

    void StartNewSnowflakesSegment();
};