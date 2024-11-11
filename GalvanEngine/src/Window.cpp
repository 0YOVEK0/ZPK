#include "Window.h"

/**
 * @brief Constructor que inicializa una ventana de renderizado y una textura de renderizado.
 *
 * Crea una ventana `sf::RenderWindow` con las dimensiones y el título especificados.
 * Inicializa ImGui para trabajar con la ventana de SFML y configura una `sf::RenderTexture` de las mismas dimensiones.
 *
 * @param width Ancho de la ventana.
 * @param height Alto de la ventana.
 * @param title Título de la ventana.
 */
Window::Window(int width, int height, const std::string& title) {
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    if (!m_window) {
        ERROR("Window", "RenderTexture", "CHECK CREATION");
    }
    else {
        MESSAGE("Window", "Window", "OK");
    }

    ImGui::SFML::Init(*m_window); // Inicializar ImGui

    // Crear RenderTexture con las mismas dimensiones que la ventana
    if (!m_renderTexture.create(width, height)) {
        ERROR("Window", "RenderTexture", "CHECK CREATION");
    }
}

/**
 * @brief Destructor que cierra y libera la ventana.
 *
 * Finaliza ImGui y elimina la ventana de renderizado.
 */
Window::~Window() {
    ImGui::SFML::Shutdown();
    delete m_window;
}

/**
 * @brief Renderiza el contenido actual en la textura `RenderTexture`.
 */
void
Window::renderToTexture() {
    m_renderTexture.display();
}

/**
 * @brief Muestra la textura `RenderTexture` en la GUI de ImGui.
 *
 * Renderiza la textura en una ventana de ImGui llamada "Scene" con coordenadas UV invertidas en el eje Y.
 */
void
Window::showInImGui() {
    const sf::Texture& texture = m_renderTexture.getTexture();
    ImVec2 size(texture.getSize().x, texture.getSize().y);

    ImGui::Begin("Scene");
    ImGui::Image((void*)(intptr_t)texture.getNativeHandle(), size, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

/**
 * @brief Maneja eventos de la ventana, incluyendo el cierre y el redimensionado.
 *
 * Procesa eventos de SFML e ImGui. Redimensiona `RenderTexture` si la ventana cambia de tamaño.
 */
void
Window::handleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::Resized:
            unsigned int width = event.size.width;
            unsigned int height = event.size.height;

            m_view = m_window->getView();
            m_view.setSize(static_cast<float>(width),
                           static_cast<float>(height));
            m_window->setView(m_view);

            m_renderTexture.create(width, height);
            break;
        }
    }
}

/**
 * @brief Limpia el contenido de la ventana y la textura de renderizado.
 */
void
Window::clear() {
    if (m_window != nullptr) {
        m_window->clear();
    }
    else {
        ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");
    }

    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.clear();
    }
}

/**
 * @brief Muestra el contenido de la ventana en pantalla.
 */
void
Window::display() {
    if (m_window != nullptr) {
        m_window->display();
    }
    else {
        ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
    }
}

/**
 * @brief Verifica si la ventana sigue abierta.
 *
 * @return `true` si la ventana está abierta, `false` en caso contrario.
 */
bool
Window::isOpen() const {
    if (m_window != nullptr) {
        return m_window->isOpen();
    }
    else {
        ERROR("Window", "isOpen", "CHECK FOR WINDOW POINTER DATA");
        return false;
    }
}

/**
 * @brief Dibuja un objeto en la ventana y en la `RenderTexture`.
 *
 * @param drawable Referencia a un objeto `sf::Drawable` que puede ser dibujado en SFML.
 */
void
Window::draw(const sf::Drawable& drawable) {
    if (m_window != nullptr) {
        m_window->draw(drawable);
    }
    else {
        ERROR("Window", "draw", "CHECK FOR WINDOW POINTER DATA");
    }

    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.draw(drawable);
    }
}

/**
 * @brief Obtiene el puntero a la ventana `RenderWindow`.
 *
 * @return Puntero a `sf::RenderWindow`, o `nullptr` si la ventana no existe.
 */
sf::RenderWindow* Window::getWindow() {
    if (m_window != nullptr) {
        return m_window;
    }
    else {
        ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");
        return nullptr;
    }
}

/**
 * @brief Actualiza el delta time y procesa eventos de ImGui.
 */
void
Window::update() {
    deltaTime = clock.restart();
    ImGui::SFML::Update(*m_window, deltaTime);
}

/**
 * @brief Renderiza los elementos de ImGui en la ventana.
 */
void
Window::render() {
    ImGui::SFML::Render(*m_window);
}

/**
 * @brief Libera y cierra la ventana y finaliza ImGui.
 */
void
Window::destroy() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_window);
}
