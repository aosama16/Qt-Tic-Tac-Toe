#ifndef NOAGENT_H
#define NOAGENT_H
#include "AIAgent.h"
#include "TTTCommonTypes.h"
#include <qglobal.h>

class NoAgent final : public AIAgent{
public:
    NoAgent() {}
    ~NoAgent() {}

    int play(Board& board) override {
        Q_UNUSED(board);
        return defaults::INVALID_CELL;
    }
};
#endif // NOAGENT_H
