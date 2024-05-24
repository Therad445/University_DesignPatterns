//#include "GameMap.h"
//
//GameMap::GameMap(int rows, int cols) : rows(rows), cols(cols) {
//    // Инициализация игровой карты
//    map = std::vector<std::vector<char>>(rows, std::vector<char>(cols, '.'));
//}
//
//void GameMap::printMap() const {
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            std::cout << map[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//}
//
//bool GameMap::isValidMove(int x, int y) const {
//    return x >= 0 && x < rows && y >= 0 && y < cols;
//}
