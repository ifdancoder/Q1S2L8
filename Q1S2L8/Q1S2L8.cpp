#include <iostream>

using namespace std;

const int n = 10;
enum dir { UP, DOWN, LEFT, RIGHT, UNKNOWN };
string dr[5] = { "Up", "Down", "Left", "Right", "Unknown" };

class Exception {
protected:
    string text;
    int coord[2];
    dir direction;
public:
    Exception(string text, int x, int y, dir direction=UNKNOWN) : text(text), direction(direction) {
        coord[0] = x;
        coord[1] = y;
    }

    friend ostream& operator<< (ostream& out, const Exception& ex);
};

ostream& operator<< (ostream& out, const Exception& ex) {
    out << endl << "Error: " << ex.text << endl << "Robot's coordinates: " << "(" << ex.coord[0] << ", " << ex.coord[1] << ")" << endl << "Robot's direction: " << dr[ex.direction] << endl;
    return out;
}

class OffTheField : public Exception {
public:
    OffTheField(int x, int y, dir direction) : Exception("The robot went out of the field", x, y, direction) {
    
    }
};

class IllegalCommand : public Exception {
public:
    IllegalCommand(int x, int y) : Exception("An incorrect command was passed to the robot", x, y) {

    }
};

class Robot {
protected:
    int coord[2];
public:
    Robot(int x=0, int y=0) {
        coord[0] = x;
        coord[1] = y;
    }

    void move(dir direction) {
        int tmp = coord[direction > 1] + !((direction + 1) % 2) * 2 - 1;
        if (tmp <= n && tmp > 0) {
            coord[direction > 1] += !((direction + 1) % 2) * 2 - 1;
        }
        else {
            throw OffTheField(coord[0], coord[1], direction);
        }
    }
    
    void checkAndMove(string tmp) {
        if (tmp != "u" && tmp != "U" && tmp != "d" && tmp != "D" && tmp != "l" && tmp != "L" && tmp != "r" && tmp != "R") {
            throw IllegalCommand(coord[0], coord[1]);
        }
        else {
            dir direction = UNKNOWN;
            switch (tmp[0]) {
            case 'u':
            case 'U':
                direction = UP;
                break;
            case 'd':
            case 'D':
                direction = DOWN;
                break;
            case 'l':
            case 'L':
                direction = LEFT;
                break;
            case 'r':
            case 'R':
                direction = RIGHT;
                break;
            }
            move(direction);
        }
    }

    friend ostream& operator<< (ostream& out, const Robot& robot);
};

ostream& operator<< (ostream& out, const Robot& robot) {
    out << "Robot's coordinates: " << "(" << robot.coord[0] << ", " << robot.coord[1] << ")";
    return out;
}

class Ex {
protected:
    double x;
public:
    Ex(double x) : x(x) {
    
    }
    double getX() const {
        return x;
    }
};

class Bar {
protected:
    double y;
public:
    Bar(double y=0) : y(y) {

    }
    void set(double a) {
        if (y + a > 100) {
            throw Ex(a * y);
        }
        y = a;
    }
};

template<class A>
A div(A a, A b) {
    if (b) {
        return a / b;
    }
    throw "DivisionByZero";
}

int main()
{
    // #1
    double a, b;
    cout << "Input a and b (a b): ";
    cin >> a >> b;
    try {
        cout << div(a, b) << endl;
    }
    catch (const char* error) {
        cout << error << endl;
    }
    cout << endl << endl;


    // #2
    Bar c;
    int n;
    cout << "Input a number: ";
    cin >> n;
    while (n != 0) {
        try {
            c.set(n);
            cout << "Input a number: ";
            cin >> n;
        }
        catch (const Ex& ExErr) {
            cout << "Error " << ExErr.getX() << endl;
            break;
        }
    }
    cout << endl << endl;


    // #3
    Robot r;
    cout << "You can do 20 moves with this robot" << endl;
    for (int i = 0; i < 20; i++) {
        cout << r << endl << endl;
        try {
            string tmp;
            cout << "Input a dir (u/U, d/D, l/L, r/R): ";
            cin >> tmp;
            r.checkAndMove(tmp);
        }
        catch (OffTheField &otf) {
            cout << otf << endl;
            i--;
        }
        catch (IllegalCommand& ic) {
            cout << ic << endl;
            i--;
        }
    }
    return 0;
}