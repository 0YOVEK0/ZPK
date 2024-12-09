#include "Actor.h"

Actor::Actor(std::string actorName) {
    // Setup Actor Name 
    m_name = actorName;

    // Setup Shape 
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);

    // Setup Transform
    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);

    // Setup Sprite Actor
}

void
Actor::update(float deltaTime) {
    auto transform = getComponent<Transform>();
    auto shape = getComponent<ShapeFactory>();

    if (transform && shape) {
        Vector2 position(transform->getPosition().x, transform->getPosition().y);
        shape->setPosition(position);
        shape->setRotation(transform->getRotation().x);
        Vector2 scale(transform->getScale().x, transform->getScale().y);
        shape->setScale(scale);
    }
}

void
Actor::render(Window& window) {
    for (unsigned int i = 0; i < components.size(); i++) {
        if (components[i].dynamic_pointer_cast<ShapeFactory>()) {
            window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
        }
    }
}

void
Actor::destroy() {
}

std::string
Actor::getName() const {
    return m_name;
}

void
Actor::setName(const std::string& newName) {
    m_name = newName;
}