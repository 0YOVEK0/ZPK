#include "BaseApp.h"
#include "NotifySingleton.h"

// Inicializa la instancia estática del singleton NotifySingleton
NotifySingleton* NotifySingleton::m_instance = nullptr;


int
BaseApp::run() {
    NotifySingleton* noty = NotifySingleton::getInstance();

    if (!initialize()) {
        noty->addMessage(ConsoleErrorType::ERROR, "Initializes result on a false statement, check method validations");
    }
    m_GUI.init();

    while (m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }

    cleanup();
    return 0;
}

/**
 * @brief Inicializa los recursos de la aplicación, incluidos la ventana y los actores.
 *
 * Configura la ventana y crea instancias de actores `Circuit`, `Circle`, y `Triangle`.
 *
 * @return `true` si la inicialización fue exitosa, `false` en caso de error.
 */
bool
BaseApp::initialize() {
    NotifySingleton* noty = NotifySingleton::getInstance();

    // Configura la ventana principal
    m_window = new Window(1920, 1080, "Charreton Engine OG");
    if (!m_window) {
        noty->addMessage(ConsoleErrorType::ERROR, "initialize, Error on window creation, var is null");
        return false;
    }

    shape = new sf::CircleShape(10.0f);
    if (!shape) {
        noty->addMessage(ConsoleErrorType::ERROR, "initialize, Error on shape creation, var is null");
        return false;
    }

    // Inicializa el actor Circuit
    Circuit = EngineUtilities::MakeShared<Actor>("Circuit");
    if (!Circuit.isNull()) {
        noty->addMessage(ConsoleErrorType::NORMAL, "Actor Circuit created");
        Circuit->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
        Circuit->getComponent<Transform>()->setPosition(sf::Vector2f(10, 10.0f));
        Circuit->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
        Circuit->getComponent<Transform>()->setScale(sf::Vector2f(5.0f, 10.0f));

        m_actors.push_back(Circuit);

        if (!texture.loadFromFile("Circuit.png")) {
            noty->addMessage(ConsoleErrorType::WARNING, "Esa textura no existe circuit");
        }
        else {
            noty->addMessage(ConsoleErrorType::NORMAL, "Loaded Texture ");
        }
        Circuit->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);
    }

    // Inicializa el actor Circle
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull()) {
        noty->addMessage(ConsoleErrorType::NORMAL, "Actor Circle created");
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<Transform>()->setPosition(sf::Vector2f(280.0f, 460.0f));
        Circle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
        Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

        m_actors.push_back(Circle);

        if (!shyGuy.loadFromFile("sprites/Image12.png")) {
            noty->addMessage(ConsoleErrorType::WARNING, "Esa textura no existe circle");
        }
        else {
            noty->addMessage(ConsoleErrorType::NORMAL, "Loaded Texture Circle");
        }
        Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&shyGuy);
    }

    // Inicializa el actor Triangle
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
    }

    return true;
}

/**
 * @brief Actualiza el estado de la aplicación en cada frame.
 *
 * Llama a la actualización de la ventana, los actores, y ejecuta el patrón de patrullaje en el actor `Circle`.
 */
void
BaseApp::update() {
    m_window->update();

    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->update(m_window->deltaTime.asSeconds());
        }
    }

    if (!Circuit.isNull()) {
        Circuit->update(m_window->deltaTime.asSeconds());
    }

    if (!Circle.isNull()) {
        Circle->update(m_window->deltaTime.asSeconds());
        patrolPattern(m_window->deltaTime.asSeconds(), Circle);
    }
}

/**
 * @brief Renderiza los elementos de la aplicación en la ventana.
 *
 * Limpia la ventana, dibuja los actores y muestra la GUI con la jerarquía de actores y mensajes de consola.
 */
void
BaseApp::render() {
    NotifySingleton* noty = NotifySingleton::getInstance();

    m_window->clear();
    m_window->draw(*shape);

    if (!Triangle.isNull()) {
        Triangle->render(*m_window);
    }
    if (!Circuit.isNull()) {
        Circuit->render(*m_window);
    }
    if (!Circle.isNull()) {
        Circle->render(*m_window);
    }

    for (const auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->render(*m_window);
        }
    }

    m_window->renderToTexture();
    m_window->showInImGui();
    m_GUI.console(noty->showNotification());
    m_GUI.hierarchy(m_actors);
    m_GUI.actor(m_actors);
    m_window->render();
    m_window->display();
}


void
BaseApp::cleanup() {
         m_window->destroy();
         delete m_window;
}

/**
 * @brief Ejecuta un patrón de patrullaje para el actor proporcionado.
 *
 * Este método mueve el actor `circulo` entre una serie de puntos (`waypoints`) en secuencia,
 * simulando un comportamiento de patrullaje.
 *
 * @param deltaTime Tiempo transcurrido desde el último frame.
 * @param circulo Puntero al actor que realiza el patrullaje.
 */
void
BaseApp::patrolPattern(float deltaTime, EngineUtilities::TSharedPointer<Actor> circulo) {
    if (!circulo || circulo.isNull()) {
        return;
    }

    auto transform = circulo->getComponent<Transform>();
    if (transform.isNull()) {
        return;
    }

    sf::Vector2f targetPos = waypoints[currentPoint];
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    sf::Vector2f currentPos = transform->getPosition();
    float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    if (distanceToTarget < 10.0f) {
        currentPoint = (currentPoint + 1) % waypoints.size();
    }
}

