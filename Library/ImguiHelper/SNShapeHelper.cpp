//
//  SNShapeHelper.c
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#include "SNShapeHelper.h"
namespace simpleNet {

void SNShapeHelper::drawTriangleAtCenter(
                        const ImVec2 &center,
                        const float &size,
                        const ImColor &color) {
    auto* drawList = ImGui::GetBackgroundDrawList();

    float halfSize = size * 0.5f;
    
    drawList->AddTriangleFilled(ImVec2(center.x, center.y-halfSize),
                                ImVec2(center.x - halfSize, center.y+halfSize),
                                ImVec2(center.x + halfSize, center.y+halfSize),
                                color);

}


void SNShapeHelper::drawRectAtCenter(
                        const ImVec2 &center,
                        const float &size,
                        const ImColor &color) {
    auto* drawList = ImGui::GetBackgroundDrawList();

    float halfSize = size * 0.5f;
    
    drawList->AddRectFilled(ImVec2(center.x - halfSize, center.y-halfSize),
                            ImVec2(center.x + halfSize, center.y+halfSize),
                            color);

}

void SNShapeHelper::drawCircleAtCenter(
                        const ImVec2 &center,
                        const float &radius,
                        const ImColor &color)
{
    auto* drawList = ImGui::GetBackgroundDrawList();

    drawList->AddCircleFilled(center, radius, color);
}


}
