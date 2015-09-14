#include "stdafx.h"
#include "SnowflakesFractal.h"


const static int MAX_RANDOM = 6;

SnowflakesFractal::SnowflakesFractal()
{

}


void SnowflakesFractal::Iterate()
{
    int s = segs.size();

    for (int i = 0; i < s; i++)
    {
        if (r_as.GetRandomAS( i, s, segs.at( i ).GetLength() ))
        {
              std::vector<KochSegment> cur_segs = segs.at( i ).Divide();  
              segs.erase( segs.begin() + i );
		        for (auto it_c = begin(cur_segs); it_c != end(cur_segs); it_c++)
                    segs.push_back( *it_c );
        }
    }    

}


void SnowflakesFractal::SetKochSegments( const std::vector<KochSegment>& segs_ )
{
    segs = segs_;
}

std::vector<KochSegment> SnowflakesFractal::GetKochSegments() const
{
    return segs;
}