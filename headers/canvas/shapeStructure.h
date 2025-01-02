#include <gtk/gtk.h>
#include <stdlib.h>
#include "shapes.h"

struct FigureNode
{
    int type;
    int dim[6];
    double color[3];
    double lineWidth;
    struct FigureNode *next;
};

struct FigureStack
{
    struct FigureNode *head;
};

struct FigureStack *createFigureStack()
{
    struct FigureStack *figureStack = (struct FigureStack *)malloc(sizeof(struct FigureStack));
    figureStack->head = NULL;
    return figureStack;
}

// for undoing called in undo.h
// popping return the node pointer without freeing it

struct FigureNode *pop_figure(struct FigureStack *figureStack)
{
    if (figureStack->head != NULL)
    {
        struct FigureNode *node = figureStack->head;
        figureStack->head = figureStack->head->next;
        return node;
    }
    return NULL;
}

// for clearing all figures
// called in clear.h
void clear_figures(struct FigureStack *figureStack)
{
    struct FigureNode *next = figureStack->head;

    while (figureStack->head != NULL)
    {
        next = figureStack->head->next;
        free(figureStack->head);
        figureStack->head = next;
    }
}

void push_figure(struct FigureStack *figureStack, int dimension[], int type, double *colorValue, double lineWidth)
{
    struct FigureNode *newNode = (struct FigureNode *)malloc(sizeof(struct FigureNode));

    newNode->type = type;
    newNode->color[0] = colorValue[0];
    newNode->color[1] = colorValue[1];
    newNode->color[2] = colorValue[2];
    newNode->lineWidth = lineWidth;

    for (int i = 0; i < 6; i++)
    {
        newNode->dim[i] = dimension[i];
    }

    newNode->next = figureStack->head;
    figureStack->head = newNode;
}

// tranfering node from "from" to "to" stack
void transfer_figure(struct FigureStack *from, struct FigureStack *to)
{
    // popping out that something from stack;
    struct FigureNode *poppedFigure = pop_figure(from);
    if (poppedFigure != NULL)
    {
        push_figure(to, poppedFigure->dim, poppedFigure->type, poppedFigure->color, poppedFigure->lineWidth);
        free(poppedFigure);
    }
}
void drawFigures(struct FigureStack *figureStack, cairo_t *cr, int cx, int cy)
{
    struct FigureNode *head = figureStack->head;
    while (head != NULL)
    {
        switch (head->type)
        {
        case 1:
            // for creating a point
            draw_point(cr, cx + head->dim[1], cy - head->dim[0], head->color);
            break;
        case 2:
            // for creating a line
            draw_line(cr, cx + head->dim[3], cy - head->dim[2], cx + head->dim[1], cy - head->dim[0], head->color, head->lineWidth);
            break;
        case 3:
            // for creating an arc
            draw_arc(cr, cx + head->dim[4], cy - head->dim[3], head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 4:
            // for creating a circle
            draw_circle(cr, cx + head->dim[2], cy - head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 5:
            // for creating a triangle
            draw_traingle(cr, cx + head->dim[5], cy - head->dim[4], cx + head->dim[3], cy - head->dim[2], cx + head->dim[1], cy - head->dim[0], head->color, head->lineWidth);
            break;
        case 6:
            // for creating a rectangle
            draw_rectangle(cr, cx + head->dim[3] - head->dim[1] / 2, cy - head->dim[2] - head->dim[0] / 2, head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 7:
            // for creating an ellipse
            draw_ellipse(cr, cx + head->dim[3], cy - head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 8:
            // for creating a horizontal parabola
            draw_H_parabola(cr, 2 * cy, cx + head->dim[2], cy - head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 9:
            // for creating a vertical parabola
            draw_V_parabola(cr, 2 * cx, cx + head->dim[2], cy - head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 10:
            // for creating a horizontal hyperbola
            draw_H_hyperbola(cr, cx + head->dim[3], cy - head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 11:
            // for creating a vertical hyperbola
            draw_V_hyperbola(cr, cx + head->dim[3], cy - head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 12:
            // for creating a cycloid
            draw_cycloid(cr, cx + head->dim[3], cy - head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 13:
            // for creating a epicycloid
            draw_epicycloid(cr, cx + head->dim[3], cy - head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 14:
            // for creating a hypocycloid
            draw_hypocycloid(cr, cx + head->dim[3], cy - head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 15:
            // for creating a spiral
            draw_spiral(cr, cx + head->dim[3], cy - head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        case 16:
            // for creating  mirror image of a point
            draw_mirrorImage(cr,cx, cy, cx + head->dim[3], cy - head->dim[2], head->dim[1], head->dim[0], head->color, head->lineWidth);
            break;
        default:
            break;
        }
        head = head->next;
    }
}
