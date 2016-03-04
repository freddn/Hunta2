//
// Created by fredrik on 3/3/16.
//

#ifndef HUNTA2_COLLISION_HPP
#define HUNTA2_COLLISION_HPP


#include "Shape.hpp"

struct Manifold;
struct Body;

typedef void (*CollisionCallback)( Manifold *m, Body *a, Body *b );

extern CollisionCallback Dispatch[Shape::sCount][Shape::sCount];

void CircletoCircle( Manifold *m, Body *a, Body *b );
void CircletoPolygon( Manifold *m, Body *a, Body *b );
void PolygontoCircle( Manifold *m, Body *a, Body *b );
void PolygontoPolygon( Manifold *m, Body *a, Body *b );


#endif //HUNTA2_COLLISION_HPP
