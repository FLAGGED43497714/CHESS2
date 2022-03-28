#include "initBoard.h"

#include <vector>
#include <bitset>
#include <string>
#include <iostream>

void initBoard(std::bitset<64> board[12])
{

    std::bitset<64> r("1000000100000000000000000000000000000000000000000000000000000000");
    std::bitset<64> n("0100001000000000000000000000000000000000000000000000000000000000");
    std::bitset<64> b("0010010000000000000000000000000000000000000000000000000000000000");
    std::bitset<64> q("0001000000000000000000000000000000000000000000000000000000000000");
    std::bitset<64> k("0000100000000000000000000000000000000000000000000000000000000000");
    std::bitset<64> p("0000000011111111000000000000000000000000000000000000000000000000");
    std::bitset<64> R("0000000000000000000000000000000000000000000000000000000010000001");
    std::bitset<64> N("0000000000000000000000000000000000000000000000000000000001000010");
    std::bitset<64> B("0000000000000000000000000000000000000000000000000000000000100100");
    std::bitset<64> Q("0000000000000000000000000000000000000000000000000000000000010000");
    std::bitset<64> K("0000000000000000000000000000000000000000000000000000000000001000");
    std::bitset<64> P("0000000000000000000000000000000000000000000000001111111100000000");

    board[0] = r;
    board[1] = n;
    board[2] = b;
    board[3] = q;
    board[4] = k;
    board[5] = p;
    board[6] = R;
    board[7] = N;
    board[8] = B;
    board[9] = Q;
    board[10] = K;
    board[11] = P;

}

void initBoard2(std::bitset<64>& r,std::bitset<64>& n,std::bitset<64>& b,std::bitset<64>& q,std::bitset<64>& k,
                std::bitset<64>& p,std::bitset<64>& R,std::bitset<64>& N,std::bitset<64>& B,std::bitset<64>& Q,
                std::bitset<64>& K,std::bitset<64>& P)
{

    std::bitset<64> r1("1000000100000000000000000000000000000000000000000000000000000000");
    std::bitset<64> n1("0100001000000000000000000000000000000000000000000000000000000000");
    std::bitset<64> b1("0010010000000000000000000000000000000000000000000000000000000000");
    std::bitset<64> q1("0001000000000000000000000000000000000000000000000000000000000000");
    std::bitset<64> k1("0000100000000000000000000000000000000000000000000000000000000000");
    std::bitset<64> p1("0000000011111111000000000000000000000000000000000000000000000000");
    std::bitset<64> R1("0000000000000000000000000000000000000000000000000000000010000001");
    std::bitset<64> N1("0000000000000000000000000000000000000000000000000000000001000010");
    std::bitset<64> B1("0000000000000000000000000000000000000000000000000000000000100100");
    std::bitset<64> Q1("0000000000000000000000000000000000000000000000000000000000010000");
    std::bitset<64> K1("0000000000000000000000000000000000000000000000000000000000001000");
    std::bitset<64> P1("0000000000000000000000000000000000000000000000001111111100000000");

    r = r1;
    n = n1;
    b = b1;
    q = q1;
    k = k1;
    p = p1;
    R = R1;
    N = N1;
    B = B1;
    Q = Q1;
    K = K1;
    P = P1;

}

void initFromFEN(std::string fen, std::bitset<64>& r,std::bitset<64>& n,std::bitset<64>& b,std::bitset<64>& q,std::bitset<64>& k,
                std::bitset<64>& p,std::bitset<64>& R,std::bitset<64>& N,std::bitset<64>& B,std::bitset<64>& Q,
                std::bitset<64>& K,std::bitset<64>& P)
{

    std::string r1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string n1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string b1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string q1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string k1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string p1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string R1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string N1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string B1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string Q1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string K1String ("0000000000000000000000000000000000000000000000000000000000000000");
    std::string P1String ("0000000000000000000000000000000000000000000000000000000000000000");

    int i = 0 ;
    for (int k = 0 ; k < fen.size() ; k++){
        //std::cout << fen[k] ;
        switch(fen[k]){
            case 'r' :
                r1String[i] = '1' ;
                break ;
            case 'n' :
                n1String[i] = '1' ;
                break ;
            case 'b' :
                b1String[i] = '1' ;
                break ;
            case 'q' :
                q1String[i] = '1' ;
                break ;
            case 'k' :
                k1String[i] = '1' ;
                break ;
            case 'p' :
                p1String[i] = '1' ;
                break ;

            case 'R' :
                R1String[i] = '1' ;
                break ;
            case 'N' :
                N1String[i] = '1' ;
                break ;
            case 'B' :
                B1String[i] = '1' ;
                break ;
            case 'Q' :
                Q1String[i] = '1' ;
                break ;
            case 'K' :
                K1String[i] = '1' ;
                break ;
            case 'P' :
                P1String[i] = '1' ;
                break ;

            case '/' :
                i -= 1 ; // pour ignorer parce qu'on va faire +1 à la fin du switch
                break;
            case '1' :
                i+=0;
                break;
            case '2' :
                i+=1;
                break;
            case '3' :
                i+=2;
                break;
            case '4' :
                i+=3;
                break;
            case '5' :
                i+=4;
                break;
            case '6' :
                i+=5;
                break;
            case '7' :
                i+=6;
                break;
            case '8' :
                i+=7;
                break;
        }
        i+=1 ;
    }


    //std::cout << r1String<< std::endl;
    //std::cout << n1String.size() << std::endl;
    //std::cout << b1String.size() << std::endl;
    //std::cout << q1String.size()<< std::endl ;
    //std::cout << k1String.size() << std::endl;
    //std::cout << p1String << std::endl;
    //std::cout << R1String.size() << std::endl;
    //std::cout << N1String.size() << std::endl;
    //std::cout << B1String.size() << std::endl;
    //std::cout << Q1String.size() << std::endl;
    //std::cout << K1String.size() << std::endl;
    //std::cout << P1String << std::endl;




    std::bitset<64> r1(r1String);
    std::bitset<64> n1(n1String);
    std::bitset<64> b1(b1String);
    std::bitset<64> q1(q1String);
    std::bitset<64> k1(k1String);
    std::bitset<64> p1(p1String);
    std::bitset<64> R1(R1String);
    std::bitset<64> N1(N1String);
    std::bitset<64> B1(B1String);
    std::bitset<64> Q1(Q1String);
    std::bitset<64> K1(K1String);
    std::bitset<64> P1(P1String);

    r = r1;
    n = n1;
    b = b1;
    q = q1;
    k = k1;
    p = p1;
    R = R1;
    N = N1;
    B = B1;
    Q = Q1;
    K = K1;
    P = P1;

}
