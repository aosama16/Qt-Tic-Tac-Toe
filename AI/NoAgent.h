#ifndef NOAGENT_H
#define NOAGENT_H
#include "AIAgent.h"
#include "TTTCommonTypes.h"
#include <qglobal.h>

/**
 * @brief The NoAgent class is an empty class that does not play,
 * it specifies the null object behaviour,
 * so it represents the lack of an AI agent,
 * which is useful to avoid using if conditions in
 * code when checking on the existence of an AI agent.
 *
 * This class has no CPP file as it does not have any
 * implementation details.
 */

class NoAgent final : public AIAgent
{
public:
    NoAgent() {}
    ~NoAgent() override {}
    /**
     * @brief play does nothing to simulate a null agent behaviour.
     * @param board: a reference to the board model.
     * @return an invalid cell location to not trigger any kind of updates.
     */
    int play(Board& board) override {
        Q_UNUSED(board);
        return defaults::INVALID_CELL;
    }
};
#endif // NOAGENT_H
