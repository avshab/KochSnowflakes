#include "stdafx.h"
#include "PainterI.h"
#include "KochSegment.h"



PainterI::PainterI()
{

}


PainterI::~PainterI()
{
    DestroyWindow();
}


BEGIN_MESSAGE_MAP( PainterI, CWnd )
    ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL PainterI::PreCreateWindow( CREATESTRUCT& cs )
{
    if (!CWnd::PreCreateWindow( cs ))
        return FALSE;
    return TRUE;
}


void PainterI::CreateVirtualWindow( CDC *dc_virt, CRect w_rect )
{
    CPen rect_pen( PS_SOLID, 3, Color::WhiteSmoke );
    CBrush rect_brush( Color::White );
    dc_virt->SelectObject( rect_pen );
    dc_virt->SelectObject( rect_brush );
    dc_virt->Rectangle( w_rect );
    rect_pen.DeleteObject();
    rect_brush.DeleteObject();


    CFont newFont;
    newFont.CreatePointFont( 20, L"Times New Roman" );
    dc_virt->SelectObject( &newFont );

    newFont.DeleteObject();
}



void PainterI::OnPaint()
{

    CPaintDC hdc( this );

    RECT rc;
    GetClientRect( &rc );
    RectF bounds( 0, 0, float( rc.right ), float( rc.bottom ) );

    HDC hdcMem = CreateCompatibleDC( hdc );
    HBITMAP hScreen = CreateCompatibleBitmap( hdc, (int)bounds.Width, (int)bounds.Height );
    HBITMAP oldScreen = (HBITMAP)SelectObject( hdcMem, hScreen );
    PatBlt( hdcMem, 0, 0, (int)bounds.Width, (int)bounds.Height, WHITENESS );

    Graphics g( hdcMem );
    g.Clear( StylesFigures::fon_color );
    g.SetPageUnit( UnitPixel );                               

    window_width = (int)bounds.Width;
    window_height = (int)bounds.Height;

    g.SetSmoothingMode( SmoothingMode::SmoothingModeAntiAlias ); 


    Color color = StylesFigures::section_lines_color;
    Pen pen( color, StylesFigures::pen_width );
    pen.SetDashStyle( DashStyle::DashStyleDash );

	std::map<eModelObjectType, std::vector<CoordinatesObject*>> model_map = model.GetObjectMap();
	

    for (auto it = begin(model_map); it != end(model_map); it++)
	{
		if (it->first == eModelObjectType::BASE_POINT)
			if (!it->second.empty())
				PaintPoints(it->second, &g);



       if (it->first == eModelObjectType::BASE_POLYGON)
            if (!it->second.empty())
                PaintFaces( it->second, &g );  
        
        if (it->first == eModelObjectType::BASE_SEGMENT)
			if (!it->second.empty())
				PaintSegments(it->second, &g);
		
	}

    BitBlt( hdc, 0, 0, 1200, 700, hdcMem, 0, 0, SRCCOPY );
    SelectObject( hdcMem, oldScreen );
    DeleteObject( hScreen );
    DeleteDC( hdcMem );
}


bool PainterI::IsDushSegment( int id_elem ) const
{
   
    return false;
}


void PainterI::PaintSegments(const std::vector<CoordinatesObject*>& segments, Graphics* g) const
{
    for (int i = 0; i < segments.size(); i++)
        PaintSegment( *dynamic_cast<CoordinatesSegment*>(segments.at(i)), g );
}


void PainterI::PaintSegment( const CoordinatesSegment& seg, Graphics* g ) const
{
    Color cr = seg.GetColor();

    Gdiplus::Point p1 = AdaptPointCoordinates( seg.GetUnitPoints().c1 );
    Gdiplus::Point p2 = AdaptPointCoordinates( seg.GetUnitPoints().c2 );

    Color color( cr.GetRed(), cr.GetGreen(), cr.GetBlue() );
    Pen pen( color, 1 );
    SolidBrush brush( color );
    g->DrawLine( &pen, p1, p2 );
}


//void PainterI::PaintSnowSegment( const CoordinatesSegment& seg, Graphics* g ) const
//{
//    Color cr = seg.GetColor();
//
//    Gdiplus::Point p1 = AdaptPointCoordinates( seg.GetUnitPoints().c1 );
//    Gdiplus::Point p2 = AdaptPointCoordinates( seg.GetUnitPoints().c2 );
//
//    Color color( cr.GetRed(), cr.GetGreen(), cr.GetBlue() );
//    Pen pen( color, 1 );
//    SolidBrush brush( color );
//    g->DrawLine( &pen, p1, p2 );
//}


void PainterI::PaintPoints( const std::vector<CoordinatesObject*>& points, Graphics* g ) const
{
	for (int i = 0; i < points.size(); i++)
        PaintPoint( *dynamic_cast<CoordinatesPoint*>(points.at( i )), g );
}



Point Rotate( Point p, Point c, double a ) 
{
    double alfa = a * 3.14159265 / 180.0;
    double Bx = cos( alfa ) * (p.X - c.X) - sin( alfa ) * (p.Y - c.Y);
    double By = sin( alfa ) * (p.X - c.X) + cos( alfa ) * (p.Y - c.Y);
    Point cp( c.X + Bx, c.Y + By );
    return  cp;
}


