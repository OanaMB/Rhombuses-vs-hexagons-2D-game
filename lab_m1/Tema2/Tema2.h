#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"


namespace u1
{
    enum class MovementState
    {
        GoingForward,
        GoingBackward,
        InPlaceRotationLeft,
        InPlaceRotationRight
    };


    struct Proiectile {
        glm::vec3 translateproiectil = glm::vec3(0);
        glm::vec3 dir = glm::vec3(0);
        float life = 300.f;
        float radius = 0.5f;
    };

    struct Building {
        glm::vec3 position = glm::vec3(0);
        int type;
    };

    struct BadTanks {
        glm::vec3 translatecorp = glm::vec3(0, 0.35f, 0);
        glm::vec3 translateturela = glm::vec3(0, 0.62f, 0);
        glm::vec3 translatetun = glm::vec3(0, 0.62f, 0.0f);
        glm::vec3 translatesenile = glm::vec3(0, 0, 0);
        glm::vec3 dir = glm::vec3(0, 0, 1);
        glm::vec3 dir_tun = glm::vec3(0,0,1);
        MovementState movement = MovementState::GoingForward;
        float distancetanctanc = 0.f;
        float distanceprojectiletanc = 0.f;
        float elapsedtime;
        float rotiretanc = 0;
        float rotiretun = 0;
        float radius = 0.635f;
        float lives = 100.f;
        bool dead = false;
        int counterproiectile = 0;
        std::unordered_map<int, Proiectile> projectiles;
        int pointadded = 0;
        float lastFrameTimeProjectiles = glfwGetTime(), elapsedTimeProjectiles = 0, spawnTimeProjectiles = 3.0f;
    };



    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, float HP);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

        void GoodTank(float deltaTimeSeconds);
        void Buildings(float deltaTimeSeconds);
        void BadTank(float deltaTimeSeconds);
        float getRandomFloat(float min, float max);
        int GetRandomNumberInRange(const int minInclusive, const int maxInclusive);
        MovementState GetNextMovementState(const MovementState currentState);
        std::string GetMovementStateName(const MovementState state);
        bool IntersectionProjectileBuilding(Proiectile projectile);
        int IntersectionTankTank(glm::vec3 positiontanc, int tancnumber);
        float IntersectionTankBuilding(glm::vec3 positiontank);
        int IntersectionGoodTankTank();
        bool IntersectionTankWall(glm::vec3 positiontank);
        int IntersectionProjectileBadtanc(glm::vec3 positiontanc, int tancnumber);
        bool ApropiereGoodTankTank(glm::vec3 positiontanc);
        void IntersectionProjectileGoodTank();
        
    protected:
        implementedTema2::CameraTema2* camera;
        glm::mat4 projectionMatrix;
        float timer;
        float start_time = glfwGetTime(), elapsedTime = 0, time_out = 120.f;
        int score = 0;
        int score_showed = 0;
       
        // translatari
        glm::vec3 translatecorp = glm::vec3(0, 0.35f, 0);
        glm::vec3 translateturela = glm::vec3(0, 0.62f, 0);
        glm::vec3 translatetun = glm::vec3(0, 0.62f, 0.0f);
        glm::vec3 translatesenile = glm::vec3(0, 0, 0);
        

        // rotiri
        float radius = 0.5f;
        float rotireCorp = 0;
        float rotireTurela = 0;
        float rotireTun = 0;
        float rotireSenile = 0;
        float rotireindependentaturela = 0;
        float rotireindependentatun = 0;
        bool fata_spate = true;
        glm::vec3 dir;
        glm::vec3 dir_tun;
        float lastFrameTimeProjectiles = glfwGetTime(), elapsedTimeProjectiles = 0, spawnTimeProjectiles = 1.0f;
        float lives = 100.f;
        bool dead = false;

        // proiectile tun good
        int counterproiectile = 0;
        std::unordered_map<int, Proiectile> projectiles;

        //cladiri
        int number_buildings = 0;
        std::unordered_map<int, Building> buildings;

        //tancuri rele
        int number_badtanks = 0;
        std::unordered_map<int, BadTanks> badtanks;
        float distancetanctanc;
        float distancetancprojectile;
    };
}   // namespace u1
