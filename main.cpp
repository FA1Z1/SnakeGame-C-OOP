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
    int X;
    int Y;
    int *tail_x;
    int *tail_y;
    int dir;
    int size;
    int prevX;
    int prevY;

public:
    Snake(int height, int width) : X(width / 2), Y(height / 2), dir(0), size(0)
    {
        tail_x = new int[size];
        tail_y = new int[size];
    } // continues with tail function
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
        updateSize();
        if (size == 0)
        {
            tail_x[0] = X;
            tail_y[0] = Y;
        }
        else
        {
            tail_x[size] = tail_x[size - 1];
            tail_y[size] = tail_y[size - 1];
        }
        size++;
    }
    int getSize()
    {
        return size;
    }
    int getTail_x(int n)
    {
        return tail_x[n];
    }
    int getTail_y(int n)
    {
        return tail_y[n];
    }
    void updateSize()
    {
        int *temp1 = new int[size + 1];
        int *temp2 = new int[size + 1];
        for (int i = 0; i < size; i++)
        {
            temp2[i] = tail_y[i];
            temp1[i] = tail_x[i];
        }
        delete[] tail_x;
        delete[] tail_y;
        tail_x = temp1;
        tail_y = temp2;
        temp1 = nullptr;
        temp2 = nullptr;
    }
    void updateBody()
    {
        if (size == 0)
            return;
        if (size == 0)
            return;
        for (int i = size - 1; i > 0; i--)
        {
            tail_x[i] = tail_x[i - 1];
            tail_y[i] = tail_y[i - 1];
        }
        tail_x[0] = prevX; // ✅ where head WAS, not where it is now
        tail_y[0] = prevY;
    }
    void movement()
    {
        prevX = X; // save before moving
        prevY = Y;
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
    ~Snake()
    {
        delete[] tail_x;
        delete[] tail_y;
        tail_x = nullptr;
        tail_y = nullptr;
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
    bool blob;

public:
    Grid()
    {
        height = 25;
        width = 30;
        p = new Player;
        p->setName();
        s = new Snake(height, width);
        gameOver = false;
        blob = false;
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
                {
                    bool flag = false;
                    if (blob == false)
                    {
                        for (int k = 0; k < s->getSize(); k++)
                        {
                            if (j == s->getTail_x(k) && i == s->getTail_y(k))
                            {
                                cout << "o";
                                flag = true;
                                break;
                            }
                        }
                    }
                    if (flag == false)
                        cout << " ";
                }
            }
            cout << endl;
        }
    }
    void forBody()
    {
        s->updateBody();
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
        g->forBody();
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