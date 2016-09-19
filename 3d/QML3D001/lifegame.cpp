#include "lifegame.h"

#include <QPainter>
#include <QDebug>

LifeGame::LifeGame(QObject *parent)
    : QObject( parent )

{
    connect( &m_timer, SIGNAL(timeout()), this, SLOT(tick()) );
}

LifeGame::~LifeGame()
{
}

void LifeGame::start()
{
    if( m_timer.isActive() ){
        m_timer.stop();
    }
    clear();

    invertCellState(  1,  1 );
    invertCellState(  0,  1 );
    invertCellState( -1,  1 );
    invertCellState( -1,  0 );
    invertCellState( -1, -1 );
    invertCellState(  0, -1 );
    invertCellState(  1, -1 );
    invertCellState(  1,  0 );

    m_timer.setInterval( 1000 );
    m_timer.start();
}

void LifeGame::stop()
{
    if( m_timer.isActive() ){
        m_timer.stop();
    }
}

bool LifeGame::isActive() const
{
    return m_timer.isActive();
}

void LifeGame::tick()
{
    next();
}

void LifeGame::invertCellState( int row, int col )
{
    CellPosition pos( row, col );
    if( m_cellsWithLife.contains( pos ) ){
        m_cellsWithLife.remove( pos );
    }
    else{
        m_cellsWithLife << pos;
    }
//    emit cellChanged( row, col );
}

bool LifeGame::isLifeInCell( int row, int col )
{
    CellPosition pos( row, col );
    return m_cellsWithLife.contains( pos );
}

void LifeGame::next()
{
    QSet< CellPosition > nextCellsWithLife;
    foreach( const CellPosition &pos, m_cellsWithLife ){
        for( int row = pos.row() - 1; row <= pos.row() + 1; row ++ ){
            for( int col = pos.column() - 1; col <= pos.column() + 1; col ++ ){
                if( isNextLife( row, col ) ){
                    CellPosition posLife( row, col );
                    nextCellsWithLife << posLife;
                }
            }
        }
    }
    m_cellsWithLife = nextCellsWithLife;

    emit allChanged();
}

bool LifeGame::isNextLife( int row, int col )
{
    int count = 0;
    for( int r = row - 1; r <= row + 1; r ++ ){
        for( int c = col - 1; c <= col + 1; c ++ ){
            if( isLifeInCell( r, c ) ){
                count ++;
            }
        }
    }
    return (3 <= count) && (count <= 4);
}

void LifeGame::clear()
{
    m_cellsWithLife.clear();
    emit allChanged();
}

