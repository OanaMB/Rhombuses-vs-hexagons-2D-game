#include "lab_m1/Tema1/tema_object2D.h"
#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <cmath>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* tobject2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* tobject2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* tobject2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float raza_mare,
    float raza_mica,
    float z,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(raza_mare * cos(18 * 3.14/180), raza_mare * sin(18 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mica * cos(54 * 3.14 / 180), raza_mica * sin(54 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mare * cos(90 * 3.14 / 180), raza_mare * sin(90 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mica * cos(126 * 3.14 / 180), raza_mica * sin(126 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mare * cos(162 * 3.14 / 180), raza_mare * sin(162 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mica * cos(198 * 3.14 / 180), raza_mica * sin(198 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mare * cos(234 * 3.14 / 180), raza_mare * sin(234 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mica * cos(270 * 3.14 / 180), raza_mica * sin(270 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mare * cos(306 * 3.14 / 180), raza_mare * sin(306 * 3.14 / 180), z), color),
        VertexFormat(center + glm::vec3(raza_mica * cos(342 * 3.14 / 180), raza_mica * sin(342 * 3.14 / 180), z), color)
    };

    std::vector<unsigned int> indices = { 
        0, 1, 9, 
        2, 3, 1, 
        4, 5, 3,
        6, 7, 5,
        8, 9, 7,
        1, 5, 7,
        1, 3, 5,
        1, 7, 9   
    };

    Mesh* star = new Mesh(name);
    star->InitFromData(vertices, indices);
    return star;
}

Mesh* tobject2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float raza,
    float coordz,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(raza * cos(45 * 3.14 / 180), raza * sin(45 * 3.14 / 180), coordz), color),
        VertexFormat(center + glm::vec3(raza * cos(105 * 3.14 / 180), raza * sin(105 * 3.14 / 180), coordz), color),
        VertexFormat(center + glm::vec3(raza * cos(165 * 3.14 / 180), raza * sin(165 * 3.14 / 180), coordz), color),
        VertexFormat(center + glm::vec3(raza * cos(225 * 3.14 / 180), raza * sin(225 * 3.14 / 180), coordz), color),
        VertexFormat(center + glm::vec3(raza * cos(285 * 3.14 / 180), raza * sin(285 * 3.14 / 180), coordz), color),
        VertexFormat(center + glm::vec3(raza * cos(345 * 3.14 / 180), raza * sin(345 * 3.14 / 180), coordz), color)
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5
    };

    Mesh* star = new Mesh(name);
    star->InitFromData(vertices, indices);
    return star;
}


Mesh* tobject2D::CreateRomb(
    const std::string& name,
    glm::vec3 center,
    float raza_mare,
    float raza_mica,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, raza_mare, 1), color),
        VertexFormat(center + glm::vec3(-raza_mica, 0, 1), color),
        VertexFormat(center + glm::vec3(0, -raza_mare, 1), color),
        VertexFormat(center + glm::vec3(raza_mica * 0.8, -raza_mica * 0.6, 1), color),
        VertexFormat(center + glm::vec3(raza_mare, -raza_mica * 0.6, 1), color),
        VertexFormat(center + glm::vec3(raza_mare, raza_mica * 0.6, 1), color),
        VertexFormat(center + glm::vec3(raza_mica * 0.8, raza_mica * 0.6, 1), color)
    };

    std::vector<unsigned int> indices = {
        0, 1, 6,
        6, 1, 3,
        1, 2, 3,
        3, 4, 5,
        5, 6, 3
    };

    Mesh* star = new Mesh(name);
    star->InitFromData(vertices, indices);
    return star;
}