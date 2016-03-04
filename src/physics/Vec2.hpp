//
// Created by fredrik on 3/2/16.
//

#ifndef HUNTA2_VEC2_HPP
#define HUNTA2_VEC2_HPP

#include <algorithm> // max, min

const float EPSILON = 0.0001f;


struct Vec2 {
    Vec2(float vX, float vY) : x(vX), y(vY) {};
    Vec2() {};
    float x;
    float y;
    void setVec2(float x_, float y_) {x = x_; y=y_;}

    Vec2 operator -() const {
        return Vec2(-x,-y);
    }

    Vec2 operator -(const Vec2& a) const {
        return Vec2( x-a.x, y-a.y);
    }
    void operator -=(const Vec2& a) {
        x-=a.x;
        y-=a.y;
    }

    /*Vec2 operator*(float a ) const {
        return Vec2(x * a, y * a);
    }*/

    /*Vec2 operator/(float a) const {
        return Vec2( x / a, y / a);
    }*/

    Vec2 operator+(const Vec2& a) const {
        return Vec2( x +a.x, y + a.y );
    }

    Vec2 operator+(float a) const {
        return Vec2( x+a, y+a);
    }

    void operator+=( const Vec2& a) {
        x += a.x;
        y += a.y;
    }

    float LenSqr() const {
        return x * x + y * y;
    }

    float Len() const {
        return std::sqrt(x * x + y * y);
    }

    void Rotate(float radians) {
        float c = std::cos(radians);
        float s = std::sin(radians);

        float xp = x*c - y*s;
        float yp = x*s + y*c;

        x = xp;
        y = yp;
    }

    void Normalize() {
        float len = Len();
        if(len > EPSILON) {
            float invLen = 1.0f / len;
            x *= invLen;
            y *= invLen;
        }
    }
};

inline Vec2 operator *(const Vec2 &a, float b) {
    return Vec2(a.x * b, a.y * b);
}
inline Vec2 operator *(float a, const Vec2 &b) {
    return Vec2(b.x * a, b.y * a);
}

inline Vec2 operator /(float a, const Vec2& b) {
    return Vec2( a / b.x,a / b.y);
}

inline Vec2 operator /(const Vec2 &a, float b) {
    return Vec2(a.x / b, a.y / b);
}



#endif //HUNTA2_VEC2_HPP
