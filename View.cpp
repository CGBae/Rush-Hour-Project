//#include "View.h"
//
//int getKey() { int ch = 0; ch = _getch(); return (ch != 0xe0) ? ch : (0xe000 | _getch()); }
//
//int View::drawTitle() {
//    int menu = 0; int key = 0;
//
//    gotoxy(START * 2, START);
//    cout << "RUSH HOUR GAME";
//
//    for (int i = 0; i < 3; i++) {
//        gotoxy(START * 2 + 3, START + 2 + i);
//        cout << "LEVEL  " << i + 1;
//    }
//
//    while (1) {
//        gotoxy(START * 2, START + 2 + menu);
//        cout << ">";
//        key = getKey();
//        if (key == KEY_ENTER) return menu;
//        else if (key == KEY_DOWN && menu < 2) { gotoxy(START * 2, START + 2 + menu); cout << " "; menu++; }
//        else if (key == KEY_UP && menu > 0) { gotoxy(START * 2, START + 2 + menu); cout << " "; menu--; }
//    }
//}
//
//void View::drawMap() {
//    for (int i = 0; i < MAP_SIZE + 2; i++) {
//        gotoxy((START - 1 + i) * 2, START - 1);
//        cout << "M";
//    }
//    for (int i = 0; i < MAP_SIZE; i++) {
//        gotoxy((START - 1) * 2, START + i);
//        cout << "M";
//        gotoxy((START + MAP_SIZE) * 2, START + i);
//        cout << "M";
//    }
//    for (int i = 0; i < MAP_SIZE + 2; i++) {
//        gotoxy((START - 1 + i) * 2, START + MAP_SIZE);
//        cout << "M";
//    }
//
//    gotoxy((START + MAP_SIZE) * 2, START + 3);
//    cout << "#";
//}
//
//void View::drawCar(int level) {
//    int key = 0;
//    int car = 0;
//
//    Car carList[6] = {};
//
//    carList[0].setPos(0, 2);
//    carList[0].setOrientation(false);
//    carList[0].setLength(2);
//
//    carList[1].setPos(4, 3);
//    carList[1].setOrientation(true);
//    carList[1].setLength(3);
//
//    carList[2].setPos(0, 1);
//    carList[2].setOrientation(false);
//    carList[2].setLength(3);
//
//    carList[3].setPos(3, 0);
//    carList[3].setOrientation(true);
//    carList[3].setLength(3);
//
//    drawMap();
//
//    while (1) {
//        for (int carNo = 0; carNo < 6; carNo++) {
//            Car currentCar = carList[carNo];
//
//            for (int i = 0; i < currentCar.getLength(); i++) {
//                if (currentCar.getOrientation() == true)
//                    gotoxy((START + currentCar.getPosX()) * 2, START + currentCar.getPosY() + i);
//                else
//                    gotoxy((START + currentCar.getPosX() + i) * 2, START + currentCar.getPosY());
//                cout << carNo + 1;
//            }
//        }
//
//        gotoxy((START - 1) * 2, START + MAP_SIZE + 2);
//        cout << "Keycode: 0x" << hex << key;
//        gotoxy((START - 1) * 2, START + MAP_SIZE + 3);
//        cout << "Selected Car: " << dec << car + 1;
//        gotoxy((START - 1) * 2, START + MAP_SIZE + 4);
//        cout << "Level: " << dec << level + 1;
//
//        key = getKey();
//
//        clrscr(); drawMap();
//
//        if (key == KEY_1) car = 0;
//        else if (key == KEY_2) car = 1;
//        else if (key == KEY_3) car = 2;
//        else if (key == KEY_4) car = 3;
//
//        switch (key) {
//        case KEY_UP: carList[car].moveCar(0, carList); break;
//        case KEY_RIGHT: carList[car].moveCar(1, carList); break;
//        case KEY_DOWN: carList[car].moveCar(2, carList); break;
//        case KEY_LEFT: carList[car].moveCar(3, carList); break;
//        }
//    }
//}
