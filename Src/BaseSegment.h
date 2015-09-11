#pragma once
#include "BasePoint.h"


class BaseSegment
{
public:
    BaseSegment( const BasePoint& p1, const BasePoint& p2 );

    BaseSegment();

    virtual ~BaseSegment();

protected:

    void SetName( const std::string& name_str );

    std::string GetName() const;

    void SetVisible( bool is_visible );

    bool IsVisible() const;

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

    BasePoint p1;

    BasePoint p2;

private:

    std::string name;

    bool is_visible;
};