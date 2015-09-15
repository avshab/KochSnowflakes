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

private:

    RandomAS r_as;

    std::vector<KochSegment> segs;

    void DivideAll();    

    void DoubleDivideAll();

    void SimpleRandom();



};