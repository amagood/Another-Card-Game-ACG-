#include "Room.h"

#include <cmath>
#include <ctime>
#include <limits>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>

#include "Router.h"

Room::Room(uint32_t id, const std::string& name, const std::string& password, uint32_t playerid) : _ID(id), _name(name), _password(password)
{
    _player.push_back(playerid);
    _deskController = DeskController();
}
Room::~Room()
{
    _player.clear();
    _player.shrink_to_fit();
}
nlohmann::json Room::deskAction(nlohmann::json json)
{
    return _deskController.getJson(json);
}
RoomMode Room::getMode(const std::string& mode)
{
    for(int i=0;i<(int)RoomMode::ROOMMODE_COUNT;i++)
    {
        std::string str(_roomModeString[i]);
        if(mode==str)
            return (RoomMode)i;
    }
    return RoomMode::ROOMMODE_COUNT;
}
Room* Room::createRoom(uint32_t player, RoomMode mode, uint32_t id, const std::string& name, const std::string& password)
{
    switch(mode)
    {
        case SINGLE_ROOM:
            break;
        case ONEONONE_ROOM:
            return new OneOnOneRoom(id, name, password, player);
        case LADDER_ROOM:
            return new LadderRoom(id, name, password, player);
        default:
            break;
    }
    return nullptr;
}
void Room::endGame()
{
    if(_deskController.winer_and_endgame()==1)
        _winner = 0;
    else if(_deskController.winer_and_endgame()==-1)
        _winner = 1;
    _loser = (_winner+1)&1;
}



constexpr short OneOnOneRoom::MaxPlayerNum;
bool OneOnOneRoom::addPlayer(uint32_t playerid)
{
    if(isFull()) return false;
    _player.push_back(playerid);
    return true;
}
void OneOnOneRoom::startGame(std::vector<U32vec> deck)
{
    _deskController.run(deck[0], deck[1]);
    deck.clear();
    deck.shrink_to_fit();
}


constexpr short OneOnOneRoom::MaxPlayerNum;
bool LadderRoom::addPlayer(uint32_t playerid)
{
    if(isFull()) return false;
    _player.push_back(playerid);
    return true;
}
void LadderRoom::startGame(std::vector<U32vec> deck)
{
    _deskController.run(deck[0], deck[1]);
    deck.clear();
    deck.shrink_to_fit();
}
int LadderRoom::getWinnerScore()
{
    return 30;
}
int LadderRoom::getLoserScore()
{
    return -5;
}
