#include "../include/shader.h"
#include <vector>
#include "shaderGlobal.h"
using namespace ShaderGlobal;
void Bling_Phong::vertex(int iface) {
    std::vector<int>face = model->face(iface);
    for(int i = 0;i < 3;i++){
        varying_vertex[i] = M * model->vert(face[i]);
        varying_uv[i] = model-> uv(iface,i);
        varying_norm[i] = model->normal(iface,i);
    }
}
bool Bling_Phong::fragment(int x,int y) {
    //if return true, skip this pixel.
    Vec3f bary = Barycentric(varying_vertex,Vec2i(x,y));
    if(bary.x < -eps || bary.y < -eps || bary.z < -eps)return true;
    depth = 0;
    Vec2f diffuse_uv;
    Vec3f cur_position,cur_norm;
    for(int i = 0;i < 3;i++){
        depth += bary[i] * varying_vertex[i].z;
        diffuse_uv.x += bary[i] * varying_uv[i].x;
        diffuse_uv.y += bary[i] * varying_uv[i].y;
        cur_position = cur_position + varying_vertex[i] * bary[i];
        cur_norm = cur_norm + varying_norm[i] * bary[i];
    }
//    cur_norm = model->normal(diffuse_uv);
    //texture
    texture_color = model->diffuse(diffuse_uv);
    //diffuse light
    Vec3f light_direction = (light_position - cur_position).normalize();
    float dis = (light_position - cur_position).norm();
    float diffuse_light = light_intensity / (dis * dis) * fmax(0.0,light_direction * cur_norm);
    //specular light
    Vec3f view_direction = (eye_position - cur_position).normalize();
    Vec3f bisector = (view_direction + light_direction).normalize();
    float  specular_light = light_intensity / (dis * dis) * pow(fmax(0.0,cur_norm * bisector),5);
//    std::cout << diffuse_light << " " << specular_light << std::endl;
    TGAColor white = TGAColor(255,255,255,255);
    output_color = texture_color * (diffuse_light + specular_light);
//    std::cout << dis << " " << diffuse_light << " " << output_color << std::endl;
//    output_color = texture_color;
    return false;
}

Shader::~Shader() {

}
