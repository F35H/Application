//Q3 - Fix or improve the name and the implementation of the below method
//
//function do_sth_with_PlayerParty(playerId, membername)
//player = Player(playerId)
//local party = player:getParty()
//
//for k, v in pairs(party : getMembers()) do
//if v == Player(membername) then
//party : removeMember(Player(membername))
//end
//end
//end
//
//const bool do_sth_with_PlayerParty

#include <array>
#include <memory>

//Define is not necessarily bad, but it is considered outdated.
//This is a more modern way to do it. 
inline constexpr uint8_t partiedPlayerCount = 4;

//Emulating the PlayerClass
class Player {
  //A map could easily be used here, but due to the constant nature of allocation an array may or maynot be better.
  //You could also use something like a list or vector, but a list in particular would have issues regarding memory locality depending on how parties are set-up or used
  typedef std::array<Player, 4> Party;
  
  //Presumably all players share the same "party pointer."
  //Smart pointers are common form modernly, but in game development in particular it may or may not be the best idea. 
  //This differs between programmers, computers, and compilers, but sometimes smart pointers are faster than manual memory management.
  //shared_ptrs in particular run a specifically high risk of performance issues, and here you'd likely need to share pointers between the different player classes
  //Therefore, raw pointer it is.
  //The being said, because it's not smart, it's prone to memory leaks. This should probably be clearly labled and noted down SOMEWHERE
  Party* playerPartyPtr;

  //Types should be greatest to lowest in byte size in any class or struct specifically to maintain memory locality and have a cleanly packed struct.
  //Of course, that's not always possible, but here it clearly is.
  uint32_t playerId = 0;

public:
  //rhs for Right Hand Side
  bool operator==(const Player rhs) {
    return rhs.playerId == this->playerId;
  };
  bool operator==(Player rhs) {
    return rhs.playerId == this->playerId;
  }; 
  bool operator==(Player* rhs) {
    return rhs->playerId == this->playerId;
  };

  Player();
  Player(uint32_t userId) {
    //Obviously in a real scenario you would look up the player data in SQL or some other solution.
    //This is probably a bad idea because the pointer is shared.
    //In this current scenario "addPlayerToParty" should handle this.
    playerPartyPtr = new Party({ userId ,0,0,0});
    
    //Using the this pointer could have performance implications and should be avoided if possible.
    //Mainly this is with virtual functions, but still, good practice
    playerId = userId;
  };
  uint32_t getId() const {
    return playerId;
  };
  Party* getPartyArrayPtr() const {
    return playerPartyPtr;
  }; 
  void setPartyArrayPtr(Party* partyPtr) {
    playerPartyPtr = partyPtr;
  };
}; //Player

bool operator==(const Player lhs, const Player rhs) {
  return lhs.getId() == rhs.getId();
}; 

//This assuming that copying the player reference isn't an option for the parameters.
//That or simply using the party member index isn't also an option.
bool removePlayerFromParty(uint32_t localPlayerId, uint32_t partyPlayerId) {
  auto player = Player(localPlayerId); 
  auto playerParty   = *player.getPartyArrayPtr();
  bool determineSuccess = false;

  //I use this simply following the idea "fast" should only be used in short-term use situations due to memory locality.
  for (uint_fast8_t playerIndex = 0; playerIndex <= partiedPlayerCount; ++playerIndex) {
    if (playerParty[playerIndex].getId() == partyPlayerId) {
      auto removedPlayer = playerParty[playerIndex];
      
      //determine if deallocating the array is the correct move
      for (uint_fast8_t emptyPlayerIdx = 0; emptyPlayerIdx <= partiedPlayerCount; ++emptyPlayerIdx) {
        if (playerParty[emptyPlayerIdx].getId() == partyPlayerId) continue;
        if (playerParty[emptyPlayerIdx].getId() == localPlayerId) continue;
        if (playerParty[emptyPlayerIdx].getId() == 0) determineSuccess = true;
        if (playerParty[emptyPlayerIdx].getId() != 0) { determineSuccess = false; break; };
      };

      //This is rather prone to memory leaks. This should probably be clearly labled and noted down SOMEWHERE
      if (determineSuccess) delete playerParty[playerIndex].getPartyArrayPtr();
      determineSuccess = true;
    }
    else {
      playerParty[playerIndex].setPartyArrayPtr(&playerParty);
    }
  }; 
  return determineSuccess;
}; 

