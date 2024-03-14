#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <random>
#include <map>
#include <cmath>

using namespace std;
using namespace u1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    // INITIALIZE CAMERA
    camera = new implementedTema2::CameraTema2();    
    camera->Set(glm::vec3(0, 0.75f, -2.f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    
    // INITIALIZE DIRECTIONS
    dir = glm::normalize(glm::vec3(0,0,1));
    dir_tun = glm::normalize(glm::vec3(0, 0, 1));

    // INITIALIZE BUILDINGS
    srand(time(NULL));
    number_buildings = GetRandomNumberInRange(30, 40);

    for (int i = 0; i < number_buildings; i++) {
        buildings[i].type = rand() % 3 + 1;
        float x[2] = { getRandomFloat(-39.f,-2),  getRandomFloat(2, 39.f) };
        int RandInt1 = rand() % 2;
        float z[2] = { getRandomFloat(-39.f,-2),  getRandomFloat(2, 39.f) };
        int RandInt2 = rand() % 2;
        buildings[i].position = glm::vec3(x[RandInt1], 0, z[RandInt2]);
    }

    // INITIALIZE BAD TANKS
    srand(time(NULL));
    number_badtanks = GetRandomNumberInRange(20, 25);

    for (int i = 0; i < number_badtanks; i++) {
        float x[2] = { getRandomFloat(-30.7f,-2),  getRandomFloat(2, 30.7f) };
        int RandInt1 = rand() % 2;
        float z[2] = { getRandomFloat(-30.7f,-2),  getRandomFloat(2, 30.7f) };
        int RandInt2 = rand() % 2;
        badtanks[i].translatesenile += glm::vec3(x[RandInt1], 0, z[RandInt2]);
        badtanks[i].translatecorp += glm::vec3(x[RandInt1], 0, z[RandInt2]);
        badtanks[i].translateturela += glm::vec3(x[RandInt1], 0, z[RandInt2]);
        badtanks[i].translatetun += glm::vec3(x[RandInt1], 0, z[RandInt2]);
        badtanks[i].elapsedtime = GetRandomNumberInRange(30, 60);
        MovementState vec[4] = { MovementState::GoingForward, MovementState::GoingBackward, MovementState::InPlaceRotationLeft, MovementState::InPlaceRotationRight};
        badtanks[i].movement = vec[rand() % 4];
    }

    {
        Mesh* mesh = new Mesh("ground");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("proiectil");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("senile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "Senile.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "Tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "Corp.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("turela");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "Turela.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("bloc1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "Bloc1.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("bloc2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "Bloc2.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("bloc3");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "Bloc3.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("Tema2Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.369f, 0.671f, 0.8f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Buildings(float deltaTimeSeconds) {
    // show buildings
    
    for (int i = 0; i < number_buildings; i++) {
        
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::translate(modelMatrix, buildings[i].position);
       std::string name = "bloc";
       name = name + std::to_string(buildings[i].type);
       if(buildings[i].type == 1) {
           RenderSimpleMesh(meshes[name], shaders["Tema2Shader"], modelMatrix, glm::vec3(1, 0.082f, 0), 100.f);
       }
       if (buildings[i].type == 2) {
           RenderSimpleMesh(meshes[name], shaders["Tema2Shader"], modelMatrix, glm::vec3(1, 0.984f, 0), 100.f);
       }
       if (buildings[i].type == 3) {
           RenderSimpleMesh(meshes[name], shaders["Tema2Shader"], modelMatrix, glm::vec3(0, 0.243f, 1), 100.f);
       }
       
    }
    
}

void Tema2::GoodTank(float deltaTimeSeconds) 
{
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTimeProjectiles;
    lastFrameTimeProjectiles = currentFrameTime;
    elapsedTimeProjectiles += deltaTime;

    float speed = 6;
    float distance = deltaTimeSeconds * speed;

    if (elapsedTime < time_out && dead == false) {
        // DETECTIE COLIZIUNE PERETE
        float distance_building = IntersectionTankBuilding(translatecorp);
        if (distance_building != -1) {
            if (fata_spate == true) {
                translatecorp -= dir * distance_building;
                translateturela -= dir * distance_building;
                translatetun -= dir * distance_building;
                translatesenile -= dir * distance_building;
                camera->MoveForward(-distance_building, dir);
            }
            else {
                translatecorp += dir * distance_building;
                translateturela += dir * distance_building;
                translatetun += dir * distance_building;
                translatesenile += dir * distance_building;
                camera->MoveForward(distance_building, dir);
            }
        }

        // DETECTIE COLIZIUNE LIMITA LUME
        if (IntersectionTankWall(translatesenile) == true) {
            if (fata_spate == true) {
                translatecorp -= dir * 0.5f;
                translateturela -= dir * 0.5f;
                translatetun -= dir * 0.5f;
                translatesenile -= dir * 0.5f;
                camera->MoveForward(-0.5f, dir);
            }
            else {
                translatecorp += dir * 0.5f;
                translateturela += dir * 0.5f;
                translatetun += dir * 0.5f;
                translatesenile += dir * 0.5f;
                camera->MoveForward(0.5f, dir);
            }
        }

        // DETECTIE COLIZIUNE TANC
        int tanc_inamic = IntersectionGoodTankTank();
        if (tanc_inamic != -1) {
            float P = fabs(radius + badtanks[tanc_inamic].radius - distancetanctanc);

            glm::vec3 Dif = badtanks[tanc_inamic].translatesenile - translatesenile;
            glm::vec3 Po = P * glm::normalize(Dif);

            badtanks[tanc_inamic].translatetun += Po * 0.07f;
            badtanks[tanc_inamic].translateturela += Po * 0.07f;
            badtanks[tanc_inamic].translatecorp += Po * 0.07f;
            badtanks[tanc_inamic].translatesenile += Po * 0.07f;

            translatecorp += Po * (-0.07f);
            translateturela += Po * (-0.07f);
            translatetun += Po * (-0.07f);
            translatesenile += Po * (-0.07f);
            camera->MoveForward(-0.07f, Po);
        }

        // DETECTIE COLIZIUNE PROIECTIL
        IntersectionProjectileGoodTank();

    }

    // TRANSLATARE TUN
    
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, translatesenile);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(rotireSenile), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -translatesenile);
        modelMatrix = glm::translate(modelMatrix, translatesenile);
        
        RenderSimpleMesh(meshes["senile"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.631f, 0.51f, 0.545f), lives);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, translatecorp);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(rotireCorp), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -translatecorp);
        modelMatrix = glm::translate(modelMatrix, translatecorp);
        
        RenderSimpleMesh(meshes["corp"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.961f, 0.31f, 0.51f), lives);
    }

     {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, translateturela);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(rotireTurela), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -translateturela);

        modelMatrix = glm::translate(modelMatrix, translateturela);

        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(rotireindependentaturela), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderSimpleMesh(meshes["turela"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.643f, 0.404f, 0.839f), lives);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        
        modelMatrix = glm::translate(modelMatrix, translatetun);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(rotireTun), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -translatetun);
       
        modelMatrix = glm::translate(modelMatrix, translatetun);

        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(rotireindependentatun), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderSimpleMesh(meshes["tun"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.631f, 0.51f, 0.545f), lives);
    }

    //TRANSLATARE PROIECTILE
    if (elapsedTime < time_out && dead == false) {
        for (auto itr = projectiles.begin(); itr != projectiles.end();)
        {
            if (IntersectionProjectileBuilding(itr->second) == true) {
                
                itr = projectiles.erase(itr);
                continue;
            }
            if (itr->second.life > 0) {
                glm::mat4 modelMatrix = glm::mat4(1);

                modelMatrix = glm::translate(modelMatrix, itr->second.translateproiectil);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f));
                RenderSimpleMesh(meshes["proiectil"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.031f, 0.031f, 0.027f), 100.f);

                itr->second.translateproiectil += distance * itr->second.dir;
                itr->second.life--;
                ++itr;

            }
            else {
                itr = projectiles.erase(itr);
            }
            
        }
    }
    else {
        for (auto itr = projectiles.begin(); itr != projectiles.end();)
        {
            glm::mat4 modelMatrix = glm::mat4(1);

            modelMatrix = glm::translate(modelMatrix, itr->second.translateproiectil);

            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f));
            RenderSimpleMesh(meshes["proiectil"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.031f, 0.031f, 0.027f), 100.f);
            ++itr;
        }
    }
}

