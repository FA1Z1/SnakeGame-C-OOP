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
    void setName(string name)
    {
        this->name = name;
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
    }
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
            tail_x[0] = prevX;
            tail_y[0] = prevY;
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
        tail_x[0] = prevX;
        tail_y[0] = prevY;
    }
    void movement()
    {
        prevX = X;
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
                    if (dir != 2)
                        dir = 1;
                    break;
                }
                case 80:
                { // down
                    if (dir != 1)
                        dir = 2;
                    break;
                }
                case 75:
                { // left
                    if (dir != 4)
                        dir = 3;
                    break;
                }
                case 77:
                { // right
                    if (dir != 3)
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
    void askName(string name)
    {
        p->setName(name);
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
        if (blob == false)
        {
            for (int i = 1; i < s->getSize(); i++)
            {
                if (s->getX() == s->getTail_x(i) && s->getY() == s->getTail_y(i))
                {
                    gameOver = true;
                }
            }
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
    while (1)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t __  _  _   _   _  _ ___    __   _   _   _  ___ \n";
        cout << "\t\t\t\t\t\t\t\t/ _|| \\| | / \\ | |//| __|  / _| / \\ | \\_/ || __|\n";
        cout << "\t\t\t\t\t\t\t\t\\_ \\| \\\\ || o ||  ( | _|  ( |_n| o || \\_/ || _| \n";
        cout << "\t\t\t\t\t\t\t\t|__/|_|\\_||_n_||_|\\\\|___|  \\__/|_n_||_| |_||___|\n\n";

        cout << "\t\t\t\t\t\t\t\t\t _     __  ___  _   ___  ___ \n";
        cout << "\t\t\t\t\t\t\t\t\t/_|   / _||_ _|/ \\ | o \\|_ _|\n";
        cout << "\t\t\t\t\t\t\t\t\t ||   \\_ \\ | || o ||   / | | \n";
        cout << "\t\t\t\t\t\t\t\t\t L| O |__/ |_||_n_||_|\\\\ |_|\n";

        cout << "\t\t\t\t\t\t\t\t\t   __     ___ __ __ _  ___ \n";
        cout << "\t\t\t\t\t\t\t\t\t  [o )   | __|\\ V /| ||_ _|\n";
        cout << "\t\t\t\t\t\t\t\t\t   /(    | _|  ) ( | | | | \n";
        cout << "\t\t\t\t\t\t\t\t\t  /__| O |___|/_n_\\|_| |_|\n";
        int main_choice = _getch();
        if (main_choice == '2')
            exit(0);
        else if (main_choice == '1')
            break;
        else
            cout << "\a";
    }
    Grid *g = new Grid;
    string name;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\t\t\t\t\t\t  ___  _  _  ___  ___  ___  __ __ _   _ _  ___   _  _   _   _   _  ___ \n";
        cout << "\t\t\t\t\t\t | __|| \\| ||_ _|| __|| o \\ \\ V // \\ | | || o \\ | \\| | / \\ | \\_/ || __|\n";
        cout << "\t\t\t\t\t\t | _| | \\\\ | | | | _| |   /  \\ /( o )| U ||   / | \\\\ || o || \\_/ || _| \n";
        cout << "\t\t\t\t\t\t |___||_|\\_| |_| |___||_|\\\\  |_| \\_/ |___||_|\\\\ |_|\\_||_n_||_| |_||___|\n";
        if (name.length() <= 20)
            g->askName(name);
        else
        {
            cout << "\a";
            cout << "\n\n\n\n\t\t\t\t\t\t\t\t";
            cout << "*Name cannot be longer than 20 characters*\n";
                }
        getline(cin, name);
    } while (name.length() > 20);

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