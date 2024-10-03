#include "BaseApp.h"

int
BaseApp::run() {
    if (!initialize()) {
        ERROR("BaseApp", "run", "Initialize result on a false statement, check method validations");
    }
    initialize();
    while (m_window->isOpen()) {
        m_window->handleEvents();
        deltaTime = clock.restart();
        update();
        render();
    }

    cleanup();
    return 0;
}

// Funcion de inicializacion
bool
BaseApp::initialize() {
    m_window = new Window(800, 600, "ZPK");
    if (!m_window) {
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // Circle Actor
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<ShapeFactory>()->setPosition(200.0f, 200.0f);
        Circle->getComponent<ShapeFactory>()->setFillColor(sf::Color::Blue);
    }

    // Triangle Actor
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        //Triangle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Blue);

        // NUEVO CODIGO DE PRACTICA
        Triangle->getComponent<ShapeFactory>()->setPosition(100.0f, 100.0f);
        m_trianglePoints.push_back(sf::Vector2f(100.0f, 100.0f));
        m_trianglePoints.push_back(sf::Vector2f(700.0f, 100.0f));
        m_trianglePoints.push_back(sf::Vector2f(700.0f, 500.0f));
        m_trianglePoints.push_back(sf::Vector2f(100.0f, 500.0f));
        m_currentTargetIndex = 0;
        m_speed = 200.0f;
    }

    return true;
}

// Funcion que se actualiza por frame
void
BaseApp::update() {
    // Mouse Position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x),
                           static_cast<float>(mousePosition.y));

    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->Seek(mousePosF,
                                                   200.0f,
                                                   deltaTime.asSeconds(),
                                                   50.0f);
    }

    // NUEVO CODIGO DE PRACTICA
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->MoveTriangle(m_trianglePoints, m_currentTargetIndex, m_speed,
                                                             deltaTime.asSeconds());
    }
}

// Funcion de renderizado
void
BaseApp::render() {
    m_window->clear();
    Triangle->render(*m_window);
    Circle->render(*m_window);
    // if(!Triangle.isNull())
    // {
    //     m_window->draw(*Triangle->getComponent<ShapeFactory>()->getShape());
    // }
    m_window->display();
}

void
BaseApp::cleanup() {
    m_window->destroy();
    delete m_window;
    // delete Triangulo;
}
