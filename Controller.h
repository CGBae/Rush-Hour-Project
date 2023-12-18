#pragma once

#include "View.h"

class Controller {
    View _view;
public:
    void init() {
        gameEnded = false;
        moveCount = 0;
    }

    int start() {
        init();
        clrscr();
        int level = _view.drawTitle();
        clrscr();
        _view.drawCar(level);
        clrscr();
        return _view.drawResult(level);
    }
};