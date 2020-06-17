#ifndef MINIMAXAGENT_H
#define MINIMAXAGENT_H
#include "TTTCommonTypes.h"
#include "AIAgent.h"

class MiniMaxAgent final : public AIAgent
{
public:
    MiniMaxAgent(unsigned short depth, BoardMarks AImark, BoardMarks playerMark);
    int play(Board &board) override;

private:
    const unsigned short depth_;
    const BoardMarks AImark_;
    const BoardMarks playerMark_;

    static constexpr short AI_WIN_SCORE = 1;
    static constexpr short PLAYER_WIN_SCORE = -1;
    static constexpr short TIE_SCORE = 0;

    short maxMove(Board &board, unsigned short depth, short alpha, short beta) const;
    short minMove(Board &board, unsigned short depth, short alpha, short beta) const;
    int score(const BoardState state) const;
};

#endif // MINIMAXAGENT_H
