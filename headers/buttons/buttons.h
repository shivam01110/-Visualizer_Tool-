#include <gtk/gtk.h>

void on_button_enter(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    GdkWindow *gdkWindow = gtk_widget_get_window(widget);
    GdkCursor *cursor = gdk_cursor_new_from_name(gdk_window_get_display(gdkWindow), "pointer");
    gdk_window_set_cursor(gdkWindow, cursor);
    g_object_unref(cursor);

    // Add CSS class for hover effect
    GtkStyleContext *styleContext = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(styleContext, "hover");
}

void on_button_leave(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    GdkWindow *gdkWindow = gtk_widget_get_window(widget);
    gdk_window_set_cursor(gdkWindow, NULL);

    // Remove CSS class for hover effect
    GtkStyleContext *styleContext = gtk_widget_get_style_context(widget);
    gtk_style_context_remove_class(styleContext, "hover");
}
