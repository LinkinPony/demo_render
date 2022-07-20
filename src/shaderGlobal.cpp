#include "../include/shaderGlobal.h"

namespace ShaderGlobal{
    Mat4f M;//Matrix for transform
    Matrix<float>M2;
    Vec3f varying_vertex[3] = {};// Write this in vertex shader, and it's read-only in fragment shader
    Vec2f varying_uv[3] = {}; //uv now is in range [0,1]
    Vec3f varying_norm[3] = {};
    Model * model = nullptr;
    float depth = 0;//for z-buffer
    TGAColor texture_color;
    TGAColor output_color;
    Vec3f light_position;
    Vec3f eye_position;
    float light_intensity;
    Drawer * current_drawer;//TODO: change this stupid code
}