#pragma once
#include "BasePoint.h"


struct SegmentBasePoints
{
	SegmentBasePoints(const BasePoint& p1_, const BasePoint& p2_)
		: p1(p1_), p2(p2_) 	{};
	SegmentBasePoints(){};
	BasePoint p1;
	BasePoint p2;
};

class BaseSegment
	: public BaseObject
{
public:
    BaseSegment( const BasePoint& p1, const BasePoint& p2 );

    BaseSegment();

    virtual ~BaseSegment();

	void SetBasePoints(const SegmentBasePoints& pts);

	SegmentBasePoints GetBasePoints() const;

protected:

    bool IsEqual( const BaseSegment& l ) const;
    
    //bool HasPoint( const BasePoint& p ) const;

    //struct ValueP
    //{
    //    ValueP(double v1, double vc1, double v2, double vc2)
    //    {
    //        val_1 = v1;
    //        val_cos_1 = vc1;
    //        val_2 = v2;
    //        val_cos_2 = vc2;
    //    };
    //    double val_1;
    //    double val_cos_1;
    //    double val_2;
    //    double val_cos_2;
    //};
    //std::pair<double, double> GetCoord( ValueP c1, ValueP c2 );

    
protected:

	SegmentBasePoints pts;
};