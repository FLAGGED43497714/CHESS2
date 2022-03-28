#include "LegalMoves.h"
#include "coutBoard.h"

#include <vector>
#include <bitset>
#include <string>
#include <iostream>

std::bitset<64> const FILEA("1000000010000000100000001000000010000000100000001000000010000000") ;
std::bitset<64> const FILEH("0000000100000001000000010000000100000001000000010000000100000001") ;

std::bitset<64> const RANK4("0000000000000000000000000000000011111111000000000000000000000000") ;
std::bitset<64> const RANK5("0000000000000000000000001111111100000000000000000000000000000000") ;


void legPaW (std::vector<int>& moves, std::bitset<64> P,
             std::bitset<64> whitePieces, std::bitset<64> blackPieces,
             std::bitset<64> occupied, std::bitset<64> enPassant){

    std::bitset<64> attackRight, attackLeft, advance1, advance2 ;

    attackRight = P ;
    attackLeft = P ;
    advance1 = P ;
    advance2 = P ;

    attackRight <<= 7 ;
    attackLeft <<= 9 ;
    advance1 <<= 8 ;
    advance2 <<= 16 ;

    attackRight = attackRight & ~FILEA & (blackPieces | enPassant) ;
    attackLeft = attackLeft & ~FILEH & (blackPieces | enPassant) ;
    advance1 = advance1 &~occupied;
    advance2 = advance2 &RANK4 &~occupied &~(occupied<<8);

    //coutBitSet(pAttackRight) ;

    for (int k = 16 ; k < 64 ; k++ ){
        if (attackRight[k]) {
            int dest = k ;
            int pos = k - 7 ;
            moves.push_back(pos);
            moves.push_back(dest);
        }
    }
    for (int k = 18 ; k < 64 ; k++ ){
        if (attackLeft[k]) {
            int dest = k ;
            int pos = k - 9 ;
            moves.push_back(pos);
            moves.push_back(dest);
        }
    }
    for (int k = 16 ; k < 64 ; k++ ){
        if (advance1[k]) {
            int dest = k ;
            int pos = k - 8 ;
            moves.push_back(pos);
            moves.push_back(dest);
        }
    }

    for (int k = 24 ; k < 32 ; k++ ){
        if (advance2[k]) {
            int dest = k ;
            int pos = k - 16 ;
            moves.push_back(pos);
            moves.push_back(dest);
        }
    }


    //coutBitSet(pAttackRight) ;

}

void legPaB (std::vector<int>& moves, std::bitset<64> p,
             std::bitset<64> whitePieces, std::bitset<64> blackPieces,
             std::bitset<64> occupied, std::bitset<64> enPassant){

    std::bitset<64> attackRight, attackLeft, advance1, advance2 ;

    attackRight = p ;
    attackLeft = p ;
    advance1 = p ;
    advance2 = p ;

    attackRight >>= 9 ;
    attackLeft >>= 7 ;
    advance1 >>= 8 ;
    advance2 >>= 16 ;

    attackRight = attackRight & ~FILEA & (whitePieces | enPassant) ;
    attackLeft = attackLeft & ~FILEH & (whitePieces | enPassant) ;
    advance1 = advance1 &~occupied ;
    advance2 = advance2 &RANK5 &~occupied &~(occupied>>8);

    //coutBitSet(pAttackRight) ;

    for (int k = 0 ; k < 47 ; k++ ){
        if (attackRight[k]) {
            int dest = k ;
            int pos = k + 9 ;
            moves.push_back(pos);
            moves.push_back(dest);
        }
    }
    for (int k = 1 ; k < 48 ; k++ ){
        if (attackLeft[k]) {
            int dest = k ;
            int pos = k + 7 ;
            moves.push_back(pos);
            moves.push_back(dest);
        }
    }
    for (int k = 0 ; k < 48 ; k++ ){
        if (advance1[k]) {
            int dest = k ;
            int pos = k + 8 ;
            moves.push_back(pos);
            moves.push_back(dest);
        }
    }

    for (int k = 32 ; k < 40 ; k++ ){
        if (advance2[k]) {
            int dest = k ;
            int pos = k + 16 ;
            moves.push_back(pos);
            moves.push_back(dest);
        }
    }


    //coutBitSet(pAttackRight) ;

}

void sliderHV (std::vector<int>& moves, std::bitset<64> piece,
             std::bitset<64> allyPieces, std::bitset<64> ennemyPieces,
             std::bitset<64> occupied){

    std::bitset<64> slider("0000000000000000000000000000000000000000000000000000000000000000") ;
    std::bitset<64> left ;
    std::bitset<64> right ;

    for (int k = 0 ; k < 64 ; k++ ){
        if (piece[k]){
            slider[k] = 1 ;
            left = occupied ^ (occupied - slider - slider) ;
        }
    }

    coutBitSet(left) ;



