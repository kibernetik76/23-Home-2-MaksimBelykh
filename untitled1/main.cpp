#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
template <typename T>
class Matrica {
    int strok;
    int stolb;
    T** matr;

public:
    //Конструктор для создания основы матрицы
    Matrica(int a, int b) {
        strok = a;
        stolb = b;
        matr = new T* [strok];
        for (int i = 0; i < strok; i++)
            matr[i] = new T[stolb];
    }
    //Консутрктор пустой матрицы
    Matrica() {
        strok = 0;
        stolb = 0;
        matr = nullptr;
    }
    //Консутрктор для считывания матрицы из файла
    Matrica(char* filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> strok >> stolb;

            matr = new T* [strok];
            for (int i = 0; i < strok; i++)
                matr[i] = new T[stolb];

            for (int i = 0; i < strok; i++) {
                for (int j = 0; j < stolb; j++) {
                    file >> matr[i][j];
                }
            }
            file.close();
        }
        else
            cout << "Can not open file" << endl;
    }
    //Заполнение матрицы с консоли
    void ConsoleRead() {
        cout << "Enter matrix elements: ";
        for (int i = 0; i < strok; i++)
            for (int j = 0; j < stolb; j++)
                cin >> matr[i][j];
    }
    //Вывод матрицы в консоль
    void ConsolePrint() {
        cout << endl;
        for (int i = 0; i < strok; i++) {
            for (int j = 0; j < stolb; j++)
                cout << matr[i][j] << " ";
            cout << endl;
        }
    }
    //Умножение матриц
    Matrica operator*(Matrica B) {
        if (stolb != B.strok) {
            cout << "Error";
            return Matrica(0, 0);
        }
        Matrica proizvedenie(strok, B.stolb);
        for (int i = 0; i < strok; i++) {
            for (int j = 0; j < B.stolb; j++) {
                proizvedenie.matr[i][j] = 0;
                for (int k = 0; k < stolb; k++)
                    proizvedenie.matr[i][j] += matr[i][k] * B.matr[k][j];
            }
        }
        return proizvedenie;
    }
    //Умножение на скаляр
    Matrica operator*(int a) {
        Matrica proizvedenie(strok, stolb);
        for (int i = 0; i < strok; i++)
            for (int j = 0; j < stolb; j++)
                proizvedenie.matr[i][j] = a * matr[i][j];
        return proizvedenie;
    }
    //Сложение матриц
    Matrica operator+(Matrica B) {
        if (strok != B.strok || stolb != B.stolb) {
            cout << "Error";
            return Matrica(0, 0);
        }
        Matrica summa(strok, stolb);
        for (int i = 0; i < strok; i++)
            for (int j = 0; j < stolb; j++){
                summa.matr[i][j] = matr[i][j] + B.matr[i][j];

            }
        return summa;
    }
    //Вычитание матриц
    Matrica operator-(Matrica B) {
        if (strok != B.strok && stolb != B.stolb) {
            cout << "Error";
            return Matrica(0, 0);
        }
        Matrica razn(strok, stolb);
        for (int i = 0; i < strok; i++)
            for (int j = 0; j < stolb; j++) {
                razn.matr[i][j] = matr[i][j] - B.matr[i][j];
            }
        return razn;
    }

    void FileRead(char* filename) {
        ifstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < stolb; i++) {
                for (int j = 0; j < strok; j++) {
                    file >> matr[i][j];
                }
            }
            file.close();
        }
        else
            cout << "Can not open file"<< endl;
    }
    void FilePrint(char* filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < strok; i++) {
                for (int j = 0; j < stolb; j++) {
                    file << matr[i][j] << " ";
                }
                file << endl;
            }
            file.close();
        }
        else
            std::cout << "Can not open file"<<endl;

    }

    int opredelitel() {
        if (stolb != strok){
            cout << "Error"<<endl;
            return 0;
        }
        if (strok == 1){
            return matr[0][0];
        }
        int opred = 0;
        if (strok == 2){
            opred = matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];}
        else {
            for (int n = 0;n<strok;n++){
                Matrica algdop(strok -1,stolb -1);
                for (int i = 1;i<strok;i++ ) {
                    int flag=0;
                    for (int j = 0; j < stolb; j++) {
                        if (j == n)
                            flag = 1;

                        if (j != n) {
                            algdop.matr[i-1][j-flag]=matr[i][j];

                        }
                    }
                }
                opred = opred + pow(-1,1+(n+1))*matr[0][n]*algdop.opredelitel();
            }
        }
        return opred;
    }
    Matrica operator!() {
        Matrica obratn_matr(strok, stolb);
        float opred = opredelitel();
        if (opred == 0) {
            throw;

        }
        if (strok!=stolb){
            cout << "Error" << endl;
            throw;
        }

        if (strok == 1 && stolb == 1) {
            obratn_matr.matr[0][0] = 1 / matr[0][0];
            return obratn_matr;
        }
        Matrica dop_matr(strok - 1, stolb - 1);
        for (int i = 0; i < strok; i++) {
            for (int j = 0; j < stolb; j++) {
                int flagi = 0;
                int flagj = 0;
                for (int n = 0; n < strok - 1; n++) {
                    if (n == i)
                        flagi = 1;
                    flagj=0;
                    for (int m = 0; m < stolb - 1; m++) {
                        if (m == j)
                            flagj = 1;
                        dop_matr.matr[n][m] = matr[n + flagi][m + flagj];
                    }
                }
                obratn_matr.matr[j][i] = pow(-1, (i+j))* dop_matr.opredelitel()*(1/opred);
            }
        }
        return obratn_matr;
    }

    // перегрузка оператора присваивания
    Matrica& operator=(const Matrica& other) {
        if (this != &other) {
            for (int i = 0; i < strok; i++) {
                delete[] matr[i];
            }
            delete[] matr;

            strok = other.strok;
            stolb = other.stolb;


            matr = new T*[strok];
            for (int i = 0; i < strok; i++) {
                matr[i] = new T[stolb];
            }


            for (int i = 0; i < strok; i++) {
                for (int j = 0; j < stolb; j++) {
                    matr[i][j] = other.matr[i][j];
                }
            }
        }
        return *this;
    }

    static Matrica<T> createZeroMatrica(int a, int b) {
        Matrica<T> zeroMatrica(a, b);
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                zeroMatrica.matr[i][j] = 0;
            }
        }
        return zeroMatrica;
    }

    static Matrica<T> createEdMatrica(int size) {
        Matrica<T> EdMatrica(size, size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    EdMatrica.matr[i][j] = 1;
                } else {
                    EdMatrica.matr[i][j] = 0;
                }
            }
        }
        return EdMatrica;
    }
};

