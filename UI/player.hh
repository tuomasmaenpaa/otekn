#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"


class Player : public Common::IPlayer
{
public:
    Player();
    ~Player();

    int getPlayerId();
    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft();
};

#endif // PLAYER_HH