void Tema2::BadTank(float deltaTimeSeconds) {
    float speed = 2;
    float distance = deltaTimeSeconds * speed;

    for (int i = 0; i < number_badtanks; i++) {

        if (elapsedTime < time_out && dead == false) {
            // DETECTIE COLIZIUNE PERETE
            float distance_building = IntersectionTankBuilding(badtanks[i].translatecorp);
            if (distance_building != -1) {
                if (badtanks[i].movement == MovementState::GoingForward) {
                    badtanks[i].translatecorp -= badtanks[i].dir * distance_building;
                    badtanks[i].translateturela -= badtanks[i].dir * distance_building;
                    badtanks[i].translatetun -= badtanks[i].dir * distance_building;
                    badtanks[i].translatesenile -= badtanks[i].dir * distance_building;
                }
                else if (badtanks[i].movement == MovementState::GoingBackward) {
                    badtanks[i].translatecorp += badtanks[i].dir * distance_building;
                    badtanks[i].translateturela += badtanks[i].dir * distance_building;
                    badtanks[i].translatetun += badtanks[i].dir * distance_building;
                    badtanks[i].translatesenile += badtanks[i].dir * distance_building;
                }
            }

            // DETECTIE COLIZIUNE LIMITA LUME
            if (IntersectionTankWall(badtanks[i].translatesenile) == true) {
                if (badtanks[i].movement == MovementState::GoingForward || badtanks[i].movement == MovementState::InPlaceRotationLeft || badtanks[i].movement == MovementState::InPlaceRotationRight) {
                    badtanks[i].translatecorp -= badtanks[i].dir * 0.5f;
                    badtanks[i].translateturela -= badtanks[i].dir * 0.5f;
                    badtanks[i].translatetun -= badtanks[i].dir * 0.5f;
                    badtanks[i].translatesenile -= badtanks[i].dir * 0.5f;
                }
                else if (badtanks[i].movement == MovementState::GoingBackward) {
                    badtanks[i].translatecorp += badtanks[i].dir * 0.5f;
                    badtanks[i].translateturela += badtanks[i].dir * 0.5f;
                    badtanks[i].translatetun += badtanks[i].dir * 0.5f;
                    badtanks[i].translatesenile += badtanks[i].dir * 0.5f;
                }
            }


            // DETECTIE COLIZIUNE TANC
            int tanc_inamic = IntersectionTankTank(badtanks[i].translatecorp, i);
            if (tanc_inamic != -1) {
                float P = fabs(badtanks[i].radius + badtanks[tanc_inamic].radius - badtanks[tanc_inamic].distancetanctanc);
                glm::vec3 Dif = badtanks[tanc_inamic].translatesenile - badtanks[i].translatesenile;
                glm::vec3 Po = P * glm::normalize(Dif);

                badtanks[tanc_inamic].translatetun += Po * 0.01f;
                badtanks[tanc_inamic].translateturela += Po * 0.01f;
                badtanks[tanc_inamic].translatecorp += Po * 0.01f;
                badtanks[tanc_inamic].translatesenile += Po * 0.01f;

                badtanks[i].translatecorp += Po * (-0.01f);
                badtanks[i].translateturela += Po * (-0.01f);
                badtanks[i].translatetun += Po * (-0.01f);
                badtanks[i].translatesenile += Po * (-0.01f);
            }

            // DETECTIE COLIZIUNE PROIECTIL
            int proiectil_atacant = IntersectionProjectileBadtanc(badtanks[i].translateturela, i);
            if (proiectil_atacant != -1) {
                if (badtanks[i].lives > 0) {
                    badtanks[i].lives -= 25;

                    for (auto itr = projectiles.begin(); itr != projectiles.end();)
                    {
                        if (itr->first != proiectil_atacant) {
                            ++itr;
                        }
                        else {
                            itr = projectiles.erase(itr);
                        }
                    }

                }
                else {
                    for (auto itr = projectiles.begin(); itr != projectiles.end();)
                    {
                        if (itr->first != proiectil_atacant) {
                            ++itr;
                        }
                        else {
                            itr = projectiles.erase(itr);
                        }
                    }
                    badtanks[i].dead = true;
                    if (badtanks[i].pointadded != 1) {
                        score += 1;
                        badtanks[i].pointadded = 1;
                    }
                }
            }


            // DETECTIE APROPIERE TANC BUN
            if (badtanks[i].dead == false) {
                bool close = ApropiereGoodTankTank(badtanks[i].translatesenile);

                if (close == true) {
                    glm::vec3 directiontotanc = glm::normalize(badtanks[i].translateturela - translateturela);

                    float angle = atan(directiontotanc.x / directiontotanc.z);
                    if (translateturela.z < badtanks[i].translateturela.z) {
                        angle += 3.14;
                    }
                    badtanks[i].rotiretun = angle;
                    badtanks[i].dir_tun = directiontotanc;

                    // attack the good tank

                    double currentFrameTime = glfwGetTime();
                    double deltaTime = currentFrameTime - badtanks[i].lastFrameTimeProjectiles;
                    badtanks[i].lastFrameTimeProjectiles = currentFrameTime;
                    badtanks[i].elapsedTimeProjectiles += deltaTime;

                    if (badtanks[i].elapsedTimeProjectiles >= badtanks[i].spawnTimeProjectiles) {
                        glm::vec3 directie = -badtanks[i].dir_tun;
                        badtanks[i].projectiles[badtanks[i].counterproiectile].translateproiectil = badtanks[i].translatetun + directie * 0.5f;
                        badtanks[i].projectiles[badtanks[i].counterproiectile].dir = directie;
                        badtanks[i].counterproiectile++;
                        badtanks[i].elapsedTimeProjectiles = 0.0f;
                        badtanks[i].spawnTimeProjectiles = 3.0f;
                          
                    }

                }

            }   
        }

            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, badtanks[i].translatesenile);
                modelMatrix = glm::rotate(modelMatrix, RADIANS(badtanks[i].rotiretanc), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, -badtanks[i].translatesenile);
                modelMatrix = glm::translate(modelMatrix, badtanks[i].translatesenile);

                RenderSimpleMesh(meshes["senile"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.667f, 0.71f, 0.651f), badtanks[i].lives);
            }

            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, badtanks[i].translatecorp);
                modelMatrix = glm::rotate(modelMatrix, RADIANS(badtanks[i].rotiretanc), glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, -badtanks[i].translatecorp);
                modelMatrix = glm::translate(modelMatrix, badtanks[i].translatecorp);

                RenderSimpleMesh(meshes["corp"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.212f, 0.722f, 0.071f), badtanks[i].lives);
            }

            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, badtanks[i].translateturela);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, badtanks[i].rotiretun, glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
                
                RenderSimpleMesh(meshes["turela"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.118f, 0.459f, 0.024f), badtanks[i].lives);
            }

            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, badtanks[i].translatetun);    
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
                modelMatrix = glm::rotate(modelMatrix, badtanks[i].rotiretun, glm::vec3(0, 1, 0));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
                
                RenderSimpleMesh(meshes["tun"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.667f, 0.71f, 0.651f), badtanks[i].lives);
            }

            // Proiectile
            
            if (elapsedTime < time_out && dead == false) {
                for (auto itr = badtanks[i].projectiles.begin(); itr != badtanks[i].projectiles.end();)
                {
                    if (IntersectionProjectileBuilding(itr->second) == true) {

                        itr = badtanks[i].projectiles.erase(itr);
                        continue;
                    }
                    if (itr->second.life > 0) {
                        glm::mat4 modelMatrix = glm::mat4(1);
                        
                        modelMatrix = glm::translate(modelMatrix, itr->second.translateproiectil);
                        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f));
                        RenderSimpleMesh(meshes["proiectil"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.031f, 0.031f, 0.027f), 100.f);

                        itr->second.translateproiectil += distance * itr->second.dir;
                        itr->second.life--;
                        ++itr;

                    }
                    else {
                        itr = badtanks[i].projectiles.erase(itr);
                    }

                }
            }
            else {
                for (auto itr = badtanks[i].projectiles.begin(); itr != badtanks[i].projectiles.end();)
                {
                    glm::mat4 modelMatrix = glm::mat4(1);

                    modelMatrix = glm::translate(modelMatrix, itr->second.translateproiectil);

                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f));
                    RenderSimpleMesh(meshes["proiectil"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.031f, 0.031f, 0.027f), 100.f);
                    ++itr;
                }
            }


            if (elapsedTime < time_out && dead == false) {

                if (badtanks[i].dead == false) {

                    if (badtanks[i].movement == MovementState::GoingForward) {
                        badtanks[i].translatetun += distance * badtanks[i].dir;
                        badtanks[i].translateturela += distance * badtanks[i].dir;
                        badtanks[i].translatecorp += distance * badtanks[i].dir;
                        badtanks[i].translatesenile += distance * badtanks[i].dir;
                    }

                    if (badtanks[i].movement == MovementState::GoingBackward) {
                        badtanks[i].translatetun -= distance * badtanks[i].dir;
                        badtanks[i].translateturela -= distance * badtanks[i].dir;
                        badtanks[i].translatecorp -= distance * badtanks[i].dir;
                        badtanks[i].translatesenile -= distance * badtanks[i].dir;
                    }

                    if (badtanks[i].movement == MovementState::InPlaceRotationLeft) {
                        badtanks[i].rotiretanc += deltaTimeSeconds * 20;
                        badtanks[i].dir = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(deltaTimeSeconds * 20), glm::vec3(0, 1, 0)) * glm::vec4(badtanks[i].dir, 0)));
                    }

                    if (badtanks[i].movement == MovementState::InPlaceRotationRight) {
                        badtanks[i].rotiretanc -= deltaTimeSeconds * 20;
                        badtanks[i].dir = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), -RADIANS(deltaTimeSeconds * 20), glm::vec3(0, 1, 0)) * glm::vec4(badtanks[i].dir, 0)));
                    }

                    // DECIDE WHICH ACTION TO DO
                    if (badtanks[i].elapsedtime > 0) {
                        badtanks[i].elapsedtime -= 0.5;
                    }
                    else {
                        badtanks[i].movement = GetNextMovementState(badtanks[i].movement);
                        badtanks[i].elapsedtime = GetRandomNumberInRange(30, 60);
                    }
                }
            }

    }

}

