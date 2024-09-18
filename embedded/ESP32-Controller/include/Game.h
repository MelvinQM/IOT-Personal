#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include "Gyroscope.h"
#include "Api.h"
#include "BluetoothClient.h"

class Game {
    public:
        Game();
        ~Game();
        void Init();
        void Run();
    private:
        Gyroscope gyro;
        Api api;
        BluetoothClient btClient;
};


#endif