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
void Drawer::Triangle(int iface,Shader * shader,float * zbuffer) {
    Vec3f * vertex = ShaderGlobal::varying_vertex;
    int lx = std::max(std::min({vertex[0].x,vertex[1].x,vertex[2].x}),0.f);
    int rx = std::min(std::max({vertex[0].x,vertex[1].x,vertex[2].x}),get_width()-1.f);
    int ly = std::max(std::min({vertex[0].y,vertex[1].y,vertex[2].y}),0.f);
    int ry = std::min(std::max({vertex[0].y,vertex[1].y,vertex[2].y,}),get_height()-1.f);
    int width = get_width();
    for(int x = lx;x <= rx;x++){
        for(int y = ly;y <= ry;y++){
            bool skip = shader->fragment(x,y);
            if(skip)continue;
            int idx = x + y * width;
            if(zbuffer[idx] > ShaderGlobal::depth){
                zbuffer[idx] = ShaderGlobal::depth;
                set(x,y,ShaderGlobal::output_color);
            }
        }
    }
}
Vec3i Drawer::world2screen(Vec3f v) {
    return Vec3i(int((v.x+1.)*width/2.+.5), int((v.y+1.)*height/2.+.5), v.z);
}