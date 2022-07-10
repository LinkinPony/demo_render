#include "../include/geometry.h"
Vec3f Barycentric(const Vec3f (&vertex)[3],const Vec2i & P){
    //Calculate barycentric of P in triangle defined by vertex[3]
    Vec3f result =  //cal cross
            Vec3f(vertex[1].x - vertex[0].x,vertex[2].x - vertex[0].x,vertex[0].x - P.x) ^
            Vec3f(vertex[1].y - vertex[0].y,vertex[2].y - vertex[0].y,vertex[0].y - P.y);
    if(abs(result.z) < 1)return Vec3f(-1,1,1);
    result.x /= result.z,result.y /= result.z;
    return {(float)1.0 - result.x - result.y,result.x,result.y};
}