#include <iostream>
#include <memory.h>
#include <deque>
#include "include/tgaimage.h"
#include "include/drawer.h"
#include "include/model.h"
const TGAColor white = TGAColor(255, 255, 255, 100);
const TGAColor red   = TGAColor(255, 0,   0,   100);
const TGAColor green = TGAColor(0  , 128, 0,   100);
int main(int argc, char** argv) {
    int width = 2000,height = 2000;
    int * zbuffer = new int[width*height];
    std::fill(zbuffer,zbuffer+width*height,INT_MIN);
    Drawer drawer = Drawer(width,height, TGAImage::RGB);
    Model * model = new Model("african_head.obj");
    Vec3f light_dir(0,0,-1); // define light_dir

    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x+1.)*width/2., (v.y+1.)*height/2.);
            world_coords[j]  = v;
        }
        Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
        n.normalize();
        float intensity = n*light_dir;
        if (intensity>0) {
            Vec2i ver[3] = {screen_coords[0], screen_coords[1], screen_coords[2]};
            drawer.Triangle(ver, TGAColor(intensity*255, intensity*255, intensity*255, 255),zbuffer);
        }
    }
    drawer.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    drawer.write_tga_file("output.tga");
    return 0;
}