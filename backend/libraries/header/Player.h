#pragma once

#include "User.h"

class Player : public User
{
public:
    bool isReady = false;

    int progress = 0;
};