#include "crosswordtemplates.h"
#include "xwccommon.h"

using namespace Crossword;

namespace Editor
{

namespace CrosswordTemplates
{

CrosswordState Empty::make2DGrid(int x, int y)
{
    CrosswordState state;

    auto& grid = state.m_GridState;

    grid.m_Dimensions = VectorMath::Vec3i(x, y, 1);

    for(int gridY = 0; y < gridY; gridY++)
    {
        for(int gridX = 0; x < gridX; gridX++)
        {
            grid.m_Grid.push_back(std::make_tuple(CrosswordItem("", VectorMath::Vec3i(gridX, gridY, 0), QColor(Qt::white))));
        }
    }

    return state;
}

CrosswordState Empty::make3DGrid(int x, int y, int z)
{
    CrosswordState state;

    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(z);

    return state;
}

CrosswordState Empty::make3DCombinationLock(int radius, int segments, int depth)
{
    CrosswordState state;

    Q_UNUSED(radius);
    Q_UNUSED(segments);
    Q_UNUSED(depth);

    return state;
}

}

}
