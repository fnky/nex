#include <nex/math/boundingfrustum.h>
#include <nex/math/boundingsphere.h>
#include <nex/math/plane.h>
#include <nex/math/ray.h>

#include <limits>

namespace nx
{
    BoundingFrustum::BoundingFrustum()
    { }

    void BoundingFrustum::setMatrix(const mat4f& value)
    {
        // Store our matrix.
        mMatrix = value;

        // Calculate all of the planes for the bounding frustum.
        // TODO (Tyler): Test this.
        mPlanes[2].normal.x = -value[0][3] - value[0][0];
        mPlanes[2].normal.y = -value[1][3] - value[1][0];
        mPlanes[2].normal.z = -value[2][3] - value[2][0];
        mPlanes[2].distance = -value[3][3] - value[3][0];

        mPlanes[3].normal.x = -value[0][3] + value[0][0];
        mPlanes[3].normal.y = -value[1][3] + value[1][0];
        mPlanes[3].normal.z = -value[2][3] + value[2][0];
        mPlanes[3].distance = -value[3][3] + value[3][0];

        mPlanes[4].normal.x = -value[0][3] + value[0][1];
        mPlanes[4].normal.y = -value[1][3] + value[1][1];
        mPlanes[4].normal.z = -value[2][3] + value[2][1];
        mPlanes[4].distance = -value[3][3] + value[3][1];

        mPlanes[5].normal.x = -value[0][3] - value[0][1];
        mPlanes[5].normal.y = -value[1][3] - value[1][1];
        mPlanes[5].normal.z = -value[2][3] - value[2][1];
        mPlanes[5].distance = -value[3][3] - value[3][1];

        mPlanes[0].normal.x = -value[0][2];
        mPlanes[0].normal.y = -value[1][2];
        mPlanes[0].normal.z = -value[2][2];
        mPlanes[0].distance = -value[3][2];

        mPlanes[1].normal.x = -value[0][3] + value[0][2];
        mPlanes[1].normal.y = -value[1][3] + value[1][2];
        mPlanes[1].normal.z = -value[2][3] + value[2][2];
        mPlanes[1].distance = -value[3][3] + value[3][2];

        // Normalize all of the planes.
        for (int index = 0; index < 6; ++index)
        {
            const float oneOverLength = 1.0f / mPlanes[index].normal.length();

            mPlanes[index].normal *= oneOverLength;
            mPlanes[index].distance *= oneOverLength;
        }

        Ray intersectionLine1 = Plane::computeIntersectionLine(mPlanes[0], mPlanes[2]);
        mCornerArray[0] = intersectionLine1.computeIntersection(mPlanes[4]);
        mCornerArray[3] = intersectionLine1.computeIntersection(mPlanes[5]);

        Ray intersectionLine2 = Plane::computeIntersectionLine(mPlanes[3], mPlanes[0]);
        mCornerArray[1] = intersectionLine2.computeIntersection(mPlanes[4]);
        mCornerArray[2] = intersectionLine2.computeIntersection(mPlanes[5]);

        intersectionLine2 = Plane::computeIntersectionLine(mPlanes[2], mPlanes[1]);
        mCornerArray[4] = intersectionLine2.computeIntersection(mPlanes[4]);
        mCornerArray[7] = intersectionLine2.computeIntersection(mPlanes[5]);

        intersectionLine2 = Plane::computeIntersectionLine(mPlanes[1], mPlanes[3]);
        mCornerArray[5] = intersectionLine2.computeIntersection(mPlanes[4]);
        mCornerArray[6] = intersectionLine2.computeIntersection(mPlanes[5]);
    }

    vec3f BoundingFrustum::supportMapping(const vec3f vector) const
    {
        int searchIndex = 0;
        float thetaA = vec3f::dot(mCornerArray[0], vector);

        for (int index2 = 1; index2 < 8; ++index2)
        {
            float thetaB = vec3f::dot(mCornerArray[index2], vector);
            if (thetaB > thetaA)
            {
                searchIndex = index2;
                thetaA = thetaB;
            }
        }

        return mCornerArray[searchIndex];
    }

    bool BoundingFrustum::intersects(const BoundingBox& box) const
    {
        mGJK.reset();

        vec3f result1 = mCornerArray[0] - box.min;

        if ((double)result1.lengthSquared() < 9.99999974737875E-06)
            result1 = mCornerArray[0] - box.max;

        float num1 = std::numeric_limits<float>::max();
        float num2;
        do
        {
            vec3f v;

            v.x = -result1.x;
            v.y = -result1.y;
            v.z = -result1.z;

            vec3f result2 = supportMapping(v);
            vec3f result3 = supportMapping(result1);
            vec3f result4 = result2 - result3;

            if (result1.x * result4.x + result1.y * result4.y + result1.z * result4.z > 0.0f)
                return false;

            mGJK.addSupportPoint(result4);

            result1 = mGJK.closestPoint();
            float num3 = num1;
            num1 = result1.lengthSquared();
            if ((double)num3 - (double)num1 <= 9.99999974737875E-06 * (double)num3)
                return false;
            num2 = 4E-05f * mGJK.maxLengthSquared();
        }
        while (!mGJK.fullSimplex() && num1 >= num2);
        return true;
    }

