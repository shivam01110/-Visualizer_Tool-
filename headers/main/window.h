#include <gtk/gtk.h>

GtkWidget *createWindow()
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Visualizer Tool");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);

    // connecting the destroy signal to the callback function
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    return window;
}