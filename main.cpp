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
    int tail_x;
    int tail_y;
    int dir;
    int size;

public:
    Snake(int height, int width) : X(width / 2), Y(height / 2), l_X(0), l_Y(0), dir(0), size(0), tail_x(0), tail_y(0) {}
    int getX()
    {
        return X;
    }
    int getY()
    {
        return Y;
    }
    void setBody()
    {
        size++;
    }
    void movement()
    {
        if (_kbhit())
        {
            int c = _getch();
            if (c == 0 || c == 224)
            {
                c = _getch();
                switch (c)
                {
                case 72:
                { // up
                    dir = 1;
                    break;
                }
                case 80:
                { // down
                    dir = 2;
                    break;
                }
                case 75:
                { // left
                    dir = 3;
                    break;
                }
                case 77:
                { // right
                    dir = 4;
                    break;
                }
                }
            }
        }
        switch (dir)
        {
        case 1:
        { // up
            Y--;
            break;
        }
        case 2:
        { // down
            Y++;
            break;
        }
        case 3:
        { // left
            X--;
            break;
        }
        case 4:
        { // right
            X++;
            break;
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
    int fruit_x;
    int fruit_y;
    int score;

public:
    Grid()
    {
        height = 25;
        width = 30;
        p = new Player;
        p->setName();
        s = new Snake(height, width);
        gameOver = false;
        score = 0;
        generateFruit();
    }
    void generateFruit()
    {

        fruit_y = (rand() % (height - 2)) + 1;
        fruit_x = (rand() % (width - 2)) + 1;
    }
    bool ifGameOver()
    {
        return gameOver;
    }
    void render()
    {
        system("cls");
        cout << "Player : " << p->getName() << "\t" << "Score : " << score << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {

                if ((i == 0 || i == height - 1) || (j == 0 || j == width - 1))
                    cout << "#";
                else if (fruit_x == j && fruit_y == i)
                {
                    cout << "@";
                }
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
        if (s->getX() == fruit_x && s->getY() == fruit_y)
        {
            s->setBody();
            score++;
            generateFruit();
        }
    }
    void move()
    {
        s->movement();
    }
    ~Grid()
    {
        delete p;
        p = nullptr;
        delete s;
        s = nullptr;
    }
};
int main()
{
    srand(time(NULL));
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
    delete g;
    g = nullptr;
    return 0;
}