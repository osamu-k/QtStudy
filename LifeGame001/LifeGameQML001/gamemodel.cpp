#include "gamemodel.h"

GameModel::GameModel(QObject *parent) :
    QObject(parent)
{
}

GameModel::~GameModel()
{
}

void GameModel::invertCellState( int row, int col )
{
    CellPosition pos( row, col );
    if( cellsWithLife.contains( pos ) ){
        cellsWithLife.remove( pos );
    }
    else{
        cellsWithLife << pos;
    }
    emit cellChanged( row, col );
}

bool GameModel::isLifeInCell( int row, int col )
{
    CellPosition pos( row, col );
    return cellsWithLife.contains( pos );
}

void GameModel::next()
{
    QSet< CellPosition > nextCellsWithLife;
    foreach( const CellPosition &pos, cellsWithLife ){
        for( int row = pos.row() - 1; row <= pos.row() + 1; row ++ ){
            for( int col = pos.column() - 1; col <= pos.column() + 1; col ++ ){
                if( isNextLife( row, col ) ){
                    CellPosition posLife( row, col );
                    nextCellsWithLife << posLife;
                }
            }
        }
    }
    cellsWithLife = nextCellsWithLife;
    emit allChanged();
}

bool GameModel::isNextLife( int row, int col )
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

void GameModel::clear()
{
    cellsWithLife.clear();
    emit allChanged();
}
