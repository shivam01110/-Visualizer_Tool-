#include <gtk/gtk.h>

void on_color_choosen(GtkColorButton *colorbutton, gpointer user_data)
{   

    // Get the RGBA color from the color button
    GdkRGBA color;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(colorbutton), &color);

    // set the RGB values
    colorValue[0] =(double)color.red;
    colorValue[1] =(double) color.green;
    colorValue[2] = (double)color.blue;
}

GtkWidget *createColorChooser()
{
    GtkWidget *color_button = gtk_color_button_new();
    g_signal_connect(color_button, "color-set", G_CALLBACK(on_color_choosen), NULL);
    return color_button;
}
