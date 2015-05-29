inline bool operator ==(const Ray& left, const Ray& right)
{
    return (left.position == right.position) && (left.direction == right.direction);
}

inline bool operator !=(const Ray& left, const Ray& right)
{
    return (left.position != right.position) || (left.direction != right.direction);
}
