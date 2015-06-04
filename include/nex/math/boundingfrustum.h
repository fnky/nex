#ifndef BOUNDINGFRUSTUM_H_INCLUDE
#define BOUNDINGFRUSTUM_H_INCLUDE

#include <nex/system/typedefs.h>
#include <nex/math/vec3.h>
#include <nex/math/matrix.h>
#include <nex/math/gjk.h>
#include <nex/math/plane.h>
#include <nex/math/boundingbox.h>

namespace nx
{
class BoundingSphere;

class BoundingFrustum
{
public:

    BoundingFrustum();

    /**
     * @brief Specifies the total number of corners (8) in the BoundingFrustum.
     */
    const int CornerCount = 8;

    /**
     * @brief Bounding Frustum Plane Index
     */
    enum BFPlaneIndex {
        NearPlaneIndex = 0,
        FarPlaneIndex = 1,
        LeftPlaneIndex = 2,
        RightPlaneIndex = 3,
        TopPlaneIndex = 4,
        BottomPlaneIndex = 5
    };

    /**
     * @brief Get the specified plane
     * @param index = index of the plane to get.
     * @return the specified plane.
     */
    const Plane getPlane(BFPlaneIndex index) const {
        return mPlanes[index];
    }

    /**
     * @brief Get a pointer to the current corner array.
     * @return const pointer.
     */
    const vec3f* getCorners() const { return mCornerArray; }

    /**
     * @brief Get the current matrix.
     * @return the matrix.
     */
    Matrix getMatrix() const { return mMatrix; }

    /**
     * @brief Checks whether the current BoundingFrustum intersects a BoundingBox.
     * @param box = The BoundingBox to check for intersection with.
     * @return true if the BoundingFrustum and BoundingBox intersect; false otherwise.
     */
    bool intersects(const BoundingBox& box) const;

    /**
     * @brief Checks whether the current BoundingFrustum intersects the specified BoundingFrustum.
     * @param frustum = The BoundingFrustum to check for intersection.
     * @return the intersection result.
     */
    bool intersects(const BoundingFrustum& frustum) const;

    /**
     * @brief Checks whether the current BoundingFrustum intersects the specified BoundingSphere.
     * @param sphere = The BoundingSphere to check for intersection with.
     * @return true if the BoundingFrustum and BoundingSphere intersect; false otherwise.
     */
    bool intersects(const BoundingSphere& sphere) const;

    /**
     * @brief Checks whether the current BoundingFrustum intersects a Ray.
     * @param ray = The Ray to check for intersection with.
     * @return Distance at which the ray intersects the BoundingFrustum or 0 if there is no intersection.
     */
    float intersects(const Ray& ray) const;

    /**
     * @brief Checks whether the current BoundingFrustum intersects the specified Plane.
     * @param plane = The Plane to check for intersection.
     * @return the itnersection type.
     */
    PlaneIntersectionType intersects(const Plane& plane) const;

    /**
     * @brief Checks whether the current BoundingFrustum contains the specified point.
     * @param point = The point to check against the current BoundingFrustum.
     * @return the containment type.
     */
    ContainmentType contains(const vec3f& point) const;

    /**
     * @brief Checks whether the current BoundingFrustum contains the specified BoundingBox.
     * @param box = The BoundingBox to check against the current BoundingFrustum.
     * @return the containment type.
     */
    ContainmentType contains(const BoundingBox& box) const;

    /**
     * @brief Checks whether the current BoundingFrustum contains the specified BoundingFrustum.
     * @param frustum = The BoundingFrustum to check against the current BoundingFrustum.
     * @return the containment type.
     */
    ContainmentType contains(const BoundingFrustum& frustum) const;

    /**
     * @brief Checks whether the current BoundingFrustum contains the specified BoundingSphere.
     * @param sphere = The BoundingSphere to check against the current BoundingFrustum.
     * @return the containment type.
     */
    ContainmentType contains(const BoundingSphere& sphere) const;

    /**
     * @brief Compute the bounding frustum from the given matrix.
     * @param matrix = matrix to compute from.
     */
    void setMatrix(const Matrix& matrix);

    /**
     * @brief supportMapping
     * @param vector
     * @return
     */
    vec3f supportMapping(const vec3f vector) const;

private:

    const int NumPlanes = 6;

    vec3f mCornerArray[8];

    Plane mPlanes[6];

    Matrix mMatrix;

    mutable GJK mGJK;

}; //class BoundingFrustum
} //namespace nx

#endif // BOUNDINGFRUSTUM_H_INCLUDE
