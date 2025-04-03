#include <cmath>
#include <iostream>

#define SIZE 3
#define EMPTY '_'
#define PLAYER_X 'X'
#define PLAYER_O 'O'

class TicTacToe {
private:
    char board[SIZE][SIZE];
    char currentPlayer;
    bool gameOver;

public:
    TicTacToe() {
        /// конструктор класа
        resetBoard();
        currentPlayer = PLAYER_X;
        gameOver = false;
    }

    void resetBoard() {
        // функция малювання доски в початковому стані
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                board[i][j] = EMPTY;
        gameOver = false;
        currentPlayer = PLAYER_X;
    }

    void displayBoard() {
        // отрисовуємо доску
        std::cout << "\n    1   2   3\n";
        std::cout << "  -------------\n";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << i + 1 << " | ";
            for (int j = 0; j < SIZE; ++j) {
                std::cout << board[i][j] << " | ";
            }
            std::cout << "\n  -------------\n";
        }
        std::cout << "\n";
    }

    bool makeMove(int row, int col) {
        // записуємо хід гравця
        row -= 1;
        col -= 1;
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != EMPTY) {
            std::cout << "Invalid move. Try again.\n";
            return false;
        }
        board[row][col] = currentPlayer;
        checkGameState();
        if (!gameOver) switchPlayer();
        return true;
    }

    void switchPlayer() {
        if (currentPlayer == PLAYER_X) {currentPlayer = PLAYER_O;} else currentPlayer = PLAYER_X;
    }

    void checkGameState() {
        for (int i = 0; i < SIZE; ++i) {
            // горизонталь і вертикаль
            if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                announceWinner(); return;
            }
            if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                announceWinner(); return;
            }
        }
        //наискось
        if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            announceWinner(); return;
        }
        if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            announceWinner(); return;
        }
        if (isBoardFull()) {
            std::cout << "The game ended no winer!\n";
            gameOver = true;
        }
    }

    bool isBoardFull() {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == EMPTY)
                    return false;
        return true;
    }

    void announceWinner() {
        std::cout << "Player " << currentPlayer << " wins!\n";
        gameOver = true;
    }

    bool isGameOver() {
        return gameOver;
    }

    char getCurrentPlayer() {
        return currentPlayer;
    }
};

