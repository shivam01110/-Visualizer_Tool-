#include <gtk/gtk.h>
#include "../buttons/draw.h"
#include "../buttons/clear.h"
#include "figureSelect.h"
#include "../canvas/canva.h"
#include "entryBox.h"
#include "../buttons/undo.h"
#include "../buttons/redo.h"
#include "../buttons/chooseColour.h"
#include "../buttons/linewidth.h"

struct KeypressArgs
{
	GtkWidget *draw_button;
	GtkWidget *clear_button;
	GtkWidget *undo_button;
	GtkWidget *redo_button;
};

gboolean on_key_pressed(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	// for activating draw click
	if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_d) || (event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_D))
	{
		GtkWidget *button = ((struct KeypressArgs *)(user_data))->draw_button;
		g_signal_emit_by_name(button, "clicked");
	}
	// for activating undo click
	else if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_z) || (event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_Z))
	{
		GtkWidget *button = ((struct KeypressArgs *)(user_data))->undo_button;
		g_signal_emit_by_name(button, "clicked");
	}
	// for activating redo click
	else if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_y) || (event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_Y))
	{
		GtkWidget *button = ((struct KeypressArgs *)(user_data))->redo_button;
		g_signal_emit_by_name(button, "clicked");
	}
	// for activating clear click
	else if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_c) || (event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_C))
	{
		GtkWidget *button = ((struct KeypressArgs *)(user_data))->clear_button;
		g_signal_emit_by_name(button, "clicked");
	}

	return FALSE;
}

