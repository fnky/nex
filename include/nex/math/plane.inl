inline bool operator ==(const Plane& left, const Plane& right)
{
    return (left.normal == right.normal) && (left.distance == right.distance);
}

inline bool operator !=(const Plane& left, const Plane& right)
{
    return (left.normal != right.normal) || (left.distance != right.distance);
}
