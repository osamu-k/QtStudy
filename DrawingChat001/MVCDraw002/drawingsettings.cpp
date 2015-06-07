#include "drawingsettings.h"

DrawingSettings::DrawingSettings()
    : m_lineColor( Qt::black )
    , m_fillColor( Qt::black )
    , m_lineWidth( 0 )
    , m_outlineEnabled( true )
    , m_fillColorEnabled( false )
{
}

DrawingSettings::~DrawingSettings()
{
}

void DrawingSettings::writeTo( QDataStream &out ) const
{
    out << m_lineColor;
    out << m_fillColor;
    out << static_cast<qint16>(m_lineWidth);
    out << m_outlineEnabled;
    out << m_fillColorEnabled;
}

void DrawingSettings::readFrom( QDataStream &in )
{
    qint16 i16;
    in >> m_lineColor;
    in >> m_fillColor;
    in >> i16;
    m_lineWidth = i16;
    in >> m_outlineEnabled;
    in >> m_fillColorEnabled;
}
