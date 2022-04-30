#include <iostream>
#include "include/tgaimage.h"
#include "include/drawer.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
int main(int argc, char** argv) {
    Drawer drawer = Drawer(500, 500, TGAImage::RGB);
    drawer.Line(5,10,30,400,white);
    drawer.Line(5,10,400,300,red);
    drawer.set(52, 41, red);
    drawer.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    drawer.write_tga_file("output.tga");
    return 0;
}