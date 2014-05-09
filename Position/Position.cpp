#include "Position.h"
#include "assert.h"


Position::Position(void) : x(0), y(0)
{
}

Position::Position(float x, float y) : x(x), y(y)
{
}

Position::Position(const Position& other) : x(other.x), y(other.y)
{
}

Position& Position::operator= (const Position& other)
{
	SetPoint(other.x, other.y);
	return *this;
}


Position Position::operator+(const Position& right) const
{
	return Position(this->x + right.x, this->y + right.y);
}

Position Position::operator-(const Position& right) const
{
	return Position(this->x - right.x, this->y - right.y);
}

Position Position::operator-() const
{
	return Position(-x, -y);
}

Position Position::operator*(float a) const
{
	return Position(this->x * a, this->y * a);
}

Position Position::operator/(float a) const
{
	if (!a)
	{
		assert(false);
	}
	return Position(this->x / a, this->y / a);
}

void Position::SetPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool Position::Equals(const Position& target) const 
{
	return (fabs(this->x - target.x) < FLT_EPSILON) && (fabs(this->y - target.y) < FLT_EPSILON);
}

bool Position::FuzzyEquals(const Position& b, float var) const
{
	if(x - var <= b.x && b.x <= x + var)
		if(y - var <= b.y && b.y <= y + var)
			return true;
	return false;
}

float Position::getAngle(const Position& other) const
{
	Position a2 = normalize();
	Position b2 = other.normalize();
	float angle = atan2f(a2.cross(b2), a2.dot(b2));
	if( fabs(angle) < FLT_EPSILON ) return 0.f;
	return angle;
}

Position Position::rotateByAngle(const Position& pivot, float angle) const
{
	return pivot + (*this - pivot).rotate(Position::forAngle(angle));
}