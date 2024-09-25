#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include "gyroscope.h"
#include "api.h"

class Game {
    public:
        Game();
        ~Game();
        void Init();
        void Run();
    private:
        Gyroscope gyro;
        Api api;
};


#endif