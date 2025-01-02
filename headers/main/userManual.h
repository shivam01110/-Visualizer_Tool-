#include <gtk/gtk.h>

// Callback function for the 'Close' button
void on_dialog_close(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

GtkWidget *createUserManual(){

    // Create the dialog box
    GtkWidget *dialog = gtk_dialog_new_with_buttons("User Manual", GTK_WINDOW(window), GTK_DIALOG_MODAL,
                                                    "OK", GTK_RESPONSE_CLOSE, NULL);

    // Set the position of the dialog box
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    // Create a label with the user manual content
    GtkWidget *label = gtk_label_new("This is the user manual content.");

    // Add the label to the dialog's content area
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_add(GTK_CONTAINER(content_area), label);

    // Connect the close signal to the callback function
    g_signal_connect(dialog, "response", G_CALLBACK(on_dialog_close), NULL);

    // Show the dialog box
    gtk_widget_show_all(dialog);
}