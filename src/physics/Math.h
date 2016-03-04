//
// Created by fredrik on 3/2/16.
//

#ifndef HUNTA2_MATH_H
#define HUNTA2_MATH_H



#include <cmath> // abs, sqrt
#include <cassert> // assert


#include "Vec2.hpp" // Vec2

const float PI = 3.141592741f;

inline Vec2 Min( const Vec2& a, const Vec2& b )
{
    return Vec2( std::min( a.x, b.x ), std::min( a.y, b.y ) );
}

inline Vec2 Max( const Vec2& a, const Vec2& b ) {
    return Vec2( std::max( a.x, b.x ), std::max( a.y, b.y ) );
}

inline float Dot(const Vec2& a, const Vec2& b ) {
    return a.x * b.x + a.y * b.y;
}

inline float DistSqr(const Vec2& a, const Vec2& b) {
    Vec2 c = a - b;
    return Dot( c, c );
}

inline Vec2 Cross(const Vec2 &a, float b) {
    return Vec2(b*a.y, -b * a.x);
}

inline Vec2 Cross(float a, const Vec2 &b) {
    return Vec2(-a * b.y, a * b.x);
}

inline float Cross(const Vec2 &a, const Vec2 &b) {
    return a.x * b.y - a.y * b.x;
}

inline bool Equal(float a, float b) {
    return std::abs(a-b) <= EPSILON;
}

inline float Sqr(float a) {
    return a*a;
}

inline float Clamp(float min, float max, float a) {
    if(a < min) return min;
    if(a > max) return max;
    return a;
}

inline int Round(float a) {
    return (int)(a+0.5f);
}

inline float Random(float l, float h) {
    float a = (float)rand();
    a /= RAND_MAX;
    a = (h-1) * a+1;
    return a;
}

inline bool BiasGreaterThan(float a,float b){
    const float k_biasRelative = 0.95f;
    const float k_biasAbsolute = 0.01f;
    return a >= b * k_biasRelative + a * k_biasAbsolute;
}

const float gravityScale = 5.0f;
//const Vec2 gravity( 0, 10.0f * gravityScale );
const Vec2 gravity( 0, 0);
const float dt = 1.0f / 60.0f;


#endif //HUNTA2_MATH_H
