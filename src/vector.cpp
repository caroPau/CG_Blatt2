#include "vector.h"
#include <math.h>

#define EPSILON 1e-5

Vector::Vector( float x, float y, float z): X(x), Y(y), Z(z)
{
}

Vector::Vector(){}

float Vector::dot(const Vector& v) const
{
	return (this->X * v.X + this->Y * v.Y + this->Z * v.Z);
}

Vector Vector::cross(const Vector& v) const
{
    Vector a;
    a.X = this->Y * v.Z - this->Z * v.Y;
    a.Y = this->Z * v.X - this->X * v.Z;
    a.Z = this->X * v.Y - this->Y * v.X;
    return a;
}



Vector Vector::operator+(const Vector& v) const
{
    return Vector{this->X+v.X, this->Y+v.Y, this->Z+v.Z};
}

Vector Vector::operator-(const Vector& v) const
{
    return Vector{this->X-v.X, this->Y-v.Y, this->Z-v.Z};
}

Vector Vector::operator*(float c) const
{
    return Vector{c*X, c*Y, c*Z};
}

Vector Vector::operator-() const
{
    return *this * (-1);
}

Vector& Vector::operator+=(const Vector& v)
{
    *this = *this + v;
    return *this;
}

Vector& Vector::normalize()
{
    float len = this->length();
    if (len != 0) {
        this->X /= len;
        this->Y /= len;
        this->Z /= len;
    }
    return *this;
}

float Vector::length() const
{
    return sqrt(this->lengthSquared());
}

float Vector::lengthSquared() const
{
    return pow(X,2) + pow(Y,2) + pow(Z ,2);
}

Vector Vector::reflection(const Vector& normal) const
{
    Vector reflection = *this - normal * 2 * dot(normal);
    return reflection;
}

bool Vector::triangleIntersection( const Vector& d, const Vector& a, const Vector& b, const Vector& c, float& s) const
{
    //Berechnung der Normalen des Dreiecks
    Vector n_notnorm = (b - a).cross(c - a);
    Vector n = n_notnorm.normalize();

    // Projektion des Strahls auf die Normale des Dreiecks
    float dotnd = d.dot(n);

    // Prüfen ob Strahl parallel zum Dreieck
    if ( fabs(dotnd) < EPSILON) { return false; }

    // Länge des Vektors zwischen o und a
    float oa = n.dot(a);

    // Skalar s repsäsentiert Abstand des Strahlursprungs zum Dreieck Schnittpunkt
    s = (oa - n.dot(*this)) / (n.dot(d));

    // Falls s negativ, liegt Strahl hinter dem Ursprung
    if (s < 0.0f) { return false; }

    // Schnittpunkt des Strahls
    Vector dest = *this + d * s;

    // Berechnung der Dreiecksfläche
    float abc = (b - a).cross(c - a).length() / 2.0f;

    // Berechnung der Flächen der Teildreiecke über die Baryzentrischen Koordinaten

    float abp = (b - a).cross(dest - a).length() / 2.0f;
    float bcp = (dest - a).cross(c - a).length() / 2.0f;
    float acp = (dest - c).cross(b - c).length() / 2.0f;

    // Vergleich der Dreiecke
    if ((abp + bcp + acp) <= abc + EPSILON ) {
        return true;
    }

    return false;
}