bool Tema2::IntersectionProjectileBuilding(Proiectile projectile) {

    // MAI INTOARCE TE AICI SA VEZI VALORILE APROX

    for (int i = 0; i < number_buildings; i++) {
        int x = 0, y = 0, z = 0;
        glm::vec3 closestpoint = glm::vec3(0);
        if (buildings[i].type == 1) {
            closestpoint.x = glm::clamp(projectile.translateproiectil.x, buildings[i].position.x, buildings[i].position.x + 1.43f);
            closestpoint.y = glm::clamp(projectile.translateproiectil.y, buildings[i].position.y, buildings[i].position.y + 2.83f);
            closestpoint.z = glm::clamp(projectile.translateproiectil.z, buildings[i].position.z, buildings[i].position.z + 1.57f);
        }

        if (buildings[i].type == 2) {
            closestpoint.x = glm::clamp(projectile.translateproiectil.x, buildings[i].position.x, buildings[i].position.x + 0.903f);
            closestpoint.y = glm::clamp(projectile.translateproiectil.y, buildings[i].position.y, buildings[i].position.y + 1.79f);
            closestpoint.z = glm::clamp(projectile.translateproiectil.z, buildings[i].position.z, buildings[i].position.z + 0.994f);
        }

        if (buildings[i].type == 3) {
            closestpoint.x = glm::clamp(projectile.translateproiectil.x, buildings[i].position.x, buildings[i].position.x + 2.66f);
            closestpoint.y = glm::clamp(projectile.translateproiectil.y, buildings[i].position.y, buildings[i].position.y + 2.83f);
            closestpoint.z = glm::clamp(projectile.translateproiectil.z, buildings[i].position.z, buildings[i].position.z + 0.971f);
        }

        float distance = glm::distance(closestpoint, projectile.translateproiectil);

        if (distance < 0.3f) {
            return true;
        }
    }
    return false;
}

