#include <unordered_map>
#include <functional>
#include <queue>

//Note: I honestly think the functions could be severely cut-back here.
//But it's better to follow presumed style provided the performance isn't in the gutter.

//Emulating the Player Class
class Player {
  //Simulating a database
  //There's no ordering required, so unordered map seems like the best call.
  std::unordered_map<uint32_t, int32_t> data_base;

public:
  Player() {};
  //Constants should be used to prevent unecessary changes to variables and show intention
  const bool setStorageValue(uint32_t key, uint32_t value) {
    return data_base.emplace(key, value).second;
  };
  const uint32_t getStorageValue(uint32_t key) const {
    return data_base.find(key)->second; 
  };

}; //Player

class EventHandler {
  typedef std::function<void(void)> Event;
  //A namespace would probably be better than using a static class here simply due to the possibility of errors.
  //However, in a small scenario like this it doesn't make too much of a difference.
  static std::queue<Event> EventQueue;

public:
  static const bool addEvent(std::function<bool(Player&,uint32_t)> storageFunction, Player& player, uint32_t storageKey) {
    EventQueue.push([&]() {storageFunction(player, storageKey); });
  }

};

//References are preferred over pointers for legibility and ease-of-use.
//In classes, inline would automatically take place. That isn't the case here.
inline bool zeroStorageByKey(Player& player, uint32_t storageValue) {
  //Presuming that -1 and 0 is never actually used, it'd be better to use zero to avoid the extra comparison operator.
  return player.setStorageValue(storageValue, 0);
};

//References are preferred over pointers for legibility and ease-of-use.
//In classes, inline would automatically take place. That isn't the case here.
inline const bool onPlayerLogout(Player& player) {
  //Presuming that -1 and 0 is never actually used, it'd be better to use zero to avoid the extra comparison operator.
  //That's also assuming I was supposed to use -1 and not positive 1
  if (player.getStorageValue(1000) != std::end) {
    //Personally, I would prefer to use a bit flag or similar notification.
    //However, I will assume using a function like this is intentional.
    //Assuming the reason for a boolean is error correction, return false on failure
    if (!EventHandler::addEvent(zeroStorageByKey, player, 1000)) return false;
  }
  else return false;
  return true;
};