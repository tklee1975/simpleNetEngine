//
//  SNParticle.cpp
//  SimpleNet
//
//  Created by kenlee on 10/4/2021.
//

#include "SNParticleSystem.h"
#include "ImguiHelper.h"

namespace simpleNet {

#pragma mark - Particle
SNParticle::SNParticle(float _duration)
: color(255, 255, 255, 255)
, pos(100, 100)
, speed(0, 0)
, duration(_duration)
{
    _life = duration;
}

void SNParticle::onUpdate(float delta) {
    
    _life = _life - delta;   // /????
    
    if(isAlive() == false) {
        return;
    }
    //LOG("2 life: %f/%f/%f/%p", _life, duration, delta, this);
    color.Value.w = lerp(0.0, 1.0, _life/duration);
    //LOG("2 life: alpha=%f", color.Value.w);
}

void SNParticle::onRender() {
    if(isAlive() == false) {
        return;
    }

    SNShapeHelper::drawCircleAtCenter(pos, size, color);
}

#pragma mark - Particle System
void SNParticleSystem::onUpdate(float delta)
{
    //LOG("Particle List: %d", _particleList.size());
    for(SNParticle & particle : _particleList) {
        particle.onUpdate(delta);
    }
    
    removeDiedParticle();
    
    onRender();
}

void SNParticleSystem::onRender()
{
    for(SNParticle &particle : _particleList) {
        particle.onRender();
    }
}

void SNParticleSystem::addParticle(SNParticle particle)
{
    LOG("particle is added!");
    _particleList.push_back(particle);
}

//https://stackoverflow.com/questions/8628951/remove-elements-of-a-vector-inside-the-loop
void SNParticleSystem::removeDiedParticle()
{
    auto it = _particleList.begin();
    
    for(;it != _particleList.end(); ) {
        if(it->isAlive()){
            it++;
            continue;
        }
        _particleList.erase(it);
    }
}

} // End of simpleNet
