cmake_minimum_required(VERSION 3.8)
project(TCPserver)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pthread")
set(SOURCE_FILES main.cpp
                Server.cpp
                Server.h
                FileReader.cpp
                FileReader.h
                CommandsManager.cpp
                CommandsManager.h
                Command.h
                PlayCommand.h
                PlayCommand.cpp
                JoinCommand.cpp
                JoinCommand.h
                PrintCommand.cpp
                PrintCommand.h
                CloseCommand.cpp
                CloseCommand.h
                StartCommand.cpp
                StartCommand.h
        GameroomData.h ClientHandler.cpp ClientHandler.h GameHandler.cpp GameHandler.h)
add_executable(TCPserver ${SOURCE_FILES})