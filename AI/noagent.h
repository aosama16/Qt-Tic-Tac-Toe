#ifndef NOAGENT_H
#define NOAGENT_H
#include "AIAgent.h"
#include <qglobal.h>

class NoAgent final : public AIAgent{
public:
    NoAgent() {}
    ~NoAgent() {}

    int play(Board& board, BoardMarks mark) override {
        Q_UNUSED(board);
        Q_UNUSED(mark);
        return -1;
    }
    void reset() override {}
};
#endif // NOAGENT_H
