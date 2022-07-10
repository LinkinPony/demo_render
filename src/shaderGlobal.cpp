#include "../include/shaderGlobal.h"

namespace ShaderGlobal{
    Matrix<float>M = Matrix<float>(4,4);//Matrix for transform
    Vec3f varying_vertex[3] = {};// Write this in vertex shader, and it's read-only in fragment shader
    Vec2i varying_uv[3] = {};
    Vec3f varying_norm[3] = {};
    Model * model = nullptr;
    float depth = 0;//for z-buffer
    TGAColor texture_color;
    TGAColor output_color;
    Vec3f light_position;
    Vec3f eye_position;
    float light_intensity;
}