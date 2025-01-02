#include <gtk/gtk.h>

GtkWidget *createEntryBox()
{

    GtkWidget *entryBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(entryBox), grid, FALSE, FALSE, 0);

    return entryBox;
}
