#include "stdafx.h"
#include "SnowflakesFractal.h"


SnowflakesFractal::SnowflakesFractal()
{

}


void SnowflakesFractal::Iterate()
{
    std::vector<KochSegment> new_segs;

    for (auto it = begin( segs ); it != end( segs ); it++)
    {
        std::vector<KochSegment> cur_segs = it->Divide();
		for (auto it_c = begin(cur_segs); it_c != end(cur_segs); it_c++)
            new_segs.push_back( *it );
    }    

    segs = new_segs;
}


void SnowflakesFractal::SetKochSegments( const std::vector<KochSegment>& segs_ )
{
    segs = segs_;
}

std::vector<KochSegment> SnowflakesFractal::GetKochSegments() const
{
    return segs;
}