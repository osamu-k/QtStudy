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

