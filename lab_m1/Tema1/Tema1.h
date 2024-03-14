#pragma once

#include "components/simple_scene.h"
#include <unordered_map>


namespace t1
{
    struct Element_star {
        float x, y, pos_X_poz, pos_X_neg, pos_Y_poz, pos_Y_neg;
    };

    struct Coords_squares_rombs {
        float x, y;
        int cost_stars;
    };

    struct Coords_squares {
        float x, y;
        bool occupied = false;
    };

    struct Rombs {
        float x, y, number_square, counter_projectiles = 3;
        std::string type;
        bool detected = false;
        float distance_from_enemy = 1350;
        float lastFrameTimeProjectiles = glfwGetTime(), elapsedTimeProjectiles = 0, spawnTimeProjectiles = 2.0f;
    };

    struct Scaling_rombs_to_kill {
        float scaleX, scaleY;
        bool kill = false;
        std::string type_romb;
        glm::vec2 coordinates = glm::vec2(0, 0);
    };

    struct Scaling_enemies_to_kill {
        float scaleX, scaleY;
        bool kill = false;
        std::string type_hexagon;
        glm::vec2 coordinates = glm::vec2(0, 0);
    };

    struct Enemy {
        float x, y, translateX, distanceRectangle = 1350, hearts_left = 3, distance_projectile = 1350;
        std::string type;
        bool detected = false;
    };

    struct Projectiles {
        float x, y, translateX, angularStep = 0;
        std::string type;
        int romb_id;
    };

    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

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

        void RenderGUI(float deltaTimeSeconds);
        void InitPlaySpace(float deltaTimeSecoonds);
        void ShootProjectileAnimation(float deltaTimeSeconds);
        void KillRombAnimation(float deltaTimeSeconds, int number_projectile, std::string type , glm::vec2 coords);
        void KillEnemyAnimation(float deltaTimeSeconds, int number_enemies, std::string type, glm::vec2 coords);
        float getRandomFloat(float min, float max);
        void StarSystem();
        void EnemyAttack(float deltaTimeSeconds);
        void cost_romb(std::string type);
        void SpawnProjectiles(float deltaTimeSeconds, int romb_id);
        void RombSystemCollision(float deltaTimeSeconds);
        
    protected:
       
        glm::mat3 modelMatrix;
        glm::mat3 modelMatrix1;
        glm::vec3 color = glm::vec3(0, 0, 0);
        glm::vec2 coordinates = glm::vec2(0, 0);
        float squareSide, width, height;
    
        int number_lives = 3;
        int number_stars = 5;
        int counter_stars = 0;
        int counter_enemies = 0;
        int counter_rombs = 0;
        int counter_projectiles = 0;
        float raza_romb = 50, raza_hexagon_mare = 40, raza_stea = 40;
        glm::vec3 linii_joc = glm::vec3(0,0,0);
        
        float lastFrameTimeStars, lastFrameTimeEnemies;
        float elapsedTimeStars = 0.0, elapsedTimeEnemies = 0.0;
        float spawnTimeStars, spawnTimeEnemies;

        bool mousepressed = false;
       
        std::string type_romb_selected;
        int romb_identifier, enemy_identifier;

        std::unordered_map<int, Element_star> stars;
        std::unordered_map<int, Enemy> enemies;
        std::unordered_map<int, Projectiles> projectiles;
        std::unordered_map<int, Coords_squares> coord_squares;
        std::unordered_map<std::string, Coords_squares_rombs> coord_squares_rombs;
        std::unordered_map<int, Rombs> rombs;
        std::unordered_map<int, Scaling_rombs_to_kill> kill_romb;
        std::unordered_map<int, Scaling_enemies_to_kill> kill_enemies;
    };
}   // namespace t1
