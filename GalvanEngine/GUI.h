#pragma once
#include "Prerequisites.h"
#include "Actor.h"

class Window;

/**
 * @class GUI
 * @brief Clase que gestiona la interfaz gráfica de usuario (GUI) de la aplicación.
 *
 * Esta clase controla la inicialización, actualización, renderizado y destrucción de los elementos de la interfaz.
 */
class GUI {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	GUI() = default;

	/**
	 * @brief Destructor por defecto.
	 */
	~GUI() = default;

	/**
	 * @brief Constructor que inicializa la GUI con una lista de actores.
	 * @param actors Referencia al vector de punteros compartidos de actores.
	 */
	GUI(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) : m_actores(actors) {}

	/**
	 * @brief Inicializa la interfaz gráfica.
	 */
	void
		init();

	/**
	 * @brief Actualiza el estado de la interfaz gráfica cada frame.
	 */
	void
		update();

	/**
	 * @brief Renderiza los elementos de la interfaz gráfica.
	 */
	void
		render();

	/**
	 * @brief Libera los recursos asociados a la interfaz gráfica.
	 */
	void
		destroy();

	/**
	 * @brief Configura el estilo visual de la GUI.
	 */
	void
		setupGUIStyle();

	/**
	 * @brief Muestra la jerarquía de actores en la interfaz.
	 * @param m_actors Vector de punteros compartidos a los actores en la aplicación.
	 */
	void
		hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& m_actors);

	/**
	 * @brief Muestra mensajes de la consola en la interfaz.
	 * @param m_programMessage Mapa de mensajes clasificados por tipo de error.
	 */
	void
		console(std::map<ConsoleErrorType, std::vector<std::string>> m_programMessage);

	/**
	 * @brief Permite crear y manejar actores desde la GUI.
	 * @param m_actores Vector de punteros compartidos a los actores que se actualizarán en la GUI.
	 */
	void
		actor(std::vector<EngineUtilities::TSharedPointer<Actor>>& m_actores);

private:
	sf::Texture texture; ///< Textura general usada en la interfaz.
	EngineUtilities::TSharedPointer<Actor> DAm; ///< Puntero compartido a un actor específico (propósito general).
	std::vector<EngineUtilities::TSharedPointer<Actor>> m_actores; ///< Lista de actores manejados en la GUI.
	sf::Texture shiguis; ///< Textura adicional para elementos específicos de la interfaz.
};

