/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "CommandsManager.h"
#include "PlayCommand.h"
#include "PrintCommand.h"
#include "JoinCommand.h"
#include "CloseCommand.h"
#include "StartCommand.h"


CommandsManager::CommandsManager() {
    openGames = new map<string,int>();
    lobbyMap = new map<string, GameroomData *>();
    commandsMap["play"] = new PlayCommand();
    commandsMap["list_games"] = new PrintCommand(openGames, &openGamesLock);
    commandsMap["join"] = new JoinCommand(openGames, lobbyMap, &openGamesLock, &lobbyMapLock);
    commandsMap["close"] = new CloseCommand(lobbyMap, &lobbyMapLock);
    commandsMap["start"] = new StartCommand(openGames, &openGamesLock);
}
void CommandsManager::executeCommand(string command, vector<string> args, int clientSocket1, int clientSocket2) {
    Command *commandObj = commandsMap[command];
    // lock it so only one gets access to the commands at a time
    commandObj->execute(args, clientSocket1, clientSocket2);
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    map<string, GameroomData *>::iterator it2;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
    delete(openGames);
    for (it2 = lobbyMap->begin(); it2 != lobbyMap->end(); it2++) {
        delete it->second;
    }
    delete lobbyMap;
}

void CommandsManager::addToOpenGames(string roomName, int clientSocket) {
    pthread_mutex_lock(&openGamesLock);
    (*openGames)[roomName] = clientSocket;
    pthread_mutex_unlock(&openGamesLock);
}

void CommandsManager::removeFromOpenGames(string roomName) {
    pthread_mutex_lock(&openGamesLock);
    openGames->erase(roomName);
    pthread_mutex_unlock(&openGamesLock);
}

bool CommandsManager::isOpenGame(string &roomName) {
    bool result;
    pthread_mutex_lock(&openGamesLock);
    result = openGames->find(roomName) != openGames->end();
    pthread_mutex_unlock(&openGamesLock);
    return result;
}

void CommandsManager::removeFromLobby(string roomName) {
    pthread_mutex_lock(&lobbyMapLock);
    lobbyMap->erase(roomName);
    pthread_mutex_unlock(&lobbyMapLock);
}

void CommandsManager::addToLobby(string roomName, GameroomData *data) {
    pthread_mutex_lock(&lobbyMapLock);
    (*lobbyMap)[roomName] = data;
    pthread_mutex_unlock(&lobbyMapLock);
}