Point GetPointIntoSeg( Point p1, Point p2, double k )
{
    return Point( p1.X + (p2.X - p1.X) * k, p1.Y + (p2.Y - p1.Y) * k );
}

void PainterI::PaintSnowFace(const CoordinatesPolygon& face, Graphics* g ) const
{
    Color c = face.GetColor();
    Pen pen( c, 1 );
    SolidBrush brush( c );
    const int t = face.pts_size;
    Point pts[12];
    std::vector<CoordinatesPoint> coords = face.GetCoordinates();
    for (int i = 0; i < face.pts_size; i++)
        pts[i*4] = AdaptPointCoordinates( coords.at( i ) );


    Point pm = GetPointIntoSeg( pts[4], pts[0], 0.5 );
    Point pc = GetPointIntoSeg( pts[8], pm, 2.0/3.0 );
    
    pts[1] = GetPointIntoSeg( pts[0], pts[4], 1.0 / 3.0 );

    pts[2] = Rotate( pts[0], pc, 60 );

    pts[3] = GetPointIntoSeg( pts[0], pts[4], 2.0 / 3.0 );

    pts[5] = GetPointIntoSeg( pts[4], pts[8], 1.0 / 3.0 );

    pts[6] = Rotate( pts[0], pc, 180 );

    pts[7] = GetPointIntoSeg( pts[4], pts[8], 2.0 / 3.0 );

    pts[9] = GetPointIntoSeg( pts[8], pts[0], 1.0 / 3.0 );

    pts[10] = Rotate( pts[0], pc, -60);

    pts[11] = GetPointIntoSeg( pts[8], pts[0], 2.0 / 3.0 );

    PointF fp( (Gdiplus::REAL)pc.X, (Gdiplus::REAL)pc.Y );
    Rect rect( pc.X - StylesFigures::point_radius, pc.Y - StylesFigures::point_radius, 2 * StylesFigures::point_radius, 2 * StylesFigures::point_radius );
    Rect rect2( pts[9].X - StylesFigures::point_radius, pts[9].Y - StylesFigures::point_radius, 2 * StylesFigures::point_radius, 2 * StylesFigures::point_radius );
    SolidBrush brush2( Color::DarkSeaGreen );
   
    
    g->FillPolygon( &brush, pts, 12 );
    //g->FillEllipse( &brush, rect );
    //g->FillEllipse( &brush, rect2 );
}

void PainterI::PaintFace( const CoordinatesPolygon& face, Graphics* g ) const
{
    Color c = face.GetColor();
    Pen pen( c, 1 );
    SolidBrush brush( c );
    const int t = face.pts_size;
    Point pts[300];
    std::vector<CoordinatesPoint> coords = face.GetCoordinates();
    for (int i = 0; i < face.pts_size; i++)
        pts[i] = AdaptPointCoordinates( coords.at( i ) );

    g->FillPolygon( &brush, pts, face.pts_size );
}


void PainterI::PaintFaces( const std::vector<CoordinatesObject*>& faces, Graphics* g ) const
{
    for (unsigned int i = 0; i < faces.size(); i++)
        PaintFace( *dynamic_cast<CoordinatesPolygon*>(faces.at( i )), g );
}


void PainterI::PaintPoint( const CoordinatesPoint& point, Graphics* g ) const
{
    Color color;

    Point p( AdaptPointCoordinates( point ) );
    PointF fp((Gdiplus::REAL)p.X, (Gdiplus::REAL)p.Y); 
    Rect rect( p.X - StylesFigures::point_radius, p.Y - StylesFigures::point_radius, 2 * StylesFigures::point_radius, 2 * StylesFigures::point_radius );
    SolidBrush brush( color );
    if (!point.IsVisible())
        brush.SetColor( Color( 100, 72, 27, 72) );
    g->FillEllipse( &brush, rect );
}


void PainterI::PaintPointName( const CoordinatesPoint& point, Graphics* g ) const
{
    Point p( AdaptPointCoordinates( point ) );
    Gdiplus::Font myFont( L"Arial", 11 );
    SolidBrush blackBrush( Color( 255, 0, 0, 0 ) );
    PointF fp( (Gdiplus::REAL)p.X, (Gdiplus::REAL)p.Y );
    g->DrawString( CStringW( point.GetName().c_str() ), 2, &myFont, fp, &blackBrush );
}


void PainterI::PaintPointsName( const std::vector<CoordinatesPoint>& points, Graphics* g ) const
{
    Color color;

    for (auto it = begin( points ); it != end( points ); it++)
        PaintPointName( *it, g );

}


Gdiplus::Point PainterI::AdaptPointCoordinates(const CoordinatesPoint& p) const
{
   // int sw = (int)(window_width / 2);
   // int sh = (int)(window_height / 2);
	//Gdiplus::Point pt( p.GetPos().x + sw, window_height - (p.GetPos().y + sh) );
	return Gdiplus::Point(p.GetPos().x, p.GetPos().y);
}


void PainterI::SetModel( CoordinatesModel* model_ )
{
    model.SetObjectMap(model_->GetObjectMap());
}