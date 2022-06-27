#include "../include/matrix.h"
Matrix<float> v2m(const Vec3f & X){
    Matrix<float> res(4,1);
    res[0][0] = X.x,res[1][0] = X.y,res[2][0] = X.z;
    res[3][0] = 1;
    return res;
}

Vec3f m2v(const Matrix<float> & X){
    return {X[0][0]/X[3][0],X[1][0]/X[3][0],X[2][0]/X[3][0]};
}
