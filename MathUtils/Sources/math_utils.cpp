#include <math_utils.h>
#include <cstring>    // memset
#include <iostream>   // cout

Matrix3f::Matrix3f() {
    values = new float[3 * 3];
    memset(values, 0, sizeof(float) * 3 * 3);
}

Matrix3f::Matrix3f(const Matrix3f& rhs) {
    values = new float[3 * 3];
    memcpy(values, rhs.values, sizeof(float) * 3 * 3);
}

Matrix3f::Matrix3f(const Values& data) {
    const int rows = 3, cols = 3;
    values = new float[rows * cols];
    for(int row = 0, offset = 0; row < rows; ++row, offset += cols) {
        memcpy(values + offset, data[row].data(), sizeof(float) * cols);
    }
}

Matrix3f  Matrix3f::operator+  (const Matrix3f& rhs) const {
    const int rows = 3, cols = 3;
    Matrix3f result(*this);
    for(int offset = 0, n = rows * cols; offset < n; ++offset)
        result.values[offset] += rhs.values[offset];
    return result;
}

Matrix3f& Matrix3f::operator+= (const Matrix3f& rhs) {
    const int rows = 3, cols = 3;
    for(int offset = 0, n = rows * cols; offset < n; ++offset)
        values[offset] += rhs.values[offset];
    return *this;
}

Matrix3f  Matrix3f::operator*  (const Matrix3f& rhs) const {
    /*
        | 0 1 2 |
        | 3 4 5 |
        | 6 7 8 |
    */
    Matrix3f result(*this);
    result.values[0] = values[0] * rhs.values[0] + values[1] * rhs.values[3] + values[2] * rhs.values[6];
    result.values[1] = values[0] * rhs.values[1] + values[1] * rhs.values[4] + values[2] * rhs.values[7];
    result.values[2] = values[0] * rhs.values[2] + values[1] * rhs.values[5] + values[2] * rhs.values[8];

    result.values[3] = values[3] * rhs.values[0] + values[4] * rhs.values[3] + values[5] * rhs.values[6];
    result.values[4] = values[3] * rhs.values[1] + values[4] * rhs.values[4] + values[5] * rhs.values[7];
    result.values[5] = values[3] * rhs.values[2] + values[4] * rhs.values[5] + values[5] * rhs.values[8];

    result.values[6] = values[6] * rhs.values[0] + values[7] * rhs.values[3] + values[8] * rhs.values[6];
    result.values[7] = values[6] * rhs.values[1] + values[7] * rhs.values[4] + values[8] * rhs.values[7];
    result.values[8] = values[6] * rhs.values[2] + values[7] * rhs.values[5] + values[8] * rhs.values[8];
    return result;
}

Matrix3f& Matrix3f::operator*= (const Matrix3f& rhs) {
    /*
        | 0 1 2 |
        | 3 4 5 |
        | 6 7 8 |
    */
    const int rows = 3, cols = 3;
    float tmp[rows * cols];
    tmp[0] = values[0] * rhs.values[0] + values[1] * rhs.values[3] + values[2] * rhs.values[6];
    tmp[1] = values[0] * rhs.values[1] + values[1] * rhs.values[4] + values[2] * rhs.values[7];
    tmp[2] = values[0] * rhs.values[2] + values[1] * rhs.values[5] + values[2] * rhs.values[8];

    tmp[3] = values[3] * rhs.values[0] + values[4] * rhs.values[3] + values[5] * rhs.values[6];
    tmp[4] = values[3] * rhs.values[1] + values[4] * rhs.values[4] + values[5] * rhs.values[7];
    tmp[5] = values[3] * rhs.values[2] + values[4] * rhs.values[5] + values[5] * rhs.values[8];

    tmp[6] = values[6] * rhs.values[0] + values[7] * rhs.values[3] + values[8] * rhs.values[6];
    tmp[7] = values[6] * rhs.values[1] + values[7] * rhs.values[4] + values[8] * rhs.values[7];
    tmp[8] = values[6] * rhs.values[2] + values[7] * rhs.values[5] + values[8] * rhs.values[8];

    memcpy(values, tmp, sizeof(float) * rows * cols);
    return *this;
}

