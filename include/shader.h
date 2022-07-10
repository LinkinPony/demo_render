#ifndef __SHADER_H__
#define __SHADER_H__
#include "shaderGlobal.h"
#include "const.h"
//This is just a sketch with garbage
class Shader{
public:
    virtual ~Shader();
    virtual void vertex(int iface) = 0;
    virtual bool fragment(int x,int y) = 0;
};
class Bling_Phong : public Shader{
public:
    void vertex(int iface);
    bool fragment(int x,int y);
};
#endif //__SHADER_H__ 