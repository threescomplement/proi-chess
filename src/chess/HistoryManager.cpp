#include "HistoryManager.h"
#include "GameState.h"

HistoryManager::HistoryManager(int movesIntoThePast, const std::vector<HistoryEntry> &history)
        : movesIntoThePast(movesIntoThePast), history(history) {}

void HistoryManager::update(const Move &move, const GameState &state) {
    this->history.erase(this->history.end() - movesIntoThePast, this->history.end());
    this->movesIntoThePast = 0;
    this->history.push_back({move, state});
}

int HistoryManager::getMovesIntoThePast() const {
    return movesIntoThePast;
}

const std::vector<HistoryEntry> &HistoryManager::getHistory() const {
    return history;
}

void HistoryManager::setMovesIntoThePast(int movesIntoThePast) {
    HistoryManager::movesIntoThePast = movesIntoThePast;
}

void HistoryManager::setHistory(const std::vector<HistoryEntry> &history) {
    HistoryManager::history = history;
}

bool HistoryManager::canUndoMove() {
    return (movesIntoThePast < history.size());
}

Move HistoryManager::getMoveToUndo() {
    auto entry = this->history[this->history.size() - 1 - movesIntoThePast];
    movesIntoThePast++;
    return entry.move;
}

bool HistoryManager::canRedoMove() {
    return (movesIntoThePast > 0);
}

Move HistoryManager::getMoveToRedo() {
    auto entry = this->history[this->history.size() - movesIntoThePast];
    movesIntoThePast--;
    return entry.move;
}
