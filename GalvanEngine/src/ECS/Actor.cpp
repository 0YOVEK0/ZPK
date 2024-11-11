#include "Actor.h"

/**
 * @brief Constructor que inicializa un actor con un nombre específico y configura sus componentes básicos.
 *
 * Este constructor asigna un nombre al actor, agrega un componente de `ShapeFactory` para representar su forma
 * y un componente `Transform` para manejar su posición, rotación y escala.
 *
 * @param actorName Nombre del actor.
 */
Actor::Actor(std::string actorName) {
    // Configura el nombre del actor
    m_name = actorName;

    // Configura el componente ShapeFactory para la forma
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);

    // Configura el componente Transform para la transformación
    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);

    // Setup Sprite (componente no implementado aquí)
}

/**
 * @brief Actualiza el estado del actor.
 *
 * Este método obtiene los componentes `Transform` y `ShapeFactory` del actor, y sincroniza la posición,
 * rotación y escala de la forma con los valores del `Transform`.
 *
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void
Actor::update(float deltaTime) {
    auto transform = getComponent<Transform>();
    auto shape = getComponent<ShapeFactory>();
    if (transform && shape) {
        shape->setPosition(transform->getPosition());
        shape->setRotation(transform->getRotation().x);
        shape->setScale(transform->getScale());
    }
}

/**
 * @brief Renderiza el actor en la ventana proporcionada.
 *
 * Este método recorre los componentes del actor y, si encuentra un `ShapeFactory`,
 * obtiene su forma y la dibuja en la ventana.
 *
 * @param window Referencia a la ventana de renderizado.
 */
void Actor::render(Window& window) {
    for (unsigned int i = 0; i < components.size(); i++) {
        if (components[i].dynamic_pointer_cast<ShapeFactory>()) {
            window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
        }
    }
}

/**
 * @brief Libera los recursos asociados al actor.
 *
 * Método vacío en esta implementación, pero puede expandirse para limpiar recursos específicos.
 */
void
Actor::destroy() {
    // Implementación vacía
}
