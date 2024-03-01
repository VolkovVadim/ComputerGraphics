#include <iostream>
#include <math_utils.h>

using namespace std;

void print(const Values& values) {
    for(size_t row = 0, rows = values.size(); row < rows; ++row) {
        for(size_t col = 0, cols = values[row].size(); col < cols; ++col) {
            cout << " " << values[row][col];
        }
        cout << endl;
    }
}

int main(int argc, char** argv)
{
    cout << "Application started..." << endl;

    Values valuesA3 = {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    Values valuesB3 = {
        {1.0f, 2.0f, 3.0f},
        {4.0f, 5.0f, 6.0f},
        {7.0f, 8.0f, 9.0f}
    };

    Matrix3f A3(valuesA3);
    Matrix3f B3(valuesB3);

    cout << "\nA3 + B3:" << endl;
    print(A3 + B3);

    Matrix3f E3(
        {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    );

    cout << "\nE3 * E3:" << endl;
    print(E3 * E3);

    cout << "\nE3 * B3:" << endl;
    print(E3 * B3);


    Matrix4f E4(
        {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    );

    Matrix4f B4(
        {
            { 1.0f,  2.0f,  3.0f,  4.0f},
            { 5.0f,  6.0f,  7.0f,  8.0f},
            { 9.0f, 10.0f, 11.0f, 12.0f},
            {13.0f, 14.0f, 15.0f, 16.0f}
        }
    );

    cout << "\nE4 * E4" << endl;
    print(E4 * E4);

    cout << "\nE4 * B4" << endl;
    print(E4 * B4);

    cout << "\nSuccess" << endl;
    return 0;
}
