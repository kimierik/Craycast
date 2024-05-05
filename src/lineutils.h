#ifndef __LINE_H
#define __LINE_H


#include <raylib.h>


typedef struct Line{
    Vector2 a;
    Vector2 b;
}Line;




Vector2* lineSegmentIntersection(Line l1, Line l2);
Vector2 lineIntersect(Line l1, Line l2);


float distanceBetweenPoints(Vector2 p1, Vector2 p2);







#endif
