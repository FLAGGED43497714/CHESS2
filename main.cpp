#include <iostream>
#include <bitset>
#include <string>
#include <vector>

#include "coutBoard.h"
#include "initBoard.h"
#include "LegalMoves.h"


int main()
{

    std::bitset<64> r,n,b,q,k,p,R,N,B,Q,K,P;

    std::bitset<64> enPassant("0000000000000000000000000000000000000000000000000000000000000000");

    //std::string fen = "7Q/pp1R4/1kp1B3/8/1P6/8/P1P3PK/8" ;
    //std::string fen = "8/4p3/8/1PP1r1P1/8/8/8/8" ;
    std::string fen = "rnbqkbnr/1p2p1p1/2pp4/pP2Pp2/7p/5N2/P1PP1PPP/RNBQKB1R" ;

    //std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" ;

    initFromFEN(fen,r,n,b,q,k,p,R,N,B,Q,K,P) ;

    //coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P);

    std::bitset<64> occupied ;
    std::bitset<64> blackPieces ;
    std::bitset<64> whitePieces ;


    occupied = r | n | b | q | k | p | R | N | B | Q | K | P ;

    blackPieces = r | n | b | q | k | p ;
    whitePieces = R | N | B | Q | K | P ;

    std::vector<int> moves ;

    /* En passant :
    Faire l'update après chaque moves*/




    //legPaW(moves, P, whitePieces, blackPieces, occupied, enPassant) ;
    sliderHV(moves, r, blackPieces, whitePieces,occupied);

    for (int k = 0 ; k < moves.size() ; k ++){
        std::cout << moves[k] << std::endl ;
    }

    return 0;
}
