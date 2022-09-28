#include <iostream>
using namespace std;

void inicio(int board[][3]);
char preenche(int p);
void tabuleiro(int board[][3]);
void jogada(int board[][3], int);
int continua(int *board[3]);
int vencedor(int *board[3]);
int jogo(int board[][3]);
void placar(int, int &, int &);

void inicio(int board[][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = 0;
}

char preenche(int block)
{
    if (block == 0)
        return ' ';
    else if (block == 1)
        return 'X';
    else
        return 'O';
}

void tabuleiro(int board[][3])
{
    cout << endl;
    for (int lin = 0; lin < 3; lin++)
    {
        cout << " " << preenche(board[lin][0]) << " |";
        cout << " " << preenche(board[lin][1]) << " |";
        cout << " " << preenche(board[lin][2]) << endl;

        if (lin != 2)
        {
            cout << "___ ___ ___\n"
                 << endl;
        }
    }
}

void jogada(int board[][3], int player)
{
    int lin, col, check;
    do
    {
        cout << "Linha: ";
        cin >> lin;
        cout << "Coluna: ";
        cin >> col;
        lin--;
        col--;

        check = board[lin][col] || lin < 0 || lin > 2 || col < 0 || col > 2;
        if (check)
            cout << "Essa casa não está vazia ou fora do intervalo 3x3" << endl;

    } while (check);

    if (player == 0)
        board[lin][col] = 1;
    else
        board[lin][col] = -1;
}

int continua(int board[][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0)
                return 1;
    return 0;
}

int vencedor(int board[][3])
{
    int lin, col, sm;

    for (lin = 0; lin < 3; lin++)
    {
        sm = 0;

        for (col = 0; col < 3; col++)
            sm += board[lin][col];

        if (sm == 3)
            return 1;
        if (sm == -3)
            return -1;
    }

    for (col = 0; col < 3; col++)
    {
        sm = 0;

        for (lin = 0; lin < 3; lin++)
            sm += board[lin][col];

        if (sm == 3)
            return 1;
        if (sm == -3)
            return -1;
    }

    sm = 0;
    for (lin = 0; lin < 3; lin++)
        sm += board[lin][lin];
    if (sm == 3)
        return 1;
    if (sm == -3)
        return -1;

    sm = board[0][2] + board[1][1] + board[2][0];
    if (sm == 3)
        return 1;
    if (sm == -3)
        return -1;

    return 0;
}

void placar(int result, int &player1, int &player2)
{
    if (result == 1)
        player1++;
    if (result == 2)
        player2++;

    cout << "Placar: " << endl;
    cout << player1 << " x " << player2 << endl;
}

int jogo(int board[][3])
{
    int turn = 0, cont, win;

    do
    {
        tabuleiro(board);
        cout << "Jogador " << 1 + turn % 2 << endl;
        jogada(board, turn % 2);
        turn++;

        cont = continua(board);
        win = vencedor(board);
    } while (cont && !win);

    if (win == 1)
    {
        cout << "Jogador 1 ganhou!\n"
             << endl;
        return 1;
    }
    else if (win == -1)
    {
        cout << "Jogador 2 ganhou!\n"
             << endl;
        return 2;
    }
    else
        cout << "Empate\n"
             << endl;
    return 0;
}

int main()
{
    int board[3][3];

    int cont = 0, player1 = 0, player2 = 0, result;
    do
    {
        inicio(board);
        result = jogo(board);
        tabuleiro(board);
        placar(result, player1, player2);

        cout << "\n Outra partida?" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Jogar de novo" << endl;
        cin >> cont;
    } while (cont);

    return 0;
}