float Tema2::IntersectionTankBuilding(glm::vec3 positiontank) {

    for (int i = 0; i < number_buildings; i++) {
        glm::vec3 closestpoint = glm::vec3(0);
        if (buildings[i].type == 1) {
            closestpoint.x = glm::clamp(positiontank.x, buildings[i].position.x, buildings[i].position.x + 1.43f);
            closestpoint.y = glm::clamp(positiontank.y, buildings[i].position.y, buildings[i].position.y + 2.83f);
            closestpoint.z = glm::clamp(positiontank.z, buildings[i].position.z, buildings[i].position.z + 1.57f);
        }

        if (buildings[i].type == 2) {
            closestpoint.x = glm::clamp(positiontank.x, buildings[i].position.x, buildings[i].position.x + 0.903f);
            closestpoint.y = glm::clamp(positiontank.y, buildings[i].position.y, buildings[i].position.y + 1.79f);
            closestpoint.z = glm::clamp(positiontank.z, buildings[i].position.z, buildings[i].position.z + 0.994f);
        }

        if (buildings[i].type == 3) {
            closestpoint.x = glm::clamp(positiontank.x, buildings[i].position.x, buildings[i].position.x + 2.66f);
            closestpoint.y = glm::clamp(positiontank.y, buildings[i].position.y, buildings[i].position.y + 2.83f);
            closestpoint.z = glm::clamp(positiontank.z, buildings[i].position.z, buildings[i].position.z + 0.971f);
        }

        float distance = glm::distance(closestpoint, positiontank);

        if (distance < 0.635f) {
            return distance;
        }
    }
    return -1;
}

