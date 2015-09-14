#pragma once
#include "CoordinatesFace.h"
#include "CoordinatesModel.h"
#include <vector>



class PainterI 
    : public CWnd
{
public:

    PainterI();

    virtual ~PainterI();

    void OnPaint();

    virtual void SetModel( const CoordinatesModel& model );

protected:

    DECLARE_MESSAGE_MAP();

    BOOL PreCreateWindow( CREATESTRUCT& cs );

private:

    int window_width;

    int window_height;

    CoordinatesModel model;

private:

    void CreateVirtualWindow( CDC* dc_virt, CRect w_rect );

	Gdiplus::Point AdaptPointCoordinates(const CoordinatesPoint& point) const;

	void PaintSegments(const std::vector<ModelObject*>& segments, Graphics* g) const;

    void PaintFiguresFaces( const std::vector<CoordinatesFace>& faces, Graphics* g ) const;

    void PaintFace( int iteration, const CoordinatesFace& points, Graphics* g ) const;
    
    bool IsDushSegment( int id_elem ) const;

    bool IsVisibleSegment( int id_elem ) const;

    void PaintPoint( const CoordinatesPoint& point, Graphics* g ) const;

	void PaintPoints(const std::vector<ModelObject*>& point, Graphics* g) const;

    void PaintPointName( const CoordinatesPoint& point, Graphics* g ) const;

    void PaintPointsName( const std::vector<CoordinatesPoint>& points, Graphics* g ) const;

};

