#pragma once

#include "math.h"

#define pos2D(__X__,__Y__) PositionMake2D((float)(__X__), (float)(__Y__))
#define PositionMake2D(x, y) Position2D((float)(x), (float)(y))
#define FLT_EPSILON     1.192092896e-07F        /* smallest such that 1.0+FLT_EPSILON != 1.0 */

class Position2D
{
public:
    float x;
    float y;

public:
    Position2D();

    Position2D(float x, float y);

    Position2D(const Position2D& other);

    Position2D& operator= (const Position2D& other);

    Position2D operator+(const Position2D& right) const;

    Position2D operator-(const Position2D& right) const;

    Position2D operator-() const;

    Position2D operator*(float a) const;

    Position2D operator/(float a) const;
   
    void SetPoint(float x, float y);

    bool Equals(const Position2D& target) const;
    
    bool FuzzyEquals(const Position2D& target, float variance) const;

    inline float GetLength() const {
        return sqrtf(x*x + y*y);
    };

    inline float GetLengthSq() const {
        return Dot(*this); //x*x + y*y;
    };

    inline float GetDistanceSq(const Position2D& other) const {
        return (*this - other).GetLengthSq();
    };

    inline float GetDistance(const Position2D& other) const {																	//������ü���������֮��ľ���;
        return (*this - other).GetLength();
    };

    inline float GetAngle() const {																										//����ǵõ��Լ���1,0 ��֮��ĽǶ�,�õ������ĽǶ� 2PI ������ѧ��ʽ��360��;
        return atan2f(y, x);
    };

    float GetAngle(const Position2D& other) const;																					//����ǵõ�������֮��ĽǶ�;


    inline float Dot(const Position2D& other) const {																				//����㷨 ע��:��������Ǽ�����������֮��ļн�,�������ֵΪ���� ��ô������֮���ڽ�С��90��,���Ϊ���� ��ô��������֮����ڽǴ���90�� �ڽ�:��ָ��������֮��С��180��Ľ�;
        return x*other.x + y*other.y;
    };

    /** Calculates cross product of two points.
     @return float
     @since v2.1.4
     */
    inline float Cross(const Position2D& other) const {																			//����㷨 Ŀǰֻ֪���и�Ӧ����3D��Ⱦ����,�ж����Ƿ����ڱ���Ͳ�����Ⱦ,����㷨��ŵ���˼��,�������������õ� ����һ��γ�ȵĳ���ֵ(�Ժ���ѧϰ�����Ȱ���);
        return x*other.y - y*other.x;
    };

    /** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
     @return CCPoint
     @since v2.1.4
     */
    inline Position2D getPerp() const {
        return Position2D(-y, x);
    };

    /** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
     @return CCPoint
     @since v2.1.4
     */
    inline Position2D getRPerp() const {
        return Position2D(y, -x);
    };

    /** Calculates the projection of this over other.
     @return CCPoint
     @since v2.1.4
     */
    inline Position2D project(const Position2D& other) const {
        return other * (Dot(other)/other.Dot(other));
    };

    /** Complex multiplication of two points ("rotates" two points).
     @return CCPoint vector with an angle of this.getAngle() + other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     */
    inline Position2D rotate(const Position2D& other) const {
        return Position2D(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** Unrotates two points.
     @return CCPoint vector with an angle of this.getAngle() - other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     */
    inline Position2D unrotate(const Position2D& other) const {
        return Position2D(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** Returns point multiplied to a length of 1.
     * If the point is 0, it returns (1, 0)
     @return CCPoint
     @since v2.1.4
     */
    inline Position2D normalize() const {
        float length = GetLength();
        if(length == 0.) return Position2D(1.f, 0);
        return *this / GetLength();
    };

    /** Linear Interpolation between two points a and b
     @returns
        alpha == 0 ? a
        alpha == 1 ? b
        otherwise a value between a..b
     @since v2.1.4
     */
    inline Position2D lerp(const Position2D& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** Rotates a point counter clockwise by the angle around a pivot
     @param pivot is the pivot, naturally
     @param angle is the angle of rotation ccw in radians
     @returns the rotated point
     @since v2.1.4
     */
    Position2D rotateByAngle(const Position2D& pivot, float angle) const;

    static inline Position2D forAngle(const float a)
    {
    	return Position2D(cosf(a), sinf(a));
    }
};