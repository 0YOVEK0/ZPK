#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/**
 * @class Transform
 * @brief Componente de transformación que gestiona la posición, rotación y escala de una entidad.
 *
 * La clase `Transform` permite manipular la posición, rotación y escala de una entidad en la escena.
 * Además, proporciona un método de movimiento que permite al objeto dirigirse a una posición objetivo.
 */
class Transform : public Component {
public:
    
    Transform() : position(0.0f, 0.0f),
                  rotation(0.0f, 0.0f), 
                  scale(1.0f, 1.0f),  
                  Component(ComponentType::TRANSFORM) {}

    /**
     * @brief Destructor virtual por defecto.
     */
    virtual
        ~Transform() = default;

    /**
     * @brief Actualiza el componente de transformación.
     *
     * Este método se llama cada frame, pero en este caso no tiene implementación específica.
     * @param deltaTime Tiempo transcurrido desde el último frame.
     */
    void
        update(float deltaTime) override {}

    /**
     * @brief Renderiza el componente de transformación.
     *
     * No tiene implementación específica en este caso.
     * @param window Ventana donde se renderizaría la transformación.
     */
    void
        render(Window window) override {}

    /**
     * @brief Libera recursos asociados al componente de transformación.
     */
    void
        destroy();

    /**
     * @brief Establece la posición del objeto.
     * @param _position Nueva posición en la escena.
     */
    void
        setPosition(const sf::Vector2f& _position) {
        position = _position;
    }

    /**
     * @brief Establece la rotación del objeto.
     * @param _rotation Nueva rotación en la escena.
     */
    void
        setRotation(const sf::Vector2f& _rotation) {
        rotation = _rotation;
    }

    /**
     * @brief Establece la escala del objeto.
     * @param _scale Nueva escala en la escena.
     */
    void
        setScale(const sf::Vector2f& _scale) {
        scale = _scale;
    }

    /**
     * @brief Mueve el objeto hacia una posición objetivo.
     *
     * Este método ajusta la posición del objeto en dirección a una posición de destino.
     * Solo se mueve si la distancia al objetivo es mayor que el rango especificado.
     *
     * @param targetPosition Posición objetivo hacia la que moverse.
     * @param speed Velocidad de movimiento.
     * @param deltaTime Tiempo transcurrido desde el último frame.
     * @param range Distancia mínima a la posición objetivo antes de detenerse.
     */
    void
        Seek(const sf::Vector2f& targetPosition, 
             float speed,
             float deltaTime, 
             float range) {
        sf::Vector2f direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > range) {
            direction /= length;  // Normaliza el vector
            position += direction * speed * deltaTime;
        }
    }

    /**
     * @brief Obtiene la posición actual del objeto.
     * @return Referencia a la posición actual (`sf::Vector2f`).
     */
    sf::Vector2f& getPosition() {
        return position;
    }

    /**
     * @brief Obtiene la rotación actual del objeto.
     * @return Referencia a la rotación actual (`sf::Vector2f`).
     */
    sf::Vector2f& getRotation() {
        return rotation;
    }

    /**
     * @brief Obtiene la escala actual del objeto.
     * @return Referencia a la escala actual (`sf::Vector2f`).
     */
    sf::Vector2f& getScale() {
        return scale;
    }

private:
    ShapeFactory* m_shape; ///< Puntero a un componente de `ShapeFactory` asociado (opcional).
    sf::Vector2f position; ///< Posición del objeto en la escena.
    sf::Vector2f rotation; ///< Rotación del objeto en la escena.
    sf::Vector2f scale; ///< Escala del objeto en la escena.
};

