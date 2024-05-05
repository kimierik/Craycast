
#include "lineutils.h"
#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>



// //this is wt we need to use since we asre using intersections
// https://en.wikipedia.org/wiki/Intersection_(geometry)
//
// i have no idea where this person gets this math from but if it works then good
// //https://github.com/Immugio/three-math-extensions/blob/master/src/Line2D.ts#L710
//mallocs the line needs to be freed
Vector2* lineSegmentIntersection(Line l1, Line l2){

    //how do i make return possible error
    //do i must make this into pointer
    //i do not want to malloc this
    //do i give it as input into param?
    //that would be stupid
    //
    //but do we have to since im not gonna malloc this anyway
    //fuck this is stuppid

    

    if ((l1.a.x == l1.b.x && l1.a.y == l1.b.y) || (l2.a.x == l2.b.x && l2.a.y == l2.b.y)) {
        return 0;
    }

    float denominator = ((l2.b.y - l2.a.y) * (l1.b.x - l1.a.x) - (l2.b.x - l2.a.x) * (l1.b.y - l1.a.y));


    // Lines are parallel
    if (denominator == 0) {
        return NULL;
    }

    float ua = ((l2.b.x - l2.a.x) * (l1.a.y - l2.a.y) - (l2.b.y - l2.a.y) * (l1.a.x - l2.a.x)) / denominator;

    float ub = ((l1.b.x - l1.a.x) * (l1.a.y - l2.a.y) - (l1.b.y - l1.a.y) * (l1.a.x - l2.a.x)) / denominator;
    if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
        return 0;
    }

    Vector2* returnVec=malloc(sizeof(Vector2));
    returnVec->x=0;
    returnVec->y=0;
    // Return an object with the x and y coordinates of the intersection
    returnVec->x = l1.a.x + ua * (l1.b.x - l1.a.x);
    returnVec->y = l1.a.y + ua * (l1.b.y - l1.a.y);





    return returnVec;
}








//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
Vector2 lineIntersect(Line l1, Line l2){
    Vector2 returnVec={
        .x=0,
        .y=0,
    };

    // x1 = l1.a.x
    // x2 = l1.b.x
    // x3 = l2.a.x
    // x4 = l2.b.x

    // y1 = l1.a.y
    // y2 = l1.b.y
    // y3 = l2.a.y
    // y4 = l2.b.y

    returnVec.x = ((l1.a.x*l1.b.y-l1.a.y*l1.b.x)* (l2.a.x-l2.b.x)-(l1.a.x-l1.b.x) * (l2.a.x*l2.b.y-l2.a.y*l2.b.x))/
       ((l1.a.x-l1.b.x)*(l2.a.y-l2.b.y)-(l1.a.y-l1.b.y)*(l2.a.x-l2.b.x));

    returnVec.y= ((l1.a.x*l1.b.y-l1.a.y*l1.b.x)* (l2.a.y-l2.b.y)-(l1.a.y-l1.b.y) *(l2.a.x*l2.b.y-l2.a.y*l2.b.x))/
       ((l1.a.x-l1.b.x)*(l2.a.y-l2.b.y)-(l1.a.y-l1.b.y)*(l2.a.x-l2.b.x));


    return returnVec;
}











float distanceBetweenPoints(Vector2 p1, Vector2 p2){

    float delta_x=p2.x-p1.x;
    float delta_y=p2.y-p1.y;

    float hypotenuse= sqrtf(powf(delta_x, 2)+powf(delta_y, 2));

    return hypotenuse;
}







