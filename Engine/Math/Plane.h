//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse ��rni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "Ray.h"
#include "Vector3.h"

class Ray;

/// Surface in three-dimensional space
class Plane
{
public:
    /// Construct an undefined plane
    Plane()
    {
    }
    
    /// Copy-construct from another plane
    Plane(const Plane& plane) :
        normal_(plane.normal_),
        intercept_(plane.intercept_)
    {
    }
    
    /// Construct from 3 vertices
    Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2)
    {
        Define(v0, v1, v2);
    }
    /// Construct from a normal vector and a point on the plane
    Plane(const Vector3& normal, const Vector3& point)
    {
        Define(normal, point);
    }
    
    /// Define from 3 vertices
    void Define(const Vector3& v0, const Vector3& v1, const Vector3& v2)
    {
        Vector3 dist1 = v1 - v0;
        Vector3 dist2 = v2 - v0;
        
        normal_ = (dist1.CrossProduct(dist2)).Normalized();
        absNormal_ = Vector3(fabsf(normal_.x_), fabsf(normal_.y_), fabsf(normal_.z_));
        intercept_ = -normal_.DotProduct(v0);
    }

    void Define(const Vector3& normal, const Vector3& point)
    {
        normal_ = normal;
        absNormal_ = Vector3(fabsf(normal_.x_), fabsf(normal_.y_), fabsf(normal_.z_));
        intercept_ = -normal_.DotProduct(point);
    }
    
    /// Return distance to a point
    float Distance(const Vector3& point) const
    {
        return normal_.DotProduct(point) + intercept_;
    }
    
    /// Return absolute distance to a point
    float AbsDistance(const Vector3& point) const
    {
        return normal_.AbsDotProduct(point);
    }
    
    /// Return absolute distance to a point which has only positive coordinates
    float AbsDistanceFast(const Vector3& absPoint) const
    {
        // Point must contain only positive X, Y, Z
        return absNormal_.DotProduct(absPoint);
    }
    
    /// Return ray hit distance, or infinity if no hit
    float Distance(const Ray& ray) const
    {
        float d = normal_.DotProduct(ray.direction_);
        if (fabsf(d) >= M_EPSILON)
            return (-normal_.DotProduct(ray.origin_) + intercept_) / d;
        else
            return M_INFINITY;
    }
    
    /// Plane normal
    Vector3 normal_;
    /// Plane absolute normal
    Vector3 absNormal_;
    /// Plane intercept parameter
    float intercept_;
};
