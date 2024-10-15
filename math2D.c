#include "math2D.h"

// Funzione per calcolare la distanza euclidea tra due punti
double distance(Vector2D v1, Vector2D v2) {
    return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

// Funzioner per calcolare il prodotto scalare tra due vettori
double dot(Vector2D v1, Vector2D v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

// Funzioner per sommare due vettori
Vector2D add(Vector2D v1, Vector2D v2) {
    Vector2D sum;
    sum.x = v1.x + v2.x;
    sum.y = v1.y + v2.y;
    return sum;
}

// Funzioner per moltiplicare due vettori
Vector2D mul(Vector2D v1, Vector2D v2) {
    Vector2D sum;
    sum.x = v1.x * v2.x;
    sum.y = v1.y * v2.y;
    return sum;
}

// Funzione per sottrarre un vettore da un altro
Vector2D subtract(Vector2D v1, Vector2D v2) {
    Vector2D difference;
    difference.x = v1.x - v2.x;
    difference.y = v1.y - v2.y;
    return difference;
}

// Funzione per ottenere un versore, partendo dalla direzione (in base alle define dei tasti freccia)
Vector2D versor(int direction) {
    Vector2D versor = {0, 0}; // Versore "nullo" di partenza

    switch (direction) {
        case ARROW_UP:
            versor.y = -1;
            break;
        case ARROW_DOWN:
            versor.y = 1;
            break;
        case ARROW_LEFT:
            versor.x = -1;
            break;
        case ARROW_RIGHT:
            versor.x = 1;
            break;
        default:
            // Se la direzione non è valida, restituisci il versore nullo
            break;
    }

    return versor;
}


// Funzione per convertire da Point a Vector2D
Vector2D point_to_vector2d(Point point) {
    Vector2D vector;
    vector.x = point.x;
    vector.y = point.y;
    return vector;
}

// Funzione per convertire da Vector2D a Point
Point vector2d_to_point(Vector2D vector) {
    Point point;
    point.x = vector.x;
    point.y = vector.y;
    return point;
}
