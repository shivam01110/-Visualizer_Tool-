#include <gtk/gtk.h>
void designTitleBar()
{
    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "VISUALISER TOOL");
    gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);
    
    // GtkWidget *user_m
    // Create the logo widget (e.g., an image or a label)
    GtkWidget * logo = gtk_image_new_from_file("icons/logo.png");
    // Set the desired size for the logo

    // Add the logo widget to the headerbar
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), logo);
}