#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "matrix.h"
#include "geometry.h"

template <class T>
class Transform{
public:
    static Matrix<T> Scale(int a,int b){
        //x' = a * x,y' = b * sy
        Matrix<T> res(2,2);
        res[0][0] = a,res[1][1] = b;
        return res;
    }
    static Matrix<T> Scale(int a,int b,int c){
        Matrix<T> res(3,3);
        res[0][0] = a,res[1][1] = b,res[2][2] = c;
    }

};
Matrix<float> ViewTrans(Vec3f e,Vec3f g,Vec3f t);
Matrix<float> OrthoTrans(float l,float r,float b,float t,float f,float n);
Matrix<float> PerspTrans(float l,float r,float b,float t,float f,float n);
Matrix<float> ViewportTrans(int width,int height);
#endif //__TRANSFORM_H__