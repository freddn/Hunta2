//
// Created by fredrik on 3/3/16.
//

#include <iostream>
#include "Collision.hpp"
#include "Manifold.hpp"

CollisionCallback Dispatch[Shape::sCount][Shape::sCount] =
        {
                {
                        CircletoCircle, CircletoPolygon
                },
                {
                        PolygontoCircle, PolygontoPolygon
                },
        };

void CircletoCircle(Manifold *m, Body *b1, Body *b2) {
    Circle *a = reinterpret_cast<Circle*>(b1->shape);
    Circle *b = reinterpret_cast<Circle*>(b2->shape);

    Vec2 normal = b2->position - b1->position;

    float distSqr = normal.LenSqr();
    float radius = a->radius + b->radius;

    if(distSqr >= radius*radius) {
        m->contactCount = 0;
        return;
    }

    //Circles have collided, compute manifold
    float distance = std::sqrt(distSqr);

    m->contactCount = 1;

    // distance between circles is not zero
    if(distance == 0.0f) {
        // Distance is difference between radius and distance
        m->penetration = a->radius;
        m->normal = Vec2(1,0);
        m->contacts[0] = b1->position;
    } else {
        m->penetration = radius - distance;
        m->normal = normal / distance;
        m->contacts[0] = m->normal * a->radius + b1->position;
    }
}


void CircletoPolygon(Manifold *m, Body *a, Body *b) {

}

void PolygontoCircle(Manifold *m, Body *a, Body *b) {

}

void PolygontoPolygon(Manifold *m, Body *b1, Body *b2) {
    AABB *abox = reinterpret_cast<AABB*>(b1->shape);
    AABB *bbox = reinterpret_cast<AABB*>(b2->shape);
    //m->contactCount = 0;

    Vec2 n = b2->position - b1->position;

    // Calculate half extents along x axis
    float a_extent = (abox->max.x - abox->min.x) / 2;
    float b_extent = (bbox->max.x - bbox->min.x) / 2;

    // Overlap on x axis
    float x_overlap = a_extent + b_extent - std::abs(n.x);

    // SAT test
    if(x_overlap > 0) {
        // same for y
        float a_extent = (abox->max.y - abox->min.y) / 2;
        float b_extent = (bbox->max.y - bbox->min.y) / 2;

        float y_overlap = a_extent + b_extent - std::abs(n.y);

        if(y_overlap > 0) {
            // Which axis is axis of least penetration
            if(x_overlap > y_overlap) {
                // Point towards b, n points from a to b
                if(n.x < 0)
                    m->normal = Vec2(-1, 0);
                else
                    m->normal = Vec2(1, 0);
                m->penetration = x_overlap;
            } else {
                if(n.y < 0)
                    m->normal = Vec2(0, -1);
                else
                    m->normal = Vec2(0, 1);
                m->penetration = y_overlap;
            }
            //m->contacts[m->contactCount] = n;
           // m->contactCount ++;
        }
    }
}

void AABBtoCircle(Manifold *m, Body *a, Body *b) {


}
