#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <time.h>
#include <windows.h>
using namespace std;


#include "lab_m1/Tema1/tema_transform2D.h"
#include "lab_m1/Tema1/tema_object2D.h"


using namespace std;
using namespace t1;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // mesh square and rectangle for play scene
    glm::vec3 corner = glm::vec3(0, 0, 0);
    squareSide = 120, width = 60, height = 440;
    color.r = 1.0f * 59 / 255;
    color.g = 1.0f * 227 / 255;
    color.b = 1.0f * 107 / 255;
    
    // squares
    Mesh* square_play = tobject2D::CreateSquare("square_play", corner, squareSide, glm::vec3(color.r, color.g, color.b), true);
    AddMeshToList(square_play);

    color.r = 0;
    color.g = 0;
    color.b = 0;

    Mesh* square_romb = tobject2D::CreateSquare("square_romb", corner, squareSide, glm::vec3(color.r, color.g, color.b), false);
    AddMeshToList(square_romb);

    // red square life
    color.r = 1.0f * 203 / 255;
    color.g = 1.0f * 3 / 255;
    color.b = 1.0f * 3 / 255; 
    squareSide = 80;
    Mesh* square_life = tobject2D::CreateSquare("square_life", corner, squareSide, glm::vec3(color.r, color.g, color.b), true);
    AddMeshToList(square_life);

    squareSide = 120;

    // rectangle  
    Mesh* rectangle1 = tobject2D::CreateRectangle("rectangle1", corner, width, height, glm::vec3(color.r, color.g, color.b), true);
    AddMeshToList(rectangle1);

    //pink star 
    color.r = 1;
    color.g = 0;
    color.b = 1.0f * 234 / 255; 
    Mesh* star_pink = tobject2D::CreateStar("star_pink", corner, 40, 15.2f, 3, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(star_pink);

    // grey star
    color.r = 1.0f * 146 / 255;
    color.g = 1.0f * 146 / 255;
    color.b = 1.0f * 146 / 255;
    Mesh* star_grey = tobject2D::CreateStar("star_grey", corner, 20, 7.6f, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(star_grey);

    // orange star
    color.r = 1.0f * 252 / 255;
    color.g = 1.0f * 94 / 255;
    color.b = 1.0f * 3 / 255;
    Mesh* star_orange = tobject2D::CreateStar("star_orange", corner, 40, 15.2f, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(star_orange);

    // blue star
    color.r = 1.0f * 3 / 255;
    color.g = 1.0f * 98 / 255;
    color.b = 1.0f * 252 / 255;
    Mesh* star_blue = tobject2D::CreateStar("star_blue", corner, 40, 15.2f, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(star_blue);

    // yellow star
    color.r = 1.0f * 252 / 255;
    color.g = 1.0f * 211 / 255;
    color.b = 1.0f * 3 / 255;
    Mesh* star_yellow = tobject2D::CreateStar("star_yellow", corner, 40, 15.2f, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(star_yellow);

    // purple star
    color.r = 1.0f * 169 / 255;
    color.g = 1.0f * 3 / 255;
    color.b = 1.0f * 252 / 255;
    Mesh* star_purple = tobject2D::CreateStar("star_purple", corner, 40, 15.2f, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(star_purple);

    // green hexagon
    color.r = 1.0f * 50 / 255;
    color.g = 1.0f * 168 / 255;
    color.b = 1.0f * 164 / 255;
    Mesh* hexagon_green = tobject2D::CreateHexagon("hexagon_green", corner, 27, 2, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(hexagon_green);

    // orange hexagon
    color.r = 1.0f * 252 / 255;
    color.g = 1.0f * 94 / 255;
    color.b = 1.0f * 3 / 255;
    Mesh* hexagon_orange = tobject2D::CreateHexagon("hexagon_orange", corner, 40, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(hexagon_orange);

    // blue hexagon
    color.r = 1.0f * 3 / 255;
    color.g = 1.0f * 98 / 255;
    color.b = 1.0f * 252 / 255;
    Mesh* hexagon_blue = tobject2D::CreateHexagon("hexagon_blue", corner, 40, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(hexagon_blue);

    // yellow hexagon
    color.r = 1.0f * 252 / 255;
    color.g = 1.0f * 211 / 255;
    color.b = 1.0f * 3 / 255;
    Mesh* hexagon_yellow = tobject2D::CreateHexagon("hexagon_yellow", corner, 40, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(hexagon_yellow);

    // purple hexagon
    color.r = 1.0f * 169 / 255;
    color.g = 1.0f * 3 / 255;
    color.b = 1.0f * 252 / 255;
    Mesh* hexagon_purple = tobject2D::CreateHexagon("hexagon_purple", corner, 40, 1, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(hexagon_purple);

    // orange romb
    color.r = 1.0f * 252 / 255;
    color.g = 1.0f * 94 / 255;
    color.b = 1.0f * 3 / 255;
    Mesh* romb_orange = tobject2D::CreateRomb("romb_orange", corner, 50, 20, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(romb_orange);

    // blue romb
    color.r = 1.0f * 3 / 255;
    color.g = 1.0f * 98 / 255;
    color.b = 1.0f * 252 / 255;
    Mesh* romb_blue = tobject2D::CreateRomb("romb_blue", corner, 50, 20, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(romb_blue);

    // yellow romb
    color.r = 1.0f * 252 / 255;
    color.g = 1.0f * 211 / 255;
    color.b = 1.0f * 3 / 255;
    Mesh* romb_yellow = tobject2D::CreateRomb("romb_yellow", corner, 50, 20, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(romb_yellow);

    // purple romb
    color.r = 1.0f * 169 / 255;
    color.g = 1.0f * 3 / 255;
    color.b = 1.0f * 252 / 255;
    Mesh* romb_purple = tobject2D::CreateRomb("romb_purple", corner, 50, 20, glm::vec3(color.r, color.g, color.b));
    AddMeshToList(romb_purple);

    // randomize time at which stars appear
    lastFrameTimeStars = glfwGetTime();
    lastFrameTimeEnemies = glfwGetTime();
    spawnTimeStars = getRandomFloat(7.0f, 13.0f);
    spawnTimeEnemies = getRandomFloat(4.0f, 7.0f);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    color.r = 1.0f * 51 / 255;
    color.g = 1.0f * 51 / 255;
    color.b = 1.0f * 51 / 255;
    glClearColor(color.r, color.g, color.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

float Tema1::getRandomFloat(float min, float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

void Tema1::InitPlaySpace(float deltaTimeSeconds) 
{
    // we put the rectangle 
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(10, 20);
    RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);

    // in order to put the squares at even distances, we calculate their positions
    coordinates.x = 10 + width + 30;
    coordinates.y = 20;
    int i = 1;
    coord_squares[i].x = coordinates.x;
    coord_squares[i].y = coordinates.y;
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coordinates.x, coordinates.y);
    RenderMesh2D(meshes["square_play"], shaders["VertexColor"], modelMatrix);

    linii_joc[0] = coordinates.y + squareSide / 2;

    for (i = 2; i <= 9; i++) {

        if (i % 3 == 1 && i != 1) {
            coordinates.y += squareSide + 40;
            coordinates.x = 10 + width + 30;
            linii_joc[i / 3] = coordinates.y + squareSide / 2;
        }
        else {
            coordinates.x += squareSide + 40;
        }

        coord_squares[i].x = coordinates.x;
        coord_squares[i].y = coordinates.y;

        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coordinates.x, coordinates.y);
        RenderMesh2D(meshes["square_play"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderGUI(float deltaTimeSeconds)
{
    // orange
    int coord_X = 40;
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X, 580);

    // coordonate folosite la drag and drop ca sa stim de unde incepem translate ul
    coord_squares_rombs["orange"].x = coord_X;
    coord_squares_rombs["orange"].y = 580;
    coord_squares_rombs["orange"].cost_stars = 1;
    RenderMesh2D(meshes["square_romb"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= ttransform2D::Translate(60, 60);
    RenderMesh2D(meshes["romb_orange"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X + 20, 560);
    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);


    // blue
    coord_X += squareSide + 60;
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X, 580);

    // coordonate folosite la drag and drop ca sa stim de unde incepem translate ul
    coord_squares_rombs["blue"].x = coord_X;
    coord_squares_rombs["blue"].y = 580;
    coord_squares_rombs["blue"].cost_stars = 2;
    RenderMesh2D(meshes["square_romb"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= ttransform2D::Translate(60, 60);
    RenderMesh2D(meshes["romb_blue"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X + 20, 560);
    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= ttransform2D::Translate(40, 0);
    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    // yellow
    coord_X += squareSide + 60;
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X, 580);

    // coordonate folosite la drag and drop ca sa stim de unde incepem translate ul
    coord_squares_rombs["yellow"].x = coord_X;
    coord_squares_rombs["yellow"].y = 580;
    coord_squares_rombs["yellow"].cost_stars = 2;
    RenderMesh2D(meshes["square_romb"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= ttransform2D::Translate(60, 60);
    RenderMesh2D(meshes["romb_yellow"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X + 20, 560);
    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= ttransform2D::Translate(40, 0);
    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    // purple
    coord_X += squareSide + 60;
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X, 580);

    // coordonate folosite la drag and drop ca sa stim de unde incepem translate ul
    coord_squares_rombs["purple"].x = coord_X;
    coord_squares_rombs["purple"].y = 580;
    coord_squares_rombs["purple"].cost_stars = 3;
    RenderMesh2D(meshes["square_romb"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= ttransform2D::Translate(60, 60);
    RenderMesh2D(meshes["romb_purple"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X + 20, 560);
    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= ttransform2D::Translate(40, 0);
    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= ttransform2D::Translate(40, 0);
    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);


    // lives
    int coord_X_copy;
    coord_X += squareSide + 60;
    coord_X_copy = coord_X;
    modelMatrix = glm::mat3(1);
    modelMatrix *= ttransform2D::Translate(coord_X, 600);
    squareSide = 80;
    for (int i = 1; i <= number_lives; i++) {
        RenderMesh2D(meshes["square_life"], shaders["VertexColor"], modelMatrix);
        coord_X = squareSide + 40;        
        modelMatrix *= ttransform2D::Translate(coord_X, 0);
    }
    squareSide = 120;

    // stars
    float x_coord_star = coord_X_copy + 20;
    float y_coord_star = 580;

    for (int i = 0; i < number_stars; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(x_coord_star, y_coord_star);
        RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);      
        
        if (i % 12 == 11) {
            x_coord_star = coord_X_copy + 20;
            y_coord_star -= 40;
        }
        else {
            x_coord_star += 40;
        }
    }

}

void Tema1::ShootProjectileAnimation(float deltaTimeSeconds) {
    
    // proiectile curente
    for (auto itr = projectiles.begin(); itr != projectiles.end();)
    {
        if (itr->second.translateX <= 1400) {

            modelMatrix = glm::mat3(1);
            modelMatrix *= ttransform2D::Translate(itr->second.x, itr->second.y);

            itr->second.translateX += deltaTimeSeconds * 300;
            itr->second.angularStep -= deltaTimeSeconds * 5;

            modelMatrix *= ttransform2D::Translate(itr->second.translateX, 0);
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Rotate(itr->second.angularStep);
            modelMatrix *= ttransform2D::Translate(0, 0);

            std::string name = "star_";
            std::string result = name + itr->second.type;
            RenderMesh2D(meshes[result], shaders["VertexColor"], modelMatrix);
            ++itr;
        }
        else {
            itr = projectiles.erase(itr);
        }
    }
}

void Tema1::KillEnemyAnimation(float deltaTimeSeconds, int number_enemies, std::string type, glm::vec2 coords) {
    if (type == "orange") {
        // animatie disparitie hexa
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coords[0], coords[1]);

        kill_enemies[number_enemies].scaleX -= deltaTimeSeconds * 0.8;
        kill_enemies[number_enemies].scaleY -= deltaTimeSeconds * 0.8;


        if (kill_enemies[number_enemies].scaleX > 0.0f && kill_enemies[number_enemies].scaleY > 0.0f) {
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Scale(kill_enemies[number_enemies].scaleX, kill_enemies[number_enemies].scaleY);
            modelMatrix *= ttransform2D::Translate(0, 0);
            RenderMesh2D(meshes["hexagon_green"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["hexagon_orange"], shaders["VertexColor"], modelMatrix);
        }
        else {
            kill_enemies[number_enemies].kill = false;
        }
    }

    if (type == "blue") {
        // animatie disparitie hexa
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coords[0], coords[1]);

        kill_enemies[number_enemies].scaleX -= deltaTimeSeconds * 0.8;
        kill_enemies[number_enemies].scaleY -= deltaTimeSeconds * 0.8;


        if (kill_enemies[number_enemies].scaleX > 0.0f && kill_enemies[number_enemies].scaleY > 0.0f) {
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Scale(kill_enemies[number_enemies].scaleX, kill_enemies[number_enemies].scaleY);
            modelMatrix *= ttransform2D::Translate(0, 0);
            RenderMesh2D(meshes["hexagon_green"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["hexagon_blue"], shaders["VertexColor"], modelMatrix);
        }
        else {
            kill_enemies[number_enemies].kill = false;
        }
    }

    if (type == "yellow") {
        // animatie disparitie hexa
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coords[0], coords[1]);

        kill_enemies[number_enemies].scaleX -= deltaTimeSeconds * 0.8;
        kill_enemies[number_enemies].scaleY -= deltaTimeSeconds * 0.8;


        if (kill_enemies[number_enemies].scaleX > 0.0f && kill_enemies[number_enemies].scaleY > 0.0f) {
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Scale(kill_enemies[number_enemies].scaleX, kill_enemies[number_enemies].scaleY);
            modelMatrix *= ttransform2D::Translate(0, 0);
            RenderMesh2D(meshes["hexagon_green"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["hexagon_yellow"], shaders["VertexColor"], modelMatrix);
        }
        else {
            kill_enemies[number_enemies].kill = false;
        }
    }

    if (type == "purple") {
        // animatie disparitie hexa
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coords[0], coords[1]);

        kill_enemies[number_enemies].scaleX -= deltaTimeSeconds * 0.8;
        kill_enemies[number_enemies].scaleY -= deltaTimeSeconds * 0.8;


        if (kill_enemies[number_enemies].scaleX > 0.0f && kill_enemies[number_enemies].scaleY > 0.0f) {
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Scale(kill_enemies[number_enemies].scaleX, kill_enemies[number_enemies].scaleY);
            modelMatrix *= ttransform2D::Translate(0, 0);
            RenderMesh2D(meshes["hexagon_green"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["hexagon_purple"], shaders["VertexColor"], modelMatrix);
        }
        else {
            kill_enemies[number_enemies].kill = false;
        }
    }

}

void Tema1::KillRombAnimation(float deltaTimeSeconds, int number_romb, std::string type, glm::vec2 coords) {
    if (type == "orange") {
        // animatie disparitie romb
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coords[0], coords[1]);

        kill_romb[number_romb].scaleX -= deltaTimeSeconds * 0.8;
        kill_romb[number_romb].scaleY -= deltaTimeSeconds * 0.8;


        if (kill_romb[number_romb].scaleX > 0.0f && kill_romb[number_romb].scaleY > 0.0f) {
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Scale(kill_romb[number_romb].scaleX, kill_romb[number_romb].scaleY);
            modelMatrix *= ttransform2D::Translate(0, 0);
            RenderMesh2D(meshes["romb_orange"], shaders["VertexColor"], modelMatrix);
           
        }
        else {
            kill_romb[number_romb].kill = false;
        }
    }

    if (type == "blue") {
        // animatie disparitie romb
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coords[0], coords[1]);

        kill_romb[number_romb].scaleX -= deltaTimeSeconds * 0.8;
        kill_romb[number_romb].scaleY -= deltaTimeSeconds * 0.8;


        if (kill_romb[number_romb].scaleX > 0.0f && kill_romb[number_romb].scaleY > 0.0f) {
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Scale(kill_romb[number_romb].scaleX, kill_romb[number_romb].scaleY);
            modelMatrix *= ttransform2D::Translate(0, 0);
            RenderMesh2D(meshes["romb_blue"], shaders["VertexColor"], modelMatrix);

        }
        else {
            kill_romb[number_romb].kill = false;
        }
    }

    if (type == "yellow") {
        // animatie disparitie romb
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coords[0], coords[1]);

        kill_romb[number_romb].scaleX -= deltaTimeSeconds * 0.8;
        kill_romb[number_romb].scaleY -= deltaTimeSeconds * 0.8;


        if (kill_romb[number_romb].scaleX > 0.0f && kill_romb[number_romb].scaleY > 0.0f) {
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Scale(kill_romb[number_romb].scaleX, kill_romb[number_romb].scaleY);
            modelMatrix *= ttransform2D::Translate(0, 0);
            RenderMesh2D(meshes["romb_yellow"], shaders["VertexColor"], modelMatrix);

        }
        else {
           
            kill_romb[number_romb].kill = false;
        }
    }

    if (type == "purple") {
        // animatie disparitie romb
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(coords[0], coords[1]);

        kill_romb[number_romb].scaleX -= deltaTimeSeconds * 0.8;
        kill_romb[number_romb].scaleY -= deltaTimeSeconds * 0.8;


        if (kill_romb[number_romb].scaleX > 0.0f && kill_romb[number_romb].scaleY > 0.0f) {
            modelMatrix *= ttransform2D::Translate(0, 0);
            modelMatrix *= ttransform2D::Scale(kill_romb[number_romb].scaleX, kill_romb[number_romb].scaleY);
            modelMatrix *= ttransform2D::Translate(0, 0);
            RenderMesh2D(meshes["romb_purple"], shaders["VertexColor"], modelMatrix);

        }
        else {
            kill_romb[number_romb].kill = false;
        }
    }
}

void Tema1::StarSystem() {
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTimeStars;
    lastFrameTimeStars = currentFrameTime;

    elapsedTimeStars += deltaTime;

    if (elapsedTimeStars >= spawnTimeStars) {

        for (int i = 0; i < 3; i++) {
            stars[counter_stars].x = getRandomFloat(0.0f, 1280.0f);
            stars[counter_stars].y = getRandomFloat(0.0f, 720.0f);
            stars[counter_stars].pos_X_poz = raza_stea;
            stars[counter_stars].pos_Y_poz = raza_stea;
            stars[counter_stars].pos_X_neg = raza_stea;
            stars[counter_stars].pos_Y_neg = raza_stea;
            counter_stars++;
        }
        elapsedTimeStars = 0.0;
        spawnTimeStars = getRandomFloat(7.0f, 13.0f);
    }

    // show pink stars
    for (auto& itr : stars)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(itr.second.x, itr.second.y);
        RenderMesh2D(meshes["star_pink"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::EnemyAttack(float deltaTimeSeconds)
{
    // enemy attacks rectangle
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTimeEnemies;
    lastFrameTimeEnemies = currentFrameTime;

    elapsedTimeEnemies += deltaTime;

    if (elapsedTimeEnemies >= spawnTimeEnemies) {
        enemies[counter_enemies].x = 1310;

        srand(time(NULL));
        int RanIndex = rand() % 3;
        enemies[counter_enemies].y = linii_joc[RanIndex];

        std::string arraytype[4] = { "orange", "blue", "yellow", "purple" };
        int RanIndex1 = rand() % 4;
        enemies[counter_enemies].type = arraytype[RanIndex1];


        counter_enemies++;
        elapsedTimeEnemies = 0.0;
        spawnTimeEnemies = getRandomFloat(4.0f, 7.0f);
    }

    for (auto itr = enemies.begin(); itr != enemies.end();) {
        if (itr->second.distanceRectangle >= raza_hexagon_mare) {

            float coordonata_hexagon = itr->second.x + itr->second.translateX;
            itr->second.distanceRectangle = glm::distance(10 + width / 2, coordonata_hexagon);
            ++itr;
        } else {
            number_lives--;
            itr = enemies.erase(itr);
            if (number_lives == 0) {
                exit(0);
            }
        }
    }
    
    // check if being attacked by a projectile
    for (auto itr = enemies.begin(); itr != enemies.end();) {
        float coordonata_x_projectile = 0, translateX_projectile = 0;
        int projectile_id;

        for (auto& itr1 : projectiles) {
            if (itr1.second.y == itr->second.y && itr1.second.type == itr->second.type) {
                coordonata_x_projectile = itr1.second.x;
                translateX_projectile = itr1.second.translateX;
                projectile_id = itr1.first;
                itr->second.detected = true;
                break;

            }
        }

        // algoritm find the distance
        if (itr->second.detected == true) {
            if (itr->second.distance_projectile >= raza_hexagon_mare + raza_romb - 20 && itr->second.hearts_left > 0) {

                float coordonata_projectile = coordonata_x_projectile + translateX_projectile;
                float coordonata_enemy = itr->second.x + itr->second.translateX;
                itr->second.distance_projectile = glm::distance(coordonata_enemy, coordonata_projectile);
                ++itr;
            }
            else if (itr->second.distance_projectile < raza_hexagon_mare + raza_romb - 20 && itr->second.hearts_left > 0) {
                itr->second.hearts_left--;
                itr->second.distance_projectile = 1350;
                int romb_id = projectiles[projectile_id].romb_id;
                projectiles.erase(projectile_id);
                itr->second.detected = false;

                if (itr->second.hearts_left == 0) {

                    enemy_identifier = itr->first;
                    kill_enemies[enemy_identifier].kill = true;
                    kill_enemies[enemy_identifier].scaleX = 1;
                    kill_enemies[enemy_identifier].scaleY = 1;
                    kill_enemies[enemy_identifier].type_hexagon = itr->second.type;
                    kill_enemies[enemy_identifier].coordinates = glm::vec2(itr->second.x + itr->second.translateX, itr->second.y);

                    itr = enemies.erase(itr);
                    rombs[romb_id].detected = false;
                    rombs[romb_id].distance_from_enemy = 1350;
                    rombs[romb_id].counter_projectiles = 3;
                }
            }
        } else {
            ++itr;
        }
       
        
    }

    // show all enemies on the screen
    for (auto& itr : enemies)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(itr.second.x, itr.second.y);

        itr.second.translateX -= deltaTimeSeconds * 70;
        modelMatrix *= ttransform2D::Translate(itr.second.translateX, 0);

        std::string name = "hexagon_";
        std::string result = name + itr.second.type;

        RenderMesh2D(meshes["hexagon_green"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes[result], shaders["VertexColor"], modelMatrix);
    }

    // kill enemies
    for (auto itr = kill_enemies.begin(); itr != kill_enemies.end();) {
        if (itr->second.kill) {
            KillEnemyAnimation(deltaTimeSeconds, itr->first, itr->second.type_hexagon, itr->second.coordinates);
            ++itr;
        }
        else {
            itr = kill_enemies.erase(itr);
        }
    }

}

void Tema1::SpawnProjectiles(float deltaTimeSeconds, int romb_id) {
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - rombs[romb_id].lastFrameTimeProjectiles;
    rombs[romb_id].lastFrameTimeProjectiles = currentFrameTime;

    rombs[romb_id].elapsedTimeProjectiles += deltaTime;

    if (rombs[romb_id].elapsedTimeProjectiles >= rombs[romb_id].spawnTimeProjectiles && rombs[romb_id].counter_projectiles > 0) {
        projectiles[counter_projectiles].x = rombs[romb_id].x + 60;
        projectiles[counter_projectiles].y = rombs[romb_id].y;
        projectiles[counter_projectiles].type = rombs[romb_id].type;
        projectiles[counter_projectiles].romb_id = romb_id;
        counter_projectiles++;
        rombs[romb_id].counter_projectiles--;
        rombs[romb_id].elapsedTimeProjectiles = 0.0;
        rombs[romb_id].spawnTimeProjectiles = 3.0f;
    }

}


void Tema1::RombSystemCollision(float deltaTimeSeconds) {
    // coliziune romburi-enemy
    for (auto itr = rombs.begin(); itr != rombs.end();)
    {
        float coordonata_x_enemy = 0, translateX_enemy = 0;
        std::string type_hexagon;

        for (auto& itr1 : enemies) {
            if (itr1.second.y == itr->second.y) {
                coordonata_x_enemy = itr1.second.x;
                translateX_enemy = itr1.second.translateX;
                type_hexagon = itr1.second.type;
                itr->second.detected = true;
                break;

            }
        }

        if (itr->second.detected == true) {

            if (type_hexagon == itr->second.type) {
                SpawnProjectiles(deltaTimeSeconds, itr->first);
            }

            if (itr->second.distance_from_enemy >= raza_hexagon_mare + raza_romb) {

                float coordonata_hexagon = coordonata_x_enemy + translateX_enemy;
                itr->second.distance_from_enemy = glm::distance(coordonata_hexagon, itr->second.x);
                ++itr;
            }
            else {
                kill_romb[itr->first].kill = true;
                kill_romb[itr->first].scaleX = 1;
                kill_romb[itr->first].scaleY = 1;
                kill_romb[itr->first].type_romb = itr->second.type;
                kill_romb[itr->first].coordinates = glm::vec2(itr->second.x, itr->second.y);

                coord_squares[itr->second.number_square].occupied = false;
                itr = rombs.erase(itr);

            }
        }
        else {
            ++itr;
        }

    }

    // kill rombs
    for (auto itr = kill_romb.begin(); itr != kill_romb.end();) {
        if (itr->second.kill) {
            KillRombAnimation(deltaTimeSeconds, itr->first, itr->second.type_romb, itr->second.coordinates);
            ++itr;
        }
        else {
            itr = kill_romb.erase(itr);
        }
    }


    // show rombs
    for (auto& itr : rombs)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= ttransform2D::Translate(itr.second.x, itr.second.y);
        std::string name = "romb_";
        std::string result = name + itr.second.type;
        RenderMesh2D(meshes[result], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::Update(float deltaTimeSeconds)
{
    // Play Space (the squares)
    InitPlaySpace(deltaTimeSeconds);
    // GUI
    RenderGUI(deltaTimeSeconds);
    
    // stars appear randomly
    StarSystem();

    //shoot all projectiles
    ShootProjectileAnimation(deltaTimeSeconds);

    //enemy attacks rectangle
    EnemyAttack(deltaTimeSeconds);

    // rombs show and collision system
    RombSystemCollision(deltaTimeSeconds);

    // for drag and drop in case we select a romb
    if (mousepressed) {
        std::string name = "romb_";
        std::string result = name + type_romb_selected;
        RenderMesh2D(meshes[result], shaders["VertexColor"], modelMatrix1);
    }
}


void Tema1::FrameEnd()
{

}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    int Y_scena_joc = 720 - mouseY;
    // Add mouse move event
    if (mousepressed) {
        modelMatrix1 = glm::mat3(1);
        modelMatrix1 *= ttransform2D::Translate(mouseX, Y_scena_joc);
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    int Y_scena_joc = 720 - mouseY;
    bool star_found = false;
    // GLFW_MOUSE_BUTTON_2 = mouse left
    if (button == GLFW_MOUSE_BUTTON_2) {

        if (number_stars <= 35) {
            for (auto itr = stars.begin(); itr != stars.end();) {
                if (mouseX >= (itr->second.x - itr->second.pos_X_neg) && mouseX <= (itr->second.x + itr->second.pos_X_poz) &&
                    Y_scena_joc >= (itr->second.y - itr->second.pos_Y_neg) && Y_scena_joc <= (itr->second.y + itr->second.pos_Y_poz)) {
                    itr = stars.erase(itr);
                    star_found = true;
                    number_stars++;
                }
                else {
                    ++itr;
                }
            }
        }
        else {
            for (auto itr = stars.begin(); itr != stars.end();) {
                if (mouseX >= (itr->second.x - itr->second.pos_X_neg) && mouseX <= (itr->second.x + itr->second.pos_X_poz) &&
                    Y_scena_joc >= (itr->second.y - itr->second.pos_Y_neg) && Y_scena_joc <= (itr->second.y + itr->second.pos_Y_poz)) {
                    itr = stars.erase(itr);
                    star_found = true;
                }
                else {
                    ++itr;
                }
            }
        }

        if (star_found == false) {
            for (auto& itr : coord_squares_rombs) {
                if (mouseX >= itr.second.x && mouseX <= (itr.second.x + squareSide) &&
                    Y_scena_joc >= itr.second.y && Y_scena_joc <= (itr.second.y + squareSide)) {
                    if (number_stars - itr.second.cost_stars >= 0) {
                        modelMatrix1 = glm::mat3(1);
                        modelMatrix1 *= ttransform2D::Translate(mouseX, Y_scena_joc);
                        mousepressed = true;
                        type_romb_selected = itr.first;
                    }
                }
            }
        }

        star_found = false;
        
    }

    // GLFW_MOUSE_BUTTON_3 = mouse right
    if (button == GLFW_MOUSE_BUTTON_3) {

        for (auto& itr : coord_squares) {
            if (mouseX >= itr.second.x && mouseX <= (itr.second.x + squareSide) &&
                Y_scena_joc >= itr.second.y && Y_scena_joc <= (itr.second.y + squareSide)) {
                    for (auto itr1 = rombs.begin(); itr1 != rombs.end();) {
                        if (itr1->second.number_square == itr.first) {

                            romb_identifier = itr1->first;
                            kill_romb[romb_identifier].kill = true;
                            kill_romb[romb_identifier].scaleX = 1;
                            kill_romb[romb_identifier].scaleY = 1;
                            kill_romb[romb_identifier].type_romb = itr1->second.type;
                            kill_romb[romb_identifier].coordinates = glm::vec2(itr1->second.x, itr1->second.y);

                            itr1 = rombs.erase(itr1);
                            itr.second.occupied = false;

                        }
                        else {
                            ++itr1;
                        }
                    }
            }
            
        }
    }

}

void Tema1::cost_romb(std::string type) {
    
    if (type == "orange") {
        number_stars -= 1;
    }
    if (type == "blue") {
        number_stars -= 2;
    }
    if (type == "yellow") {
        number_stars -= 2;
    }
    if (type == "purple") {
        number_stars -= 3;
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    int Y_scena_joc = 720 - mouseY;

    if (button == GLFW_MOUSE_BUTTON_2 && mousepressed) {
        mousepressed = false;

        for (auto& itr : coord_squares) {
            if (mouseX >= itr.second.x && mouseX <= (itr.second.x + squareSide) &&
                Y_scena_joc >= itr.second.y && Y_scena_joc <= (itr.second.y + squareSide) && (itr.second.occupied == false)) {
                rombs[counter_rombs].x = itr.second.x + squareSide / 2;
                rombs[counter_rombs].y = itr.second.y + squareSide / 2;
                rombs[counter_rombs].number_square = itr.first;
                rombs[counter_rombs].type = type_romb_selected;
                itr.second.occupied = true;
                counter_rombs++;
                cost_romb(type_romb_selected);
            }
        }

    }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}