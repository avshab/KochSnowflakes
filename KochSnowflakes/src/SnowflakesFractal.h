#pragma once
#include "KochSegment.h"
#include "CoordinatesModel.h"
#include "RandomAS.h"

class SnowflakesFractal
{
public:

    SnowflakesFractal();     
    
    void Iterate();
    
    void SetKochSegments( const std::vector<KochSegment>& segs );

    std::vector<KochSegment> GetKochSegments() const;

    void SetCenterPoint( const BasePoint& p );

private:

    RandomAS r_as;

    std::vector<KochSegment> segs;

	int random_status;

    double min_w;

    int rand_size;

    double iter;

    BasePoint center_point;

private:

    void DivideAll();    

    void DoubleDivideAll();

    void SimpleRandom();

	void DoubleSimpleRandom();

    void NewRandom();

    void CenterRandom();


    void StartNewSnowflakesSegment();
};