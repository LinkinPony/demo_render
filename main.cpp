#include <iostream>
#include "include/tgaimage.h"
#include "include/drawer.h"
#include "include/model.h"
const TGAColor white = TGAColor(255, 255, 255, 100);
const TGAColor red   = TGAColor(255, 0,   0,   100);
const TGAColor green = TGAColor(0  , 128, 0,   100);
int main(int argc, char** argv) {
    int width = 2000,height = 2000;
    Drawer drawer = Drawer(width,height, TGAImage::RGB);
//    1000 1562 1118 1725 1000 1724
//    Vec2i t0[3] = {Vec2i(1000, 1562),   Vec2i(1118, 1725),  Vec2i(1000, 1500)};
//    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
//    Vec2i t2[3] = {Vec2i(50, 50), Vec2i(50, 150), Vec2i(150, 50)};
//    drawer.Triangle(t0[0], t0[1], t0[2], red);
//    drawer.Triangle(t1[0], t1[1], t1[2], white);
//    drawer.Triangle(t2[0], t2[1], t2[2], green);
    Model * model = new Model("african_head.obj");
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f world_coords = model->vert(face[j]);
            screen_coords[j] = Vec2i((world_coords.x+1.)*width/2., (world_coords.y+1.)*height/2.);
        }
        drawer.Triangle(screen_coords[0], screen_coords[1], screen_coords[2], TGAColor(rand()%255, rand()%255, rand()%255, 255));
    }
    drawer.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    drawer.write_tga_file("output.tga");
    return 0;
}