#include <gtk/gtk.h>

static void clear_button_clicked(GtkWidget *widget, gpointer data)
{
    // deleting all figures
    clear_figures(figureStack);

    //redrawing the canvas for cleared output
    gtk_widget_queue_draw(canvas);

}

GtkWidget *createClearButton()
{
    // creating a button
    GtkWidget *button = gtk_button_new_with_label("Clear");

    g_signal_connect(button, "clicked", G_CALLBACK(clear_button_clicked), NULL);

    // Connect the enter and leave signals to change the cursor
    g_signal_connect(button, "enter-notify-event", G_CALLBACK(on_button_enter), NULL);
    g_signal_connect(button, "leave-notify-event", G_CALLBACK(on_button_leave), NULL);

    // Add a custom CSS class to the button
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "btn");
    gtk_widget_set_size_request(button, 10, 20);
    return button;
}