#ifndef API_H
#define API_H

#include "utilities.h"
#include "WiFiManager.h"

class Api {
    public:
        Api();
        ~Api();
        void Init();
        bool IsConnected();
        void CreatePlayer(String name);
    private:

};

#endif