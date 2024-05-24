//#pragma once
//#ifndef GAMEMAP_H
//#define GAMEMAP_H
//
//#include <vector>
//#include <iostream>
//
//class GameMap {
//private:
//    std::vector<std::vector<char>> map;
//    int rows;
//    int cols;
//
//public:
//    GameMap(int rows, int cols);
//
//    void printMap() const;
//    bool isValidMove(int x, int y) const;
//    void moveUnit(int oldX, int oldY, int newX, int newY, char unitSymbol);
//};
//void GameMap::moveUnit(int oldX, int oldY, int newX, int newY, char unitSymbol) {
//    map[oldX][oldY] = '.'; // Очистка старой позиции
//    map[newX][newY] = unitSymbol; // Обновление новой позиции на карте
//}
//#endif // GAMEMAP_H
