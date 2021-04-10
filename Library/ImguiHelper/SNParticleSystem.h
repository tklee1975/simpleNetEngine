//
//  SNParticle.hpp
//  SimpleNet
//
//  Created by kenlee on 10/4/2021.
//

#pragma once

#include "imgui.h"
#include <simpleNet/CoreLib.h>

namespace simpleNet {

class SNParticle {
public:
    ImVec2 pos;
    float duration = 0;            // seconds
    double size = 10;
    ImColor color;
    ImVec2 speed;
    
    SNParticle(float _duration);
    
    virtual void onUpdate(float delta);
    virtual void onRender();
    
    bool isAlive() { return _life > 0; }
protected:
    float _life;
};

class SNParticleSystem : NonCopyable {
public:
    SNParticleSystem() {}
    virtual ~SNParticleSystem() {}            // ken: must need virtual destructor??

    void addParticle(SNParticle particle);  // ken: should use reference here??
    virtual void onUpdate(float delta);
    virtual void onRender();
    
    
protected:
    SNVector<SNParticle> _particleList;
    
    void removeDiedParticle();
};


} // End of simpleNet

