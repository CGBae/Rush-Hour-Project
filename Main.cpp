#include <iostream>
#include <conio.h>
#include "Consola.h"
#include "macro.h"

using namespace std;

int moveCount = 0;
bool gameEnded = false;

int getKey() {
    int ch = 0;
    ch = _getch();
    return (ch != 0xe0) ? ch : (0xe000 | _getch());
}

class Car {
    int _posx;
    int _posy;
    bool _isVertical;
    int _length;
    bool _isMainCar;
public:
    void setPos(int x, int y) {
        _posx = x; _posy = y;
    }

    void setOrientation(bool isVertical) {
        _isVertical = isVertical;
    }

    void setLength(int l) {
        _length = l;
    }

    void setMainCar(bool flag) {
        _isMainCar = flag;
    }

    int getPosX() {
        return _posx;
    }

    int getPosY() {
        return _posy;
    }

    int getLength() {
        return _length;
    }

    bool getOrientation() {
        return _isVertical;
    }

    bool isMainCar() {
        return _isMainCar;
    }

    void moveCar(int direction, Car carList[]) {
        // 0: up, 1: right, 2: down, 4: left
        if (direction == 1 && _isMainCar == true && _posx + _length == MAP_SIZE) {
            gameEnded = true;
        }
        else if (isMoveValid(direction, carList)) {
            switch (direction) {
            case 0:
                if (_isVertical == true && _posy > 0) { _posy--; moveCount++; }
                break;
            case 1:
                if (_isVertical == false && _posx + _length < MAP_SIZE) { _posx++; moveCount++; }
                break;
            case 2:
                if (_isVertical == true && _posy + _length < MAP_SIZE) { _posy++; moveCount++; }
                break;
            case 3:
                if (_isVertical == false && _posx > 0) { _posx--; moveCount++; }
                break;
            }
        }
    }

    bool isMoveValid(int direction, Car carList[]) {
        int nposx = _posx;
        int nposy = _posy;

        // 새로운 위치 계산
        switch (direction) {
        case 0:  // Up
            if (_isVertical == true && _posy > 0) nposy--;
            break;
        case 1:  // Right
            if (_isVertical == false && _posx + _length < MAP_SIZE) nposx++;
            break;
        case 2:  // Down
            if (_isVertical == true && _posy + _length < MAP_SIZE) nposy++;
            break;
        case 3:  // Left
            if (_isVertical == false && _posx > 0) nposx--;
            break;
        }

        // 벽에 충돌하는 경우 false 반환
        if (nposx < 0 || nposy < 0 || nposx + (_isVertical ? 0 : _length) > MAP_SIZE || nposy + (_isVertical ? _length : 0) > MAP_SIZE) {
            return false;
        }

        // 다른 차와 충돌하는 경우 false 반환
        for (int i = 0; i < 6; i++) {
            if (&carList[i] != this) {
                if (carList[i].getOrientation() == true) {
                    if (direction == 0) {
                        if ((_isVertical == true && nposx == carList[i].getPosX() && nposy == carList[i].getPosY() + carList[i].getLength()))
                            return false;
                    }

                    if (direction == 1) {
                        if (_isVertical == false && nposy >= carList[i].getPosY() && nposy < carList[i].getPosY() + carList[i].getLength() && nposx + _length - 1 == carList[i].getPosX())
                            return false;
                    }

                    if (direction == 2) {
                        if (_isVertical == true && nposx == carList[i].getPosX() && nposy + _length - 1 == carList[i].getPosY())
                            return false;
                    }

                    if (direction == 3) {
                        if (_isVertical == false && nposy >= carList[i].getPosY() && nposy < carList[i].getPosY() + carList[i].getLength() && nposx == carList[i].getPosX())
                            return false;
                    }
                }

                if (carList[i].getOrientation() == false) {
                    if (direction == 0) {
                        if ((_isVertical == true && nposx >= carList[i].getPosX() && nposx < carList[i].getPosX() + carList[i].getLength() && nposy == carList[i].getPosY()))
                            return false;
                    }

                    if (direction == 1) {
                        if (_isVertical == false && nposy == carList[i].getPosY() && nposx + _length - 1 == carList[i].getPosX())
                            return false;
                    }

                    if (direction == 2) {
                        if (_isVertical == true && nposx >= carList[i].getPosX() && nposx < carList[i].getPosX() + carList[i].getLength() && nposy + _length - 1 == carList[i].getPosY())
                            return false;
                    }

                    if (direction == 3) {
                        if (_isVertical == false && nposy == carList[i].getPosY() && nposx == carList[i].getPosX() + carList[i].getLength())
                            return false;
                    }
                }
            }
        }


        return true;
    }

};

