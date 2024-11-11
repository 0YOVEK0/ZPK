#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/**
 * @class Transform
 * @brief Componente de transformaci�n que gestiona la posici�n, rotaci�n y escala de una entidad.
 *
 * La clase `Transform` permite manipular la posici�n, rotaci�n y escala de una entidad en la escena.
 * Adem�s, proporciona un m�todo de movimiento que permite al objeto dirigirse a una posici�n objetivo.
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
     * @brief Actualiza el componente de transformaci�n.
     *
     * Este m�todo se llama cada frame, pero en este caso no tiene implementaci�n espec�fica.
     * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
     */
    void
        update(float deltaTime) override {}

    /**
     * @brief Renderiza el componente de transformaci�n.
     *
     * No tiene implementaci�n espec�fica en este caso.
     * @param window Ventana donde se renderizar�a la transformaci�n.
     */
    void
        render(Window window) override {}

    /**
     * @brief Libera recursos asociados al componente de transformaci�n.
     */
    void
        destroy();

    /**
     * @brief Establece la posici�n del objeto.
     * @param _position Nueva posici�n en la escena.
     */
    void
        setPosition(const sf::Vector2f& _position) {
        position = _position;
    }

    /**
     * @brief Establece la rotaci�n del objeto.
     * @param _rotation Nueva rotaci�n en la escena.
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
     * @brief Mueve el objeto hacia una posici�n objetivo.
     *
     * Este m�todo ajusta la posici�n del objeto en direcci�n a una posici�n de destino.
     * Solo se mueve si la distancia al objetivo es mayor que el rango especificado.
     *
     * @param targetPosition Posici�n objetivo hacia la que moverse.
     * @param speed Velocidad de movimiento.
     * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
     * @param range Distancia m�nima a la posici�n objetivo antes de detenerse.
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
     * @brief Obtiene la posici�n actual del objeto.
     * @return Referencia a la posici�n actual (`sf::Vector2f`).
     */
    sf::Vector2f& getPosition() {
        return position;
    }

    /**
     * @brief Obtiene la rotaci�n actual del objeto.
     * @return Referencia a la rotaci�n actual (`sf::Vector2f`).
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
    sf::Vector2f position; ///< Posici�n del objeto en la escena.
    sf::Vector2f rotation; ///< Rotaci�n del objeto en la escena.
    sf::Vector2f scale; ///< Escala del objeto en la escena.
};

