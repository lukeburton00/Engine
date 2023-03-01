#include "Sandbox.hpp"
#include "PlayerController.hpp"

void Sandbox::start()
{
    setWidth(800);
    setHeight(600);
    setTitle("Sandbox");

    Scene scene;
    setActiveScene(scene);

    auto entity = activeScene->createEntity();

    std::shared_ptr<PlayerController> controller = std::make_shared<PlayerController>(entity, activeScene->getRegistry());
    activeScene->addComponent<Transform>(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 1.0f));
    activeScene->addComponent<Sprite>(entity);
    activeScene->addComponent<Script>(entity, controller);

    int numObjects = 10000;

    for (int i = 0; i < numObjects; ++i)
    {
        auto ent = activeScene->createEntity();
        activeScene->addComponent<Transform>(ent);
    }
}

int main() 
{
    Sandbox game;
    Application engine(game);
    engine.start();
    return 0;
}