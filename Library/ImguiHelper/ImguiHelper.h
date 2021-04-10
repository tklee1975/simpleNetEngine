#ifndef __SN_IMGUI_APP
#define __SN_IMGUI_APP

#define SN_IMGUI_APP_VERSION     "0.0.1"

#include "BaseImguiApp.h"
#include "SNShapeHelper.h"
#include "SNColorHelper.h"
#include "SNParticleSystem.h"

namespace simpleNet {


// https://developer.download.nvidia.com/cg/lerp.html
template<class T>
T lerp(T min, T max, double potion) {
    return min + potion * (max - min);
}



}   // end of namespace


#endif 
