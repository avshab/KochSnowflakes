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

	std::map<eModelObjectType, std::vector<ModelObject*>> model_map = model.GetObjectMap();
	
	for (auto it = begin(model_map); it != end(model_map); it++)
	{
		if (it->first == eModelObjectType::BASE_POINT)
			if (!it->second.empty())
				PaintPoints(it->second, &g);

		if (it->first == eModelObjectType::BASE_SEGMENT)
			if (!it->second.empty())
				PaintSegments(it->second, &g);
		
	}

    BitBlt( hdc, 0, 0, 1200, 700, hdcMem, 0, 0, SRCCOPY );
    SelectObject( hdcMem, oldScreen );
    DeleteObject( hScreen );
    DeleteDC( hdcMem );

    model.Clear();
}


bool PainterI::IsDushSegment( int id_elem ) const
{
   
    return false;
}


void PainterI::PaintSegments(const std::vector<ModelObject*>& segments, Graphics* g) const
{
    Color color;
	for (auto it = begin(segments); it != end(segments); it++)
    {
        Color color = StylesFigures::section_lines_color;
        Pen pen( color, 1 );
		CoordinatesSegment* s = dynamic_cast<CoordinatesSegment*>(*it);
        Gdiplus::Point p1 = AdaptPointCoordinates( s->GetPoints().c1 );
        Gdiplus::Point p2 = AdaptPointCoordinates( s->GetPoints().c2 );
		g->DrawLine(&pen, p1, p2);
    }

}

void PainterI::PaintPoints(const std::vector<ModelObject*>& points, Graphics* g) const
{
	for (int i = 0; i < points.size(); i++)
	{
		CoordinatesPoint* s = dynamic_cast<CoordinatesPoint*>(points.at(i));
		PaintPoint( *s, g );
	}   
}


void PainterI::PaintFace( int iteration, const CoordinatesFace& face, Graphics* g ) const
{
    Color color;

   
    SolidBrush brush( color );
    Point pts[10];

   // for (int i = 0; i < face.num_nodes; i++)
   //     pts[i] = AdaptPointCoordinates( face.nodes.at( i ) );

    
   // g->FillPolygon( &brush, pts, face.num_nodes );
}


void PainterI::PaintFiguresFaces( const std::vector<CoordinatesFace>& faces, Graphics* g ) const
{
    for (unsigned int i = 0; i < faces.size(); i++)
        if (faces.at( i ).GetVisible())//IsVisibleSegment(i))       // if (i == 0 || i == 3 || i == 5)       //      
            PaintFace( i, faces.at( i ), g );
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


void PainterI::SetModel( const CoordinatesModel& model_ )
{
    model = model_;
}