bool Tema2::IntersectionTankWall(glm::vec3 positiontank) {

    glm::vec3 closestpoint1 = glm::vec3(0);
    glm::vec3 closestpoint2 = glm::vec3(0);
    glm::vec3 closestpoint3 = glm::vec3(0);
    glm::vec3 closestpoint4 = glm::vec3(0);
   
    closestpoint1.x = glm::clamp(positiontank.x, -49.8f, 49.8f);
    closestpoint1.z = glm::clamp(positiontank.z, -49.8f, -49.8f);
    float distance1 = glm::distance(closestpoint1, positiontank);

    closestpoint2.x = glm::clamp(positiontank.x, -49.8f, 49.8f);
    closestpoint2.z = glm::clamp(positiontank.z, 49.8f, 49.8f);
    float distance2 = glm::distance(closestpoint2, positiontank);
    
    closestpoint3.x = glm::clamp(positiontank.x, 49.8f, 49.8f);
    closestpoint3.z = glm::clamp(positiontank.z, -49.8f, 49.8f);
    float distance3 = glm::distance(closestpoint3, positiontank);

    closestpoint4.x = glm::clamp(positiontank.x, -49.8f, -49.8f);
    closestpoint4.z = glm::clamp(positiontank.z, -49.8f, 49.8f);
    float distance4 = glm::distance(closestpoint4, positiontank);


    if (distance1 < 0.635f || distance2 < 0.635f || distance3 < 0.635f || distance4 < 0.635f) {
            return true;
    }
    return false;
}

