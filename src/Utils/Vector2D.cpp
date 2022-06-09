#include "../../include/headers/UtilsHeader/Vector2D.h"
#include <math.h>

Vector2D::Vector2D(double x, double y):
    m_x(x), m_y(y)
{}

double Vector2D::getX() const
{
    return m_x;
}

double Vector2D::getY() const
{
    return m_y;
}

void Vector2D::setX(double x)
{
    m_x = x;
}

void Vector2D::setY(double y)
{
    m_y = y;
}

double Vector2D::length() const
{
    return sqrt(m_x * m_x + m_y * m_y);
}

void Vector2D::normalize()
{
    m_x /= length();
    m_y /= length();
}

Vector2D Vector2D::operator+(const Vector2D& v2) const
{
    return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const
{
    return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

// the friend function
Vector2D operator*(double scalar, const Vector2D& v1)
{
    return Vector2D(v1.m_x * scalar, v1.m_y * scalar);
}

Vector2D Vector2D::operator*(double scalar) const
{
    return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D Vector2D::operator/(double scalar) const
{
    return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& v2)
{
    m_x += v2.m_x;
    m_y += v2.m_y;

    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v2)
{
    m_x -= v2.m_x;
    m_y -= v2.m_y;

    return *this;
}

Vector2D& Vector2D::operator*=(double scalar)
{
    m_x *= scalar;
    m_y *= scalar;

    return *this;
}

Vector2D& Vector2D::operator/=(double scalar)
{
    m_x /= scalar;
    m_y /= scalar;

    return *this;
}



