//
//  SNShapeHelper.h
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#ifndef SNShapeHelper_h
#define SNShapeHelper_h

#include <stdio.h>


#include "imgui.h"


namespace simpleNet {

class SNShapeHelper {
public:
    static void drawTriangleAtCenter(
                            const ImVec2 &center,
                            const float &size,
                            const ImColor &color);
    
    
    static void drawRectAtCenter(
                            const ImVec2 &center,
                            const float &size,
                            const ImColor &color);
    
    static void drawCircleAtCenter(
                            const ImVec2 &center,
                            const float &radius,
                                   const ImColor &color);
    
};
}




#endif /* SNShapeHelper_h */
