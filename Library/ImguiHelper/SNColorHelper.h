//
//  SNColorHelper.h
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#ifndef SNColorHelper_h
#define SNColorHelper_h

#include <stdio.h>
#include "imgui.h"

namespace simpleNet {
    const ImColor ColorBlack= ImColor(0, 0, 0);
    const ImColor ColorWhite = ImColor(255, 255, 255);
    const ImColor ColorYellow = ImColor(255, 255, 0);
    const ImColor ColorRed = ImColor(255, 0, 0);
    const ImColor ColorGreen = ImColor(0, 255, 0);
    const ImColor ColorBlue = ImColor(0, 0, 255);
    const ImColor ColorPurple = ImColor(255, 0, 255);
}

//#define SN_RED              ImColor(255, 0, 0)
//#define SN_GREEN            ImColor(0, 255, 0)
//#define SN_BLUE             ImColor(0, 0, 255)
//#define SN_YELLOW           ImColor(255, 255, 0)
//#define SN_PURPLE           ImColor(255, 0, 255)

#endif /* SNColorHelper_h */