GtkWidget *createSideBar()
{
	GtkWidget *contentArea;
	GtkWidget *hpaned;
	GtkCssProvider *cssProvider;

	GtkWidget *sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_style_context_add_class(gtk_widget_get_style_context(sidebar), "sidebar");

	GtkWidget *selector_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget *tool_bar_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *tools_Label = gtk_label_new("TOOLS");
	gtk_box_pack_start(GTK_BOX(selector_box), tools_Label, FALSE, FALSE, 10);
	gtk_style_context_add_class(gtk_widget_get_style_context(tools_Label), "head-label");

	// creating a select combo box
	GtkWidget *entryBox = createEntryBox();
	GtkWidget *figure_combo = createComboBox(window, entryBox);

	// adding figure combo box and entry box in sidebar
	gtk_box_pack_start(GTK_BOX(selector_box), figure_combo, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(selector_box), entryBox, FALSE, FALSE, 0);

	// creating a x,y coordinate label;
	GtkWidget *coordinate_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget *x_coordinate_label = gtk_label_new("X: 0");
	GtkWidget *y_coordinate_label = gtk_label_new("Y: 0");
	gtk_style_context_add_class(gtk_widget_get_style_context(x_coordinate_label), "x-coordinate");
	gtk_style_context_add_class(gtk_widget_get_style_context(y_coordinate_label), "y-coordinate");
	gtk_box_pack_start(GTK_BOX(coordinate_box), x_coordinate_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(coordinate_box), y_coordinate_label, FALSE, FALSE, 5);
	gtk_widget_set_halign(x_coordinate_label, GTK_ALIGN_START);
	gtk_widget_set_halign(y_coordinate_label, GTK_ALIGN_START);

	gtk_box_pack_start(GTK_BOX(tool_bar_box), coordinate_box, FALSE, FALSE, 10);

	// Create the color button
	GtkWidget *color_label = gtk_label_new("CHOOSE COLOUR");
	GtkWidget *color_button = createColorChooser(colorValue);
	GtkWidget *color_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(color_button_box), color_label, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(color_button_box), color_button, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(tool_bar_box), color_button_box, FALSE, FALSE, 10);

	// creating line width slider
	GtkWidget *line_width_label = gtk_label_new("CHOOSE WIDTH");
	GtkWidget *line_width_slider = createRangeSlider();
	GtkWidget *line_width_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(line_width_box), line_width_label, FALSE, FALSE, 10);
	gtk_widget_set_valign(line_width_label, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(line_width_slider, GTK_ALIGN_CENTER);
	gtk_box_pack_start(GTK_BOX(line_width_box), line_width_slider, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(tool_bar_box), line_width_box, FALSE, FALSE, 10);

	// adding selector box and tool bar box to the sidebar
	gtk_box_pack_start(GTK_BOX(sidebar), selector_box, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(sidebar), tool_bar_box, FALSE, FALSE, 20);

	contentArea = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	// adding the canvas into content area
	canvas = createCanvas(figureStack, x_coordinate_label, y_coordinate_label);
	GtkWidget *canvas_Label = gtk_label_new("CANVAS");
	gtk_style_context_add_class(gtk_widget_get_style_context(canvas_Label), "head-label");
	gtk_box_pack_start(GTK_BOX(contentArea), canvas_Label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(contentArea), canvas, TRUE, TRUE, 0);

	// creating the draw button in the bottom bar
	GtkWidget *draw_button = createDrawButton(figure_combo, entryBox);

	// creating the clear button in the bottom bar
	GtkWidget *clear_button = createClearButton();

	// creating undo button in the bottom bar
	GtkWidget *undo_button = createUndoButton();

	// creating a redo button in the bottom bar
	GtkWidget *redo_button = createRedoButton();

	// creating the bottom bar
	GtkWidget *bottom_bar = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(bottom_bar), TRUE);
	gtk_style_context_add_class(gtk_widget_get_style_context(bottom_bar), "bottom-bar");

	// Set the height of the bottom bar
	gtk_widget_set_size_request(bottom_bar, -1, 30); // Set the desired height

	// Create another horizontal box to hold the draw_button
	GtkWidget *draw_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(draw_button_box), draw_button, FALSE, FALSE, 0);
	gtk_grid_attach(GTK_GRID(bottom_bar), draw_button_box, 0, 0, 1, 1);

	// Create a horizontal grid to hold the undo_button and redo_button
	GtkWidget *middle_buttons_box = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(middle_buttons_box), TRUE);

	GtkWidget *undo_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *redo_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(GTK_GRID(middle_buttons_box), undo_button_box, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(middle_buttons_box), redo_button_box, 1, 0, 1, 1);
	gtk_box_pack_end(GTK_BOX(undo_button_box), undo_button, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(redo_button_box), redo_button, FALSE, FALSE, 5);

	// Create another horizontal box to hold the clear_button
	GtkWidget *clear_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_end(GTK_BOX(clear_button_box), clear_button, FALSE, FALSE, 0);

	// Attach the middle_buttons_box to the buttons_grid
	gtk_grid_attach(GTK_GRID(bottom_bar), middle_buttons_box, 1, 0, 1, 1);

	// Attach the clear_button_box to the rightmost column of the buttons_grid
	gtk_grid_attach(GTK_GRID(bottom_bar), clear_button_box, 2, 0, 1, 1);

	// Create the paned widget
	hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

	// Add the sidebar and content area to the paned widget
	gtk_paned_pack1(GTK_PANED(hpaned), sidebar, FALSE, FALSE);
	gtk_paned_pack2(GTK_PANED(hpaned), contentArea, TRUE, FALSE);
	gtk_paned_set_position(GTK_PANED(hpaned), 400);

	// Creating another paned widget
	GtkWidget *vpaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

	// Add the prev paned widget and bottombar to the new paned widget
	gtk_paned_pack1(GTK_PANED(vpaned), hpaned, TRUE, FALSE);
	gtk_paned_pack2(GTK_PANED(vpaned), bottom_bar, FALSE, FALSE);
	gtk_paned_set_position(GTK_PANED(vpaned), 800);

	// Add the paned widget to the main window
	gtk_container_add(GTK_CONTAINER(window), vpaned);

	// adding key bindings
	struct KeypressArgs *args = (struct KeypressArgs *)malloc(sizeof(struct KeypressArgs));

	args->clear_button = clear_button;
	args->draw_button = draw_button;
	args->redo_button = redo_button;
	args->undo_button = undo_button;

	// Connect the key-press-event signal to the callback function
	g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_pressed), args);

	return sidebar;
}