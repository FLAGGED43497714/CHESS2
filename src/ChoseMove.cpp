#include "ChoseMove.h"
#include "Eval.h"
#include "MakeMove.h"
#include "LegalMoves.h"
//#include "Constants.h"
#include "coutBoard.h"
#include "BitwiseFunction.h"

#include <unistd.h>
#include <limits>
#include <iostream>
#include <vector>
#include <unordered_map>

int intINFINITY = std::numeric_limits<int>::max() ;


//extern std::unordered_map<unsigned long long int, int> ump ;
//extern std::unordered_map<unsigned long long int, int>::iterator it ;


int minimax(unsigned long long int & r,unsigned long long int & n,unsigned long long int & b,
        unsigned long long int & q,unsigned long long int & k,unsigned long long int & p,
        unsigned long long int & R,unsigned long long int & N,unsigned long long int & B,
        unsigned long long int & Q,unsigned long long int & K,unsigned long long int & P,
        bool & CstlL, bool & CstlS , bool & cstlL , bool & cstlS, unsigned long long int & enPassant,
        int depth, int veryMaxDepth, int alpha, int beta, bool maximizingPlayer)
{


        /*unsigned long long int zobKey ;
        zobKey = ZobristHash(r,n,b,q,k,p,R,N,B,Q,K,P,CstlS,CstlL,cstlS,cstlL, maximizingPlayer) ;

        it = ump.find(zobKey); //Finding an element

        if(it != ump.end()){
            return it->second ;
        }*/




        bool brokeCastleL = false ;
        bool brokeCastleS = false ;
        bool brokecastleL = false ;
        bool brokecastleS = false ;


        bool verbose = false ;
        std::string nothing ;
        //std::cout << "in minimax " << std::endl ;
        //std::cout << "maximizingPlayer = " << maximizingPlayer << std::endl ;
        //std::cin >> nothing ;
        unsigned long long int whitePieces = R | N | B | Q | K | P ;
        unsigned long long int blackPieces = r | n | b | q | k | p ;
        unsigned long long int occupied = whitePieces | blackPieces ;

        int pieceCaptured  ;
        bool wasCastle  ;
        bool wasPromote  ;

        int position ;
        int destination ;


        int maxEval (0) ;
        int minEval (0) ;
        int eval (0) ;

        bool depthIncreased ;

        //move ordering
        int captInd =0 ;
        int dest = 0 ;
        unsigned long long int destInt  = 1;
        int temp1 = 0;
        int temp2 = 0;



        if ( ( depth == 0 ) || ( veryMaxDepth == 0 ) || ( K == 0 ) || ( k == 0 ) ){

            return EvalFunction(r,n,b,q,k,p,R,N,B,Q,K,P) ;

        }

        std::vector<int> moves ;
        std::vector<int> moves2 ;


        if (maximizingPlayer){
            //std::cout << "in minimax with maximizing player = false" << std::endl ;
            //std::cin >> nothing ;

            /* compute legal moves */
            legPaW(moves, P, whitePieces, blackPieces, occupied, enPassant) ;
            KnightMoves(moves, N, whitePieces) ;
            sliderD(moves, B, whitePieces, occupied) ;
            sliderCD(moves, B, whitePieces, occupied) ;
            sliderHV(moves, Q, whitePieces, occupied) ;
            sliderD(moves, Q, whitePieces, occupied) ;
            sliderCD(moves, Q, whitePieces, occupied) ;
            sliderHV(moves, R, whitePieces, occupied) ;
            KingMoves(moves, K, R, whitePieces, occupied, CstlL, CstlS, cstlL, cstlS) ;


            /*______________________*/

            /*for (int movInd = 0 ; movInd < moves.size() ; movInd++)
            {
                moves2.push_back(moves[movInd]) ;
            }*/

            /*captInd = 0 ;
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
            }*/



            maxEval = - intINFINITY ;
            for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                pieceCaptured = 0 ;
                wasCastle = false ;
                wasPromote = false ;
                depthIncreased = false ;
                brokeCastleL = false ;
                brokeCastleS = false ;
                brokecastleL = false ;
                brokecastleS = false ;

                position = moves[2*semIdx] ;
                destination = moves[2*semIdx+1] ;
                Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,wasCastle, wasPromote, pieceCaptured) ;
                /*if (verbose){
                    std::cout << "done move" << std::endl ;
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    std::cin >> nothing ;
                    }*/
                if ((depth == 1) && (pieceCaptured != 0)){
                    depth += 1 ;
                }


                eval = minimax(r,n,b,q,k,p,R,N,B,Q,K,P,CstlL,CstlS,cstlL,cstlS,enPassant,depth-1, veryMaxDepth-1, alpha,beta,false) ;
                //ump.insert(std::pair<unsigned long long int, int>(zobKey, eval));


                if (verbose && (eval > maxEval)){
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    std::cout << "eval = " << eval << std::endl ;
                    std::cout << "pieceCaptured = " << pieceCaptured << std::endl ;
                    std::cin >> nothing ;}

                if (depthIncreased){
                    depth -= 1 ;
                }

                Undo_move(position,destination,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,wasCastle, wasPromote,pieceCaptured,CstlL,CstlS,cstlL,cstlS,r,n,b,q,k,p,R,N,B,Q,K,P) ;
                /*if (verbose){
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    std::cout << "undone move in minimax" << std::endl ;
                    std::cin >> nothing ;}*/

                maxEval = std::max(maxEval,eval) ;
                alpha = std::max(alpha, eval) ;
                if (beta <= alpha) {
                    if (verbose){
                    std::cout << "Beta <= alpha : break" << std::endl ;
                    std::cin >> nothing ;
                    }

                    break ;
                }
            }
            return maxEval ;

            }







        else {
            //std::cout << "in minimax with maximizing player = false" << std::endl ;
            //std::cin >> nothing ;

            /* compute legal moves */
            legPaB(moves, p, whitePieces, blackPieces, occupied, enPassant) ;
            KnightMoves(moves, n, blackPieces) ;
            sliderD(moves, b, blackPieces, occupied) ;
            sliderCD(moves, b, blackPieces, occupied) ;
            sliderHV(moves, q, blackPieces, occupied) ;
            sliderD(moves, q, blackPieces, occupied) ;
            sliderCD(moves, q, blackPieces, occupied) ;
            sliderHV(moves, r, blackPieces, occupied) ;
            KingMoves(moves, k, r,  blackPieces, occupied, CstlL, CstlS, cstlL, cstlS) ;


            /*______________________*/


            /*for (int movInd = 0 ; movInd < moves.size() ; movInd++)
            {
                moves2.push_back(moves[movInd]) ;
            }*/


            /*captInd = 0 ;
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
            }*/


            minEval = intINFINITY ;
            for (int semIdx = 0 ; semIdx < moves.size()/2 ; semIdx++){
                pieceCaptured = 0 ;
                wasCastle = false ;
                wasPromote = false ;
                depthIncreased = false ;
                brokeCastleL = false ;
                brokeCastleS = false ;
                brokecastleL = false ;
                brokecastleS = false ;

                position = moves[2*semIdx] ;
                destination = moves[2*semIdx+1] ;
                Do_move(position,destination,CstlL,CstlS,cstlL,cstlS,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,r,n,b,q,k,p,R,N,B,Q,K,P,wasCastle, wasPromote,pieceCaptured) ;
                /*if (verbose){
                    std::cout << "done move" << std::endl ;
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    std::cin >> nothing ;}*/
                if ((depth == 1) && (pieceCaptured != 0)){
                    depth += 1 ;
                    depthIncreased = true ;
                }


                eval = minimax(r,n,b,q,k,p,R,N,B,Q,K,P,CstlL,CstlS,cstlL,cstlS,enPassant, depth-1, veryMaxDepth-1 ,alpha,beta,true) ;
                //ump.insert(std::pair<unsigned long long int, int>(zobKey, eval));

                if (verbose && (eval < minEval)){
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    std::cout << "eval = " << eval << std::endl ;
                    std::cout << "pieceCaptured = " << pieceCaptured << std::endl ;
                    std::cin >> nothing ;}
                if (depthIncreased){
                    depth -= 1 ;
                }


                Undo_move(position,destination,brokeCastleS,brokeCastleL,brokecastleS,brokecastleL,wasCastle, wasPromote,pieceCaptured,CstlL,CstlS,cstlL,cstlS,r,n,b,q,k,p,R,N,B,Q,K,P) ;
                /*if (verbose){
                    coutBoard(r,n,b,q,k,p,R,N,B,Q,K,P) ;
                    std::cout << "undone move in minimax" << std::endl ;
                    std::cin >> nothing ;}*/

                minEval =  std::min(minEval,eval) ;
                beta = std::min(beta,eval) ;
                if ( beta <= alpha ){
                    if (verbose){
                    std::cout << "Beta <= alpha : break" << std::endl ;
                    std::cin >> nothing ;
                    }
                    break ;
                }
            }
            return minEval ;
   }
}