class View {
public:
    int drawTitle() {
        int menu = 0; int key = 0;

        textbackground(WHITE);
        int titleArray[11][15] = {
            { 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
            { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1 },
            { 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 },
            { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0 },
            { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
            { 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0 },
            { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0 },
            { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1 }
        };

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 15; j++) {
                gotoxy((START + j) * 2, START + i);
                if (titleArray[i][j] == 1) cout << " ";
            }
        }

        textbackground(BLACK);

        for (int i = 0; i < 3; i++) {
            gotoxy(START * 2 + 10, START + 12 + i);
            cout << "LEVEL " << i + 1;
        }

        while (1) {
            gotoxy(START * 2 + 8, START + 12 + menu);
            cout << ">";
            key = getKey();
            if (key == KEY_ENTER) return menu;
            else if (key == KEY_DOWN && menu < 2) { gotoxy(START * 2 + 8, START + 12 + menu); cout << " "; menu++; }
            else if (key == KEY_UP && menu > 0) { gotoxy(START * 2 + 8, START + 12 + menu); cout << " "; menu--; }
        }
    }

    void drawMap() {
        textbackground(WHITE);
        for (int i = 0; i < MAP_SIZE + 2; i++) {
            gotoxy((START - 1 + i) * 2, START - 1);
            cout << " ";
        }
        for (int i = 0; i < MAP_SIZE; i++) {
            gotoxy((START - 1) * 2, START + i);
            cout << " ";
            gotoxy((START + MAP_SIZE) * 2, START + i);
            cout << " ";
        }
        for (int i = 0; i < MAP_SIZE + 2; i++) {
            gotoxy((START - 1 + i) * 2, START + MAP_SIZE);
            cout << " ";
        }
        textbackground(BLACK);
        gotoxy((START + MAP_SIZE) * 2, START + 2);
        cout << " ";
    }

