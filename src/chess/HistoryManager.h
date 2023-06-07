#ifndef CHESS_HISTORYMANAGER_H
#define CHESS_HISTORYMANAGER_H

#include "Move.h"
#include "GameState.h"


struct HistoryEntry {
    Move move;
    GameState state;
};

class HistoryManager {
private:
    int movesIntoThePast;
    std::vector<HistoryEntry> history;
public:
    explicit HistoryManager(int movesIntoThePast = 0, const std::vector<HistoryEntry> &history = {});

    void update(const Move &move, const GameState &state);

    int getMovesIntoThePast() const;

    const std::vector<HistoryEntry> &getHistory() const;

    void setMovesIntoThePast(int movesIntoThePast);

    void setHistory(const std::vector<HistoryEntry> &history);

    bool canUndoMove();

    bool canRedoMove();

    Move getMoveToUndo();

    Move getMoveToRedo();
};


#endif //CHESS_HISTORYMANAGER_H
