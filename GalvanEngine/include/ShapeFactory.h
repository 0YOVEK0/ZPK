#pragma once
#include "Prerequisites.h"

class
	Window {
public:
	Window() = default;
	Window(int width, int height, const std::string& title);
	~Window();

	/**
	 * @brief Procesa los eventos de la ventana y actualiza el estado de esta.
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
	 * @return true si la ventana está abierta, false en caso contrario.
	 */
	bool
		isOpen() const;

	/**
	 * @brief Dibuja un objeto sf::Drawable en la ventana.
	 * @param drawable El objeto a dibujar en la ventana.
	 */
	void
		draw(const sf::Drawable& drawable);

	/**
	 * @brief Obtiene el objeto interno SFML RenderWindow.
	 * @return Un puntero al objeto interno SFML RenderWindow.
	 */
	sf::RenderWindow*
		getWindow();

	/**
	 * @brief Inicializa la ventana.
	 */
	void
		init();

	/**
	 * @brief Actualiza la ventana por cada frame.
	 */
	void
		update();

	/**
	 * @brief Realiza el renderizado de la ventana.
	 */
	void
		render();

	/**
	 * @brief Destruye la ventana y libera sus recursos.
	 */
	void
		destroy();

	/**
	 * @brief Permite renderizar los objetos gráficos a una textura.
	 */
	void
		renderToTexture();

	/**
	 * @brief Muestra el contenido de la ventana en ImGui.
	 */
	void
		showInImGui();

private:
	sf::RenderWindow* m_window;
	sf::View m_view;
public:
	sf::RenderTexture m_renderTexture; 
	sf::Time deltaTime;
	sf::Clock clock;
};