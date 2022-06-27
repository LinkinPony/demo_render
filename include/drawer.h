#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "tgaimage.h"
#include "geometry.h"
#include <iostream>
class Drawer: public TGAImage{
private:
public:
    using TGAImage::TGAImage;
    void Line(int x0,int y0,int x1,int y1,const TGAColor & color);
    //Draw a line between (x0,y0) and (x1,y1) use color

    void Triangle(const Vec3f (&vertex)[3],const TGAColor & color,float * zbuffer);
    //Draw a triangle defined by vertex t0,t1,t2

    static Vec3f Barycentric(const Vec3f (&vertex)[3],const Vec2i & P);
    //Calculate barycentric of P in triangle defined by vertex[3]

    Vec3i world2screen(Vec3f v);
};

#endif //__DRAWER_H__