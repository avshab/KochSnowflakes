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

    BasePoint GetMiddlePoint( const BasePoint& p1, const BasePoint& p2, double k ) const;

    BaseSegment Rotate( double alfa ) const;

    double GetLength() const;

protected:

    bool IsEqual( const BaseSegment& l ) const;
    
protected:

    double length;

	SegmentBasePoints pts;
};