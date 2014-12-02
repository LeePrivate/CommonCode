#pragma once

#include "LeeConfig.h"
#include "Position/Position.h"

#define Size2DMake(width, height) Size2D((float)(width), (float)(height))
#define Rect2DMake(x, y, width, height) Rect2D((float)(x), (float)(y), (float)(width), (float)(height))

class Size2D
{
public:
    float _Width;
    float _Height;

public:
    Size2D();

    Size2D(float width, float height);

    Size2D(const Size2D& other);

    Size2D(const Position2D& point);

    Size2D& operator= (const Size2D& other);

    Size2D& operator= (const Position2D& Pos2D);

    Size2D operator+(const Size2D& Right) const;

    Size2D operator-(const Size2D& right) const;
  
    Size2D operator*(float A) const;

    Size2D operator/(float a) const;

    void SetSize(float Width, float Height);

    bool Equals(const Size2D& Target) const;
};

class Rect2D
{
public:
    Position2D _Origin;
    Size2D  _Size2D;

public:
    Rect2D();

    Rect2D(float X, float Y, float Width, float Height);

    Rect2D(const Rect2D& Other);

    Rect2D& operator= (const Rect2D& Other);

    void SetRect(float X, float Y, float Width, float Height);

	bool Equals(const Rect2D& OtherRect2D) const; 

	bool RectSizeEquals(const Rect2D& OtherRect2D) const;

	bool ContainsPoint(const Position2D& Pos2D) const;

	bool IntersectsRect(const Rect2D& rect) const;				//这个是计算两个矩形是否有重叠部分;

    float GetMinX() const; /// return the leftmost x-value of current rect

    float GetMidX() const; /// return the midpoint x-value of current rect

    float GetMaxX() const; /// return the rightmost x-value of current rect

    float GetMinY() const; /// return the bottommost y-value of current rect

    float GetMidY() const; /// return the midpoint y-value of current rect

    float GetMaxY() const; /// return the topmost y-value of current rect
  
    
    
};