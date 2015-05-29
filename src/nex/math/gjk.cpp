#include <nex/math/gjk.h>

namespace nx
{

GJK::GJK() :
    mSimplexBits(0),
    mMaxLengthSq(0),
    mClosestPoint(vec3f())
{
    for (int i = 0; i < 4; i++) {
        mYLengthSq[i] = 0;
        for (int j = 0; j < 4; j++) {
            mEdgeLengthSq[i][j] = 0;
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 4; j++) {
            mDet[i][j] = 0;
        }
    }
}

void GJK::reset()
{
    mSimplexBits = 0;
    mMaxLengthSq = 0.0f;
}

bool GJK::addSupportPoint(const vec3f& newPoint)
{
    int index1 = (mBitsToIndices[mSimplexBits ^ 15] & 7) - 1;

    mY[index1] = newPoint;
    mYLengthSq[index1] = newPoint.lengthSquared();

    int num = mBitsToIndices[mSimplexBits];
    while (num != 0)
    {
        int index2 = (num & 7) - 1;
        vec3f vector3 = mY[index2] - newPoint;
        mEdges[index2][index1] = vector3;
        mEdges[index1][index2] = -vector3;
        mEdgeLengthSq[index1][index2] = mEdgeLengthSq[index2][index1] = vector3.lengthSquared();
        num >>= 3;
    }

    updateDeterminant(index1);

    return updateSimplex(index1);
}

void GJK::updateDeterminant(int xmIdx)
{
    int index1 = 1 << xmIdx;

    mDet[index1][xmIdx] = 1.0f;

    int num1 = mBitsToIndices[mSimplexBits];
    int num2 = num1;
    int num3 = 0;

    while (num2 != 0)
    {
        int index2 = (num2 & 7) - 1;
        int num4 = 1 << index2;
        int index3 = num4 | index1;

        mDet[index3][index2] = vec3f::dot(mEdges[xmIdx][index2], mY[xmIdx]);
        mDet[index3][xmIdx] = vec3f::dot(mEdges[index2][xmIdx], mY[index2]);

        int num5 = num1;
        for (int index4 = 0; index4 < num3; ++index4)
        {
            int index5 = (num5 & 7) - 1;
            int num6 = 1 << index5;
            int index6 = index3 | num6;
            int index7 =  mEdgeLengthSq[index2][index5] <  mEdgeLengthSq[xmIdx][index5] ? index2 : xmIdx;
            mDet[index6][index5] =  ( mDet[index3][index2] *  vec3f::dot(mEdges[index7][index5], mY[index2]) +  mDet[index3][xmIdx] *  vec3f::dot(mEdges[index7][index5], mY[xmIdx]));
            int index8 =  mEdgeLengthSq[index5][index2] <  mEdgeLengthSq[xmIdx][index2] ? index5 : xmIdx;
            mDet[index6][index2] =  ( mDet[num6 | index1][index5] *  vec3f::dot(mEdges[index8][index2], mY[index5]) +  mDet[num6 | index1][xmIdx] *  vec3f::dot(mEdges[index8][index2], mY[xmIdx]));
            int index9 =  mEdgeLengthSq[index2][xmIdx] <  mEdgeLengthSq[index5][xmIdx] ? index2 : index5;
            mDet[index6][xmIdx] =  ( mDet[num4 | num6][index5] *  vec3f::dot(mEdges[index9][xmIdx], mY[index5]) +  mDet[num4 | num6][index2] *  vec3f::dot(mEdges[index9][xmIdx], mY[index2]));
            num5 >>= 3;
        }
        num2 >>= 3;
        ++num3;
    }
    if ((mSimplexBits | index1) != 15)
        return;
    int index10 =  mEdgeLengthSq[1][0] <  mEdgeLengthSq[2][0] ? ( mEdgeLengthSq[1][0] <  mEdgeLengthSq[3][0] ? 1 : 3) : ( mEdgeLengthSq[2][0] <  mEdgeLengthSq[3][0] ? 2 : 3);
    mDet[15][0] =  ( mDet[14][1] *  vec3f::dot(mEdges[index10][0], mY[1]) +  mDet[14][2] *  vec3f::dot(mEdges[index10][0], mY[2]) +  mDet[14][3] *  vec3f::dot(mEdges[index10][0], mY[3]));
    int index11 =  mEdgeLengthSq[0][1] <  mEdgeLengthSq[2][1] ? ( mEdgeLengthSq[0][1] <  mEdgeLengthSq[3][1] ? 0 : 3) : ( mEdgeLengthSq[2][1] <  mEdgeLengthSq[3][1] ? 2 : 3);
    mDet[15][1] =  ( mDet[13][0] *  vec3f::dot(mEdges[index11][1], mY[0]) +  mDet[13][2] *  vec3f::dot(mEdges[index11][1], mY[2]) +  mDet[13][3] *  vec3f::dot(mEdges[index11][1], mY[3]));
    int index12 =  mEdgeLengthSq[0][2] <  mEdgeLengthSq[1][2] ? ( mEdgeLengthSq[0][2] <  mEdgeLengthSq[3][2] ? 0 : 3) : ( mEdgeLengthSq[1][2] <  mEdgeLengthSq[3][2] ? 1 : 3);
    mDet[15][2] =  ( mDet[11][0] *  vec3f::dot(mEdges[index12][2], mY[0]) +  mDet[11][1] *  vec3f::dot(mEdges[index12][2], mY[1]) +  mDet[11][3] *  vec3f::dot(mEdges[index12][2], mY[3]));
    int index13 =  mEdgeLengthSq[0][3] <  mEdgeLengthSq[1][3] ? ( mEdgeLengthSq[0][3] <  mEdgeLengthSq[2][3] ? 0 : 2) : ( mEdgeLengthSq[1][3] <  mEdgeLengthSq[2][3] ? 1 : 2);
    mDet[15][3] =  ( mDet[7][0] *  vec3f::dot(mEdges[index13][3], mY[0]) +  mDet[7][1] *  vec3f::dot(mEdges[index13][3], mY[1]) +  mDet[7][2] *  vec3f::dot(mEdges[index13][3], mY[2]));
}

bool GJK::updateSimplex(int newIndex)
{
    int yBits = mSimplexBits | 1 << newIndex;
    int xBits = 1 << newIndex;
    for (int index = mSimplexBits; index != 0; --index)
    {
        if ((index & yBits) == index && satisfiesRule(index | xBits, yBits))
        {
            mSimplexBits = index | xBits;
            mClosestPoint = computeClosestPoint();
            return true;
        }
    }

    bool flag = false;
    if (satisfiesRule(xBits, yBits))
    {
        mSimplexBits = xBits;
        mClosestPoint = mY[newIndex];
        mMaxLengthSq = mYLengthSq[newIndex];
        flag = true;
    }

    return flag;
}

vec3f GJK::computeClosestPoint()
{
    float num1 = 0.0f;

    vec3f zero(0.0f);

    mMaxLengthSq = 0.0f;
    int num2 = mBitsToIndices[mSimplexBits];
    while (num2 != 0)
    {
        int index = (num2 & 7) - 1;
        float num3 = this.det[this.simplexBits][index];
        num1 += num3;
        zero += this.y[index] * num3;
        mMaxLengthSq = MathHelper.Max(this.maxLengthSq, this.yLengthSq[index]);
        num2 >>= 3;
    }
    return zero / num1;
}

bool GJK::satisfiesRule(int xBits, int yBits)
{

}

} //namespace nx
