/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */
#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>
#include "iplayer.hh"

/* Headerfile of the player class that inherits Common::IPlayer.
 */

namespace Student {


class Player : public Common::IPlayer
{
public:
    // SEE IPLAYER FOR DOCUMENTATION OF FUNCTIONS BELOW.
    Player(int id);
    ~Player();

    int getPlayerId() const;
    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft() const;
    // SEE IPLAYER FOR DOCUMENTATION OF FUNCTIONS ABOVE.

private:

    // Id of the player.
    int _Id;
    // Actions that the player has left.
    int _actionsLeft;
};
}

#endif // PLAYER_HH
