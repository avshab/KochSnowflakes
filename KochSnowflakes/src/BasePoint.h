#pragma once
#include "BaseObject.h"


class BasePoint 
	: public BaseObject
    {
    public:

        BasePoint( double x, double y, double z );

        BasePoint();

        bool IsEqual( const BasePoint& p ) const;

        bool IsOnesLine( const BasePoint& p1, const BasePoint& p2 ) const;

        double GetLength( const BasePoint& p ) const;

        double GetX() const;

        double GetY() const;

        double GetZ() const;

        void SetX( double x );

        void SetY( double y );

        void SetZ( double z );

        bool IsSetX() const;

        bool IsSetY() const;
        
        bool IsSetZ() const;

        bool IsValid() const;

        bool IsVertix() const;

    private:

        double x;

        double y;

        double z;

        bool is_set[3];
};