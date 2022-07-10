#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "tgaimage.h"
#include "geometry.h"
#include "shader.h"
#include <iostream>
#include <vector>
class Drawer: public TGAImage{
private:
public:
    using TGAImage::TGAImage;
    void Line(int x0,int y0,int x1,int y1,const TGAColor & color);
    //Draw a line between (x0,y0) and (x1,y1) use color

    void Triangle(int iface,Shader * shader,float * zbuffer);
    //Draw a triangle defined by vertex t0,t1,t2

    Vec3i world2screen(Vec3f v);
};

#endif //__DRAWER_H__