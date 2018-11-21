#include "player.hh"
namespace Student {


Player::Player(int id): _Id(id)
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

}
}
