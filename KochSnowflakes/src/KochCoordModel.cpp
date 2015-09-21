#include "stdafx.h"
#include "KochCoordModel.h"
#include "CoordinatesSegment.h"


KochCoordModel::KochCoordModel() : CoordinatesModel()
{

}


KochCoordModel::~KochCoordModel()
{
}


std::vector<KochSegment> KochCoordModel::GetKochSegments() const
{
	std::vector<KochSegment> segs; 
	std::vector<ModelObject*> cs = obj_map.at(eModelObjectType::BASE_SEGMENT);
	for (int i = 0; i < cs.size(); i++)
	{
		CoordinatesSegment* m = dynamic_cast<CoordinatesSegment*>(cs.at(i));
		SegmentCoordPoints pts = m->GetPoints();
		BasePoint p1(pts.c1.GetPos().x, pts.c1.GetPos().y, 0.0);
		BasePoint p2(pts.c2.GetPos().x, pts.c2.GetPos().y, 0.0);
		KochSegment ks(p1, p2);
        ks.SetColor( m->GetColor() );
		segs.push_back(ks);
        m = NULL;
	}
	return segs;
}


void KochCoordModel::SetKochSegments(const std::vector<KochSegment>& segs_)
{
	Clear();
	for (auto it = begin(segs_); it != end(segs_); it++)
		SetKochSegment(*it);
}


void KochCoordModel::SetKochSegment(const KochSegment& seg)
{
	SegmentBasePoints base_pts = seg.GetBasePoints();
	PointPos pos_1((int)base_pts.p1.GetX(), (int)base_pts.p1.GetY());
	PointPos pos_2((int)base_pts.p2.GetX(), (int)base_pts.p2.GetY());
	CoordinatesPoint c1(pos_1, "p", true);
	CoordinatesPoint c2(pos_2, "p", true);
	SegmentCoordPoints cpts(c1, c2);
	ModelObject* s = new CoordinatesSegment(cpts, "segment", true);


    s->SetColor( seg.GetColor() );

	AddObject(eModelObjectType::BASE_SEGMENT, s);
    s = NULL;
}

#include "RandomAS.h"
void KochCoordModel::SetCenterPoint( const BasePoint& p )
{
    base_point = p;    

    RandomAS r_as;
    int* objs = r_as.GetRandomNumbers( 300, 360 );
    int par_m[2] = { objs[0], objs[1] };

    BasePoint p1( p );
    p1.SetX( p1.GetX() + par_m[0] );

    KochSegment s1( p, p1 );
    KochSegment s2( s1.Rotate( 120 ) );
    KochSegment s3( s1.Rotate( 240 ) );
    SetKochSegment( KochSegment( p1,  s2.GetBasePoints().p2 ) );
    SetKochSegment( KochSegment( s2.GetBasePoints().p2, s3.GetBasePoints().p2 ) );
    SetKochSegment( KochSegment( s3.GetBasePoints().p2, p1 ) );
}


