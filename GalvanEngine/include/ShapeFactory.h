#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/**
 * @class ShapeFactory
 * @brief Componente responsable de crear y gestionar una forma gráfica en la aplicación.
 *
 * La clase `ShapeFactory` permite crear diferentes tipos de formas (como círculos, rectángulos, etc.)
 * y aplicarles transformaciones como posición, rotación, y escala. Hereda de `Component`.
 */
class ShapeFactory : public Component {
public:
    /**
     * @brief Constructor por defecto.
     */
    ShapeFactory() = default;

    /**
     * @brief Destructor virtual por defecto.
     */
    virtual
        ~ShapeFactory() = default;

    /**
     * @brief Constructor que inicializa el `ShapeFactory` con un tipo de forma.
     * @param shapeType Tipo de forma inicial.
     */
    ShapeFactory(ShapeType shapeType) : m_shape(nullptr), 
                                        m_shapeType(ShapeType::NONE),
                                        Component(ComponentType::SHAPE) {}

    /**
     * @brief Crea una forma específica según el tipo indicado.
     * @param shapeType Tipo de forma a crear.
     * @return Puntero a la forma creada.
     */
    sf::Shape* createShape(ShapeType shapeType);

    /**
     * @brief Actualiza el estado del componente de forma.
     *
     * @param deltaTime Tiempo transcurrido desde la última actualización (no implementado en este caso).
     */
    void
        update(float deltaTime) override {}

    /**
     * @brief Establece la posición de la forma.
     * @param x Posición en el eje X.
     * @param y Posición en el eje Y.
     */
    void
        setPosition(float x, float y);

    /**
     * @brief Establece la rotación de la forma.
     * @param angle Ángulo de rotación en grados.
     */
    void
        setRotation(float angle);

    /**
     * @brief Escala la forma en base a un vector de escala.
     * @param scl Vector de escala.
     */
    void
        setScale(const sf::Vector2f& scl);

    /**
     * @brief Cambia el color de relleno de la forma.
     * @param color Color a aplicar a la forma.
     */
    void
        setFillColor(const sf::Color& color);

    /**
     * @brief Establece la posición de la forma mediante un vector de posición.
     * @param position Vector que indica la posición.
     */
    void
        setPosition(const sf::Vector2f& position);

    /**
     * @brief Renderiza la forma en la ventana proporcionada.
     *
     * @param window Objeto `Window` donde se renderiza la forma (no implementado en este caso).
     */
    void
        render(Window window) override {}

    /**
     * @brief Obtiene la forma creada.
     * @return Puntero a la forma actual (`sf::Shape*`).
     */
    sf::Shape* getShape() {
        return m_shape;
    }

private:
    ShapeType m_shapeType; ///< Tipo de la forma actual.
public:
    sf::Shape* m_shape; ///< Puntero a la forma creada.
};
