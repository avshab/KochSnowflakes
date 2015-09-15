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
		segs.push_back(ks);
        m = NULL;
	}
	return segs;
}


void KochCoordModel::SetKochSegments(const std::vector<KochSegment>& segs_)
{
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
	AddObject(eModelObjectType::BASE_SEGMENT, s);
    s = NULL;
}