int Tema2::IntersectionTankTank(glm::vec3 positiontanc, int tancnumber) {

    for (int i = 0; i < number_badtanks; i++) {
        if (i != tancnumber) {
            badtanks[tancnumber].distancetanctanc = sqrt((positiontanc.x - badtanks[i].translatecorp.x) * (positiontanc.x - badtanks[i].translatecorp.x) +
                (positiontanc.y - badtanks[i].translatecorp.y) * (positiontanc.y - badtanks[i].translatecorp.y) +
                (positiontanc.z - badtanks[i].translatecorp.z) * (positiontanc.z - badtanks[i].translatecorp.z));

            if (badtanks[tancnumber].distancetanctanc < badtanks[tancnumber].radius + badtanks[i].radius) {
                return i;
            }
        }
    }
    return -1;
}

int Tema2::IntersectionProjectileBadtanc(glm::vec3 positiontanc, int tancnumber) {
    Proiectile projectile;
    for (auto itr = projectiles.begin(); itr != projectiles.end();) {
        projectile = itr->second;
            badtanks[tancnumber].distanceprojectiletanc = sqrt((positiontanc.x - projectile.translateproiectil.x) * (positiontanc.x - projectile.translateproiectil.x) +
                (positiontanc.y - projectile.translateproiectil.y) * (positiontanc.y - projectile.translateproiectil.y) +
                (positiontanc.z - projectile.translateproiectil.z) * (positiontanc.z - projectile.translateproiectil.z));

            if (badtanks[tancnumber].distanceprojectiletanc < badtanks[tancnumber].radius + projectile.radius) {
                return itr->first;
            }
            ++itr;
    }
    return -1;
}

