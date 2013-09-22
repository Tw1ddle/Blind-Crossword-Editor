#include "xmlsaver.h"

#include <QXmlStreamWriter>
#include <QDebug>

#include "utilities.h"

namespace Crossword
{

namespace Formats
{

namespace
{
    // Element and attribute names
    QString title = "title";
    QString authors = "author";
    QString notes = "notes";

    QString dimensions = "dimensions";
    QString x = "x";
    QString y = "y";
    QString z = "z";

    QString griditem = "griditem";
    QString letter = "letter";
    QString coordinate = "coordinate";
    QString colour = "colour";

    QString clue = "clue";
    QString number = "number";
    QString guess = "guess";
    QString solution = "solution";
    QString direction = "direction";
    QString componentLengths = "componentLengths";
    QString letterPositions = "letterPositions";

    // Namespace tags
    QString metadata = "metadata";
    QString grid = "grid";
    QString clues = "clues";
}

XMLSaver::XMLSaver()
{
}

QStringList XMLSaver::save(const CrosswordState& state) const
{
    QString filepath;
    // Write the file to disk
    QFile file(filepath);
    file.open(QFile::WriteOnly);

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE TODO>"); // TODO!
    xml.writeStartElement("xml"); // ???
    xml.writeAttribute("version", "1.0"); // ??????

    const auto& m = state.m_Metadata;
    xml.writeComment("Metadata");
    xml.writeTextElement(metadata, title, m.m_Title);
    xml.writeTextElement(metadata, authors, m.m_Authors);
    xml.writeTextElement(metadata, notes, m.m_Notes);

    const auto& g = state.m_GridState;

    xml.writeComment("Grid data");
    auto d = g.m_Dimensions;
    xml.writeStartElement(grid, dimensions);
    xml.writeAttribute(grid, x, QString::number(d.x()));
    xml.writeAttribute(grid, y, QString::number(d.y()));
    xml.writeAttribute(grid, z, QString::number(d.z()));
    xml.writeEndElement();

    for(size_t i = 0; i < g.m_Grid.size(); i++)
    {
        const auto item = std::get<CrosswordState::GridState::ITEM>(g.m_Grid.at(i));

        xml.writeStartElement(grid, griditem);
        xml.writeAttribute(letter, item.getText());
        xml.writeAttribute(coordinate, x, QString::number(item.getCoordinate().x()));
        xml.writeAttribute(coordinate, y, QString::number(item.getCoordinate().y()));
        xml.writeAttribute(coordinate, z, QString::number(item.getCoordinate().z()));
        xml.writeAttribute(colour, QString::number(item.getColour().rgba(), 16)); // To hex
        xml.writeEndElement();
    }

    xml.writeComment("Clues");
    const auto& c = state.m_ClueState.m_Clues;
    for(size_t j = 0; j < c.size(); j++)
    {
        const auto& item = c.at(j);
        xml.writeStartElement(clues, clue);
        xml.writeAttribute(clue, number, item.getNumber());
        xml.writeAttribute(clue, guess, item.getGuess());
        xml.writeAttribute(clue, solution, item.getSolution());
        xml.writeAttribute(clue, direction, item.getDirection());
        // TODO!
        xml.writeEndElement();
    }

    xml.writeEndDocument();

    if(xml.hasError())
    {
        qDebug() << xml.device()->errorString();

        return QStringList();
    }

    // TODO use an IODevice that writes to a QStringList...
    return QStringList();
}

}
}
