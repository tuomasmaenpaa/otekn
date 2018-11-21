#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>
#include "iplayer.hh"


namespace Student {


class Player : public Common::IPlayer
{
public:

    Player(int id);
    ~Player();

    int getPlayerId() const;
    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft() const;

private:

    int _Id;
    int _actionsLeft;
};
}

#endif // PLAYER_HH
