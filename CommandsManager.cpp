/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "CommandsManager.h"
#include "PlayCommand.h"
#include "PrintCommand.h"
#include "JoinCommand.h"
#include "CloseCommand.h"
#include "StartCommand.h"

pthread_mutex_t mutex;

CommandsManager::CommandsManager() {
    commandsMap["play"] = new PlayCommand();
    commandsMap["list_games"] = new PrintCommand(&openGames);
    commandsMap["join"] = new JoinCommand(&openGames, &lobbyMap);
    commandsMap["close"] = new CloseCommand(&openGames, &lobbyMap);
    commandsMap["start"] = new StartCommand(&openGames);
}
void CommandsManager::executeCommand(string command, vector<string> args, ClientData *data) {
    Command *commandObj = commandsMap[command];
    // lock it so only one gets access to the commands at a time
    pthread_mutex_lock(&mutex);
    commandObj->execute(args, data);
    pthread_mutex_unlock(&mutex);
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
