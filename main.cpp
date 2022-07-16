#pragma comment(linker, "/stack:200000000")
#include <iostream>
#include <memory.h>
#include <deque>
#include "include/include_all.h"
#include "thirdPartyLib/imgui/imgui.h"
#include "GUI/editor.h"
using namespace std;
const TGAColor white = TGAColor(255, 255, 255, 100);
const TGAColor red   = TGAColor(255, 0,   0,   100);
const TGAColor green = TGAColor(0  , 128, 0,   100);
int main(int argc, char** argv) {
    int width = 500,height = 500;
    Drawer * drawer = new Drawer(width,height,TGAImage::RGB);
    auto * model = new Model("diablo3_pose.obj");
    Editor editor = Editor(width,height,drawer,model);
    auto * zbuffer = new float [width*height];
    editor.zbuffer = zbuffer;
    editor.run();
    return 0;
}
