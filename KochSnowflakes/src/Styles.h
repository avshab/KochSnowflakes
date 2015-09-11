#pragma once


namespace StylesFigures
{
    const Color fon_color( 255, 255, 255 ); //217

    const Color axis_lines_color( 219, 215, 210 );

    const Color extra_color( 102, 51, 0 );

    const Color section_lines_color( 118, 118, 188 );

    const Color figures_lines_color( 180, 64, 64, 64 );

    const Color section_face_color( 204, 204, 255 );

    const struct ColorFigureFace
    {
        const int transparency = 70;
        const int R = 96;//142;//
        const int G = 96;//180;//
        const int B = 96;//227;//
    };                        
                              
    const ColorFigureFace figure_color;

    const Color figures_points_name_color( 140, 96, 96, 96 );

    const Color section_points_name_color( 140, 96, 96, 96 );

    const Color figures_points_color( 127, 199, 255 );

    const Color section_points_color( 140, 62, 173 );

    const int point_radius = 4;

    const Gdiplus::REAL pen_width = 2;

    namespace Face
    {
        const bool line_style[3] = { 1, 1, 1 };
        const bool face_style = true;
    };

    namespace Cube
    {
        const bool line_style[12] = { 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 };
        const bool face_style[6] = { 0, 1, 0, 1, 1, 0 };
    };


    namespace Parallelogram
    {
        const bool line_style[12] = { 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 };
        const bool face_style[6] = { 0, 1, 0, 1, 1, 0 };
    };


    namespace Tetrahedron
    {
        const bool line_style[6] = { 1, 0, 0, 0, 0, 0 };
        const bool face_style[4] = { 0, 0, 1, 1 }; 
    };


    namespace SquarePyramid
    {
        const bool line_style[8] = { 1, 0, 0, 1, 1, 0, 0, 0 };
        const bool face_style[5] = { 0, 0, 1, 1, 0 };
    };

    namespace PentagonPyramid
    {
        const bool line_style[10] = { 1, 0, 0, 0, 1, 1, 0, 0, 0, 0 };
        const bool face_style[6] = { 0, 0, 1, 1, 1, 0 };
    };

    namespace PentagonPrisma
    {
        const bool line_style[15] = { 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1,0, 0, 0 };
        const bool face_style[7] = { 0, 1, 0, 0, 1, 1, 0 };
    };

    namespace TrianglePrisma
    {
        const bool line_style[9] = { 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        const bool face_style[5] = { 0, 1, 0, 1, 1 };
    };

    namespace HexagonPrisma
    {
        const bool line_style[18] = { 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 };
        const bool face_style[8] = { 0, 1, 0, 0, 1, 1, 1, 0 };
    };

    namespace HexagonPyramid
    {
        const bool line_style[12] = { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 };
        const bool face_style[7] = { 0, 0, 1, 1, 1, 1, 0 };
    };

};