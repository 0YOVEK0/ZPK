#include "BaseApp.h"

BaseApp::~BaseApp()
{
    NotificationService::getInstance().saveMessagesToFile("Data.txt");
}

int BaseApp::run() {
    NotificationService& notifier = NotificationService::getInstance();

    if (!initialize()) {
        notifier.addMessage(ConsolErrorType::ERROR, "Initializes result on a false statemente, check method validations");
        notifier.saveMessagesToFile("Data.txt");
        ERROR("BaseApp", "run", "Initializes result on a false statemente, check method validations");
    }
    else {
        notifier.addMessage(ConsolErrorType::NORMAL, "All programs were initialized correctly");
    }
    m_GUI.init();

    while (m_window->isOpen()) {
        m_window->handleEvents();
        deltaTime = clock.restart();
        update();
        render();
    }

    cleanup();
    return 0;
}

bool BaseApp::initialize() {
    NotificationService& notifier = NotificationService::getInstance();
    ResourceManager& resourceManager = ResourceManager::getInstance();

    m_window = new Window(1280, 720, "ZPK");
    if (!m_window) {
        notifier.addMessage(ConsolErrorType::ERROR, "Error on window creation, pointer is null");
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // Points for movement
    points[0] = Vector2(25.0f, 560.0f);  // Esquina superior izquierda
    points[1] = Vector2(25.0f, 20.0f);   // Esquina inferior izquierda
    points[2] = Vector2(700.0f, 20.0f);  // Esquina inferior derecha
    points[3] = Vector2(700.0f, 560.0f); // Esquina superior derecha
    

    // Initialize Track Actor
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
        Track->getComponent<Transform>()->setTransform(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(40.0f, 60.0f));

        // Load texture for Track
        if (!resourceManager.loadTexture("Map002", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Can't load texture: Circuit");
        }

        EngineUtilities::TSharedPointer<Texture> trackTexture = resourceManager.getTexture("Map002");
        if (trackTexture) {
            Track->getComponent<ShapeFactory>()->getShape()->setTexture(&trackTexture->getTexture());
        }

        m_actors.push_back(Track);
    }

    // Initialize Circle Actor (Player)
    Circle = EngineUtilities::MakeShared<Actor>("Player");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<Transform>()->setTransform(Vector2(650.0f, 560.0f), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

        // Load texture for Player
        if (!resourceManager.loadTexture("Playa2", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Can't load texture: Rob");
        }

        EngineUtilities::TSharedPointer<Texture> playerTexture = resourceManager.getTexture("Playa2");
        if (playerTexture) {
            Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&playerTexture->getTexture());
        }

        m_actors.push_back(Circle);
    }

    // Initialize Triangle Actor
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        Triangle->getComponent<Transform>()->setTransform(Vector2(150.0f, 200.0f), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

        // Load texture for Triangle
        if (!resourceManager.loadTexture("jaua23", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Can't load texture: jaua23");
        }

        EngineUtilities::TSharedPointer<Texture> triangleTexture = resourceManager.getTexture("jaua23");
        if (triangleTexture) {
            Triangle->getComponent<ShapeFactory>()->getShape()->setTexture(&triangleTexture->getTexture());
        }

        m_actors.push_back(Triangle);
    }

    // NEW: Adding a Square Actor
    Square = EngineUtilities::MakeShared<Actor>("Square");
    if (!Square.isNull()) {
        Square->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
        Square->getComponent<Transform>()->setTransform(Vector2(300.0f, 300.0f), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

        // Load texture for Square
        if (!resourceManager.loadTexture("SquareTexture", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Can't load texture: SquareTexture");
        }

        EngineUtilities::TSharedPointer<Texture> squareTexture = resourceManager.getTexture("SquareTexture");
        if (squareTexture) {
            Square->getComponent<ShapeFactory>()->getShape()->setTexture(&squareTexture->getTexture());
        }

        m_actors.push_back(Square);  
    }

    return true;
}

void BaseApp::update() {
    m_window->update();

    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->update(m_window->deltaTime.asSeconds());
            if (actor->getName() == "Player") {
                updateMovement(m_window->deltaTime.asSeconds(), actor);
            }
        }
    }
}

void BaseApp::render() {
    NotificationService& notifier = NotificationService::getInstance();

    m_window->clear();
    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->render(*m_window);
        }
    }

    m_window->renderToTexture();  // Finalizes rendering to texture
    m_window->showInImGui();      // Displays texture in ImGui

    m_GUI.console(notifier.getNotifications());  // Shows the console messages
    m_GUI.inspector();  // Shows the inspector for debugging
    m_GUI.hierarchy(m_actors);  // Shows the hierarchy of actors

    m_window->render();
    m_window->display();
}

void BaseApp::cleanup() {
    m_window->destroy();
    delete m_window;
}

void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    if (!circle || circle.isNull()) return;

    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) return;

    Vector2 targetPos = points[m_currentPoint];

    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    Vector2 currentPos = transform->getPosition();

    float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    if (distanceToTarget < 10.0f) {
        m_currentPoint = (m_currentPoint + 1);
        if (m_currentPoint > 8) {
            m_currentPoint = 0;
        }
    }
}