Matrix4f::Matrix4f() {
    values = new float[4 * 4];
    memset(values, 0, sizeof(float) * 4 * 4);
}

Matrix4f::Matrix4f(const Matrix4f& rhs) {
    values = new float[4 * 4];
    memcpy(values, rhs.values, sizeof(float) * 4 * 4);
}

Matrix4f::Matrix4f(const Values& data) {
    const int rows = 4, cols = 4;
    values = new float[rows * cols];
    for(int row = 0, offset = 0; row < rows; ++row, offset += cols) {
        memcpy(values + offset, data[row].data(), sizeof(float) * cols);
    }
}

Matrix4f  Matrix4f::operator+  (const Matrix4f& rhs) const {
    const int rows = 4, cols = 4;
    Matrix4f result(*this);
    for(int offset = 0, n = rows * cols; offset < n; ++offset)
        result.values[offset] += rhs.values[offset];
    return result;
}

Matrix4f& Matrix4f::operator+= (const Matrix4f& rhs) {
    const int rows = 4, cols = 4;
    for(int offset = 0, n = rows * cols; offset < n; ++offset)
        values[offset] += rhs.values[offset];
    return *this;
}

Matrix4f  Matrix4f::operator*  (const Matrix4f& rhs) const {
    /*
        |  0  1  2  3 |
        |  4  5  6  7 |
        |  8  9 10 11 |
        | 12 13 14 15 |
    */
    Matrix4f result(*this);
    result.values[0]  =  values[0] * rhs.values[0] +  values[1] * rhs.values[4] +  values[2] *  rhs.values[8] +  values[3] * rhs.values[12];
    result.values[1]  =  values[0] * rhs.values[1] +  values[1] * rhs.values[5] +  values[2] *  rhs.values[9] +  values[3] * rhs.values[13];
    result.values[2]  =  values[0] * rhs.values[2] +  values[1] * rhs.values[6] +  values[2] * rhs.values[10] +  values[3] * rhs.values[14];
    result.values[3]  =  values[0] * rhs.values[3] +  values[1] * rhs.values[7] +  values[2] * rhs.values[11] +  values[3] * rhs.values[15];

    result.values[4]  =  values[4] * rhs.values[0] +  values[5] * rhs.values[4] +  values[6] *  rhs.values[8] +  values[7] * rhs.values[12];
    result.values[5]  =  values[4] * rhs.values[1] +  values[5] * rhs.values[5] +  values[6] *  rhs.values[9] +  values[7] * rhs.values[13];
    result.values[6]  =  values[4] * rhs.values[2] +  values[5] * rhs.values[6] +  values[6] * rhs.values[10] +  values[7] * rhs.values[14];
    result.values[7]  =  values[4] * rhs.values[3] +  values[5] * rhs.values[7] +  values[6] * rhs.values[11] +  values[7] * rhs.values[15];

    result.values[8]  =  values[8] * rhs.values[0] +  values[9] * rhs.values[4] + values[10] *  rhs.values[8] + values[11] * rhs.values[12];
    result.values[9]  =  values[8] * rhs.values[1] +  values[9] * rhs.values[5] + values[10] *  rhs.values[9] + values[11] * rhs.values[13];
    result.values[10] =  values[8] * rhs.values[2] +  values[9] * rhs.values[6] + values[10] * rhs.values[10] + values[11] * rhs.values[14];
    result.values[11] =  values[8] * rhs.values[3] +  values[9] * rhs.values[7] + values[10] * rhs.values[11] + values[11] * rhs.values[15];

    result.values[12] = values[12] * rhs.values[0] + values[13] * rhs.values[4] + values[14] *  rhs.values[8] + values[15] * rhs.values[12];
    result.values[13] = values[12] * rhs.values[1] + values[13] * rhs.values[5] + values[14] *  rhs.values[9] + values[15] * rhs.values[13];
    result.values[14] = values[12] * rhs.values[2] + values[13] * rhs.values[6] + values[14] * rhs.values[10] + values[15] * rhs.values[14];
    result.values[15] = values[12] * rhs.values[3] + values[13] * rhs.values[7] + values[14] * rhs.values[11] + values[15] * rhs.values[15];
    return result;
}

