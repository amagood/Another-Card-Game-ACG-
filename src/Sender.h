//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_SENDER_H
#define ANOTHER_CARD_GAME_ACG_SENDER_H

#include <deque>
#include <mutex>

#include <nlohmann/json.hpp>

using json = nlohmann::json;
class Sender
{
public:
    Sender()=default;
    Sender(std::deque<json> &toTransfer, std::mutex &mut);
    void send();
    void pushJson(json json_);

private:
    std::deque<json> toTransferQueue;
    //std::mutex *queueMutex;
};

#endif //ANOTHER_CARD_GAME_ACG_SENDER_H
