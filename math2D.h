#ifndef MATH2D_H_INCLUDED
#define MATH2D_H_INCLUDED

#include <math.h>
#include "common.h"


// Definizioni di macro di utilità

#define CLAMP(x, min_val, max_val) ((x) < (min_val) ? (min_val) : ((x) > (max_val) ? (max_val) : (x)))
#define ABS(x) ((x) < 0 ? -(x) : (x))


// Definizioni di strutture

typedef struct {
    double x;
    double y;
} Vector2D;


// Dichiarazioni di funzioni

double distance(Vector2D v1, Vector2D v2);
double dot(Vector2D v1, Vector2D v2);
Vector2D add(Vector2D v1, Vector2D v2);
Vector2D mul(Vector2D v1, Vector2D v2);
Vector2D subtract(Vector2D v1, Vector2D v2);
Vector2D versor(int direction);

Vector2D point_to_vector2d(Point point);
Point vector2d_to_point(Vector2D vector);

#endif // MATH2D_H_INCLUDED
