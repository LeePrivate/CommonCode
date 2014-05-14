#include "Position.h"
#include "assert.h"


Position2D::Position2D(void) : x(0), y(0)
{
}

Position2D::Position2D(float x, float y) : x(x), y(y)
{
}

Position2D::Position2D(const Position2D& other) : x(other.x), y(other.y)
{
}

Position2D& Position2D::operator= (const Position2D& other)
{
	SetPoint(other.x, other.y);
	return *this;
}


Position2D Position2D::operator+(const Position2D& right) const
{
	return Position2D(this->x + right.x, this->y + right.y);
}

Position2D Position2D::operator-(const Position2D& right) const
{
	return Position2D(this->x - right.x, this->y - right.y);
}

Position2D Position2D::operator-() const
{
	return Position2D(-x, -y);
}

Position2D Position2D::operator*(float a) const
{
	return Position2D(this->x * a, this->y * a);
}

Position2D Position2D::operator/(float a) const
{
	if (!a)
	{
		assert(false);
	}
	return Position2D(this->x / a, this->y / a);
}

void Position2D::SetPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool Position2D::Equals(const Position2D& target) const 
{
	return (fabs(this->x - target.x) < FLT_EPSILON) && (fabs(this->y - target.y) < FLT_EPSILON);
}

bool Position2D::FuzzyEquals(const Position2D& b, float var) const
{
	if(x - var <= b.x && b.x <= x + var)
		if(y - var <= b.y && b.y <= y + var)
			return true;
	return false;
}

float Position2D::GetAngle(const Position2D& other) const
{
	Position2D a2 = normalize();
	Position2D b2 = other.normalize();
	float angle = atan2f(a2.Cross(b2), a2.Dot(b2));
	if( fabs(angle) < FLT_EPSILON ) return 0.f;
	return angle;
}

Position2D Position2D::rotateByAngle(const Position2D& pivot, float angle) const
{
	return pivot + (*this - pivot).rotate(Position2D::forAngle(angle));
}