#include <string>
//Q2 - Fix or improve the implementation of the below method
//
//function printSmallGuildNames(memberCount)
//-- this method is supposed to print names of all guilds that have less than memberCount max members
//local selectGuildQuery = "SELECT name FROM guilds WHERE max_members < %d;"
//local resultId = db.storeQuery(string.format(selectGuildQuery, memberCount))
//local guildName = result.getString("name")
//print(guildName)
//end

void printGuldNamesLessThanInput(uint32_t maxMemberCount) {
  //This is assuming there's a memberCountColumn. 
  //Otherwise I'd have to use COUNT in someway depending on context
  auto query = "SELECT name FROM guilds WHERE memberCount < " + std::to_string(maxMemberCount) + ";";
  
  //I'm kind of guessing here because there are so many unknowns.
  auto result = Database::QueryDatabase(query);
  for (auto& guildName : Database::GetData(result.getQueryData(), "names")) {
    //I'm assuming you want an in-game terminal of some kind and not the literal terminal
    PrintToGameConsole(guildName);
  }; 
};
