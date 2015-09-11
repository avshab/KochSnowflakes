#pragma once
#include "BaseSegment.h"


class BaseLine : public BaseSegment
{
public:

    BaseLine( const BasePoint& p1, const BasePoint& p2 );

    BaseLine();

    void SetName( const std::string& name_str );

    virtual std::string GetName() const;

    void SetVisible( bool is_visible );

    bool IsVisible() const;

    bool IsEqual( const BaseLine& l ) const;
    
    int GetIndex() const;

    bool HasPoint( const BasePoint& p ) const;

    BasePoint GetProgPoint( const BasePoint& p );

    double GetLenghtToPoint( const BasePoint& p );

    BasePoint GetPointLinesIntersect( const BaseLine& p );

    struct ValueP
    {
        ValueP(double v1, double vc1, double v2, double vc2)
        {
            val_1 = v1;
            val_cos_1 = vc1;
            val_2 = v2;
            val_cos_2 = vc2;
        };
        double val_1;
        double val_cos_1;
        double val_2;
        double val_cos_2;
    };
    std::pair<double, double> GetCoord( ValueP c1, ValueP c2 );

    bool SetThirdCoordinate( BasePoint* p );
    
protected:

    std::string name;

private:
    
    BasePoint p1;

    BasePoint p2;

    double a;

    double b;

    double c;

    double d;     

    bool is_visible;    
};