#include "formatscommon.h"

namespace Crossword
{

namespace Formats
{

const QMap<QString, Direction> Common::getDirections()
{
    QMap<QString, Direction> map;
    map.insert("Across", Direction::ACROSS);
    map.insert("Backwards", Direction::BACKWARDS);
    map.insert("Away", Direction::AWAY);
    map.insert("Towards", Direction::TOWARDS);
    map.insert("Down", Direction::DOWN);
    map.insert("Up", Direction::UP);
    map.insert("Diametric", Direction::DIAMETRIC);
    map.insert("Clockwise", Direction::CLOCKWISE);
    map.insert("Anticlockwise", Direction::ANTICLOCKWISE);
    map.insert("Snaking", Direction::SNAKING);
    map.insert("Unknown", Direction::UNKNOWN);

    return map;
}

template<typename T>
struct Across : public std::binary_function<T, T, bool>
{
    bool operator()(T l, T r)
    {
        return (l.x() < r.x()) && (l.y() == r.y()) && (l.z() == r.z());
    }
};

template<typename T>
struct Backwards : public std::binary_function<T, T, bool>
{
    bool operator()(T l, T r)
    {
        return (l.x() > r.x()) && (l.y() == r.y()) && (l.z() == r.z());
    }
};

template<typename T>
struct Away : public std::binary_function<T, T, bool>
{
    bool operator()(T l, T r)
    {
        return (l.x() == r.x()) && (l.y() > r.y()) && (l.z() == r.z());
    }
};

template<typename T>
struct Towards : public std::binary_function<T, T, bool>
{
    bool operator()(T l, T r)
    {
        return (l.x() == r.x()) && (l.y() < r.y()) && (l.z() == r.z());
    }
};

template<typename T>
struct Down : public std::binary_function<T, T, bool>
{
    bool operator()(T l, T r)
    {
        return (l.x() == r.x()) && (l.y() == r.y()) && (l.z() < r.z());
    }
};

template<typename T>
struct Up : public std::binary_function<T, T, bool>
{
    bool operator()(T l, T r)
    {
        return (l.x() == r.x()) && (l.y() == r.y()) && (l.z() > r.z());
    }
};

// Get a direction enum from a string argument e.g. "Across" -> enum Across
Direction getDirection(const QString& direction)
{
    auto directions = Common::getDirections();

    auto iterator = directions.find(direction);

    if(iterator == directions.end())
    {
        return Direction::UNKNOWN;
    }

    return iterator.value();
}

// Infer the direction from the positions of letters in the clue
Direction getDirection(std::vector<VectorMath::Vec3i> letterPositions)
{
    if(std::is_sorted(letterPositions.begin(), letterPositions.end(), Across<VectorMath::Vec3i>()))
    {
        return Direction::ACROSS;
    }
    if(std::is_sorted(letterPositions.begin(), letterPositions.end(), Backwards<VectorMath::Vec3i>()))
    {
        return Direction::BACKWARDS;
    }
    if(std::is_sorted(letterPositions.begin(), letterPositions.end(), Away<VectorMath::Vec3i>()))
    {
        return Direction::AWAY;
    }
    if(std::is_sorted(letterPositions.begin(), letterPositions.end(), Towards<VectorMath::Vec3i>()))
    {
        return Direction::TOWARDS;
    }
    if(std::is_sorted(letterPositions.begin(), letterPositions.end(), Down<VectorMath::Vec3i>()))
    {
        return Direction::DOWN;
    }
    if(std::is_sorted(letterPositions.begin(), letterPositions.end(), Up<VectorMath::Vec3i>()))
    {
        return Direction::UP;
    }

    return Direction::UNKNOWN;
}

}
}
