#pragma once

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