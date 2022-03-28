#ifndef LEGALMOVES_H
#define LEGALMOVES_H

#include <vector>
#include <bitset>

void legPaW (std::vector<int>& moves, std::bitset<64> P,
             std::bitset<64> whitePieces, std::bitset<64> blackPieces,
             std::bitset<64> occupied, std::bitset<64> enPassant);

void legPaB (std::vector<int>& moves, std::bitset<64> p,
             std::bitset<64> whitePieces, std::bitset<64> blackPieces,
             std::bitset<64> occupied, std::bitset<64> enPassant);

void sliderHV (std::vector<int>& moves, std::bitset<64> piece,
             std::bitset<64> allyPieces, std::bitset<64> ennemyPieces,
             std::bitset<64> occupied);


#endif // LEGALMOVES_H

