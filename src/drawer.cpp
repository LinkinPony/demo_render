#include <vector>
#include <algorithm>
#include <tuple>
#include "../include/drawer.h"

void Drawer::Line(int x0, int y0, int x1, int y1,const TGAColor & color) {
    bool flip = 0;
    if(abs(x0 - x1) < abs(y0 - y1)){
        flip = 1;
        std::swap(x0,y0),std::swap(x1,y1);
    }
    if(x0 > x1){
        std::swap(x0,x1),std::swap(y0,y1);
    }
    int dx = x1 - x0,dy = y1 - y0;
    int e = 0,de = 2*abs(dy);
    int y = y0;
    for(int x = x0;x <= x1;x++){
        e += de;
        if(e >= dx) {
            e -= dx*2;
            y += (dy > 0?1:-1);
        }
        if(!flip)set(x,y,color);
        else set(y,x,color);
    }
}
//void Drawer::Triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAColor color) {
//    int x0,y0,x1,y1,x2,y2;
//    std::vector<std::pair<int,int> >top = {{t0.x,t0.y},{t1.x,t1.y},{t2.x,t2.y}};
//    std::sort(top.begin(),top.end());
//    std::tie(x0,y0) = top[0];
//    std::tie(x1,y1) = top[1];
//    std::tie(x2,y2) = top[2];
//    int mx = std::max(x1,x2);
//    double k0 = (double)(y1 - y0)/(x1 == x0?1:x1 - x0);
//    double k1 = (double)(y2 - y1)/(x2 == x1?1:x2 - x1);
//    double k2 = (double)(y2 - y0)/(x2 == x0?1:x2 - x0);
//    for(int x = x0;x <= x2;x++){
//        int yc2 = (x - x0) * k2 + y0;
//        if(x <= x1){
//            int yc0 = (x - x0) * k0 + y0;
//            Line(x,yc0,x,yc2,color);
//        }
//        else{
//            int yc1 = (x - x1) * k1 + y1;
//            Line(x,yc1,x,yc2,color);
//        }
//    }
//}
Vec3f Drawer::Barycentric(const Vec2i (&vertex)[3],const Vec2i & P){
    Vec3f result =  //cal cross
            Vec3f(vertex[1].x - vertex[0].x,vertex[2].x - vertex[0].x,vertex[0].x - P.x) ^
            Vec3f(vertex[1].y - vertex[0].y,vertex[2].y - vertex[0].y,vertex[0].y - P.y);
    if(fabs(result.z) < 1)return Vec3f(-1,1,1);
    result.x /= result.z,result.y /= result.z;
    return {(float)1.0 - result.x - result.y,result.x,result.y};
}
void Drawer::Triangle(const Vec2i (&vertex)[3],const TGAColor & color,int * zbuffer) {
    const double eps = -1e-6;
    int lx = std::max(std::min({vertex[0].x,vertex[1].x,vertex[2].x}),0),rx = std::min(std::max({vertex[0].x,vertex[1].x,vertex[2].x}),get_width()-1);
    int ly = std::max(std::min({vertex[0].y,vertex[1].y,vertex[2].y}),0),ry = std::min(std::max({vertex[0].y,vertex[1].y,vertex[2].y,}),get_height()-1);
    for(int x = lx;x <= rx;x++){
        for(int y = ly;y <= ry;y++){
            Vec3f bary = Barycentric(vertex,Vec2i(x,y));
            if(bary.x < eps or bary.y < eps or bary.z < eps)continue;
            int idx = x + y * get_width();
            int z = bary.x * y + bary.y * y + bary.z * y;
            if(zbuffer[idx] < z){
                zbuffer[idx] = z;
                set(x,y,color);
            }
        }
    }
}