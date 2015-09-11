#include "stdafx.h"
#include "Segment.h"



namespace Figures
{
    Segment::Segment( const Figures::Point& p1_, const Figures::Point& p2_ )
        : p1( p1_ )
        , p2( p2_ )
        , is_visible( false )
    {
        long double l = p1.GetLength( p2 );
        a = (p2.GetX() - p1.GetX());// / l;
        b = (p2.GetY() - p1.GetY());// / l;
        c = (p2.GetZ() - p1.GetZ());// / l;
        d = -(a * p1.GetX() + b * p1.GetY() + c * p1.GetZ());
    }


    Segment::Segment()
        : p1( Figures::Point() )
        , p2( Figures::Point() )
        , is_visible( false )
    {
        a = 0.0;
        b = 0.0;
        c = 0.0;
        d = 0.0;
    }

    void Segment::SetName( const std::string& name_str )
    {
        name = name_str;
    }

    bool Segment::IsEqual( const Figures::Segment& l ) const
    {
        if ((p1.IsEqual( l.p1 ) && p2.IsEqual( l.p2 )))
            return true;

        if ((p1.IsEqual( l.p2 ) && p2.IsEqual( l.p1 )))
            return true;

        return false;
    }

    std::string Segment::GetName() const
    {
        return name;
    }

    int Segment::GetIndex() const
    {
        std::string index_str = name.substr( 1 );
        return atoi( index_str.c_str() );
    }


    bool Segment::HasPoint( const Figures::Point& p ) const
    {
        if (p.IsEqual( p1 ) || p.IsEqual( p2 ))
            return true;

        if (abs( (p1.GetX() - p.GetX()) - (p2.GetX() - p.GetX()) ) < 0.001 && abs( (p1.GetY() - p.GetY()) - (p2.GetY() - p.GetY())) < 0.001  && abs(p2.GetX() - p.GetX()) < 0.001 && abs(p2.GetY() - p.GetY()) < 0.001 )
            return true;

        if (abs( (p1.GetX() - p.GetX()) - (p2.GetX() - p.GetX()) ) < 0.001 && abs( (p1.GetZ() - p.GetZ()) - (p2.GetZ() - p.GetZ()) ) < 0.001 && abs( p2.GetX() - p.GetX() ) < 0.001 && abs( p2.GetZ() - p.GetZ() ) < 0.001)
            return true;

        if (abs( (p1.GetZ() - p.GetZ()) - (p2.GetZ() - p.GetZ()) ) < 0.001 && abs( (p1.GetY() - p.GetY()) - (p2.GetY() - p.GetY()) ) < 0.001 && abs( p2.GetZ() - p.GetZ() ) < 0.001 && abs( p2.GetY() - p.GetY() ) < 0.001)
            return true;



        long double k1 = (p1.GetX() - p.GetX()) / (p2.GetX() - p.GetX());
        long double k2 = (p1.GetY() - p.GetY()) / (p2.GetY() - p.GetY());
        long double k3 = (p1.GetZ() - p.GetZ()) / (p2.GetZ() - p.GetZ());

        if (abs( k1 - k2 ) < 0.000001 && abs( k1 - k3 ) < 0.000001)
            return true;

        return false;

    }

    void Segment::SetVisible( bool is_visible_)
    {
        is_visible = is_visible_;
    }

    bool Segment::IsVisible() const
    {
        return  is_visible;
    }

    bool Segment::SetThirdCoordinate( Figures::Point* p )
    {
        if (!p->IsSetX())
        {
            if (!p->IsSetY() || !p->IsSetZ())
                return false;

            if (b == 0.0 || c == 0.0)
                return false;

            long double t1 = (p->GetY() - p1.GetY()) / b;
            long double t2 = (p->GetZ() - p1.GetZ()) / c;

            if (abs(t1 - t2) > 0.005)
                return false;

            long double th_c = p1.GetX() + a * t1;
            p->SetX( th_c );
            return true;

        }

        if (!p->IsSetY())
        {
            if (!p->IsSetX() || !p->IsSetZ())
                return false;

            if (a == 0.0 || c == 0.0)
                return false;

            long double t1 = (p->GetX() - p1.GetX()) / a;
            long double t2 = (p->GetZ() - p1.GetZ()) / c;

            if (abs( t1 - t2 ) > 0.005)
                return false;

            long double th_c = p1.GetY() + b * t1;
            p->SetY( th_c );
            return true;

        }

        if (!p->IsSetZ())
        {
            if (!p->IsSetY() || !p->IsSetX())
                return false;

            if (b == 0.0 || c == 0.0)
                return false;

            long double t1 = (p->GetX() - p1.GetX()) / a;
            long double t2 = (p->GetY() - p1.GetY()) / b;

            if (abs( t1 - t2 ) > 0.005)
                return false;

            long double th_c = p1.GetZ() + c * t1;
            p->SetZ( th_c );
            return true;
        }
       
    }

