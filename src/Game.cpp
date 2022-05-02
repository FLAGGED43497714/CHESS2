#include "Game.h"

#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <limits>
#include <unistd.h>
#include <unordered_map>

#include "coutBoard.h"
#include "initBoard.h"
#include "LegalMoves.h"
#include "MakeMove.h"
#include "ChoseMove.h"
#include "SqNameToNb.h"


int GAMEintINFINITY = std::numeric_limits<int>::max() ;


void Game(){
    std::string nothing ;
    //std::cin >> nothing ;

    bool verbose = false ;

    bool whiteHuman = true ;
    bool blackHuman = 1 - whiteHuman;

    unsigned long long int r,n,b,q,k,p,R,N,B,Q,K,P;

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" ;

    //std::string fen = "8/4p3/5r2/1P4p1/8/7P/8/4P3" ;
    //std::string fen = "r3kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQK2R" ; // castle
    //std::string fen = "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR" ; //scandi
    //std::string fen = "8/8/3k4/3q4/8/8/8/2QKB3" ;
    //std::string fen = "1n6/8/8/8/8/8/8/8" ;
    //std::string fen = "8/5kpp/p2bqp2/1ppQ4/8/P1B4P/1PP3P1/R5K1" ;


    initFromFEN(fen,r,n,b,q,k,p,R,N,B,Q,K,P) ;

    std::vector<int> moves ;

    int moveNb = 0 ;

    unsigned long long int occupied ;
    unsigned long long int blackPieces ;
    unsigned long long int whitePieces ;

    unsigned long long int enPassant (0);

    std::string strPosition ;
    int position ;
    std::string strDestination ;
    int destination ;

    std::pair<int,int> lastMove ;

    bool CstlL = true;
    bool CstlS = true;
    bool cstlL = true;
    bool cstlS = true;

    bool brokeCastleS = false;
    bool brokeCastleL = false;
    bool brokecastleS = false;
    bool brokecastleL = false;

    int pieceCaptured (0);
    bool wasCastle (false);
    bool wasPromote (false);


    bool legal = false ;

    int bestInd ;
    int thisEval ;
    int bestEval ;

    //move ordering
    int captInd ;
    int dest ;
    unsigned long long int destInt ;
    int temp1 ;
    int temp2 ;

    //extern std::unordered_map<unsigned long long int, int> ump ;
    //extern std::unordered_map<unsigned long long int, int>::iterator it ;


    while(true){
        //std::cin >> nothing ;

        pieceCaptured = 0 ;
        wasCastle = false ;
        wasPromote = false ;
        brokeCastleS = false ;
        brokeCastleL = false ;
        brokecastleS = false ;
        brokecastleL = false ;

        enPassant = 0 ; // ATTENTION C'EST UN HOTFIX


        //std::cin >> nothing ;
        system("cls");
        std::cout << "CstlS " << CstlS << " CstlL "<< CstlL << " cstlS "<< cstlS <<" cstlL "<< cstlL << std::endl ;
        coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
        if (verbose){
            std::cin >> nothing ;
        }
        if (!(moveNb%2)){std::cout << "white " ;} else {std::cout << "black " ;}std::cout << "to play" << std::endl;



        moves.clear();
        occupied = r | n | b | q | k | p | R | N | B | Q | K | P ;
        blackPieces = r | n | b | q | k | p ;
        whitePieces = R | N | B | Q | K | P ;


        if (!(moveNb%2)){

            if (whiteHuman){
                legal = false ;

                legPaW(moves, P, whitePieces, blackPieces, occupied, enPassant) ;
                sliderHV(moves, R, whitePieces, occupied) ;
                sliderHV(moves, Q, whitePieces, occupied) ;
                sliderD(moves, B, whitePieces, occupied) ;
                sliderCD(moves, B, whitePieces, occupied) ;
                sliderD(moves, Q, whitePieces, occupied) ;
                sliderCD(moves, Q, whitePieces, occupied) ;
                KnightMoves(moves, N, whitePieces) ;
                KingMoves(moves, K, R, whitePieces, occupied, CstlL, CstlS, cstlL, cstlS) ;



                while (!legal){
                    std::cout << "position ?" << std::endl;
                    std::cin >> strPosition ;
                    std::cin.ignore() ;

                    position = SquareNameToNb(strPosition) ;


                    std::cout << "destination ?" << std::endl;
                    std::cin >> strDestination ;
                    std::cin.ignore() ;

                    destination = SquareNameToNb(strDestination) ;

                    for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                        if ((moves[2*semIdx] == position) && (moves[2*semIdx+1] == destination)) {
                            Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,wasCastle,wasPromote,pieceCaptured);
                            lastMove.first = position ;
                            lastMove.second = destination ;
                            //isEnPassant(lastMove, enPassant, P, true) ;
                            legal = true ;


                        }
                    }
                    if (!legal){
                        system("cls");
                        coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                        std::cout << "illegal" << std::endl;
                        if (!(moveNb%2)){std::cout << "white " ;} else {std::cout << "black " ;}std::cout << "to play" << std::endl;
                    }
                }
            } else { // white not human
                legPaW(moves, P, whitePieces, blackPieces, occupied, enPassant) ;
                sliderD(moves, B, whitePieces, occupied) ;
                sliderCD(moves, B, whitePieces, occupied) ;
                KnightMoves(moves, N, whitePieces) ;
                sliderHV(moves, Q, whitePieces, occupied) ;
                sliderD(moves, Q, whitePieces, occupied) ;
                sliderCD(moves, Q, whitePieces, occupied) ;
                sliderHV(moves, R, whitePieces, occupied) ;
                KingMoves(moves, K, R, whitePieces, occupied, CstlL, CstlS, cstlL, cstlS) ;



                captInd = 0 ;
                for (int semInd = 0 ; semInd < moves.size()/2 ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&blackPieces){
                        temp1 = moves[2*captInd] ;
                        temp2 = moves[2*captInd+1] ;
                        moves[2*captInd] = moves[2*semInd] ;
                        moves[2*captInd+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd +=1 ;
                    }
                }



                bestInd = 0 ;
                thisEval = -GAMEintINFINITY ;
                bestEval = -GAMEintINFINITY ;
                //ump.clear() ;
                for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                    position = moves[2*semIdx] ;
                    destination = moves[2*semIdx+1] ;
                    //std::cout << position << std::endl ;
                    //std::cout << destination << std::endl ;
                    pieceCaptured = 0 ;
                    wasCastle = false ;
                    wasPromote = false ;
                    brokeCastleS = false ;
                    brokeCastleL = false ;
                    brokecastleS = false ;
                    brokecastleL = false ;
                    //std::cout << "position = " << position << std::endl ;
                    //std::cout << "destination = " << destination << std::endl ;
                    //std::cout << "wasCastle = " << wasCastle << std::endl ;
                    //std::cout << "pieceCaptured = " << pieceCaptured << std::endl ;

                    //std::cout << "before do move : " << pieceCaptured << wasCastle << wasPromote << std::endl;
                    Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,wasCastle,wasPromote,pieceCaptured);
                    //std::cout << "after do move : " << pieceCaptured << wasCastle << wasPromote << std::endl;
                    if (verbose){
                        std::cout << "board before minimax " << std::endl ;
                        coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                        std::cin >> nothing ;
                    }
                    //sleep(2) ;
                    thisEval = minimax(r,n,b,q,k,p,R,N,B,Q,K,P,CstlL,CstlS,cstlL,cstlS,enPassant,4,5,-GAMEintINFINITY,GAMEintINFINITY,false) ;
                    //std::cout << thisEval << std::endl ;
                    if (verbose){
                            std::cout << "eval = " << thisEval << std::endl ;
                    }
                    if (thisEval > bestEval){
                        bestInd = 2*semIdx ;
                        bestEval = thisEval ;
                    }
                    if (verbose){std::cin >> nothing ;}
                    /*
                    std::cout << "about to undo " << std::endl;
                    std::cout << "board after minimax " << std::endl ;
                    std::cout << "position = " << position << std::endl ;
                    std::cout << "destination = " << destination << std::endl ;
                    std::cout << "wasCastle = " << wasCastle << std::endl ;
                    std::cout << "pieceCaptured = " << pieceCaptured << std::endl ;
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    */
                    //sleep(2);



                    Undo_move(position,destination,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,wasCastle,wasPromote,pieceCaptured,CstlL,CstlS,cstlL,cstlS,r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    if (verbose){
                        std::cout << "undone move in game() " << std::endl;
                        coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P);
                        std::cin >> nothing ;}
                }

                for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                    if (2*semIdx == bestInd) {
                        position = moves[2*semIdx] ;
                        destination = moves[2*semIdx+1] ;
                        Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,wasCastle,wasPromote,pieceCaptured);
                        lastMove.first = position ;
                        lastMove.second = destination ;
                        //isEnPassant(lastMove, enPassant, P, true) ;
                        legal = true ;
                    }
                }

            }















        } else {
            if (blackHuman){
            legal = false ;

            legPaB(moves, p, whitePieces, blackPieces, occupied, enPassant) ;
            KnightMoves(moves, n, blackPieces) ;
            sliderD(moves, b, blackPieces, occupied) ;
            sliderCD(moves, b, blackPieces, occupied) ;
            sliderHV(moves, q, blackPieces, occupied) ;
            sliderD(moves, q, blackPieces, occupied) ;
            sliderCD(moves, q, blackPieces, occupied) ;
            sliderHV(moves, r, blackPieces, occupied) ;
            KingMoves(moves, k, r, blackPieces, occupied, CstlL, CstlS, cstlL, cstlS) ;





            while (!legal){

                std::cout << "position ?" << std::endl;
                std::cin >> strPosition ;
                std::cin.ignore() ;

                position = SquareNameToNb(strPosition) ;


                std::cout << "destination ?" << std::endl;
                std::cin >> strDestination ;
                std::cin.ignore() ;

                destination = SquareNameToNb(strDestination) ;





            for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                if ((moves[2*semIdx] == position) && (moves[2*semIdx+1] == destination)) {
                    Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,wasCastle, wasPromote, pieceCaptured);
                    legal = true ;
                    lastMove.first = position ;
                    lastMove.second = destination ;
                    //isEnPassant(lastMove, enPassant, p, false) ;
                }
            }
            if (!legal){
                    system("cls");
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    std::cout << "illegal" << std::endl;
                    if (!(moveNb%2)){std::cout << "white " ;} else {std::cout << "black " ;}std::cout << "to play" << std::endl;
            }
            }
            } else { //black not human
                legPaB(moves, p, whitePieces, blackPieces, occupied, enPassant) ;
                KnightMoves(moves, n, blackPieces) ;
                sliderD(moves, b, blackPieces, occupied) ;
                sliderCD(moves, b, blackPieces, occupied) ;
                sliderHV(moves, q, blackPieces, occupied) ;
                sliderD(moves, q, blackPieces, occupied) ;
                sliderCD(moves, q, blackPieces, occupied) ;
                sliderHV(moves, r, blackPieces, occupied) ;
                KingMoves(moves, k, r, blackPieces, occupied, CstlL, CstlS, cstlL, cstlS) ;



                captInd = 0 ;
                for (int semInd = 0 ; semInd < moves.size()/2 ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&whitePieces){
                        temp1 = moves[2*captInd] ;
                        temp2 = moves[2*captInd+1] ;
                        moves[2*captInd] = moves[2*semInd] ;
                        moves[2*captInd+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd +=1 ;
                    }
                }

                bestInd = 0 ;
                thisEval = 0 ;
                bestEval = GAMEintINFINITY ;

                //ump.clear() ;
                for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                    position = moves[2*semIdx] ;
                    destination = moves[2*semIdx+1] ;
                    //std::cout << position << std::endl ;
                    //std::cout << destination << std::endl ;
                    pieceCaptured = 0 ;
                    wasCastle = false ;
                    wasPromote = false ;
                    brokeCastleS = false ;
                    brokeCastleL = false ;
                    brokecastleS = false ;
                    brokecastleL = false ;

                    Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,wasCastle,wasPromote,pieceCaptured);
                    if (verbose){
                        std::cout << "board before minimax " << std::endl ;
                        coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                        std::cin >> nothing ;
                    }

                    //std::cout << pieceCaptured << wasCastle << wasPromote << std::endl;
                    //sleep(2) ;

                    thisEval = minimax(r,n,b,q,k,p,R,N,B,Q,K,P,CstlL,CstlS,cstlL,cstlS,enPassant,4,5,-GAMEintINFINITY,GAMEintINFINITY,true) ;

                    //std::cout << thisEval << std::endl ;
                    if (verbose){
                            std::cout << "eval = " << thisEval << std::endl ;
                    }
                    if (thisEval < bestEval){
                        bestInd = 2*semIdx ;
                        bestEval = thisEval ;
                    }
                    if (verbose){std::cin >> nothing ;}
                    /*
                    std::cout << "about to undo " << std::endl;
                    std::cout << "board after minimax " << std::endl ;
                    std::cout << "position = " << position << std::endl ;
                    std::cout << "destination = " << destination << std::endl ;
                    std::cout << "wasCastle = " << wasCastle << std::endl ;
                    std::cout << "pieceCaptured = " << pieceCaptured << std::endl ;
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    */
                    //sleep(2);



                    Undo_move(position,destination,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,wasCastle,wasPromote,pieceCaptured,CstlL,CstlS,cstlL,cstlS,r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    if (verbose){
                        std::cout << "undone move in game() " << std::endl;
                        coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P);
                        std::cin >> nothing ;}
                }

                for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                    if (2*semIdx == bestInd) {
                        position = moves[2*semIdx] ;
                        destination = moves[2*semIdx+1] ;
                        Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,wasCastle,wasPromote,pieceCaptured);
                        lastMove.first = position ;
                        lastMove.second = destination ;
                        //isEnPassant(lastMove, enPassant, P, true) ;
                        legal = true ;
                    }
                }
            }
        }


        moveNb += 1 ;
    }
}

