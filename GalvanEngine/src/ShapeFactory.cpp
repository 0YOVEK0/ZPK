#include "ShapeFactory.h"

/**
 * @brief Crea una forma gráfica según el tipo especificado.
 *
 * Este método configura la forma (`m_shape`) en función del tipo `ShapeType` proporcionado.
 * Se crean diferentes tipos de `sf::Shape` como círculo, rectángulo, y triángulo, y cada forma
 * se inicializa con un color blanco.
 *
 * @param shapeType Tipo de forma a crear (e.g., CIRCLE, RECTANGLE, TRIANGLE).
 * @return Puntero a la forma creada (`sf::Shape*`), o `nullptr` si el tipo es `NONE` o no se reconoce.
 */
sf::Shape* ShapeFactory::createShape(ShapeType shapeType) {
    m_shapeType = shapeType;
    switch (shapeType) {
    case NONE: // No crea ninguna forma
        return nullptr;

    case CIRCLE: { // Círculo con radio de 10
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        circle->setFillColor(sf::Color::White);
        m_shape = circle;
        return circle;
    }

    case RECTANGLE: { // Rectángulo de tamaño 100x50
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);
        m_shape = rectangle;
        return rectangle;
    }

    case TRIANGLE: { // Triángulo (círculo de 3 lados)
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);
        triangle->setFillColor(sf::Color::White);
        m_shape = triangle;
        return triangle;
    }

    default: // Tipo de forma no reconocido
        return nullptr;
    }
}

/**
 * @brief Establece la posición de la forma.
 * @param x Coordenada X de la posición.
 * @param y Coordenada Y de la posición.
 */
void
ShapeFactory::setPosition(float x, float y) {
    if (m_shape) {
        m_shape->setPosition(x, y);
    }
}

/**
 * @brief Establece la rotación de la forma.
 * @param angle Ángulo de rotación en grados.
 */
void
ShapeFactory::setRotation(float angle) {
    if (m_shape) {
        m_shape->setRotation(angle);
    }
}

/**
 * @brief Escala la forma en función de un vector de escala.
 * @param scl Vector de escala (X e Y).
 */
void
ShapeFactory::setScale(const sf::Vector2f& scl) {
    if (m_shape) {
        m_shape->setScale(scl);
    }
}

/**
 * @brief Establece el color de relleno de la forma.
 * @param color Color a aplicar a la forma.
 */
void
ShapeFactory::setFillColor(const sf::Color& color) {
    if (m_shape) {
        m_shape->setFillColor(color);
    }
}

/**
 * @brief Establece la posición de la forma usando un vector.
 * @param position Vector que contiene las coordenadas X e Y de la posición.
 */
void
ShapeFactory::setPosition(const sf::Vector2f& position) {
    if (m_shape) {
        m_shape->setPosition(position);
    }
}
