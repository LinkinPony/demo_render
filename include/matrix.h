#ifndef __MATRIX_H__
#define __MATRIX_H__
//模板类无法将实现与定义分离

#include <cmath>
#include <vector>
#include <cassert>
#include "geometry.h"
#include <iostream>
using std::vector;
template <class T> class Matrix{

public:
    vector<vector<T> > A;
    int n,m;

    Matrix(int _n,int _m):n(_n),m(_m){
        A = vector<vector<T>>(n,vector<T>(m,0));
    }
    Matrix(const Matrix<T> & _matrix){
        n = _matrix.A.size();
        m = (n?_matrix[0].size():0);
        A = _matrix.A;
    }
    Matrix<T> operator * (const Matrix<T> & B) const {
        if(m != B.n){
            std::cerr << "Martix's width don't match.";
            return *this;
        }
        Matrix<T> res(n,B.m);
        for(int k = 0;k < m;k++){
            for(int i = 0;i < n;i++){
                for(int j = 0;j < B.m;j++){
                    res[i][j]  = res[i][j] + A[i][k] * B[k][j];
                }
            }
        }
        return res;
    }
    Matrix<T> operator + (const Matrix<T> & B) const {
        if(n != B.n or m != B.m){
            std::cerr << "Error: Martix Plus";
            return A;
        }
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++)A[i][j] += B[i][j];
        }
        return A;
    }
    Matrix<T> operator ~ (){//Transpose
        Matrix<T> res = Matrix<T>(m,n);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                res[j][i] = A[i][j];
            }
        }
        return res;
    }
    const vector<T> & operator [] (int idx) const{
        return A.at(idx);
    }
    vector<T> & operator [] (int idx) {
        return A.at(idx);
    }
    Matrix & operator = (const Matrix<T> & copy){
        if(this != &copy)n = copy.n,m = copy.m,A = copy.A;
        return *this;
    }

    static Matrix<T> I(int n);

    static double Det(const Matrix & matrix);
};
template <class t> std::ostream& operator<<(std::ostream& s, Matrix<t>& B) {
    for(int i = 0;i < B.n;i++){
        s << "[";
        for(int j = 0;j < B.m;j++)s << B[i][j] << " ]"[j == B.m - 1];
        s << "\n";
    }
    return s;
}
template<class T> Matrix<T> Matrix<T>::I(int n) {
    Matrix<T> res = Matrix<T>(n,n);
    for(int i = 0;i < n;i++)res[i][i] = 1;
    return res;
}
template<class T>
double Matrix<T>::Det(const Matrix & matrix) {
    assert(matrix.n == matrix.m);
    const double eps = 1e-9;
    double det = 1;
    int n = matrix.n;
    vector<vector<double> >A = matrix.A;
    for(int i = 0;i < n;i++){
        int k = i;
        for(int j = i+1;j < n;j++){
            if(fabs(A[j][i]) > fabs(A[k][i]))k = j;
        }
        if(fabs(A[k][i]) < eps){
            det = 0;
            break;
        }
        swap(A[i],A[k]);
        if(i != k)det = -det;
        det *= A[i][i];
        for(int j = i+1;j < n;j++)A[i][j] /= A[i][i];
        for(int j = 0;j < n;j++){
            if(j != i and fabs(A[j][i]) > eps){
                for(int k = i+1;k < n;k++){
                    A[j][k] -= A[i][k] * A[j][i];
                }
            }
        }
    }
    return det;
}

Matrix<float> v2m(const Vec3f & X);
Vec3f m2v(const Matrix<float> & X);
Vec3i m2vi(const Matrix<float> & X);
#endif //__MATRIX_H__
