#include <gtk/gtk.h>
#include <math.h>
// function for drawing a point
void draw_point(cairo_t *cr, double x1, double y1, double *color)
{
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    // Drawing the point with x,y coordinate
    cairo_arc(cr, x1, y1, 3.0, 0, 2 * G_PI);
    // filling the point with color
    cairo_fill(cr);
}
// function for drawing a line
void draw_line(cairo_t *cr, double x1, double y1, double x2, double y2, double *color, double lineWidth)
{
    // Set the drawing color to black
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);
    // Move to the first point of the
    cairo_move_to(cr, x1, y1);

    // Draw lines connecting the
    cairo_line_to(cr, x2, y2);

    // Stroke the path to draw the outline
    cairo_stroke(cr);
}
// function for drawing an arc
void draw_arc(cairo_t *cr, double x1, double y1, double r, float angle1, float angle2, double *color, double lineWidth)
{

    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    // Draw the circle
    // cairo_arc(cr, x1, y1, r, 2 * G_PI-(G_PI/180)*angle1, angle2);
    cairo_arc(cr, x1, y1, r, -1 * (G_PI / 180) * angle2, -1 * (G_PI / 180) * angle1);
    cairo_stroke(cr);
}
// function for drawing a circle
void draw_circle(cairo_t *cr, double x1, double y1, double r, double *color, double lineWidth)
{

    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    // Draw the circle
    cairo_arc(cr, x1, y1, r, 0, 2 * G_PI);
    cairo_stroke(cr);
}
// function for drawing a triangle
void draw_traingle(cairo_t *cr, double x1, double y1, double x2, double y2, double x3, double y3, double *color, double lineWidth)
{
    // Set the drawing color to black
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);
    // Move to the first point of the triangle
    cairo_move_to(cr, x1, y1);

    // Draw lines connecting the three points of the triangle
    cairo_line_to(cr, x2, y2);
    cairo_line_to(cr, x3, y3);
    cairo_line_to(cr, x1, y1);

    // Stroke the path to draw the outline of the triangle
    cairo_stroke(cr);
}
// function for drawing a rectangle
void draw_rectangle(cairo_t *cr, double x1, double y1, double width, double height, double *color, double lineWidth)
{
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    // draw rectangle
    cairo_rectangle(cr, x1, y1, width, height);
    cairo_stroke(cr);
}
// function for drawing an ellipse
void draw_ellipse(cairo_t *cr, double xc, double yc, double radius_x, double radius_y, double *color, double lineWidth)
{
    cairo_save(cr);
    // Set the line width and color
    cairo_set_line_width(cr, lineWidth);
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);

    // Draw the ellipse
    cairo_translate(cr, xc, yc);
    cairo_scale(cr, 1.0, radius_y / radius_x);
    cairo_arc(cr, 0, 0, radius_x, 0, 2 * G_PI);
    cairo_stroke(cr);
    cairo_restore(cr);
}
// function for drawing a horizontal parabola
void draw_H_parabola(cairo_t *cr, int height, double focus_x, double focus_y, double latus_rectum, double *color, double lineWidth)
{
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    // calculating vertex
    double vertex_x = focus_x - latus_rectum / 2.0;
    double vertex_y = focus_y;

    // Calculate the focal length of the parabola
    double focal_length = latus_rectum / 4.0;

    // Move to the starting point of the parabola
    cairo_move_to(cr, vertex_x, 0);

    // Draw the parabola by calculating points along the curve
    for (int y = 1; y <= height; y++)
    {
        // Calculate the x-coordinate using the equation of the parabola
        double x = vertex_x + ((y - vertex_y) * (y - vertex_y)) / (4 * focal_length);

        // Draw a line segment to the current point
        cairo_line_to(cr, x, y);
    }

    // Stroke the path to draw the parabola
    cairo_stroke(cr);
}
// function for drawing a vertical parabola
void draw_V_parabola(cairo_t *cr, int width, double focus_x, double focus_y, double latus_rectum, double *color, double lineWidth)
{
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    // calculating vertex
    double vertex_x = focus_x;
    double vertex_y = focus_y - 1 * (latus_rectum) / 2.0;

    // Calculate the focal length of the parabola
    double focal_length = -1 * latus_rectum / 4.0;

    // Move to the starting point of the parabola
    cairo_move_to(cr, 0, vertex_y);

    // Draw the parabola by calculating points along the curve
    for (int x = 1; x <= width; x++)
    {
        // Calculate the y-coordinate using the equation of the parabola
        double y = vertex_y + ((x - vertex_x) * (x - vertex_x)) / (4 * focal_length);

        // Draw a line segment to the current point
        cairo_line_to(cr, x, y);
    }

    // Stroke the path to draw the parabola
    cairo_stroke(cr);
}
// function for drawing a horizontal hyperbola
void draw_H_hyperbola(cairo_t *cr, double xc, double yc, double radius_x, double radius_y, double *color, double lineWidth)
{
    // radiusx = Distance from center to transverse axis
    // radiusy = Distance from center to conjugate axis

    // Set the color and width of the hyperbola
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    // Draw the hyperbola using line segments
    for (double angle = 0; angle < G_PI / 2; angle += 0.01)
    {
        double x = xc + radius_x / cos(angle);
        double y = yc + radius_y * (sin(angle) / cos(angle));
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);

    for (double angle = G_PI; angle > G_PI / 2; angle -= 0.01)
    {
        double x = xc + radius_x / cos(angle);
        double y = yc + radius_y * (sin(angle) / cos(angle));
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);

    for (double angle = G_PI; angle < 3 * G_PI / 2; angle += 0.01)
    {
        double x = xc + radius_x / cos(angle);
        double y = yc + radius_y * (sin(angle) / cos(angle));
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);

    for (double angle = 2 * G_PI; angle > 3 * G_PI / 2; angle -= 0.01)
    {
        double x = xc + radius_x / cos(angle);
        double y = yc + radius_y * (sin(angle) / cos(angle));
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);
}
// function for drawing a vertical hyperbola
void draw_V_hyperbola(cairo_t *cr, double xc, double yc, double radius_x, double radius_y, double *color, double lineWidth)
{
    // radiusx = Distance from center to transverse axis
    // radiusy = Distance from center to conjugate axis

    // Set the color and width of the hyperbola
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    // Draw the hyperbola using line segments
    for (double angle = 0; angle < G_PI / 2; angle += 0.01)
    {
        double y = yc + radius_y / cos(angle);
        double x = xc + radius_x * (sin(angle) / cos(angle));
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);

    for (double angle = G_PI; angle > G_PI / 2; angle -= 0.01)
    {
        double y = yc + radius_y / cos(angle);
        double x = xc + radius_x * (sin(angle) / cos(angle));
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);

    for (double angle = G_PI; angle < 3 * G_PI / 2; angle += 0.01)
    {
        double y = yc + radius_y / cos(angle);
        double x = xc + radius_x * (sin(angle) / cos(angle));
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);

    for (double angle = 2 * G_PI; angle > 3 * G_PI / 2; angle -= 0.01)
    {
        double y = yc + radius_y / cos(angle);
        double x = xc + radius_x * (sin(angle) / cos(angle));
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);
}
// function for drawing a cycloid
void draw_cycloid(cairo_t *cr, double xc, double yc, double radius, double revolutions, double *color, double lineWidth)
{
    // Set line color and width
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    double t, x, y;
    double angle = 0.0;

    for (angle = 0; angle <= 2 * revolutions * G_PI; angle += 0.01)
    {
        x = xc + radius * (angle - sin(angle));
        y = yc - radius * (1 - cos(angle));
        cairo_line_to(cr, x, y);
    }

    cairo_stroke(cr);
}
// function for drawing an epicycloid
void draw_epicycloid(cairo_t *cr, double xc, double yc, double r, double R, double *color, double lineWidth)
{ // r and R is  radius of revoling circle and fixed circle respectively
    //(xc,xy) is the coordinate of the fixed circle
    double x, y;
    double angle = 0.0;
    // Set the color and width of the epicycloid
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);
    for (angle = 0.0; angle <= 2 * G_PI; angle += 0.01)
    {
        x = xc + (r + R) * cos(angle) - r * cos((r + R) * angle / r);
        y = yc + (r + R) * sin(angle) - r * sin((r + R) * angle / r);
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);
    cairo_set_source_rgba(cr, color[0], color[1], color[2], 0.2);
    cairo_arc(cr, xc, yc, R, 0, 2 * G_PI);
    cairo_stroke(cr);
}
// function to draw a hypocycloid
void draw_hypocycloid(cairo_t *cr, double xc, double yc, double r, double R, double *color, double lineWidth)
{ // r and R is  radius of revoling circle and fixed circle respectively
    //(xc,xy) is the coordinate of the fixed circle
    double x, y;
    double angle = 0.0;
    // Set the color and width of the hypocycloid
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);
    for (angle = 0.0; angle <= 2 * G_PI; angle += 0.01)
    {
        x = xc + (R - r) * cos(angle) + r * cos((R - r) * angle / r);
        y = yc + (R - r) * sin(angle) - r * sin((R - r) * angle / r);
        cairo_line_to(cr, x, y);
    }
    cairo_stroke(cr);
    cairo_set_source_rgba(cr, color[0], color[1], color[2], 0.2);
    cairo_arc(cr, xc, yc, R, 0, 2 * G_PI);
    cairo_stroke(cr);
}
// function for drawing a spiral
void draw_spiral(cairo_t *cr, double x, double y, double radius, int turns, double *color, double lineWidth)
{
    // Set line color and width
    cairo_set_source_rgb(cr, color[0], color[1], color[2]);
    cairo_set_line_width(cr, lineWidth);

    // Set the initial radius and angle
    double radius_temp = 0.0;
    double angle = 0.0;

    // Draw the spiral
    cairo_move_to(cr, x, y);
    for (double t = 0; t <= turns * 2 * G_PI; t += 0.1)
    {
        radius_temp = t * radius;
        angle = t;
        double spiral_x = x + radius_temp * cos(angle);
        double spiral_y = y + radius_temp * sin(angle);
        cairo_line_to(cr, spiral_x, spiral_y);
    }

    // Stroke the path (draw the spiral)
    cairo_stroke(cr);
}
void draw_mirrorImage(cairo_t *cr, double cx, double cy, double x, double y, double m, double c, double *color, double lineWidth)
{

    // drawing the input point
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_arc(cr, x, y, 3.0, 0, 2 * G_PI);
    cairo_fill(cr);

    // if line is y = mx + c;
    double x1, y1, x2, y2;

    // calculating end points from user coordinates
    y1 = cy + 60; // adding 60 spacing for making line extend beyond the canvas
    x1 = (y1 - c) / m;
    y2 = -cy - 60; // reducing 60 spacing for making line extend beyond the canvas
    x2 = (y2 - c) / m;

    // converting to canvas coordinates and drawing line

    // drawing the mirror line
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 0.8);
    cairo_move_to(cr, x1 + cx, cy - y1);
    cairo_line_to(cr, x2 + cx, cy - y2);
    cairo_stroke(cr);

    // actual user coordinates
    double userX = x - cx;
    double userY = cy - y;

    // Calculate the mirror image point

    double d = (m * userX - userY + c) / (m * m + 1);
    double mirrorX = -2 * d * m + userX;
    double mirrorY = 2 * d + userY;

    draw_point(cr, mirrorX + cx, cy - mirrorY, color);

    cairo_stroke(cr);
}
