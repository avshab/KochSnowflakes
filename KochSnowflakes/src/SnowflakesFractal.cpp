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
    // SimpleRandom();
     DivideAll();
    // NewRandom();
   // DivideTriangles();
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
    if (tris.empty())
        return;
    eGrowthDirection grow_dir = eGrowthDirection::INSIDE;

    grow_dir = eGrowthDirection::OUTSIDE;
    std::vector<KochTriangle> cur_tris = tris.at(0).GetIterTriangles();

    model->AddKochTriangles( cur_tris );
    ITERATION_INDEX++;
}


void SnowflakesFractal::DivideAll()
{
    if (ITERATION_INDEX == 1)
    {
         model->SetKochSegments( segs );
    } else { 
        eGrowthDirection grow_dir = eGrowthDirection::OUTSIDE;

        std::vector<KochSegment> new_segs;
        for (int i = 0; i < 24; i++)
        {
            std::vector<KochSegment> new_segs_ = segs.at(i).Divide( grow_dir );
            for (int j = 0; j < new_segs_.size(); j++)
            {
                new_segs.push_back( new_segs_.at( j ) );
                segs.push_back( new_segs_.at( j ) );
            }
        }  
        for (int i = 0; i < segs.size(); i++)
            model->AddKochPolygon( segs.at( i ).GetPaintPolygon() );

        model->SetKochSegments( new_segs );      
       
    } ITERATION_INDEX++;
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
        StartNewSnowflakesTriangle();
}


void SnowflakesFractal::CenterRandom()
{
    int s = segs.size();
    int R = r_as.GetRandomNumber( 100 );
}


void SnowflakesFractal::StartNewSnowflakesTriangle()
{
    int* objs = r_as.GetRandomNumbers( 20, 20 );
    int par_m[2] = { objs[0], objs[1] };
    std::vector<KochSegment> vect;
    BasePoint p1( center_point );
    p1.SetX( p1.GetX() + par_m[0] + 250 );

    BaseSegment s0( center_point, p1 );
    BaseSegment s1( s0.Rotate( par_m[0] ) );
    BaseSegment s2( s1.Rotate( par_m[0] + 120 ) );
    BaseSegment s3( s1.Rotate( par_m[0] + 240 ) );
   
    vect.push_back( KochSegment( s1.GetBasePoints().p2, s2.GetBasePoints().p2, 0 ) );
    vect.push_back( KochSegment( s2.GetBasePoints().p2, s3.GetBasePoints().p2, 0 ) );
    vect.push_back( KochSegment( s3.GetBasePoints().p2, s1.GetBasePoints().p2, 0 ) );
    Color c = r_as.GetRandomColor( Color(255,151,187), 0, 0 );
    for (auto it = begin( vect ); it != end( vect ); it++)
    {
        it->SetColor( c );
        segs.insert( segs.begin(), *it );
    }
    rand_size = 3;
    iter = 0;
        
}
BasePoint GetPIS( BasePoint p1, BasePoint p2, double k )
{
    return BasePoint( p1.GetX() + (p2.GetX() - p1.GetX()) * k, p1.GetY() + (p2.GetY() - p1.GetY()) * k, p1.GetZ() + (p2.GetZ() - p1.GetZ()) * k );
}