int main() {
    Matrica<float> A(3, 3);
    A.ConsoleRead();
    A.ConsolePrint();

    Matrica<float> B(3, 3);
    B.ConsoleRead();
    B.ConsolePrint();

    Matrica<float> C1 = A * B;
    C1.ConsolePrint();
    Matrica<float> C2 = A - B;
    C2.ConsolePrint();
    Matrica<float> C3 = A + B;
    C3.ConsolePrint();
    Matrica<float> C4 = !A;
    C4.ConsolePrint();
    Matrica<float> C5 = A * 2;
    C5.ConsolePrint();


    Matrica<int> A1(2, 2);
    A1.ConsoleRead();
    A1.ConsolePrint();
    Matrica<int> B1(2,2);
    B1.ConsoleRead();
    B1.ConsolePrint();
    Matrica<int> C30 = A1 + B1;
    C30.ConsolePrint();

    Matrica<int> A2(2,2);
    A2.FileRead("file1.txt");
    A2.ConsolePrint();
    A2.FilePrint("file2.txt");

    Matrica<int> A3("file3.txt");
    A3.ConsolePrint();

    Matrica<int> A4(2,2);
    A4.ConsoleRead();
    Matrica<int> B4(2,2);

    B4 = A4;
    B4.ConsolePrint();


    Matrica<int> Z = Matrica<int>::createZeroMatrica(3,3);
    Z.ConsolePrint();
    Matrica<int> E = Matrica<int>::createEdMatrica(3);
    E.ConsolePrint();









}