    bool BoundingFrustum::intersects(const BoundingFrustum& frustum) const
    {
        mGJK.reset();

        const vec3f* otherCorners = frustum.getCorners();

        vec3f result1 = mCornerArray[0] - otherCorners[0];

        if ((double)result1.lengthSquared() < 9.99999974737875E-06)
            result1 = mCornerArray[0] - otherCorners[1];

        float num1 = std::numeric_limits<float>::max();
        float num2;
        do
        {
            vec3f v;

            v.x = -result1.x;
            v.y = -result1.y;
            v.z = -result1.z;

            vec3f result2 = supportMapping(v);
            vec3f result3 = frustum.supportMapping(result1);
            vec3f result4 = result2 - result3;

            if (result1.x * result4.x + result1.y * result4.y + result1.z * result4.z > 0.0f)
                return false;

            mGJK.addSupportPoint(result4);

            result1 = mGJK.closestPoint();

            float num3 = num1;
            num1 = result1.lengthSquared();
            num2 = 4E-05f * mGJK.maxLengthSquared();
            if ((double) num3 - (double)num1 <= 9.99999974737875E-06 * (double) num3)
                return false;
        }
        while (!mGJK.fullSimplex() && num1 >= num2);
        return true;
    }

    float BoundingFrustum::intersects(const Ray& ray) const
    {
        ContainmentType result1 = contains(ray.position);
        if (result1 == ContainmentType::Contains)
        {
            return  0.0f;
        }
        else
        {
            float minDistance = std::numeric_limits<float>::min();//float.MinValue;
            float maxDistance = std::numeric_limits<float>::max();//float.MaxValue;

            for (auto plane : mPlanes)
            {
                float dotA = vec3f::dot(ray.direction, plane.normal);
                float dotB = vec3f::dot(ray.position, plane.normal);

                dotB += plane.distance;

                if (std::abs(dotA) < 9.99999974737875E-06)
                {
                    if (dotB > 0.0f)
                        return 0.0f;
                }
                else
                {
                    float num3 = -dotB / dotA;
                    if (dotA < 0.0f)
                    {
                        if (num3 > maxDistance)
                            return 0.0f;

                        if (num3 > minDistance)
                            minDistance = num3;
                    }
                    else
                    {
                        if (num3 < minDistance)
                            return 0.0f;
                        if (num3 < maxDistance)
                            maxDistance = num3;
                    }
                }
            }

            float clampedResult = minDistance >= 0.0f ? minDistance : maxDistance;

            if (clampedResult < 0.0f)
                return 0.0f;

            return clampedResult;
        }
    }

    bool BoundingFrustum::intersects(const BoundingSphere& sphere) const
    {
        mGJK.reset();

        vec3f result1 = mCornerArray[0] - sphere.center;

        if ((double)result1.lengthSquared() < 9.99999974737875E-06)
            result1 = vec3f::unitX;

        float num1 = std::numeric_limits<float>::max();
        float num2;

        do
        {
            vec3f v;
            v.x = -result1.x;
            v.y = -result1.y;
            v.z = -result1.z;

            vec3f result2 = supportMapping(v);
            vec3f result3 = supportMapping(result1);

            vec3f result4 = result2 - result3;

            if (result1.x * result4.x + result1.y * result4.y + result1.z * result4.z > 0.0f)
                return false;

            mGJK.addSupportPoint(result4);
            result1 = mGJK.closestPoint();

            float num3 = num1;

            num1 = result1.lengthSquared();

            if ((double) num3 - (double) num1 <= 9.99999974737875E-06 * (double)num3)
                return false;

            num2 = 4E-05f * mGJK.maxLengthSquared();
        }
        while (!mGJK.fullSimplex() && num1 >= num2);
        return true;
    }

    PlaneIntersectionType BoundingFrustum::intersects(const Plane& plane) const
    {
        int result = 0;
        for (int index = 0; index < 8; ++index)
        {
            float dotResult = vec3f::dot(mCornerArray[index], plane.normal);

            if (dotResult + plane.distance > 0.0f)
                result |= 1;
            else
                result |= 2;

            if (result == 3)
                return PlaneIntersectionType::Intersecting;
        }
        return result != 1 ? PlaneIntersectionType::Back : PlaneIntersectionType::Front;
    }

    ContainmentType BoundingFrustum::contains(const vec3f& point) const
    {
        for (auto plane : mPlanes)
        {
            if (((plane.normal.x * point.x + plane.normal.y * point.y + plane.normal.z * point.z) + plane.distance) > 9.99999974737875E-06f)
                return ContainmentType::Disjoint;
        }
        return ContainmentType::Contains;
    }

    ContainmentType BoundingFrustum::contains(const BoundingBox& box) const
    {
        bool flag = false;
        for (auto plane : mPlanes)
        {
            switch (plane.intersects(box))
            {
            case PlaneIntersectionType::Front:
                return ContainmentType::Disjoint;
            case PlaneIntersectionType::Intersecting:
                flag = true;
                break;
            }
        }
        return !flag ? ContainmentType::Contains : ContainmentType::Intersects;
    }

    ContainmentType BoundingFrustum::contains(const BoundingFrustum& frustum) const
    {
        ContainmentType containmentType = ContainmentType::Disjoint;
        if (intersects(frustum))
        {
            containmentType = ContainmentType::Contains;
            const vec3f* cornerPtr = frustum.getCorners();
            for (int index = 0; index < 8; ++index)
            {
                if (contains(cornerPtr[index]) == ContainmentType::Disjoint)
                {
                    containmentType = ContainmentType::Intersects;
                    break;
                }
            }
        }
        return containmentType;
    }

    ContainmentType BoundingFrustum::contains(const BoundingSphere& sphere) const
    {
        const vec3f center = sphere.center;
        const float radius = sphere.radius;

        int result = 0;

        for (auto plane : mPlanes)
        {
            float cross = (plane.normal.x * center.x + plane.normal.y * center.y + plane.normal.z * center.z) + plane.distance;

            if (cross > radius)
                return ContainmentType::Disjoint;

            if (cross < -radius)
                ++result;
        }

        return result != 6 ? ContainmentType::Intersects : ContainmentType::Contains;
    }

} //namespace nx
