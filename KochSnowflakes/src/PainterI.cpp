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

		if (it->first == eModelObjectType::BASE_SEGMENT)
			if (!it->second.empty())
				PaintSegments(it->second, &g);

        if (it->first == eModelObjectType::BASE_POLYGON)
            if (!it->second.empty())
                PaintFaces( it->second, &g );
		
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
	for (auto it = begin(segments); it != end(segments); it++)
    {
		Color cr = dynamic_cast<CoordinatesSegment*>(*it)->GetColor();
        
        Gdiplus::Point p1 = AdaptPointCoordinates( dynamic_cast<CoordinatesSegment*>(*it)->GetUnitPoints().c1 );
        Gdiplus::Point p2 = AdaptPointCoordinates( dynamic_cast<CoordinatesSegment*>(*it)->GetUnitPoints().c2 );

        Color color( cr.GetRed(), cr.GetGreen(), cr.GetBlue() );    
        Pen pen( color, 1 );
        SolidBrush brush( color );
		g->DrawLine(&pen, p1, p2);
    }
}

void PainterI::PaintPoints( const std::vector<CoordinatesObject*>& points, Graphics* g ) const
{
	for (int i = 0; i < points.size(); i++)
        PaintPoint( *dynamic_cast<CoordinatesPoint*>(points.at( i )), g );
}


void PainterI::PaintFace(const CoordinatesPolygon& face, Graphics* g ) const
{
    Color c = face.GetColor();
    Pen pen( c, 1 );
    SolidBrush brush( c );
    const int t = face.pts_size;
    Point pts[3100];
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