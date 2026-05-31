#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>

using namespace std;

class Player
{
private:
    string name;

public:
    Player() {}
    Player(string n) : name(n) {}
    void setName()
    {
        cout << "Select a Username: ";
        cin >> name;
    }
    string getName()
    {
        return name;
    }
};
class Snake
{
private:
    bool blob = false;
    int X;
    int Y;
    int l_X;
    int l_Y;

public:
    Snake(int height, int width) : X(width / 2), Y(height / 2), l_X(0), l_Y(0) {}
    int getX()
    {
        return X;
    }
    int getY()
    {
        return Y;
    }
    void movement()
    {
        int c = _getch();
        if (c == 0 || c == 224)
        {
            int m = _getch();
            switch (m)
            {
            case 72:
            { // up
                Y--;
                break;
            }
            case 80:
            { // down
                Y++;
                break;
            }
            case 75:
            { // left
                X--;
                break;
            }
            case 77:
            { // right
                X++;
                break;
            }
            }
        }
    }
};
class Grid
{
private:
    int height;
    int width;
    Player *p;
    Snake *s;
    bool gameOver;

public:
    Grid()
    {
        height = 25;
        width = 30;
        p = new Player;
        p->setName();
        s = new Snake(height, width);
        bool gameOver = false;
    }
    bool ifGameOver()
    {
        return gameOver;
    }
    void render()
    {
        system("cls");
        cout << "Player : " << p->getName() << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {

                if ((i == 0 || i == height - 1) || (j == 0 || j == width - 1))
                    cout << "#";
                else if (s->getX() == j && s->getY() == i)
                    cout << "o";
                else
                    cout << " ";
            }
            cout << endl;
        }
    }
    void interaction()
    {
        if ((s->getX() == 0 || s->getX() == width - 1) || (s->getY() == 0 || s->getY() == height - 1))
            gameOver = true;
    }
    void move()
    {
        s->movement();
    }
};
int main()
{
    Grid *g = new Grid;
    g->render();
    while (1)
    {
        g->move();
        g->interaction();
        if (g->ifGameOver() == true)
            break;
        g->render();
    }
    cout << "Game Over!" << endl;
    return 0;
}