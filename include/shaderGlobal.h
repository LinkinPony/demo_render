#ifndef __SHADER_GLOBAL_H__
#define __SHADER_GLOBAL_H__
//use to set global shader variable.
#include "geometry.h"
#include "matrix.h"
#include "model.h"

namespace ShaderGlobal{
    extern Matrix<float>M;//Matrix for transform
    extern Vec3f varying_vertex[3];// Write this in vertex shader, and it's read-only in fragment shader
    extern Vec2i varying_uv[3];
    extern Vec3f varying_norm[3];
    extern Model * model;
    extern float depth;//for z-buffer
    extern TGAColor texture_color;
    extern TGAColor output_color;
};

#endif //__SHADER_GLOBAL_H__