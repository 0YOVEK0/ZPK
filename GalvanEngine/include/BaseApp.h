#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "ShapeFactory.h"
#include "Actor.h"
#include "UserInterface.h"
#include "Services/NotificationService.h"
#include "Services/ResourceManager.h"

class
	BaseApp {
public:
	/**
	 * @brief Constructor por defecto
	 */
	BaseApp() = default;

	/**
	 * @brief Destructor de la clase BaseApp
	 */
	~BaseApp();

	/**
	 * @brief Función encargada de correr la aplicación en el main
	 * @return Código de salida de la aplicación
	 */
	int
		run();

	/**
	 * @brief Función de inicialización de la aplicación, configura los recursos necesarios
	 * @return Verdadero si la inicialización fue exitosa, falso si hubo un error
	 */
	bool
		initialize();

	/**
	 * @brief Función que se actualiza por cada frame, procesando la lógica del juego
	 */
	void
		update();

	/**
	 * @brief Función de renderizado, dibuja los elementos en la ventana
	 */
	void
		render();

	/**
	 * @brief Limpia los recursos y elementos de la aplicación antes de salir
	 */
	void
		cleanup();

	/**
	 * @brief Actualiza el movimiento de los actores (por ejemplo, el círculo)
	 * @param deltaTime El tiempo transcurrido entre un frame y el siguiente
	 * @param circle Puntero compartido al actor que representa el círculo
	 */
	void
		updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
	sf::Clock clock;
	sf::Time deltaTime;

	Window* m_window; // Puntero a la ventana donde se dibujan los elementos
	                EngineUtilities::TSharedPointer<Actor> Circle;
	                EngineUtilities::TSharedPointer<Actor> Triangle;
					EngineUtilities::TSharedPointer<Actor> Square;
	                EngineUtilities::TSharedPointer<Actor> Track;

	// Lista de actores en la escena
	std::vector< EngineUtilities::TSharedPointer<Actor>> m_actors;

	//Array para la actividad de los puntos
	Vector2 points[8];
	int m_currentPoint = 0;
	int m_currentActor = 0;

	// Texturas para los elementos en escena
	sf::Texture texture;
	sf::Texture Rob;

	// Interfaz gráfica de usuario
	UserInterface m_GUI;
};
