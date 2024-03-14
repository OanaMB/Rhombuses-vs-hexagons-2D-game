#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace tobject2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill);
    Mesh* CreateStar(const std::string& name, glm::vec3 center, float raza_mare, float raza_mica,float z, glm::vec3 color);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 center, float raza, float coordz, glm::vec3 color);
    Mesh* CreateRomb(const std::string& name, glm::vec3 center, float raza_mare, float raza_mica, glm::vec3 color);
}