void Tema2::IntersectionProjectileGoodTank() {
    Proiectile projectile;
    for (auto itr = badtanks.begin(); itr != badtanks.end(); ++itr) {
        for (auto pr = itr->second.projectiles.begin(); pr != itr->second.projectiles.end();) {
           
            projectile = pr->second;
            distancetancprojectile = sqrt((translateturela.x - projectile.translateproiectil.x) * (translateturela.x - projectile.translateproiectil.x) +
                (translateturela.y - projectile.translateproiectil.y) * (translateturela.y - projectile.translateproiectil.y) +
                (translateturela.z - projectile.translateproiectil.z) * (translateturela.z - projectile.translateproiectil.z));
            if (distancetancprojectile < radius + projectile.radius) {
                if (lives > 0) {
                    
                    lives -= 25;
                    pr = itr->second.projectiles.erase(pr);
                    continue;
                }
                else {
                    pr = itr->second.projectiles.erase(pr);
                    dead = true;
                    break;
                }
            }
            
             ++pr;
            
        }
    }
}

int Tema2::IntersectionGoodTankTank() {

    for (int i = 0; i < number_badtanks; i++) {

        distancetanctanc = sqrt((translatecorp.x - badtanks[i].translatecorp.x) * (translatecorp.x - badtanks[i].translatecorp.x) +
            (translatecorp.x - badtanks[i].translatecorp.y) * (translatecorp.y - badtanks[i].translatecorp.y) +
            (translatecorp.z - badtanks[i].translatecorp.z) * (translatecorp.z - badtanks[i].translatecorp.z));

        if (distancetanctanc < radius + badtanks[i].radius) {
            return i;
        }
    }
    return -1;
}

bool Tema2::ApropiereGoodTankTank(glm::vec3 positiontanc) {
    float distancestanctanc = sqrt((translatesenile.x - positiontanc.x) * (translatesenile.x - positiontanc.x) +
        (translatesenile.x - positiontanc.y) * (translatesenile.y - positiontanc.y) +
        (translatesenile.z - positiontanc.z) * (translatesenile.z - positiontanc.z));

    if (distancestanctanc < 5.f) {
        return true;
    }
    return false;
}

MovementState Tema2::GetNextMovementState(const MovementState currentState)
{
    int randomChange = GetRandomNumberInRange(0, 1);
    MovementState nextState = currentState;

    switch (currentState)
    {
    case MovementState::GoingForward:
    case MovementState::GoingBackward:
        nextState = (randomChange == 1)
            ? MovementState::InPlaceRotationLeft
            : MovementState::InPlaceRotationRight;
        break;

    case MovementState::InPlaceRotationLeft:
    case MovementState::InPlaceRotationRight:
        nextState = (randomChange == 1)
            ? MovementState::GoingForward
            : MovementState::GoingBackward;
        break;

    default:
        break;
    }

    return nextState;
}

std::string Tema2::GetMovementStateName(const MovementState state)
{
    static const std::map<MovementState, std::string> kStateNames
    {
        { MovementState::GoingForward, "GoingForward" },
        { MovementState::GoingBackward, "GoingBackward" },
        { MovementState::InPlaceRotationLeft, "InPlaceRotationLeft" },
        { MovementState::InPlaceRotationRight, "InPlaceRotationRight" },
    };

    std::string s = "";
    if (kStateNames.count(state))
    {
        s = kStateNames.at(state);
    }

    return s;
}

void Tema2::Update(float deltaTimeSeconds)
{

    double currentTime = glfwGetTime();
    elapsedTime = currentTime - start_time;
    {
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
       modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 2, 2));
       RenderSimpleMesh(meshes["ground"], shaders["Tema2Shader"], modelMatrix, glm::vec3(0.529f, 0.333f, 0.247f), 100.f);
    }
    Buildings(deltaTimeSeconds);
    GoodTank(deltaTimeSeconds);
    BadTank(deltaTimeSeconds);    
}

