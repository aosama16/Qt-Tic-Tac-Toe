#ifndef AIAGENT_H
#define AIAGENT_H
#include "TTTCommonTypes.h"

class Board;
class AIAgent {
public:
    AIAgent() {}
    virtual ~AIAgent() {}

    virtual int play(Board &board, BoardMarks mark) = 0;
    virtual void reset() = 0;
};

#endif // AIAGENT_H
