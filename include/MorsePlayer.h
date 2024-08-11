#pragma once

#include <Arduino.h>

typedef void (*sidetone_fun_ptr)(boolean);

class MorsePlayer {
    public:
        MorsePlayer(sidetone_fun_ptr sidetone_cb);
        void play(const char *text, int wpm);
    private:
        sidetone_fun_ptr sidetone_cb;

};