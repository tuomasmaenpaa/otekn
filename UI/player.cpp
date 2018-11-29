/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */
#include "player.hh"
namespace Student {

/* Implemention of Player-class functions.
 */

Player::Player(int id): _Id(id), _actionsLeft(3)
{

}

Player::~Player()
{

}

int Player::getPlayerId() const
{
    return _Id;
}

void Player::setActionsLeft(unsigned int actionsLeft)
{
    _actionsLeft = actionsLeft;
}

unsigned int Player::getActionsLeft() const
{
    return _actionsLeft;
}
}
