#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T>
class Matrix {
private:
    T** data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols]{};
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Доступ к элементам
    T& operator()(int i, int j) {
        return data[i][j];
    }

    // Заполнение с клавиатуры
    void input() {
        cout << "Введите " << rows << "x" << cols << " элементов:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i][j];
            }
        }
    }

    // Заполнение случайными числами
    void randomFill(T min, T max) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = min + rand() % (max - min + 1);
            }
        }
    }

    // Вывод матрицы
    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Сложение
    Matrix operator+(const Matrix& other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Вычитание
    Matrix operator-(const Matrix& other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Умножение
    Matrix operator*(const Matrix& other) {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Поиск максимума
    T findMax() {
        T max = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] > max) max = data[i][j];
            }
        }
        return max;
    }

    // Поиск минимума
    T findMin() {
        T min = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] < min) min = data[i][j];
            }
        }
        return min;
    }
};

int main() {
    srand(time(0));
    
    // Демонстрация с int
    Matrix<int> A(2, 2);
    Matrix<int> B(2, 2);
    
    A.randomFill(1, 10);
    B.randomFill(1, 10);
    
    cout << "Матрица A:" << endl;
    A.print();
    
    cout << "Матрица B:" << endl;
    B.print();
    
    cout << "A + B:" << endl;
    (A + B).print();
    
    cout << "A - B:" << endl;
    (A - B).print();
    
    cout << "Максимум в A: " << A.findMax() << endl;
    cout << "Минимум в A: " << A.findMin() << endl;
    
    // Демонстрация с double
    Matrix<double> C(2, 2);
    Matrix<double> D(2, 2);
    
    C(0,0) = 1.5; C(0,1) = 2.5;
    C(1,0) = 3.5; C(1,1) = 4.5;
    
    D(0,0) = 0.5; D(0,1) = 1.5;
    D(1,0) = 2.5; D(1,1) = 3.5;
    
    cout << "Матрица C:" << endl;
    C.print();
    
    cout << "Матрица D:" << endl;
    D.print();
    
    cout << "C + D:" << endl;
    (C + D).print();

    return 0;
}