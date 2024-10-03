#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "ECS/Actor.h"

class
BaseApp {
public:
    BaseApp() = default;
    ~BaseApp() = default;

    // Funcion que corre el programa en main
    int
    run();

    // Funcion de inicializacion
    bool
    initialize();

    // Funcion que se actualiza por frame
    void
    update();

    // Funcion de renderizado
    void
    render();

    // Funcion de liberacion de memoria
    void
    cleanup();

private:
    sf::Clock clock;
    sf::Time deltaTime;

    Window* m_window;
    EngineUtilities::TSharedPointer<Actor> Triangle;
    EngineUtilities::TSharedPointer<Actor> Circle;

    // NUEVO CODIGO DE PRACTICA
    std::vector<sf::Vector2f> m_trianglePoints;
    int m_currentTargetIndex;
    float m_speed;
};
