#include "stdafx.h"
#include "SnowflakesFractal.h"




const static int MAX_RANDOM = 6;

static int ITERATION_INDEX = 1;

SnowflakesFractal::SnowflakesFractal( KochCoordModel* m )
    : model(m)
    , random_status(0)
{
    rand_size = 3;
    iter = 0;

}


void SnowflakesFractal::Iterate()
{
   // DoubleDivideAll();
    //SimpleRandom();
   // DivideAll();
   // NewRandom();
    
    DivideTriangles();

}
                                                                                                

void SnowflakesFractal::SetKochSegments( const std::vector<KochSegment>& segs_ )
{
    segs = segs_;
}

std::vector<KochSegment> SnowflakesFractal::GetKochSegments() const
{
    return segs;
}


void SnowflakesFractal::DivideTriangles()
{
    eGrowthDirection grow_dir = eGrowthDirection::INSIDE;
    // if (ITERATION_INDEX % 2 == 0)
    grow_dir = eGrowthDirection::OUTSIDE;
    std::vector<KochTriangle> new_tris;
    segs.clear();
    for (auto it = begin( tris ); it != end( tris ); it++)
    {
        
        //std::vector<KochSegment> cur_segs = it->GetSegments( );
        //for (auto it_c = begin( cur_segs ); it_c != end( cur_segs ); it_c++)
        //    segs.push_back( *it_c );


        std::vector<KochTriangle> cur_tris = it->GetIterTriangles();
        for (auto it_c = begin( cur_tris ); it_c != end( cur_tris ); it_c++)
            new_tris.push_back( *it_c );
       // new_tris.push_back( it->GetInternalTriangle() );
    }
    model->SetKochTriangles( tris );
    tris = new_tris;

    ITERATION_INDEX++;
}

void SnowflakesFractal::DivideAll()
{
    eGrowthDirection grow_dir = eGrowthDirection::INSIDE;
   // if (ITERATION_INDEX % 2 == 0)
       grow_dir = eGrowthDirection::OUTSIDE;


    std::vector<KochSegment> new_segs;
    for (auto it = begin( segs ); it != end( segs ); it++)
    {
        std::vector<KochSegment> cur_segs = it->Divide( grow_dir );
        for (auto it_c = begin( cur_segs ); it_c != end( cur_segs ); it_c++)
            new_segs.push_back( *it_c );
    }
    segs.clear();
    segs = new_segs;
    ITERATION_INDEX++;
}


void SnowflakesFractal::SimpleRandom()
{
    int s = segs.size();

    for (int i = 0; i < s; i++)
    {
        if (r_as.IsDivideRandom( i, s, segs.at( i ).GetLength() ))
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
        if (r_as.IsDivideRandom( i, s, segs.at( i ).GetLength() ))
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
        if (r_as.IsDivideRandom( i, s, segs.at( i ).GetLength() ))
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
        cur_segs = it->Divide( eGrowthDirection::OUTSIDE );
        for (auto it_c = begin( cur_segs ); it_c != end( cur_segs ); it_c++)
            new_segs.push_back( *it_c );
    }

    for (auto it = begin( segs ); it != end( segs ); it++)
    {
        std::vector<KochSegment> cur_segs = it->Divide( eGrowthDirection::INSIDE );
        for (auto it_c = begin( cur_segs ); it_c != end( cur_segs ); it_c++)
            new_segs.push_back( *it_c );
    }
    segs.clear();
    segs = new_segs;
}


void SnowflakesFractal::NewRandom()
{
    min_w = segs.at( 0 ).GetLength();
    int s = segs.size(); 
    int* objs = r_as.GetRandomNumbers( rand_size, s );
    int del_objs[2] = { objs[0], objs[1] };
    eGrowthDirection grow_dir = eGrowthDirection::INSIDE;
    if (objs[1] % 4 == 0)
        grow_dir = eGrowthDirection::OUTSIDE;
    
    std::vector<KochSegment> cur_segs_1 = segs.at( del_objs[0] ).Divide( grow_dir );
    std::vector<KochSegment> cur_segs_2 = segs.at( del_objs[1] ).Divide( grow_dir );
    segs.erase( segs.begin() + del_objs[0] );
    if (del_objs[0] < del_objs[1])
        segs.erase( segs.begin() + del_objs[1] - 1 );
    else
        segs.erase( segs.begin() + del_objs[1] );

    for (auto it_c = begin( cur_segs_1 ); it_c != end( cur_segs_1 ); it_c++)
        segs.push_back( *it_c );

    for (auto it_c = begin( cur_segs_2 ); it_c != end( cur_segs_2 ); it_c++)
        segs.push_back( *it_c );


    s = segs.size();
    iter += 0.3;
    rand_size += (int)( iter );

    if (rand_size % 20 == 0)
        StartNewSnowflakesSegment();
}


void SnowflakesFractal::CenterRandom()
{
    int s = segs.size();
    int R = r_as.GetRandomNumber( 100 );


}


void SnowflakesFractal::StartNewSnowflakesSegment()
{
    int* objs = r_as.GetRandomNumbers( 200, 200 );
    int par_m[2] = { objs[0], objs[1] };
    std::vector<KochSegment> vect;
    BasePoint p1( center_point );
    p1.SetX( p1.GetX() + par_m[0] + 100 );

    BaseSegment s0( center_point, p1 );
    BaseSegment s1( s0.Rotate( par_m[0] ) );
    BaseSegment s2( s1.Rotate( par_m[0] + 120 ) );
    BaseSegment s3( s1.Rotate( par_m[0] + 240 ) );
   
    vect.push_back( KochSegment( s1.GetBasePoints().p2, s2.GetBasePoints().p2 ) );
    vect.push_back( KochSegment( s2.GetBasePoints().p2, s3.GetBasePoints().p2 ) );
    vect.push_back( KochSegment( s3.GetBasePoints().p2, s1.GetBasePoints().p2 ) );
    Color c = r_as.GetRandomColor();
    for (auto it = begin( vect ); it != end( vect ); it++)
    {
        it->SetColor( c );
        segs.insert( segs.begin(), *it );
    }
    rand_size = 3;
    iter = 0;
        
}

void SnowflakesFractal::SetCenterPoint( const BasePoint& p )
{
    center_point = p;
    StartNewSnowflakesSegment();
    tris.push_back( KochTriangle( segs.at(0), segs.at(2), segs.at(1) ) );
}