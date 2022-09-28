#include <iostream>
using namespace std;

void inicio(int board[][3]);      // Inicia com 0 em todas as casas
char preenche(int p);             // Le cada casa se tiver 0 retorna espaco vazio " ", "1" (player1) retorna "X", "-1" (player2) retorna "O"
void tabuleiro(int board[][3]);   // Exibe o tabulerio do jogo da velha
void jogada(int board[][3], int); // Pede ao jogador da vez a linha e a coluna que deseja ocupar
int continua(int *board[3]);      // Verifica se ainda tem espacos em branco, se ainda tem retorna 1 e se nao retorna 0
int vencedor(int *board[3]);      // Verifica todas as colunas linhas e diagonais para saber se algum jogador ganhou ou deu empate
int jogo(int board[][3]);         // Inicia o jogo
void placar(int, int &, int &);   // Exibe o placar do jogo

void inicio(int board[][3]) // Inicializa o tabuleiro colocando "0" em todas as casas
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = 0;
}

char preenche(int block) // Percorre cada casa do tabuleiro
// Se na casa tiver 0 Imprime um espaco vazio " "
// Se na casa tiver 1 (player1) Imprime um X
// Se na casa tiver -1 (player2) Imprime um O

{
    if (block == 0)
        return ' ';
    else if (block == 1)
        return 'X';
    else
        return 'O';
}

void tabuleiro(int board[][3]) // Imrpimi o tabuleiro do jogo da velha
{
    cout << endl;
    for (int lin = 0; lin < 3; lin++)
    {
        cout << "\n";
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

void jogada(int board[][3], int player) // Realiza uma jogada pedindo a linha e a coluna que deseja ocupar
// Digitando valores de 1 ate 3 e os indices vao de 0 ate 2
// Entao vai subtrair uma unidade de dados digitados pelo usuario (lin-- e col--)
// E checar se ela esta ocupada(b[lin][col]) se estiver tudo correto e entre os valores pedidos preenche o local desejado com 1 (player1) ou -1 (player2)
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

int continua(int board[][3]) // Verifica se ainda tem espacos em branco
// Se o jogo pode continuar
// Se tiver espacos em branco retorna 1 e o jogo continua se nao retorna 0 e o jogo acaba
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0)
                return 1;
    return 0;
}

int vencedor(int board[][3]) // Verifica se algum jogador ganhou
// Se a soma for igual a 3 o player1 ganhou
// Se a soma for igual a -3 o player2 ganhou
// Se nenhum dos dois ganhou ate o momento retorna 0
{
    int lin, col, sm;

    for (lin = 0; lin < 3; lin++) // Verifica as linhas
    {
        sm = 0;

        for (col = 0; col < 3; col++)
            sm += board[lin][col];

        if (sm == 3)
            return 1;
        if (sm == -3)
            return -1;
    }

    for (col = 0; col < 3; col++) // Verifica as colunas
    {
        sm = 0;

        for (lin = 0; lin < 3; lin++)
            sm += board[lin][col];

        if (sm == 3)
            return 1;
        if (sm == -3)
            return -1;
    }

    for (col = 0; col < 3; col++)
    {
        sm = 0;

        for (lin = 0; lin < 3; lin++) // Verifica diagonal principal
            sm = board[0][0] + board[1][1] + board[2][2];
        if (sm == 3)
            return 1;
        if (sm == -3)
            return -1;
    }

    for (col = 0; col < 3; col++)
    {
        sm = 0;

        for (lin = 0; lin < 3; lin++)
            sm = board[0][2] + board[1][1] + board[2][0]; // Verifica a diagonal secundaria
        if (sm == 3)
            return 1;
        if (sm == -3)
            return -1;
    }

    return 0;
}

void placar(int result, int &player1, int &player2) // Exibe o placar do jogo
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
    int turn = 0, cont, win; // turn = vez de cada jogador

    do
    {
        tabuleiro(board);
        cout << "Jogador " << 1 + turn % 2 << endl; // faz a jogada usando a funcao jogada
        // turn%2 mostra se a vez e do player1 ou player2
        jogada(board, turn % 2);
        turn++;

        cont = continua(board); // Verifica se o tabuleiro ainda tem casas vazias
        win = vencedor(board);
    } while (cont && !win);

    if (win == 1) // Verifica se alguem ganhou ou empatou
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
        result = jogo(board); // result armazena o jogo e manda pra funcao placar
        tabuleiro(board);
        placar(result, player1, player2);

        // Depois de exibir o placar pergunta se os jogadores querem jogar de novo(1) ou sair(0)
        cout << "\n Outra partida?" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Jogar de novo" << endl;
        cin >> cont;
        // se cont for igual 1(Jogar denovo) while vai ser verdadeiro e outra partida vai ser iniciada se nao 0(Sair) o jogo se encerra
    } while (cont);

    return 0;
}