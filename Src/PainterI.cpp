#include "stdafx.h"
#include "PainterI.h"



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

    PaintSegments( model.GetBaseSegments(), &g );
    PaintPoints( model.GetBasePoints(), &g );


    BitBlt( hdc, 0, 0, 1200, 700, hdcMem, 0, 0, SRCCOPY );
    SelectObject( hdcMem, oldScreen );
    DeleteObject( hScreen );
    DeleteDC( hdcMem );
}


bool PainterI::IsDushSegment( int id_elem ) const
{
   
    return false;
}


void PainterI::PaintSegments( const std::vector<CoordinatesSegment>& segments, Graphics* g ) const
{
    Color color;

    int id = 0;   
    for (auto it = begin( segments ); it != end( segments ); it++)
    {
        Pen pen( color, StylesFigures::pen_width );
        
        g->DrawLine( &pen, AdaptPointCoordinates( it->GetPoints().c1 ), AdaptPointCoordinates( it->GetPoints().c2 ) );
        id++;
    }

}

void PainterI::PaintPoints( const std::vector<CoordinatesPoint>& points, Graphics* g ) const
{
    for (auto it = begin( points ); it != end( points ); it++)
        PaintPoint( *it, g );
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
    if (!point.GetVisible())
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


Point PainterI::AdaptPointCoordinates( const CoordinatesPoint& p ) const
{
    int sw = (int)(window_width / 2);
    int sh = (int)(window_height / 2);
    Point pt( p.GetPos().x + sw, window_height - (p.GetPos().y + sh) );
    return pt;
}


void PainterI::SetModel( const CoordinatesModel& model_ )
{
    model = model_;
}