void SnowflakesFractal::StartNewSnowflakesHexagon()
{
    int* objs = r_as.GetRandomNumbers( 20, 20 );
    int par_m[2] = { objs[0], objs[1] };
    std::vector<KochSegment> vect;
    BasePoint p1( center_point );
    p1.SetX( p1.GetX() + par_m[0] + 150 );

    BaseSegment s0( center_point, p1 );
    BaseSegment s1( s0.Rotate( par_m[0] ) );
    BaseSegment s2( s1.Rotate( par_m[0] + 60 ) );
    BaseSegment s3( s1.Rotate( par_m[0] + 120 ) );
    BaseSegment s4( s1.Rotate( par_m[0] + 180 ) );
    BaseSegment s5( s1.Rotate( par_m[0] + 240 ) );
    BaseSegment s6( s0.Rotate( par_m[0] - 60 ) );



    vect.push_back( KochSegment( s1.GetBasePoints().p2, GetPIS( center_point, GetPIS( s1.GetBasePoints().p2, s2.GetBasePoints().p2, 0.5 ), 2 ), 0 ));
    vect.push_back( KochSegment( GetPIS( center_point, GetPIS( s1.GetBasePoints().p2, s2.GetBasePoints().p2, 0.5 ), 2 ), s2.GetBasePoints().p2, 0 ));

    vect.push_back( KochSegment( s2.GetBasePoints().p2, GetPIS( center_point, GetPIS( s2.GetBasePoints().p2, s3.GetBasePoints().p2, 0.5 ), 2 ), 0 ));
    vect.push_back( KochSegment( GetPIS( center_point, GetPIS( s2.GetBasePoints().p2, s3.GetBasePoints().p2, 0.5 ), 2 ), s3.GetBasePoints().p2, 0 ));

    vect.push_back( KochSegment( s3.GetBasePoints().p2, GetPIS( center_point, GetPIS( s3.GetBasePoints().p2, s4.GetBasePoints().p2, 0.5 ), 2 ), 0 ));
    vect.push_back( KochSegment( GetPIS( center_point, GetPIS( s3.GetBasePoints().p2, s4.GetBasePoints().p2, 0.5 ), 2 ), s4.GetBasePoints().p2, 0 ));


    vect.push_back( KochSegment( s4.GetBasePoints().p2, GetPIS( center_point, GetPIS( s4.GetBasePoints().p2, s5.GetBasePoints().p2, 0.5 ), 2 ), 0 ));
    vect.push_back( KochSegment( GetPIS( center_point, GetPIS( s4.GetBasePoints().p2, s5.GetBasePoints().p2, 0.5 ), 2 ), s5.GetBasePoints().p2, 0 ));

    vect.push_back( KochSegment( s5.GetBasePoints().p2, GetPIS( center_point, GetPIS( s5.GetBasePoints().p2, s6.GetBasePoints().p2, 0.5 ), 2 ), 0 ));
    vect.push_back( KochSegment( GetPIS( center_point, GetPIS( s5.GetBasePoints().p2, s6.GetBasePoints().p2, 0.5 ), 2 ), s6.GetBasePoints().p2, 0 ));

    vect.push_back( KochSegment( s6.GetBasePoints().p2, GetPIS( center_point, GetPIS( s6.GetBasePoints().p2, s1.GetBasePoints().p2, 0.5 ), 2 ), 0 ));
    vect.push_back( KochSegment( GetPIS( center_point, GetPIS( s6.GetBasePoints().p2, s1.GetBasePoints().p2, 0.5 ), 2 ), s1.GetBasePoints().p2, 0 ));


    vect.push_back( KochSegment( s2.GetBasePoints().p2, s1.GetBasePoints().p2, 0 ) );
    vect.push_back( KochSegment( s3.GetBasePoints().p2, s2.GetBasePoints().p2, 0 ) );
    vect.push_back( KochSegment( s4.GetBasePoints().p2, s3.GetBasePoints().p2, 0 ) );
    vect.push_back( KochSegment( s5.GetBasePoints().p2, s4.GetBasePoints().p2, 0 ) );
    vect.push_back( KochSegment( s6.GetBasePoints().p2, s5.GetBasePoints().p2, 0 ) );
    vect.push_back( KochSegment( s1.GetBasePoints().p2, s6.GetBasePoints().p2, 0 ) );


    vect.push_back( KochSegment( s1.GetBasePoints().p2, center_point, 0 ) );
    vect.push_back( KochSegment( s2.GetBasePoints().p2, center_point, 0 ) );
    vect.push_back( KochSegment( s3.GetBasePoints().p2, center_point, 0 ) );
    vect.push_back( KochSegment( s4.GetBasePoints().p2, center_point, 0 ) );
    vect.push_back( KochSegment( s5.GetBasePoints().p2, center_point, 0 ) );
    vect.push_back( KochSegment( s6.GetBasePoints().p2, center_point, 0 ) );

    Color c = r_as.GetRandomColor( Color( 255, 151, 187 ), 0, 0 );
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
    bool is_tris = false;
    if (is_tris)
    {
        StartNewSnowflakesTriangle();
        tris.push_back( KochTriangle( segs.at( 0 ), segs.at( 2 ), segs.at( 1 ), 0 ) );
        Color c = r_as.GetBaseColor();
        tris.at( 0 ).SetColor( c );
        model->AddKochTriangles( tris );
    }
    else
        StartNewSnowflakesHexagon();
    
}