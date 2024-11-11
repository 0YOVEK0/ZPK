#pragma once
#include "Prerequisites.h"

/**
 * @class Window
 * @brief Clase que gestiona una ventana de renderizado usando SFML.
 *
 * La clase `Window` proporciona métodos para inicializar, actualizar, renderizar y manejar eventos de una ventana.
 * Además, permite la integración con ImGui y el renderizado en texturas.
 */
class Window {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	Window() = default;

	/**
	 * @brief Constructor que inicializa la ventana con dimensiones y título específicos.
	 * @param width Ancho de la ventana.
	 * @param height Alto de la ventana.
	 * @param title Título de la ventana.
	 */
	Window(int width, int height, const std::string& title);

	/**
	 * @brief Destructor que cierra y libera la ventana.
	 */
	~Window();

	/**
	 * @brief Renderiza el contenido de la ventana en una textura.
	 */
	void
		renderToTexture();

	/**
	 * @brief Muestra el contenido de la ventana en ImGui.
	 */
	void
		showInImGui();

	/**
	 * @brief Maneja eventos de la ventana, como cierres y entradas de usuario.
	 */
	void
		handleEvents();

	/**
	 * @brief Limpia el contenido de la ventana con el color predeterminado.
	 */
	void
		clear();

	/**
	 * @brief Muestra el contenido de la ventana en la pantalla.
	 */
	void
		display();

	/**
	 * @brief Verifica si la ventana sigue abierta.
	 * @return `true` si la ventana está abierta, `false` en caso contrario.
	 */
	bool
		isOpen() const;

	/**
	 * @brief Dibuja un objeto que puede ser representado en la ventana.
	 * @param drawable Referencia a un objeto SFML que puede ser dibujado.
	 */
	void
		draw(const sf::Drawable& drawable);

	/**
	 * @brief Obtiene el objeto interno de SFML `RenderWindow`.
	 * @return Un puntero al objeto interno `sf::RenderWindow`.
	 */
	sf::RenderWindow* getWindow();

	/**
	 * @brief Inicializa recursos y configuraciones de la ventana.
	 */
	void
		init();

	/**
	 * @brief Actualiza el estado de la ventana por cada frame.
	 */
	void
		update();

	/**
	 * @brief Renderiza los elementos en la ventana.
	 */
	void
		render();

	/**
	 * @brief Libera recursos asociados a la ventana.
	 */
	void
		destroy();

	sf::Time deltaTime; /// Tiempo transcurrido entre frames.
	sf::Clock clock; ///Reloj para medir el tiempo transcurrido.
	sf::RenderTexture m_renderTexture; ///< Textura de renderizado para dibujar en una textura.

private:
	sf::RenderWindow* m_window; /// ventana de SFML para renderizado.
	sf::View m_view; /// Vista de la ventana para controlar el área de renderizado.
};
