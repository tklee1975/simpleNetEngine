//
//  TestGuiApp.h
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#ifndef TestGuiApp_h
#define TestGuiApp_h

#include <stdio.h>
#include <ImguiHelper.h>

using namespace simpleNet;


class SampleGuiApp1 : public BaseImguiApp {
public:
    virtual void onInit();
    virtual void onUpdate(double delta);
};



class SampleGuiApp2: public BaseImguiApp {
public:
    virtual void onInit();
    virtual void onUpdate(double delta);
private:
    ImVec2 _pos;
    
    void drawShapes();
    void handleInput(double delta);
    
};

#endif /* TestGuiApp_h */
