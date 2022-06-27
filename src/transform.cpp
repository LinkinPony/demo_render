#include "../include/transform.h"
Matrix<float> ViewTrans(Vec3f e,Vec3f c,Vec3f t){
    /*
     * e: Camera position point
     * c: Look-at center point
     * t: Up direction
     */
    Vec3f g = (c - e).normalize();
    Vec3f w = Vec3f(-g.x,-g.y,-g.z);
    Vec3f u = (t ^ w).normalize();
    Vec3f v = w ^ u;
    Matrix<float> S(4,4),T = Matrix<float>::I(4);
    for(int i = 0;i < 3;i++){
        T[i][3] = -e[i];
        S[0][i] = u[i];
        S[1][i] = v[i];
        S[2][i] = -w[i];
    }
    S[3][3] = 1;
    return S * T;
}
Matrix<float> OrthoTrans(float l,float r,float b,float t,float f,float n){
    Matrix<float> S(4,4),T = Matrix<float>::I(4);
    S[0][0] = 2/(r-l),S[1][1] = 2/(t-b),S[2][2] = 2/(n-f),S[3][3] = 1;
    T[0][3] = -(l+r)/2,T[1][3] = -(b+t)/2,T[2][3] = -(f+n)/2;
    return S * T;
}
Matrix<float> PerspTrans(float l,float r,float b,float t,float f,float n){
    Matrix<float> M_ortho = OrthoTrans(l,r,b,t,f,n);
    Matrix<float> M_p2o(4,4);
    M_p2o[0][0] = M_p2o[1][1] = n;
    M_p2o[2][2] = n + f;
    M_p2o[2][3] = - n * f;
    M_p2o[3][2] = 1;
    return M_ortho * M_p2o;
}
Matrix<float> ViewportTrans(int width,int height){
    Matrix<float>res(4,4);
    res[0][0] = res[0][3] = (float)width/2.0f;
    res[1][1] = res[1][3] = (float)height/2.0f;
    res[2][2] = res[3][3] = 1;
    return res;
}