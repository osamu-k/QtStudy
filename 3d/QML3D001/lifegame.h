#ifndef LIFEGAME_H
#define LIFEGAME_H

#include <QImage>
#include <QObject>
#include <QSet>
#include <QTimer>

class CellPosition;

class LifeGame : public QObject
{
    Q_OBJECT

public:
    explicit LifeGame(QObject *parent = 0);
    virtual ~LifeGame();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE bool isActive() const;

    Q_INVOKABLE void invertCellState( int row, int col );
    Q_INVOKABLE bool isLifeInCell( int row, int col );
    Q_INVOKABLE void next();
    Q_INVOKABLE void clear();

    Q_INVOKABLE int activeCount();

//    QSize imageSize() const;
//    QImage image( QColor color );

signals:
    void cellChanged( int row, int col );
    void allChanged();

private slots:
    void tick();

private:
    bool isNextLife( int row, int col );

//    int m_cellSize;
//    int m_cellCount;

//    QImage m_image;
    QTimer m_timer;
    QSet<CellPosition> m_cellsWithLife;
};

class CellPosition
{
public:
    CellPosition( int row, int column )
        : _row(row), _column(column)
    {
    }

    virtual ~CellPosition()
    {
    }

    int row() const
    {
        return _row;
    }

    int column() const
    {
        return _column;
    }

    void operator=( const CellPosition &other )
    {
        this->_row = other._row;
        this->_column = other._column;
    }

    bool operator==( const CellPosition &other ) const
    {
        return (this->_row == other._row) && (this->_column == other._column);
    }

    bool operator!=( const CellPosition &other ) const
    {
        return ! (*this == other);
    }

private:
    int _row;
    int _column;
};

inline uint qHash( const CellPosition &pos )
{
    return (pos.row() << 16) + pos.column();
}

#endif // LIFEGAME_H
