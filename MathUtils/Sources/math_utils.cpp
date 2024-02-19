#include <math_utils.h>
#include <cstring>    // memset

Matrix3f::Matrix3f() {
    data = new float[3 * 3];
    memset(data, 0, sizeof(float) * 3 * 3);
}

Matrix4f::Matrix4f() {

}