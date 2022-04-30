#include "../include/drawer.h"

void Drawer::Line(int x0, int y0, int x1, int y1, TGAColor color) {
    bool flip = 0;
    if(abs(x0 - x1) < abs(y0 - y1)){
        flip = 1;
        std::swap(x0,y0),std::swap(x1,y1);
    }
    if(x0 > x1){
        std::swap(x0,x1),std::swap(y0,y1);
    }
    int dx = 2*(x1 - x0),dy = y1 - y0;
    int e = 0,de = 2*abs(dy);
    int y = y0;
    for(int x = x0;x <= x1;x++){
        e += de;
        if(e >= dx) {
            e -= 2*dx;
            y += (dy > 0?1:-1);
        }
        if(!flip)set(x,y,color);
        else set(y,x,color);
    }
}