#include<random>
#include<iostream>
#include<string>
using namespace std;
const int N = 4;
int score[2] = { 0, 0 };
const int GOAL = 1 << (3 * N - 1);
char grid[N][N] ;
char uncovered[N][N];


void print_grid() {
    for (int i = 0; i < ((N + 4) * N + 1); cout<< "-", i++);
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << "|";
        for (int j = 0; j < N; j++) {
            string e = "";
            for (int t = 0; t < 3; e += " ", t++);
            e += (grid[i][j]);
            for (int t = 0; t < 3; e += " ", t++);
            cout << e << "|";
        }
        cout << "\n";
        for (int t = 0; t < ((N + 4) * N + 1); cout << "-", t++);
        cout << "\n";
    }
}
void generate_cell()
{
    srand(time(0));
    score[0] = 0;
    score[1] = 0;
    string str = "AABBCCDDEEFFGGHH";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int rand_index = (rand() % str.length());
            uncovered[i][j] = str[rand_index];
            str.erase(rand_index, 1);

        }

    }

}


bool check_tie()
{
    if (score[0] == 4 and score[1] == 4)
        return true;
    return false;
}



bool is_valid_position(int i, int j, int k,int l)
{
    if (0 > i || i > 3)
        return false;
    if (0 > j || j > 3)
        return false;
    if (0 > k || k > 3)
        return false;
    if (0 > l || l > 3)
        return false;
    return true;
}


bool uncover_cells(int i, int j,int  k, int l)
{
    grid[i][j] = uncovered[i][j];
    grid[k][l] = uncovered[k][l];
    print_grid();
        if (uncovered[i][j] != uncovered[k][l])
        {
            grid[i][j] = '?';
            grid[k][l] = '?';
            cout<< "sorry... your guess is wrong \n\n\n";
            return false;
        }
        else {
            cout<<"your guess is right\n";
            return true;
        }

}

void grid_clear()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            grid[i][j] = '?';
        }
    }
}


void play_game()
{
    cout << "memory Game!"<<endl;
    cout << "Welcome..."<<endl;
    cout << "============================"<<endl;
    int player = 0;

    while (true)
    {

        cout << "player " << player << " turn"<<endl;
        print_grid();
        int i = 0; int j = 0; int k = 0; int l=0;

        cout << "Enter the row index and column index for the first cell: ";
        cin >> i >> j ;
        cout << "Enter the row index and column index for the second cell: ";
        cin >> k >> l ;


        while (not is_valid_position(i, j, k, l) || grid[i][j] != '?' || grid[k][l] != '?' || ((i == k) and (j == l)))
        {
            cout << ("enter valid cells")<<endl;
            cout << "Enter the row index and column index for the first cell: ";
            cin >> i >> j;
            cout << "Enter the row index and column index for the second cell: ";
            cin >> k >> l;
        }

        if (uncover_cells(i, j, k, l))
        {
            score[player] += 1;
            cout <<"player "<< player <<  " score is " << score[player] << "\n\n" ;
        }

        if (score[player] == 5)
        {
            cout<<"player " <<  player  << " won" <<endl ;
            break;
        }

        player = 1 - player;

        if (check_tie())
        {
            cout << ("its a tie")<<endl;
            break;
        }



    }

}


int main()
{
    for(int i=0;i<N;i++)
    {
        for (int j = 0; j < N; j++)
        {
            grid[i][j] = '?';

        }
    }

    while (true)
    {
        grid_clear();
        generate_cell();
        play_game();
        char c;
        cout << "Play Again [Y/N] ";
        cin >> c;
        if (c != 'y' && c != 'Y')
            break;
    }

}
