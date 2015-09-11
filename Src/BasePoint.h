#pragma once
#include <string>


class BasePoint
    {
    public:

        BasePoint( double x, double y, double z );
        BasePoint();
        bool IsEqual( const BasePoint& p ) const;
        bool IsOnesLine( const BasePoint& p1, const BasePoint& p2 ) const;
        double GetLength( const BasePoint& p ) const;
        int GetIndex();

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

        void SetName( const std::string& name_str );
        std::string GetName() const;

        bool IsVisible() const;
        void SetVisible( bool is_visible_ );
        void SetVertix( bool is_vertix_ );

        void SetUserPoint( const BasePoint& p );

        BasePoint GetUserPoint() const;

    private:
        double x;
        double y;
        double z;

        bool x_set;
        bool y_set;
        bool z_set;

        bool is_visible;
        bool is_vertix;
        std::string name;
};