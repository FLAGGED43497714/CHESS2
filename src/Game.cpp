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


void Game(int depth1, int depth2){
    std::string nothing ;
    //std::cin >> nothing ;

    int depthInit ;

    bool verbose = false ;

    bool whiteHuman = false ;
    bool blackHuman = 1 - whiteHuman;

    unsigned long long int r,n,b,q,k,p,R,N,B,Q,K,P;

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" ;
<<<<<<< HEAD

    //std::string fen = "r1b1kb1r/ppp1qppp/2B5/3nN3/8/3P4/PPP2PPP/RNBQK2R" ;
=======
    //std::string fen = "r3k2r/ppp1bppp/2n5/8/3P4/5N1P/qPQ2PP1/1RB2RK1" ;
>>>>>>> 6dbf6f8c329641586c834f0922a2ad0bd41590c8


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
    int captInd = 0 ;
    int captInd2 = 0 ;
    int captInd3 = 0 ;
    int captInd4 = 0 ;
    int captInd5 = 0 ;
    int dest ;
    unsigned long long int destInt ;
    int temp1 ;
    int temp2 ;

    unsigned long long int forbCstlS (0) ; //12
    unsigned long long int tempForbCstlS ;
    unsigned long long int forbCstlL (0) ; //24
    unsigned long long int tempForbCstlL ;
    unsigned long long int forbcstlS (0) ; //864691128455135232
    unsigned long long int tempForbcstlS ;
    unsigned long long int forbcstlL (0) ; //1729382256910270464
    unsigned long long int tempForbcstlL ;

    unsigned long long int tempassant ;

    std::vector<int> variante ;
    std::vector<int> tempVariante ;

    //extern std::unordered_map<unsigned long long int, int> ump ;
    //extern std::unordered_map<unsigned long long int, int>::iterator it ;


    while(true){

        depthInit = depth1 ;
        //std::cin >> nothing ;

        pieceCaptured = 0 ;
        wasCastle = false ;
        wasPromote = false ;
        brokeCastleS = false ;
        brokeCastleL = false ;
        brokecastleS = false ;
        brokecastleL = false ;

        //enPassant = 0 ; // ATTENTION C'EST UN HOTFIX


        //std::cin >> nothing ;
        system("cls");
        std::cout << "CstlS " << CstlS << " CstlL "<< CstlL << " cstlS "<< cstlS <<" cstlL "<< cstlL << std::endl ;
        for (int varInd =0 ; varInd < variante.size()/2 ; varInd ++){
            if (varInd != 0){
                std::cout << " => " ;
            }
            std::cout << SquareNbtoName(variante[2*varInd]) + " > " + SquareNbtoName(variante[2*varInd+1]) ;
        }
        std::cout << std::endl << "eval : " << (float) bestEval/100 << std::endl;
        coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;




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
                            Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,enPassant,forbCstlS,forbCstlL,forbcstlS,forbcstlL,wasCastle,wasPromote,pieceCaptured);
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

                variante.clear() ;
                tempVariante.clear() ;

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
                captInd2 = 0 ;
                captInd3 = 0 ;
                captInd4 = 0 ;
                captInd5 = 0 ;
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
                for (int semInd = 1 ; semInd < captInd ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&(k|q|r|n|b)){
                        temp1 = moves[2*captInd2] ;
                        temp2 = moves[2*captInd2+1] ;
                        moves[2*captInd2] = moves[2*semInd] ;
                        moves[2*captInd2+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd2 +=1 ;
                    }
                }
                for (int semInd = 1 ; semInd < captInd2 ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&(k|q|r)){
                        temp1 = moves[2*captInd3] ;
                        temp2 = moves[2*captInd3+1] ;
                        moves[2*captInd3] = moves[2*semInd] ;
                        moves[2*captInd3+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd3 +=1 ;
                    }
                }
                for (int semInd = 1 ; semInd < captInd3 ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&(k|q)){
                        temp1 = moves[2*captInd4] ;
                        temp2 = moves[2*captInd4+1] ;
                        moves[2*captInd4] = moves[2*semInd] ;
                        moves[2*captInd4+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd4 +=1 ;
                    }
                }
                for (int semInd = 1 ; semInd < captInd4 ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&(k)){
                        temp1 = moves[2*captInd5] ;
                        temp2 = moves[2*captInd5+1] ;
                        moves[2*captInd5] = moves[2*semInd] ;
                        moves[2*captInd5+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd5 +=1 ;
                    }
                }



                bestInd = 0 ;
                thisEval = -GAMEintINFINITY ;
                bestEval = -GAMEintINFINITY ;

                tempassant = enPassant ;
                tempForbCstlS = forbCstlS ;
                tempForbCstlL = forbCstlL ;
                tempForbcstlS = forbcstlS ;
                tempForbcstlL = forbcstlL ;

                //ump.clear() ;
                for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                    position = moves[2*semIdx] ;
                    destination = moves[2*semIdx+1] ;

                    //show moves :
                    //std::cout << position << " > " << destination << std::endl ;


                    pieceCaptured = 0 ;
                    wasCastle = false ;
                    wasPromote = false ;
                    brokeCastleS = false ;
                    brokeCastleL = false ;
                    brokecastleS = false ;
                    brokecastleL = false ;

                    Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,enPassant,forbCstlS,forbCstlL,forbcstlS,forbcstlL,wasCastle,wasPromote,pieceCaptured);




                    thisEval = minimax(r,n,b,q,k,p,R,N,B,Q,K,P,CstlL,CstlS,cstlL,cstlS,enPassant,forbCstlS,forbCstlL,tempForbcstlS,tempForbcstlL, tempVariante, depthInit,depth1,depth2,-GAMEintINFINITY,GAMEintINFINITY,false) ;
                    //std::cout << thisEval << std::endl ;

                    if (thisEval > bestEval){
                        variante = {position, destination} ;
<<<<<<< HEAD
                        variante.insert(variante.end(), tempVariante.begin(), tempVariante.end()) ;
=======
                        variante.resize(2) ;
                        variante.insert(variante.end(), tempVariante.begin(), tempVariante.end() ) ;
>>>>>>> 6dbf6f8c329641586c834f0922a2ad0bd41590c8
                        bestInd = 2*semIdx ;
                        bestEval = thisEval ;
                    }

                    enPassant = tempassant ;
                    forbCstlS = tempForbCstlS ;
                    forbCstlL = tempForbCstlL ;
                    forbcstlS = tempForbcstlS ;
                    forbcstlL = tempForbcstlL ;

                    Undo_move(position,destination,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,wasCastle,wasPromote,pieceCaptured,CstlL,CstlS,cstlL,cstlS,r,n,b,q,k,p,R,N,B,Q,K,P) ;


                }
                //std::cin >> nothing ;

                for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                    if (2*semIdx == bestInd) {
                        position = moves[2*semIdx] ;
                        destination = moves[2*semIdx+1] ;
                        Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,enPassant,forbCstlS,forbCstlL,forbcstlS,forbcstlL,wasCastle,wasPromote,pieceCaptured);
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
                    Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,enPassant,forbCstlS,forbCstlL,forbcstlS,forbcstlL,wasCastle, wasPromote, pieceCaptured);
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
                variante.clear();
                tempVariante.clear();

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
                captInd2 = 0 ;
                captInd3 = 0 ;
                captInd4 = 0 ;
                captInd5 = 0 ;
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
                for (int semInd = 1 ; semInd < captInd ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&(K|Q|R|N|B)){
                        temp1 = moves[2*captInd2] ;
                        temp2 = moves[2*captInd2+1] ;
                        moves[2*captInd2] = moves[2*semInd] ;
                        moves[2*captInd2+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd2 +=1 ;
                    }
                }
                for (int semInd = 1 ; semInd < captInd2 ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&(K|Q|R)){
                        temp1 = moves[2*captInd3] ;
                        temp2 = moves[2*captInd3+1] ;
                        moves[2*captInd3] = moves[2*semInd] ;
                        moves[2*captInd3+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd3 +=1 ;
                    }
                }
                for (int semInd = 1 ; semInd < captInd3 ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&(K|Q)){
                        temp1 = moves[2*captInd4] ;
                        temp2 = moves[2*captInd4+1] ;
                        moves[2*captInd4] = moves[2*semInd] ;
                        moves[2*captInd4+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd4 +=1 ;
                    }
                }
                for (int semInd = 1 ; semInd < captInd4 ; semInd ++){
                    destInt = 1 ;
                    dest = moves[2*semInd+1] ;
                    destInt <<= dest ;
                    if (destInt&(K)){
                        temp1 = moves[2*captInd5] ;
                        temp2 = moves[2*captInd5+1] ;
                        moves[2*captInd5] = moves[2*semInd] ;
                        moves[2*captInd5+1] = moves[2*semInd+1] ;
                        moves[2*semInd] = temp1 ;
                        moves[2*semInd+1] = temp2 ;

                        captInd5 +=1 ;
                    }
                }

                bestInd = 0 ;
                thisEval = 0 ;
                bestEval = GAMEintINFINITY ;

                tempassant = enPassant ;
                tempForbCstlS = forbCstlS ;
                tempForbCstlL = forbCstlL ;
                tempForbcstlS = forbcstlS ;
                tempForbcstlL = forbcstlL ;

                //ump.clear() ;
                for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                    position = moves[2*semIdx] ;
                    destination = moves[2*semIdx+1] ;



                    pieceCaptured = 0 ;
                    wasCastle = false ;
                    wasPromote = false ;
                    brokeCastleS = false ;
                    brokeCastleL = false ;
                    brokecastleS = false ;
                    brokecastleL = false ;

                    Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,enPassant,forbCstlS,forbCstlL,forbcstlS,forbcstlL,wasCastle,wasPromote,pieceCaptured);



                    thisEval = minimax(r,n,b,q,k,p,R,N,B,Q,K,P,CstlL,CstlS,cstlL,cstlS,enPassant,tempForbCstlS,tempForbCstlL,forbcstlS,forbcstlL, tempVariante, depthInit,depth1,depth2,-GAMEintINFINITY,GAMEintINFINITY,true) ;


                    //show moves :
                    //std::cout << position << " > " << destination << " = " << thisEval << std::endl ;


                    if (thisEval < bestEval){
                        variante = {position, destination} ;
                        variante.insert(variante.end(), tempVariante.begin(), tempVariante.end() ) ;

                        bestInd = 2*semIdx ;
                        bestEval = thisEval ;
                    }


                    enPassant = tempassant ;
                    forbCstlS = tempForbCstlS ;
                    forbCstlL = tempForbCstlL ;
                    forbcstlS = tempForbcstlS ;
                    forbcstlL = tempForbcstlL ;

                    Undo_move(position,destination,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,wasCastle,wasPromote,pieceCaptured,CstlL,CstlS,cstlL,cstlS,r,n,b,q,k,p,R,N,B,Q,K,P) ;

                }

                //std::cin >> nothing ;


                for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                    if (2*semIdx == bestInd) {
                        position = moves[2*semIdx] ;
                        destination = moves[2*semIdx+1] ;
                        Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,enPassant,forbCstlS,forbCstlL,forbcstlS,forbcstlL,wasCastle,wasPromote,pieceCaptured);
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

