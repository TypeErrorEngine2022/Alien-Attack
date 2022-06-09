#pragma once
#include <math.h>

class Vector2D
{
public:
    Vector2D(double x = 0.0, double y = 0.0);
    Vector2D(const Vector2D& rhs) = default;
    Vector2D(Vector2D&& rhs) = default;
    ~Vector2D() = default;

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);

    double length() const;

    void normalize();

    Vector2D operator+(const Vector2D& v2) const;
    Vector2D operator-(const Vector2D& v2) const;
    friend Vector2D operator*(double scalar, const Vector2D& v1); 
    Vector2D operator*(double scalar) const;
    Vector2D operator/(double scalar) const;

    Vector2D& operator=(const Vector2D& v2) = default;
    Vector2D& operator=(Vector2D&& v2) = default;

    Vector2D& operator+=(const Vector2D& v2);
    Vector2D& operator-=(const Vector2D& v2);
    Vector2D& operator*=(double scalar);
    Vector2D& operator/=(double scalar);

private:
    double m_x;
    double m_y;
};