Matrix4f& Matrix4f::operator*= (const Matrix4f& rhs) {
    /*
        |  0  1  2  3 |
        |  4  5  6  7 |
        |  8  9 10 11 |
        | 12 13 14 15 |
    */
    const int rows = 4, cols = 4;
    float tmp[rows * cols];
    tmp[0]  =  values[0] * rhs.values[0] +  values[1] * rhs.values[4] +  values[2] *  rhs.values[8] +  values[3] * rhs.values[12];
    tmp[1]  =  values[0] * rhs.values[1] +  values[1] * rhs.values[5] +  values[2] *  rhs.values[9] +  values[3] * rhs.values[13];
    tmp[2]  =  values[0] * rhs.values[2] +  values[1] * rhs.values[6] +  values[2] * rhs.values[10] +  values[3] * rhs.values[14];
    tmp[3]  =  values[0] * rhs.values[3] +  values[1] * rhs.values[7] +  values[2] * rhs.values[11] +  values[3] * rhs.values[15];

    tmp[4]  =  values[4] * rhs.values[0] +  values[5] * rhs.values[4] +  values[6] *  rhs.values[8] +  values[7] * rhs.values[12];
    tmp[5]  =  values[4] * rhs.values[1] +  values[5] * rhs.values[5] +  values[6] *  rhs.values[9] +  values[7] * rhs.values[13];
    tmp[6]  =  values[4] * rhs.values[2] +  values[5] * rhs.values[6] +  values[6] * rhs.values[10] +  values[7] * rhs.values[14];
    tmp[7]  =  values[4] * rhs.values[3] +  values[5] * rhs.values[7] +  values[6] * rhs.values[11] +  values[7] * rhs.values[15];

    tmp[8]  =  values[8] * rhs.values[0] +  values[9] * rhs.values[4] + values[10] *  rhs.values[8] + values[11] * rhs.values[12];
    tmp[9]  =  values[8] * rhs.values[1] +  values[9] * rhs.values[5] + values[10] *  rhs.values[9] + values[11] * rhs.values[13];
    tmp[10] =  values[8] * rhs.values[2] +  values[9] * rhs.values[6] + values[10] * rhs.values[10] + values[11] * rhs.values[14];
    tmp[11] =  values[8] * rhs.values[3] +  values[9] * rhs.values[7] + values[10] * rhs.values[11] + values[11] * rhs.values[15];

    tmp[12] = values[12] * rhs.values[0] + values[13] * rhs.values[4] + values[14] *  rhs.values[8] + values[15] * rhs.values[12];
    tmp[13] = values[12] * rhs.values[1] + values[13] * rhs.values[5] + values[14] *  rhs.values[9] + values[15] * rhs.values[13];
    tmp[14] = values[12] * rhs.values[2] + values[13] * rhs.values[6] + values[14] * rhs.values[10] + values[15] * rhs.values[14];
    tmp[15] = values[12] * rhs.values[3] + values[13] * rhs.values[7] + values[14] * rhs.values[11] + values[15] * rhs.values[15];

    memcpy(values, tmp, sizeof(float) * rows * cols);
    return *this;
}

void print(const float* values, int rows, int cols) {
    for(int row = 0; row < rows; ++row) {
        for(int col = 0; col < cols; ++col) {
            std::cout << " " << values[col + row * rows];
        }
        std::cout << std::endl;
    }
}

void print(const Matrix3f& mat) {
    print(mat.data(), 3, 3);
}

void print(const Matrix4f& mat) {
    print(mat.data(), 4, 4);
}