#ifndef AIAGENT_H
#define AIAGENT_H

/**
 * @brief The AIAgent Interface describes
 * the behaviour of any implemented AI agents.
 */

class Board;
class AIAgent
{
public:
    AIAgent() {}
    virtual ~AIAgent() {}

    virtual int play(Board &board) = 0;
    virtual void reset() {}
};

#endif // AIAGENT_H
