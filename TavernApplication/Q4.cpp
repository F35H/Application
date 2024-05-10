//Q4 - Assume all method calls work fine.Fix the memory leak issue in below method

#include <memory>

void Game::addItemToPlayer(const std::string & recipient, uint16_t itemId)
{
  //I assume this isn't a memory leak because it gathers from a function;
  Player* player = g_game.getPlayerByName(recipient);
  if (!player) {
    
    //This is a memory leak due to the new keyword. Simply update to unique pointer to have it delete automatically;
    player = std::make_unique<Player>(Player(nullptr));
    if (!IOLoginData::loadPlayerByName(player, recipient)) {
      return;
    }
  }

  //I assume this isn't a memory leak because it gathers from a function;
  Item* item = Item::CreateItem(itemId);
  if (!item) {
    return;
  }

  g_game.internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT);

  if (player->isOffline()) {
    IOLoginData::savePlayer(player);
  }
}