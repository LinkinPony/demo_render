#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "tgaimage.h"
#include "geometry.h"
#include <iostream>
class Drawer: public TGAImage{
private:
public:
    using TGAImage::TGAImage;
    void Line(int x0,int y0,int x1,int y1,TGAColor color);
    void Triangle(Vec2i t0,Vec2i t1,Vec2i t2,TGAColor color);
};

#endif //__DRAWER_H__