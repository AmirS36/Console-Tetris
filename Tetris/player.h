#pragma once
class Board;
class Tetromino;

enum class Difficulty { EASY, MEDIUM, HARD };
enum class PlayerType { HUMAN, COMPUTER };

class Player
{
private:
    PlayerType playerType;

public:
    Player() : playerType(PlayerType::HUMAN) {}
    Player(PlayerType type) : playerType(type) {}

    virtual PlayerType getType() const { return playerType; }
};

//Human player
class Human : public Player
{
public:
    Human() : Player(PlayerType::HUMAN) {}

};

//Computer player
class Computer : public Player
{
private:
    Difficulty difficulty;

public:
    Computer() : Player(PlayerType::COMPUTER), difficulty(Difficulty::HARD) {}

    void setDifficulty(Difficulty diff) { difficulty = diff; }
    Difficulty getDifficulty() const { return difficulty; }

    void calcBestMove(Board board, int& dest_col, int& rotations, Tetromino* pTetro);
    void calcAnyMove(Board board, int& dest_col, int& rotations, Tetromino* pTetro);

    void calcBestMoveShape(Board board, int& dest_col, int& rotations, Tetromino* pTetro);
    void calcAnyMoveShape(Board board, int& dest_col, int& rotations, Tetromino* pTetro);
    bool makeMoveCopy(Board board, int dest_col, int rotations, int depth, Tetromino* pTetro, int& filledLines);

    void calcBestMoveBomb(Board board, int& dest_col, Tetromino* pTetro);
    bool makeMoveBombCopy(Board board, int dest_col, int depth, Tetromino* pTetro, int& pointsCleared);

};

