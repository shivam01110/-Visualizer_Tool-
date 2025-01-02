// globals.h
#include <gtk/gtk.h>

#ifndef GLOBALS_H
#define GLOBALS_H

extern GtkWidget *window;
extern GtkWidget *canvas;
struct FigureStack *figureStack;
struct FigureStack *redoStack;
double *colorValue;
double *lineWidth;

#endif // GLOBALS_H
