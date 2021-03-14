//
//  SNBaseImageApp.hpp
//
//  Created by kenlee on 6/3/2021.
//

#ifndef SNBaseImageApp_H
#define SNBaseImageApp_H
#include <SDL.h>
#include "imgui.h"


namespace simpleNet {

class BaseImguiApp {
public:
    BaseImguiApp();
    ~BaseImguiApp();

    bool init();
    void run();
    void stopRun();
    
protected:  // implemented by the subclass
    ImVec4 _clearColor; // = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    // For implementation
    virtual void onEvent(SDL_Event &event);
    virtual void onRender();
    virtual void onUpdate(double delta);
    virtual void onInit();

    // Help methods
    bool getInputKey(SDL_Keycode key);
private:
    SDL_Window *_window = nullptr;
    SDL_GLContext _glContext = nullptr;
    bool _hasInit;
    bool _running;
    

    // For Initialization 
    
    bool initGLContext();
    bool initWindow();
    void initImgui();
    
    //
    void doUpdate();
    void doRender();
};


}



#endif /* SNBaseImageApp_H */
