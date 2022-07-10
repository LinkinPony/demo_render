#include "../include/shader.h"
#include <vector>
using namespace ShaderGlobal;
void Bling_Phong::vertex(int iface) {
    std::vector<int>face = model->face(iface);
    for(int i = 0;i < 3;i++){
        varying_vertex[i] = m2v(M * v2m(model->vert(face[i])));
        varying_uv[i] = model-> uv(iface,i);
        varying_norm[i] = model->norm(iface,i);
    }
}
bool Bling_Phong::fragment(int x,int y) {
    //if return true, skip this pixel.
    Vec3f bary = Barycentric(varying_vertex,Vec2i(x,y));
    if(bary.x < -eps or bary.y < -eps or bary.z < -eps)return true;
    depth = bary.x * (float)varying_vertex[0].z + bary.y * (float)varying_vertex[1].z + bary.z * (float)varying_vertex[2].z;
    //texture
//    std::cout << x << " " << y << std::endl;
    int u = bary.x * varying_uv[0].x + bary.y * varying_uv[1].x + bary.z * varying_uv[2].x;
    int v = bary.x * varying_uv[0].y + bary.y * varying_uv[1].y + bary.z * varying_uv[2].y;
    texture_color = model->diffuse(Vec2i(u,v));
    output_color = texture_color;
    return false;
}

Shader::~Shader() {

}