void Tema2::FrameEnd()
{
    if (dead == true && score_showed != 1) {
        cout << "GAME OVER! SCORE: " << score << endl;
        score_showed = 1;
    }
    if (elapsedTime >= time_out && score_showed != 1) {
        cout << "CONGRATULATIONS! SCORE: " << score << endl;
        score_showed = 1;
    }
    //DrawCoordinateSystem(camera->GetViewMatrix(), GetSceneCamera()->GetProjectionMatrix());
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, float HP)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int location_model = glGetUniformLocation(shader->program, "Model");
    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(location_model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // TODO(student): Get shader location for uniform mat4 "View"
    int location_view = glGetUniformLocation(shader->program, "View");

    // TODO(student): Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int location_projection = glGetUniformLocation(shader->program, "Projection");

    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Send color
    glUniform3fv(glGetUniformLocation(shader->program, "Color"), 1, glm::value_ptr(color));

    //send hp
    glUniform1f(glGetUniformLocation(shader->program, "hp"), HP);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

int Tema2::GetRandomNumberInRange(const int minInclusive, const int maxInclusive)
{
    static std::random_device randomDevice;
    static std::default_random_engine randomEngine(randomDevice());

    std::uniform_int_distribution<int> uniformDist(minInclusive, maxInclusive);

    return uniformDist(randomEngine);
}

float Tema2::getRandomFloat(float min, float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // Add key press event
    float speed = 4;
    float distance = deltaTime * speed;
    
    if (elapsedTime < time_out && dead == false) {
        //translatie
        if (window->KeyHold(GLFW_KEY_W) == true) {
            
            translatecorp += dir * distance;
            translateturela += dir * distance;
            translatetun += dir * distance;
            translatesenile += dir * distance;

            fata_spate = true;

            camera->MoveForward(distance, dir);
        }

        if (window->KeyHold(GLFW_KEY_S) == true) {
            
            translatecorp -= dir * distance;
            translateturela -= dir * distance;
            translatetun -= dir * distance;
            translatesenile -= dir * distance;

            fata_spate = false;

            camera->MoveForward(-distance, dir);
        }

        if (window->KeyHold(GLFW_KEY_A) == true) {
            rotireCorp += deltaTime * 20;
            rotireTurela += deltaTime * 20;
            rotireTun += deltaTime * 20;
            rotireSenile += deltaTime * 20;
            dir = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(deltaTime * 20), glm::vec3(0, 1, 0)) * glm::vec4(dir, 0)));
            dir_tun = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(deltaTime * 20), glm::vec3(0, 1, 0)) * glm::vec4(dir_tun, 0)));
            camera->RotateThirdPerson_OY(RADIANS(deltaTime * 20));

        }

        if (window->KeyHold(GLFW_KEY_D) == true) {
            rotireCorp -= deltaTime * 20;
            rotireTurela -= deltaTime * 20;
            rotireTun -= deltaTime * 20;
            rotireSenile -= deltaTime * 20;
            dir = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), -RADIANS(deltaTime * 20), glm::vec3(0, 1, 0)) * glm::vec4(dir, 0)));
            dir_tun = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), -RADIANS(deltaTime * 20), glm::vec3(0, 1, 0)) * glm::vec4(dir_tun, 0)));
            camera->RotateThirdPerson_OY(-RADIANS(deltaTime * 20));

        }
    }

}

void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;
    // Add mouse move event
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        if (elapsedTime < time_out && dead == false) {
            camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
            camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
        }
    }
    else {
        rotireindependentaturela -= deltaX / 2.0f;
        rotireindependentatun -= deltaX / 2.0f;
        dir_tun = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), -RADIANS(deltaX / 2.0f), glm::vec3(0, 1, 0)) * glm::vec4(dir_tun, 0)));
    }
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    // GLFW_MOUSE_BUTTON_2 = mouse left
    if (elapsedTime < time_out && dead == false) {
        if (elapsedTimeProjectiles >= spawnTimeProjectiles) {
            if (button == GLFW_MOUSE_BUTTON_2) {      
                glm::vec3 directie = dir_tun;
                projectiles[counterproiectile].translateproiectil = translatetun + directie * 0.5f;
                projectiles[counterproiectile].dir = directie;
                counterproiectile++;
                elapsedTimeProjectiles = 0.0f;
                spawnTimeProjectiles = 1.0f;
            }
        }
    }
}