    void drawCar(int level) {
        int key = 0;
        int car = 0;

        Car carList[6] = {};

        if (level == 1) {
            carList[0].setPos(0, 2);
            carList[0].setOrientation(false);
            carList[0].setLength(2);
            carList[0].setMainCar(true);

            carList[1].setPos(2, 0);
            carList[1].setOrientation(true);
            carList[1].setLength(3);

            carList[2].setPos(3, 0);
            carList[2].setOrientation(false);
            carList[2].setLength(3);

            carList[3].setPos(5, 1);
            carList[3].setOrientation(true);
            carList[3].setLength(2);

            carList[4].setPos(3, 1);
            carList[4].setOrientation(false);
            carList[4].setLength(2);

            carList[5].setPos(5, 3);
            carList[5].setOrientation(true);
            carList[5].setLength(3);

        }
        else if (level == 0) {
            carList[0].setPos(0, 2);
            carList[0].setOrientation(false);
            carList[0].setLength(2);
            carList[0].setMainCar(true);

            carList[1].setPos(0, 3);
            carList[1].setOrientation(true);
            carList[1].setLength(3);

            carList[2].setPos(1, 3);
            carList[2].setOrientation(false);
            carList[2].setLength(3);

            carList[3].setPos(3, 0);
            carList[3].setOrientation(true);
            carList[3].setLength(3);
        }
        else if (level == 2) {
            carList[0].setPos(0, 2);
            carList[0].setOrientation(false);
            carList[0].setLength(2);
            carList[0].setMainCar(true);

            carList[1].setPos(0, 3);
            carList[1].setOrientation(false);
            carList[1].setLength(3);

            carList[2].setPos(2, 0);
            carList[2].setOrientation(true);
            carList[2].setLength(3);

            carList[3].setPos(4, 0);
            carList[3].setOrientation(false);
            carList[3].setLength(2);

            carList[4].setPos(5, 3);
            carList[4].setOrientation(true);
            carList[4].setLength(3);
        }

        drawMap();

        while (gameEnded == false) {
            for (int carNo = 0; carNo < 6; carNo++) {
                Car currentCar = carList[carNo];

                for (int i = 0; i < currentCar.getLength(); i++) {
                    if (currentCar.getOrientation() == true)
                        gotoxy((START + currentCar.getPosX()) * 2, START + currentCar.getPosY() + i);
                    else
                        gotoxy((START + currentCar.getPosX() + i) * 2, START + currentCar.getPosY());
                    textbackground(carNo + 1);
                    cout << carNo + 1;
                }
            }

            textbackground(BLACK);

            gotoxy((START + MAP_SIZE + 2) * 2, START - 1);
            cout << "RUSH HOUR GAME";
            gotoxy((START + MAP_SIZE + 2) * 2, START + 1);
            cout << "Level " << dec << level + 1;
            gotoxy((START + MAP_SIZE + 2) * 2, START + 2);
            cout << "Selected Car: " << dec << car + 1;
            gotoxy((START + MAP_SIZE + 2) * 2, START + 3);
            cout << "Move Count: " << dec << moveCount;

            key = getKey();

            clrscr(); drawMap();

            if (key == KEY_1) car = 0;
            else if (key == KEY_2) car = 1;
            else if (key == KEY_3) car = 2;
            else if (key == KEY_4) car = 3;
            else if (key == KEY_5) car = 4;
            else if (key == KEY_6) car = 5;

            switch (key) {
            case KEY_UP: carList[car].moveCar(0, carList); break;
            case KEY_RIGHT: carList[car].moveCar(1, carList); break;
            case KEY_DOWN: carList[car].moveCar(2, carList); break;
            case KEY_LEFT: carList[car].moveCar(3, carList); break;
            }
        }
    }

    int drawResult(int level) {
        int menu = 0; int key = 0;

        textbackground(WHITE);

        int resultArray[5][18] = {
            { 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1 },
            { 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1 },
            { 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
            { 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1 }
        };

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 18; j++) {
                gotoxy((START + j) * 2, START + i);
                if (resultArray[i][j] == 1) cout << " ";
            }
        }

        textbackground(BLACK);

        gotoxy(START * 2, START + 7);
        cout << "Level: " << dec << level + 1 << "\t Moved " << moveCount << " times. " << endl;

        gotoxy(START * 2 + 3, START + 9);
        cout << "RESTART";
        gotoxy(START * 2 + 3, START + 10);
        cout << "EXIT";

        while (1) {
            gotoxy(START * 2, START + 9 + menu);
            cout << ">";
            key = getKey();
            if (key == KEY_ENTER) return menu;
            else if (key == KEY_DOWN && menu < 1) { gotoxy(START * 2, START + 9 + menu); cout << " "; menu++; }
            else if (key == KEY_UP && menu > 0) { gotoxy(START * 2, START + 9 + menu); cout << " "; menu--; }
        }
    }


};

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

void drawFinal() {
    textbackground(WHITE);
    int finalArray[11][23] = {
        { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1 },
    };

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 23; j++) {
            gotoxy((START + j) * 2, START + i);
            if (finalArray[i][j] == 1) cout << " ";
        }
    }

    textbackground(BLACK);
}

int main() {
    Controller con;
    int flag = 0;
    while (!flag) { flag = con.start(); }
    clrscr();
    drawFinal();
}