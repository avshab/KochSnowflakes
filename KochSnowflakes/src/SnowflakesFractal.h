#pragma once
#include "KochSegment.h"
#include "CoordinatesModel.h"


class SnowflakesFractal
{
public:

    SnowflakesFractal();     
    
    void Iterate();
    
    void SetKochSegments( const std::vector<KochSegment>& segs );

    std::vector<KochSegment> GetKochSegments() const;

private:

    std::vector<KochSegment> segs;

};