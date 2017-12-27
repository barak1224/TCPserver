/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "PrintCommand.h"

PrintCommand::PrintCommand(map<string, int> openGames) :openGames(openGames){}

void PrintCommand::execute(vector<string> args) {
    for (int i = 0; i < openGames.size(); )
}
