#include "tgaimage.h"
#include <iostream>
class Drawer: public TGAImage{
private:
public:
    using TGAImage::TGAImage;
    void Line(int x0,int y0,int x1,int y1,TGAColor color);
};