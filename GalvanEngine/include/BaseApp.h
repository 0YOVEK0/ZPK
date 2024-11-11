#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Actor.h"
#include "GUI.h"

/**
 * @class BaseApp
 * @brief Clase que representa la aplicación base del motor. Controla el ciclo de vida de la aplicación y maneja los actores.
 */
class BaseApp {
public:
    /**
     * @brief Constructor por defecto.
     */
    BaseApp() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~BaseApp() = default;

    /**
     * @brief Ejecuta la aplicación, generalmente llamada en la función `main`.
     * @return Código de retorno de la aplicación.
     */
    int
        run();

    /**
     * @brief Inicializa la aplicación y sus recursos.
     * @return `true` si la inicialización fue exitosa, `false` en caso contrario.
     */
    bool
        initialize();

    /**
     * @brief Actualiza el estado de la aplicación en cada frame.
     */
    void
        update();

    /**
     * @brief Renderiza el contenido de la aplicación.
     */
    void
        render();

    /**
     * @brief Libera los recursos de la aplicación antes de finalizar.
     */
    void
        cleanup();

    /**
     * @brief Define un patrón de patrullaje para un actor en forma de círculo.
     *
     * Esta función mueve al actor a través de una serie de puntos (waypoints) definidos,
     * simulando un comportamiento de patrullaje.
     *
     * @param deltaTime Tiempo transcurrido desde el último frame.
     * @param circle Puntero compartido al actor que realizará el patrullaje.
     */
    void
        patrolPattern(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

    /**
     * @brief Obtiene la lista de actores en la aplicación.
     * @return Referencia a un vector de punteros compartidos a los actores.
     */
    std::vector<EngineUtilities::TSharedPointer<Actor>>& getActors() { return m_actors; }

    std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors; ///< Vector de actores gestionados por la aplicación.

private:
    sf::Texture shyGuy; ///< Textura para un personaje o elemento visual específico.
    sf::Texture texture; ///< Textura genérica para elementos visuales.
    GUI m_GUI; ///< Interfaz gráfica de usuario de la aplicación.

    std::vector<sf::Vector2f> waypoints = { ///< Puntos de patrullaje.
          sf::Vector2f(290.0f, 460.0f),
          sf::Vector2f(340.0f, 460.0f),
          sf::Vector2f(420.0f, 50.0f),
          sf::Vector2f(100.0f, 80.0f),
          sf::Vector2f(220.0f, 220.0f),
          sf::Vector2f(55.0f, 450.0f)
    };
    int currentPoint = 0; ///< Índice del punto actual de patrullaje.

    Window* m_window; ///< Puntero a la ventana principal de la aplicación.
    sf::CircleShape* shape; ///< Forma circular utilizada en la aplicación.
    EngineUtilities::TSharedPointer<Actor> Triangle; ///< Puntero compartido a un actor en forma de triángulo.
    EngineUtilities::TSharedPointer<Actor> Circle; ///< Puntero compartido a un actor en forma de círculo.
    EngineUtilities::TSharedPointer<Actor> Circuit; ///< Puntero compartido a un actor en forma de circuito.
};
