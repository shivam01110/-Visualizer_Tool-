#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>

struct Canvas_hover_CallbackArgs
{
    GtkWidget *x_Label;
    GtkWidget *y_Label;
};

gboolean on_canvas_leave_notify(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    g_print("Mouse left the canvas.\n");
    return FALSE;
}

gboolean on_canvas_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{

    // Cast the data pointer to the CallbackArgs structure
    struct Canvas_hover_CallbackArgs *args = (struct Canvas_hover_CallbackArgs *)data;

    // Accessing the arguments passed to the callback
    GtkWidget *x_label = args->x_Label;
    GtkWidget *y_label = args->y_Label;

    int cx = (int)((gtk_widget_get_allocated_width(widget) / 20) / 2) * 20;
    int cy = (int)((gtk_widget_get_allocated_height(widget) / 20) / 2) * 20;

    char textx[20];
    char texty[20];
    snprintf(textx, sizeof(textx), "X: %.0lf", event->x - cx);
    snprintf(texty, sizeof(texty), "Y: %.0lf", cy - event->y);

    gtk_label_set_text(GTK_LABEL(x_label), textx);
    gtk_label_set_text(GTK_LABEL(y_label), texty);

    return TRUE;
}

void draw_arrow_head(cairo_t *cr, double x1, double y1, double x2, double y2, double arrow_size)
{
    double angle = atan2(y2 - y1, x2 - x1);
    cairo_move_to(cr, x2, y2);
    cairo_rel_line_to(cr, -arrow_size * cos(angle - G_PI / 6), -arrow_size * sin(angle - G_PI / 6));
    cairo_move_to(cr, x2, y2);
    cairo_rel_line_to(cr, -arrow_size * cos(angle + G_PI / 6), -arrow_size * sin(angle + G_PI / 6));
    cairo_stroke(cr);
}

gboolean draw_on_canvas(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    guint width, height;
    GdkRGBA color;
    gdk_rgba_parse(&color, "#FFFFFF");
    GtkStyleContext *context;

    context = gtk_widget_get_style_context(widget);

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    gtk_render_background(context, cr, 0, 0, width, height);
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_paint(cr);

    // creating coordinates lines
    int spacing = 20;
    cairo_set_line_width(cr, 2.0);
    cairo_set_source_rgb(cr, 0.90, 0.90, 0.90); // gray color

    // Draw horizontal lines
    for (int i = 0; i < height; i += spacing)
    {
        cairo_move_to(cr, 0.0, i);   // Starting point
        cairo_line_to(cr, width, i); // Ending point
        cairo_stroke(cr);
    }

    // Draw horizontal lines
    for (int i = 0; i < width; i += spacing)
    {
        cairo_move_to(cr, i, 0.0);    // Starting point
        cairo_line_to(cr, i, height); // Ending point
        cairo_stroke(cr);
    }

    // locating the center
    int cx = (int)((width / spacing) / 2) * spacing;
    int cy = (int)((height / spacing) / 2) * spacing;

    // creating vertical dark line
    cairo_set_source_rgb(cr, 0.40, 0.40, 0.40);
    cairo_move_to(cr, cx, 20.0);
    cairo_line_to(cr, cx, height - 20);
    cairo_stroke(cr);

    // for down arrow
    draw_arrow_head(cr, cx, 20.0, cx, height - 20, 10);

    // for up arrow
    draw_arrow_head(cr, cx, height - 20, cx, 20.0, 10);

    // creating horizontal dark line
    cairo_move_to(cr, 30.0, cy);
    cairo_line_to(cr, width - 30, cy);
    cairo_stroke(cr);

    // creating left arrow
    draw_arrow_head(cr, width - 30, cy, 30.0, cy, 10);

    // creating right arrow
    draw_arrow_head(cr, 30.0, cy, width - 30, cy, 10);

    gtk_style_context_get_color(context, gtk_style_context_get_state(context), &color);
    gdk_cairo_set_source_rgba(cr, &color);

    cairo_fill(cr);

    drawFigures(data, cr, cx, cy);

    return FALSE;
}

GtkWidget *createCanvas(struct FigureStack *figureStack, GtkWidget *xLabel, GtkWidget *yLabel)
{
    GtkWidget *drawing_area = gtk_drawing_area_new();

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_on_canvas), figureStack);

    // Set the event mask for the canvas to enable motion events
    gtk_widget_add_events(drawing_area, GDK_POINTER_MOTION_MASK);

    // passing x label and y label to change
    struct Canvas_hover_CallbackArgs *args = (struct Canvas_hover_CallbackArgs *)malloc(sizeof(struct Canvas_hover_CallbackArgs));
    args->x_Label = xLabel;
    args->y_Label = yLabel;
    // Connect the motion-notify-event signal to the on_canvas_motion_notify function
    g_signal_connect(drawing_area, "motion-notify-event", G_CALLBACK(on_canvas_motion_notify), args);

    // for changing cursor on mouse leave
    g_signal_connect(drawing_area, "leave-notify-event", G_CALLBACK(on_canvas_leave_notify), NULL);

    return drawing_area;
}