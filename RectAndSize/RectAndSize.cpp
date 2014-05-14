#include "RectAndSize.h"

Size2D::Size2D(void) 
	:_Width(0)
	,_Height(0)
{
}

Size2D::Size2D(float Width, float Height) 
	:_Width(Width)
	,_Height(Height)
{
}

Size2D::Size2D(const Size2D& Other) 
	:_Width(Other._Width)
	,_Height(Other._Height)
{
}

Size2D::Size2D(const Position2D& Pos2D)
	:_Width(Pos2D.x)
	,_Height(Pos2D.y)
{
}

Size2D& Size2D::operator= (const Size2D& Other)
{
	SetSize(Other._Width, Other._Height);
	return *this;
}

Size2D& Size2D::operator= (const Position2D& Pos2D)
{
	SetSize(Pos2D.x, Pos2D.y);
	return *this;
}

Size2D Size2D::operator+(const Size2D& Right) const
{
	return Size2D(this->_Width + Right._Width, this->_Height + Right._Height);
}

Size2D Size2D::operator-(const Size2D& Right) const
{
	return Size2D(this->_Width - Right._Width, this->_Height - Right._Height);
}

Size2D Size2D::operator*(float A) const
{
	return Size2D(this->_Width * A, this->_Height * A);
}

Size2D Size2D::operator/(float A) const
{
	assert(A);
	return Size2D(this->_Width / A, this->_Height / A);
}

void Size2D::SetSize(float Width, float Height)
{
	this->_Width = Width;
	this->_Height = Height;
}

bool Size2D::Equals(const Size2D& Target) const
{
	return (fabs(this->_Width  - Target._Width)  < FLT_EPSILON)
		&& (fabs(this->_Height - Target._Height) < FLT_EPSILON);
}

Rect2D::Rect2D()
{
	SetRect(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect2D::Rect2D(float X, float Y, float Width, float Height)
{
	SetRect(X, Y, Width, Height);
}

Rect2D::Rect2D(const Rect2D& Other)
{
	SetRect(Other._Origin.x, Other._Origin.y, Other._Size2D._Width, Other._Size2D._Height);
}

Rect2D& Rect2D::operator= (const Rect2D& Other)
{
	SetRect(Other._Origin.x, Other._Origin.y, Other._Size2D._Width, Other._Size2D._Height);
	return *this;
}

void Rect2D::SetRect(float X, float Y, float Width, float Height)
{
	// CGRect can support width<0 or height<0
	// CCAssert(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");

	_Origin.x = X;
	_Origin.y = Y;

	_Size2D._Width = Width;
	_Size2D._Height = Height;
}

bool Rect2D::Equals(const Rect2D& OtherRect) const
{
	return (_Origin.Equals(OtherRect._Origin) && _Size2D.Equals(OtherRect._Size2D));
}

bool Rect2D::RectSizeEquals(const Rect2D& OtherRect2D) const
{
	return _Size2D.Equals(OtherRect2D._Size2D);
}

bool Rect2D::ContainsPoint(const Position2D& Pos2D) const
{
	bool bRet = false;

	if (Pos2D.x >= GetMinX() && Pos2D.x <= GetMaxX() && Pos2D.y >= GetMinY() && Pos2D.y <= GetMaxY())
	{
		bRet = true;
	}

	return bRet;
}

float Rect2D::GetMinX() const
{
	return _Origin.x;
}

bool Rect2D::IntersectsRect(const Rect2D& rect) const
{
	return !(GetMaxX() < rect.GetMinX() || rect.GetMaxX() < GetMinX() || GetMaxY() < rect.GetMinY() || rect.GetMaxY() < GetMinY());
}

float Rect2D::GetMidX() const
{
	return (float)(_Origin.x + _Size2D._Width / 2.0);
}

float Rect2D::GetMaxX() const
{
	return (float)(_Origin.x + _Size2D._Width);
}

float Rect2D::GetMinY() const
{
	return _Origin.y;
}

float Rect2D::GetMidY() const
{
	return (float)(_Origin.y + _Size2D._Height / 2.0);
}

float Rect2D::GetMaxY() const
{
	return _Origin.y + _Size2D._Height;
}




