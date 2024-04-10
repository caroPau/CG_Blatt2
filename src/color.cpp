#include "color.h"
#include <assert.h>

Color::Color():R(0), G(0), B(0)
{
}

Color::Color( float r, float g, float b): R(r), G(g), B(b)
{
}

Color Color::operator*(const Color& c) const
{
    Color d;
    d.R = this->R * c.R;
    d.G = this->G * c.G;
    d.B = this->B * c.B;

    return d;
}

Color Color::operator*(const float Factor) const
{
	Color d;
    d.R = this->R * Factor;
    d.G = this->G * Factor;
    d.B = this->B * Factor;
    return d;
}

Color Color::operator+(const Color& c) const
{
    Color d;
    d.R = this->R + c.R;
    d.G = this->G + c.G;
    d.B = this->B + c.B;

    return d;
}

Color& Color::operator+=(const Color& c)
{
	*this = *this + c;
	return *this;
}