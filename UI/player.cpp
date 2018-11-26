#include "player.hh"
namespace Student {


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
