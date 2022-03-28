#ifndef INITBOARD_H
#define INITBOARD_H

#include <bitset>
#include <string>

void initBoard(std::bitset<64> board[12]);

void initBoard2(std::bitset<64>& r,std::bitset<64>& n,std::bitset<64>& b,std::bitset<64>& q,std::bitset<64>& k,
                std::bitset<64>& p,std::bitset<64>& R,std::bitset<64>& N,std::bitset<64>& B,std::bitset<64>& Q,
                std::bitset<64>& K,std::bitset<64>& P);

void initFromFEN(std::string fen, std::bitset<64>& r,std::bitset<64>& n,std::bitset<64>& b,std::bitset<64>& q,std::bitset<64>& k,
                std::bitset<64>& p,std::bitset<64>& R,std::bitset<64>& N,std::bitset<64>& B,std::bitset<64>& Q,
                std::bitset<64>& K,std::bitset<64>& P);

#endif // INITBOARD_H
