#include <gtk/gtk.h>

char *load_css_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open CSS file: %s\n", filename);
        return NULL;
    }

    // Determine the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory to store the file contents
    char *css_buffer = (char *)malloc(file_size + 1);
    if (css_buffer == NULL)
    {
        fclose(file);
        fprintf(stderr, "Failed to allocate memory for CSS file: %s\n", filename);
        return NULL;
    }

    // Read the file contents into the buffer
    size_t read_size = fread(css_buffer, 1, file_size, file);
    css_buffer[read_size] = '\0'; // Null-terminate the string

    fclose(file);
    return css_buffer;
}

void load_CSS()
{
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    char *css = load_css_file("headers/css/styles.css");
    gtk_css_provider_load_from_data(cssProvider, css, -1, NULL);

    // adding css provider to the screen
    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}