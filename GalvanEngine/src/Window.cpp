#include "Window.h"

/*
 * @brief Constructor de la clase Window
 * @param width Ancho de la ventana
 * @param height Alto de la ventana
 * @param title Título de la ventana
 */
Window::Window(int width, int height, const std::string& title) {
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    if (!m_window) {
        ERROR("Window", "Window", "CHECK CONSTRUCTOR");
    }
    else {
        MESSAGE("Window", "Window", "OK");
    }

    // Initialize the ImGui Resource
    ImGui::SFML::Init(*m_window);

    // Crear RenderTexture con las mismas dimensiones que la ventana
    if (!m_renderTexture.create(width, height)) {
        ERROR("Window", "RenderTexture", "CHECK CREATION");
    }
}

Window::~Window() {
    delete m_window;
    delete m_window;
}

/*
 * @brief Maneja los eventos de la ventana, como el cierre de la misma
 */
void
Window::handleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        // Procesar los inputs de IMGUI
        ImGui::SFML::ProcessEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            m_window->close();
            break;
            // Manejar el evento de redimensionar
        case sf::Event::Resized:
            unsigned int width = event.size.width;
            unsigned int height = event.size.height;

            m_view = m_window->getView();
            m_view.setSize(static_cast<float>(width), static_cast<float>(height));
            m_window->setView(m_view);

            // Actualizar RenderTexture si la ventana cambia de tamaño
            m_renderTexture.create(width, height);
            break;
        }
    }
}

/*
 * @brief Limpia la ventana, preparándola para el siguiente ciclo de renderizado
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

void
Window::display() {
    if (m_window != nullptr) {
        m_window->display();
    }
    else {
        ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
    }
}

/*
 * @brief Verifica si la ventana está abierta
 * @return true si la ventana está abierta, false de lo contrario
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

/*
 * @brief Dibuja un objeto en la ventana
 * @param drawable Objeto SFML que se va a dibujar en la ventana
 */
void
Window::draw(const sf::Drawable& drawable) {
    //if (m_window != nullptr) {
    //	m_window->draw(drawable);
    //}
    //else {
    //	ERROR("Window", "draw", "CHECK FOR WINDOW POINTER DATA");
    //}

    // Dibujar en la RenderTexture en lugar de la ventana directamente
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.draw(drawable);
    }
}

sf::RenderWindow*
Window::getWindow() {
    if (m_window != nullptr) {
        return m_window;
    }
    else {
        ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");
        return nullptr;
    }
}

void
Window::renderToTexture() {
    // Después de renderizar todo lo que quieras en la textura
    m_renderTexture.display();
}

void
Window::showInImGui() {
    const sf::Texture& texture = m_renderTexture.getTexture();

    // Obtener el tamaño de la textura
    ImVec2 size(texture.getSize().x, texture.getSize().y);

    // Renderizar la textura en ImGui con las coordenadas UV invertidas en el eje Y
    ImGui::Begin("Scene");
    ImGui::Image((void*)(intptr_t)texture.getNativeHandle(), size, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}


void
Window::update() {
    // Almacena el deltaTime una sola vez
    deltaTime = clock.restart();

    // Usa el deltaTime para actualizar ImGui
    ImGui::SFML::Update(*m_window, deltaTime);
}

void
Window::render() {
    ImGui::SFML::Render(*m_window);
}

/*
 * @brief Libera los recursos de la ventana
 */
void
Window::destroy() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_window);
}