#pragma once
#include "Prerequisites.h"
#include "Actor.h"

class Window;

/**
 * @class GUI
 * @brief Clase que gestiona la interfaz gr�fica de usuario (GUI) de la aplicaci�n.
 *
 * Esta clase controla la inicializaci�n, actualizaci�n, renderizado y destrucci�n de los elementos de la interfaz.
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
	 * @brief Inicializa la interfaz gr�fica.
	 */
	void
		init();

	/**
	 * @brief Actualiza el estado de la interfaz gr�fica cada frame.
	 */
	void
		update();

	/**
	 * @brief Renderiza los elementos de la interfaz gr�fica.
	 */
	void
		render();

	/**
	 * @brief Libera los recursos asociados a la interfaz gr�fica.
	 */
	void
		destroy();

	/**
	 * @brief Configura el estilo visual de la GUI.
	 */
	void
		setupGUIStyle();

	/**
	 * @brief Muestra la jerarqu�a de actores en la interfaz.
	 * @param m_actors Vector de punteros compartidos a los actores en la aplicaci�n.
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
	 * @param m_actores Vector de punteros compartidos a los actores que se actualizar�n en la GUI.
	 */
	void
		actor(std::vector<EngineUtilities::TSharedPointer<Actor>>& m_actores);

private:
	sf::Texture texture; ///< Textura general usada en la interfaz.
	EngineUtilities::TSharedPointer<Actor> DAm; ///< Puntero compartido a un actor espec�fico (prop�sito general).
	std::vector<EngineUtilities::TSharedPointer<Actor>> m_actores; ///< Lista de actores manejados en la GUI.
	sf::Texture shiguis; ///< Textura adicional para elementos espec�ficos de la interfaz.
};

