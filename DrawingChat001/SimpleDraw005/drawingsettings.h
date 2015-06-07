#ifndef DRAWINGSETTINGS_H
#define DRAWINGSETTINGS_H

#include <QColor>

class DrawingSettings
{
public:
    DrawingSettings();
    ~DrawingSettings();

    void setLineColor( QColor color ) { m_lineColor = color; }
    QColor lineColor() const { return m_lineColor; }

    void setFillColor( QColor color ) { m_fillColor = color; }
    QColor fillColor() const { return m_fillColor; }

    void setLineWidth( int width ) { m_lineWidth = width; }
    int lineWidth() const { return m_lineWidth; }

    void setOutlineEnabled( bool enabled ) { m_outlineEnabled = enabled; }
    bool isOutlineEnabled() const { return m_outlineEnabled; }

    void setFillColorEnabled( bool enabled ) { m_fillColorEnabled = enabled; }
    bool isFillColorEnabled() const { return m_fillColorEnabled; }

private:
    QColor m_lineColor;
    QColor m_fillColor;
    int m_lineWidth;
    bool m_outlineEnabled;
    bool m_fillColorEnabled;
};

#endif // DRAWINGSETTINGS_H
