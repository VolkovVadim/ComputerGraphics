#pragma once

#include <vector>

typedef std::vector<std::vector<float>> Values;

class Matrix3f {
    float* values;
public:
    Matrix3f();
    Matrix3f(const Matrix3f& rhs);
    Matrix3f(const Values& data);
    ~Matrix3f() {
        if (values) delete[] values;
    }

    float* data() const {
        return values;
    }

    Matrix3f  operator+  (const Matrix3f& rhs) const;
    Matrix3f& operator+= (const Matrix3f& rhs);
    Matrix3f  operator*  (const Matrix3f& rhs) const;
    Matrix3f& operator*= (const Matrix3f& rhs);
};

class Matrix4f {
    float* values;
public:
    Matrix4f();
    Matrix4f(const Matrix4f& rhs);
    Matrix4f(const Values& data);
    ~Matrix4f() {
        if (values) delete[] values;
    }

    float* data() const {
        return values;
    }

    Matrix4f  operator+  (const Matrix4f& rhs) const;
    Matrix4f& operator+= (const Matrix4f& rhs);
    Matrix4f  operator*  (const Matrix4f& rhs) const;
    Matrix4f& operator*= (const Matrix4f& rhs);
};

void print(const Matrix3f& mat);
void print(const Matrix4f& mat);