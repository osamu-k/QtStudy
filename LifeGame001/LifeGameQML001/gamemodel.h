#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QSet>

class CellPosition;

class GameModel : public QObject
{
    Q_OBJECT

public:
    explicit GameModel(QObject *parent = 0);
    virtual ~GameModel();

    Q_INVOKABLE void invertCellState( int row, int col );
    Q_INVOKABLE bool isLifeInCell( int row, int col );
    Q_INVOKABLE void next();
    Q_INVOKABLE void clear();

signals:
    void cellChanged( int row, int col );
    void allChanged();

private:
    bool isNextLife( int row, int col );

    QSet<CellPosition> cellsWithLife;
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

#endif // GAMEMODEL_H
