#include "crosswordtemplates.h"

#include "crosswordformat.h"

using namespace Crossword;

namespace Editor
{

namespace CrosswordTemplates
{

std::unique_ptr<CrosswordState> Empty::make2DGrid(int x, int y)
{
    std::unique_ptr<CrosswordState> state(new CrosswordState());

    auto& format = state->m_FileFormat;
    format.m_Extension = Crossword::Formats::XWC101.first;
    format.m_Version = Crossword::Formats::XWC101.second;

    auto& grid = state->m_GridState;

    grid.m_Dimensions = VectorMath::Vec3i(x, y, 1);

    for(int gridY = 0; gridY < y; gridY++)
    {
        for(int gridX = 0; gridX < x; gridX++)
        {
            grid.m_Grid.push_back(std::make_tuple(CrosswordItem(" ", VectorMath::Vec3i(gridX, gridY, 0), QColor(Qt::white))));
        }
    }

    return state;
}

std::unique_ptr<CrosswordState> Empty::make3DGrid(int x, int y, int z)
{
    std::unique_ptr<CrosswordState> state(new CrosswordState());

    auto& format = state->m_FileFormat;
    format.m_Extension = Crossword::Formats::XWC3D101.first;
    format.m_Version = Crossword::Formats::XWC3D101.second;

    auto& grid = state->m_GridState;

    grid.m_Dimensions = VectorMath::Vec3i(x, y, z);

    for(int gridZ = 0; gridZ < z; gridZ++)
    {
        for(int gridY = 0; gridY < y; gridY++)
        {
            for(int gridX = 0; gridX < x; gridX++)
            {
                grid.m_Grid.push_back(std::make_tuple(CrosswordItem(" ", VectorMath::Vec3i(gridX, gridY, gridZ), QColor(Qt::white))));
            }
        }
    }

    return state;
}

std::unique_ptr<CrosswordState> Empty::make3DCombinationLock(int radius, int segments, int depth)
{
    std::unique_ptr<CrosswordState> state(new CrosswordState());

    Q_UNUSED(radius);
    Q_UNUSED(segments);
    Q_UNUSED(depth);

    return state;
}

}

}
