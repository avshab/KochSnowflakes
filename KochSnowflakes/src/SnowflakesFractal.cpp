#include "stdafx.h"
#include "SnowflakesFractal.h"


const static int MAX_RANDOM = 6;

SnowflakesFractal::SnowflakesFractal()
	: random_status(0)
{

}


void SnowflakesFractal::Iterate()
{
    //DoubleDivideAll();
    //SimpleRandom();
    //DivideAll();
	DoubleSimpleRandom();

}
                                                                                                

void SnowflakesFractal::SetKochSegments( const std::vector<KochSegment>& segs_ )
{
    segs = segs_;
}

std::vector<KochSegment> SnowflakesFractal::GetKochSegments() const
{
    return segs;
}


void SnowflakesFractal::DivideAll()
{
    std::vector<KochSegment> new_segs;
    for (auto it = begin( segs ); it != end( segs ); it++)
    {
        std::vector<KochSegment> cur_segs = it->Divide();
        for (auto it_c = begin( cur_segs ); it_c != end( cur_segs ); it_c++)
            new_segs.push_back( *it_c );
    }
    segs.clear();
    segs = new_segs;
}


void SnowflakesFractal::SimpleRandom()
{
    int s = segs.size();

    for (int i = 0; i < s; i++)
    {
        if (r_as.GetRandomAS( i, s, segs.at( i ).GetLength() ))
        {
            std::vector<KochSegment> cur_segs = segs.at( i ).Divide();
            segs.erase( segs.begin() + i );
            for (auto it_c = begin( cur_segs ); it_c != end( cur_segs ); it_c++)
                segs.push_back( *it_c );
			return;
        }
    }

}

void SnowflakesFractal::DoubleSimpleRandom()
{
	int s = segs.size();

	
	for (int i = 0; i < s; i++)
	{
		eGrowthDirection grow_dir;
		if (random_status == 0 || random_status == 2 || random_status == 3)
			grow_dir = eGrowthDirection::INSIDE;

		if (random_status == 1 || random_status == 4 || random_status == 5)
			grow_dir = eGrowthDirection::OUTSIDE;

		random_status++;
		if (random_status > 5)
			random_status = 0;
		if (r_as.GetRandomAS(i, s, segs.at(i).GetLength()))
		{

			std::vector<KochSegment> cur_segs = segs.at(i).Divide(grow_dir);
			if (cur_segs.empty())
				return;
			segs.erase(segs.begin() + i);
			for (auto it_c = begin(cur_segs); it_c != end(cur_segs); it_c++)
				segs.push_back(*it_c);

				
			return;
		}
	}
	for (int i = s - 1; i > 0; i--)
	{
		eGrowthDirection grow_dir;
		if (random_status == 0 || random_status == 2 || random_status == 3)
			grow_dir = eGrowthDirection::INSIDE;

		if (random_status == 1 || random_status == 4 || random_status == 5)
			grow_dir = eGrowthDirection::OUTSIDE;

		random_status++;
		if (random_status > 5)
			random_status = 0;
		if (r_as.GetRandomAS(i, s, segs.at(i).GetLength()))
		{

			std::vector<KochSegment> cur_segs = segs.at(i).Divide(grow_dir);
			if (cur_segs.empty())
				return;
			segs.erase(segs.begin() + i);
			for (auto it_c = begin(cur_segs); it_c != end(cur_segs); it_c++)
				segs.push_back(*it_c);
			return;
		}
	}

}

void SnowflakesFractal::DoubleDivideAll()
{
    std::vector<KochSegment> new_segs;
    for (auto it = begin( segs ); it != end( segs ); it++)
    {
        std::vector<KochSegment> cur_segs = it->Divide( eGrowthDirection::INSIDE );
        for (auto it_c = begin( cur_segs ); it_c != end( cur_segs ); it_c++)
            new_segs.push_back( *it_c );

        cur_segs = it->Divide( eGrowthDirection::OUTSIDE );
        for (auto it_c = begin( cur_segs ); it_c != end( cur_segs ); it_c++)
            new_segs.push_back( *it_c );
    }
    segs.clear();
    segs = new_segs;
}