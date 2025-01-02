#include <gtk/gtk.h>

void line_width_changed(GtkRange *range, gpointer data) {

    // changing the line width to current line width value
    *lineWidth = (double)gtk_range_get_value(range);
}

GtkWidget *createRangeSlider()
{
    GtkWidget *scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 5, 0.1);
    gtk_range_set_value(GTK_RANGE(scale), 1);
    g_signal_connect(scale, "value-changed", G_CALLBACK(line_width_changed), NULL);
    return scale;
}