void playTicTacToe() {
    char playAgain;
    do {
        TicTacToe game;
        int row, col;

        std::cout << "The game 'Tic-Tac-Toe' begins!\n";
        game.displayBoard();

        while (!game.isGameOver()) {
            std::cout << "Player " << game.getCurrentPlayer() << ", enter row and column (1-3): ";
            std::cin >> row >> col;
            if (game.makeMove(row, col)) game.displayBoard();
        }

        std::cout << "Game over. Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
}

class Vector {
private:
    double arr[3]; // Масив із трьох елементів типу double
    int state; // Змінна стану: 0 - OK, 1 - помилка (NULL, ділення на 0)
    static int objectCount; // Лічильник об'єктів

public:
    // Конструктор без параметрів (ініціалізує всі елементи в 0)
    Vector() : arr{0, 0, 0}, state(0) { objectCount++; }

    // Конструктор з одним параметром (заповнює всі елементи однаковим значенням)
    Vector(double val) : arr{val, val, val}, state(0) { objectCount++; }

    // Конструктор з вказівником на масив
    Vector(double* ptr) {
        if (ptr) {
            for (int i = 0; i < 3; i++) arr[i] = ptr[i]; // Копіюємо значення з переданого масиву
            state = 0;
        } else {
            arr[0] = arr[1] = arr[2] = 0; // Якщо вказівник NULL, ініціалізуємо 0
            state = 1; // Встановлюємо стан помилки
        }
        objectCount++; // Збільшуємо лічильник об'єктів
    }

    // Деструктор (виводить повідомлення про видалення об'єкта)
    ~Vector() {
        std::cout << "dell vector : " << state << std::endl;
        objectCount--; // Зменшуємо лічильник об'єктів
    }

    // Функція встановлення значення всіх елементів масиву
    void setValues(double val = 0) { for (int i = 0; i < 3; i++) arr[i] = val; }

    // Функція отримання значення конкретного елемента масиву
    double getValue(int index) { return (index >= 0 && index < 3) ? arr[index] : 0; }

    // Функція друку вектора
    void print() {
        std::cout << "(" << arr[0] << ", " << arr[1] << ", " << arr[2] << ")" << std::endl<< std::endl;
    }

    // Функція додавання двох векторів
    Vector add(Vector& v) {
        double result[3] = {arr[0] + v.arr[0], arr[1] + v.arr[1], arr[2] + v.arr[2]};
        return Vector(result); // Використовуємо конструктор з вказівником на масив
    }


    // Функція віднімання двох векторів
    Vector subtract(Vector& v) {
        double result[3] = {arr[0] - v.arr[0], arr[1] - v.arr[1], arr[2] - v.arr[2]};
        return Vector(result); // Використовуємо конструктор з вказівником на масив
    }


    // Функція векторного добутку
    Vector crossProduct(Vector& v) {
        double result[3] = {
            arr[1] * v.arr[2] - arr[2] * v.arr[1],
            arr[2] * v.arr[0] - arr[0] * v.arr[2],
            arr[0] * v.arr[1] - arr[1] * v.arr[0]
        };
        return Vector(result); // Використовуємо конструктор з вказівником на масив
    }


    // Функція ділення на short (перевіряє ділення на 0)
    void divide(short val) {
        if (val == 0) {
            state = 1; // Встановлюємо стан помилки
            std::cout << "error devide by 0!" << std::endl;
            return;
        }
        for (int i = 0; i < 3; i++) arr[i] /= val; // Ділимо всі елементи
    }

    // Функції порівняння векторів
    bool isGreater(Vector& v) { return magnitude() > v.magnitude(); }
    bool isLess(Vector& v) { return magnitude() < v.magnitude(); }
    bool isEqual(Vector& v) { return magnitude() == v.magnitude(); }

    // Отримання кількості створених об'єктів
    static int getObjectCount() { return objectCount; }

private:
    // Обчислення модуля вектора
    double magnitude() { return sqrt(arr[0] * arr[0] + arr[1] * arr[1] + arr[2] * arr[2]); }
};


int Vector::objectCount = 0;

void runVectorClassTest() {


    Vector v1;
    Vector v2(3.5);
    double arr[3] = {1.0, 2.0, 3.0};
    Vector v3(arr);
    Vector v4(nullptr);

    // Вивід кількості об'єктів
    std::cout << "\n\n\n-----------------------------"<< std::endl;
    std::cout << "created: " << Vector::getObjectCount() << std::endl;

    // Вивід векторів
    std::cout << "vector 1:  ";  v1.print();
    std::cout << "vector 2:  ";  v2.print();
    std::cout << "vector 3:  ";  v3.print();
    std::cout << "vector 4:  ";  v4.print();

    std::cout << "Run vector class test \n-----------------------------"<< std::endl;

    // Додавання векторів
    Vector v5 = v3.add(v2);
    std::cout << "add vector v3 + v2  -> ";
    v5.print();

    // Віднімання векторів
    Vector v6 = v2.subtract(v3);
    std::cout << "subtract vector v2 - v3  -> ";
    v6.print();

    // Перевірка ділення на 0
    v3.divide(0);
    std::cout << "divide vector v3 / 0  -> ";
    v3.print();

    // Перевірка ділення
    v3.divide(2);
    std::cout << "divide vector v3 / 2 -> ";
    v3.print();

    // Перевірка встановлення значень
    v3.setValues(4);
    std::cout << "set 3v values 4  -> ";
    v3.print();

    // перевірка векторного добутку
    Vector v7 = v5.crossProduct(v2);
    std::cout << "crossProduct vector v5  v2  -> ";
    v7.print();
    std::cout << "-----------------------------"<< std::endl;

    std::cout << "end objects: " << Vector::getObjectCount() << std::endl;
}

int main() {
    int choice;
    do {
        std::cout << "Choose :\n1. Tic-Tac-Toe\n2. run vector class test\n0. Exit\n::: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                playTicTacToe();
            break;
            case 2:
                runVectorClassTest();
            break;
            case 0:
                std::cout << "Thanks for playing!\n";
            break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
