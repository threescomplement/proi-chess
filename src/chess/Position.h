#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H


class Position {
public:
    int getRow() const;
    int getCol() const;
private:
    int column;
    int row;
};


#endif //CHESS_POSITION_H
