#pragma once

#include "components/simple_scene.h"
#include <string>

namespace m1
{
    class Lab1 : public gfxc::SimpleScene
    {
     public:
        Lab1();
        ~Lab1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // TODO(student): Class variables go here
        GLfloat red = 0, green = 0, blue = 0;
        glm::vec3 colours = glm::vec3(0,0,0);
        glm::vec3 position = glm::vec3(0, 0, 0);
        std::string currentstring1 = "box";
        GLint index = 1;
        glm::vec3 position_sphere = glm::vec3(1.5, 0, 0);
        float unghi = 0;
        float raza = 1.5;
    };
}   // namespace m1