    long double Segment::GetLenghtToPoint( const Figures::Point& p )
    {

        long double am = sqrt( a * a +  b * b + c * c );

        long double s_x = ((p.GetY() - p1.GetY()) * c - (p.GetZ() - p1.GetZ()) * b);
        long double s_y = ((p.GetZ() - p1.GetZ()) * a - (p.GetX() - p1.GetX()) * c);
        long double s_z = ((p.GetX() - p1.GetX()) * b - (p.GetY() - p1.GetY()) * a);

        long double vect_pr = sqrt( s_x * s_x + s_y * s_y + s_z * s_z );

        return vect_pr / am;
    }

    Point Segment::GetProgPoint( const Figures::Point& p )
    {
        long double d_plane = a * p.GetX() + b * p.GetY() + c * p.GetZ();   //without minus
        long double sol = a * p1.GetX() + b * p1.GetY() + c * p1.GetZ();   //without minus
        long double am = a * a + b * b + c * c;
        long double t = (d_plane - sol) / am;
        Point pt( p1.GetX() + a * t, p1.GetY() + b * t, p1.GetZ() + c * t );
        return pt;
    } 
   
    std::pair<long double, long double> Segment::GetCoord( ValueP c1, ValueP c2 )
    {
        long double v1 = -1.0;
        long double v2 = -1.0;
        if (c1.val_cos_2 / c1.val_cos_1 + c2.val_cos_2 / c2.val_cos_1 != 0)
            v1 = (c2.val_2 - c1.val_2) / (c1.val_cos_2 / c1.val_cos_1 + c2.val_cos_2 / c2.val_cos_1) + c1.val_1;

        if (c2.val_cos_1 == 0.0)
            v1 = c2.val_1;

        v2 = c1.val_cos_2 * (v1 - c1.val_1) / c1.val_cos_1 + c1.val_2;
        if (c1.val_cos_1 == 0.0)
            v2 = c2.val_cos_2 * (v1 - c2.val_1) / c2.val_cos_1 + c2.val_2;


        return std::pair<long double, long double>( v1, v2 );
    }

    Point Segment::GetPointLinesIntersect( const Figures::Segment& l )
    {
        long double l_loc1 = p1.GetLength( p2 );
        long double l_loc2 = l.p1.GetLength( l.p2 );

        if (l.b == b && l.a == a && l.c == c)
            return Point();

        if (l.b == 0 && l.c == 0)
        {
            Figures::Point new_p;
            
            new_p.SetY( l.p1.GetY() );
            new_p.SetZ( l.p1.GetZ() );
            SetThirdCoordinate( &new_p );
            return new_p;
        }

        if (l.a == 0 && l.b == 0)
        {
            Figures::Point new_p;

            new_p.SetX( l.p1.GetX() );
            new_p.SetY( l.p1.GetY() );
            SetThirdCoordinate( &new_p );
            return new_p;
        }

        if (l.a == 0 && l.c == 0)
        {
            Figures::Point new_p;

            new_p.SetX( l.p1.GetX() );
            new_p.SetZ( l.p1.GetZ() );
            SetThirdCoordinate( &new_p );
            return new_p;
        }

        if (l.b == b && b == 0)
        {
            ValueP v1( p1.GetX(), a, p1.GetZ(), c );
            ValueP v2( l.p1.GetX(), l.a, l.p1.GetZ(), l.c );
            std::pair<long double, long double> pair_c = GetCoord( v1, v2 );
            return Point(pair_c.first, p1.GetY(), pair_c.second);
        }
        else if (l.c == c && c == 0)
        {
            ValueP v1( p1.GetX(), a, p1.GetY(), b );
            ValueP v2( l.p1.GetX(), l.a, l.p1.GetY(), l.b );
            std::pair<long double, long double> pair_c = GetCoord( v1, v2 );
            return Point( pair_c.first, pair_c.second, p1.GetZ());
        }
        else if (l.a == a && a == 0)
        {
            ValueP v1( p1.GetY(), b, p1.GetZ(), c );
            ValueP v2( l.p1.GetY(), l.b, l.p1.GetZ(), l.c );
            std::pair<long double, long double> pair_c = GetCoord( v1, v2 );
            return Point( p1.GetX(), pair_c.first, pair_c.second );
        }


        if (abs( b*l.a - l.b*a ) < 0.0001 || abs( a*l.b - l.a*b ) < 0.0001 || abs( b*l.c - l.b*c ) < 0.0001)
            return Point();

        long double x = (p1.GetX()*b*l.a - l.p1.GetX()*l.b*a - p1.GetY()*a*l.a + l.p1.GetY()*a*l.a) / (b*l.a - l.b*a);
        long double y = (p1.GetY()*a*l.b - l.p1.GetY()*l.a*b - p1.GetX()*b*l.b + l.p1.GetX()*b*l.b) / (a*l.b - l.a*b);
        long double z = (p1.GetZ()*b*l.c - l.p1.GetZ()*l.b*c - p1.GetY()*c*l.c + l.p1.GetY()*c*l.c) / (b*l.c - l.b*c);



        return Point( x, y, z );
    }
};