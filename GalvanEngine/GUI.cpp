#include "GUI.h"
#include "Window.h"
#include "NotifySingleton.h"

/**
 * @brief Inicializa la GUI configurando el estilo visual.
 */
void
GUI::init() {
    setupGUIStyle();
}

/**
 * @brief Actualiza el estado de la GUI (sin implementación en esta versión).
 */
void
GUI::update() {
}

/**
 * @brief Renderiza los elementos de la GUI (sin implementación en esta versión).
 */
void
GUI::render() {
}

/**
 * @brief Libera los recursos asociados a la GUI.
 */
void
GUI::destroy() {
}

/**
 * @brief Configura el estilo visual de la GUI.
 *
 * Define el tamaño de los bordes y los colores personalizados para elementos de la GUI.
 */
void
GUI::setupGUIStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 1.0f;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f); // Fondo oscuro
    colors[ImGuiCol_Border] = ImVec4(0.9f, 0.7f, 0.0f, 1.0f);   // Color del borde
    colors[ImGuiCol_TitleBg] = ImVec4(0.8f, 0.4f, 0.0f, 1.0f);  // Fondo del título
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.9f, 0.5f, 0.0f, 1.0f); // Fondo del título activo
}

/**
 * @brief Muestra una lista jerárquica de actores en la escena.
 *
 * Esta función crea una ventana de jerarquía en ImGui donde se listan todos los actores
 * creados en la escena, permitiendo la selección de un actor específico y la manipulación de sus propiedades.
 *
 * @param m_actores Vector de actores presentes en la escena.
 */
void
GUI::hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& m_actores) {
    ImGui::Begin("Hierarchy");

    static int selectedActorIndex = -1;
    ImGui::TextColored(ImVec4(1, 0, 1, 1), "%s", "Objetos creados en escena:\n");

    for (size_t i = 0; i < m_actores.size(); ++i) {
        const auto& actor = m_actores[i];
        if (actor) {
            if (ImGui::Selectable(actor->m_name.c_str(), selectedActorIndex == static_cast<int>(i))) {
                selectedActorIndex = static_cast<int>(i);
            }
        }
    }

    if (selectedActorIndex >= 0 && selectedActorIndex < static_cast<int>(m_actores.size())) {
        auto& selectedActor = m_actores[selectedActorIndex];
        if (selectedActor) {
            ImGui::Separator();
            ImGui::Text("Propiedades del Actor seleccionado:");

            // Modificación de posición y escala
            sf::Vector2f position = selectedActor->getComponent<Transform>()->getPosition();
            if (ImGui::DragFloat2("Position", reinterpret_cast<float*>(&position), 1.0f)) {
                selectedActor->getComponent<Transform>()->setPosition(position);
            }
            sf::Vector2f scale = selectedActor->getComponent<Transform>()->getScale();
            if (ImGui::DragFloat2("Scale", reinterpret_cast<float*>(&scale), 1.0f)) {
                selectedActor->getComponent<Transform>()->setScale(scale);
            }

            static int currentShapeTypeIndex = 0;
            const char* shapeTypes[] = { "EMPTY", "CIRCLE", "RECTANGLE", "TRIANGLE" };

            if (ImGui::Combo("Shape Type", &currentShapeTypeIndex, shapeTypes, IM_ARRAYSIZE(shapeTypes))) {
                ShapeType selectedShapeType = static_cast<ShapeType>(currentShapeTypeIndex);
                selectedActor->getComponent<ShapeFactory>()->createShape(selectedShapeType);
            }
        }
    }
    ImGui::End();
}

/**
 * @brief Muestra una consola en la GUI con mensajes clasificados por tipo de error.
 *
 * Los mensajes se muestran en colores específicos según el tipo: verde para normal, naranja para advertencia y rojo para error.
 *
 * @param m_programMessage Mapa de mensajes clasificados por tipo de error.
 */
void
GUI::console(std::map<ConsoleErrorType, std::vector<std::string>> m_programMessage) {
    ImGui::Begin("Console");

    for (const auto& message : m_programMessage) {
        for (const std::string& msg : message.second) {
            std::string formattedMessage;
            switch (message.first) {
            case ConsoleErrorType::NORMAL:
                formattedMessage = "[NORMAL]: " + msg;
                ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", formattedMessage.c_str());
                break;
            case ConsoleErrorType::WARNING:
                formattedMessage = "[WARNING]: " + msg;
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), "%s", formattedMessage.c_str());
                break;
            case ConsoleErrorType::ERROR:
                formattedMessage = "[ERROR]: " + msg;
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", formattedMessage.c_str());
                break;
            }
        }
    }

    ImGui::End();
}

/**
 * @brief Generador de actores en la GUI, permite crear diferentes tipos de actores (círculo, rectángulo, triángulo).
 *
 * Cada tipo de actor tiene un botón en la GUI para su creación, y se le asigna un nombre único
 * con un sufijo numérico para evitar conflictos de ID.
 *
 * @param m_actores Vector de actores donde se agregan los nuevos actores creados.
 */
#include "NotifySingleton.h"

void
GUI::actor(std::vector<EngineUtilities::TSharedPointer<Actor>>& m_actores) {
    ImGui::Begin("Actor Generator");

    // Obtener la instancia del NotifySingleton
    NotifySingleton* noty = NotifySingleton::getInstance();

    static int circleCount = 0;
    static int rectangleCount = 0;
    static int triangleCount = 0;

    ImGui::PushID("Button1");
    if (ImGui::Button("Create Circle Actor")) {
        std::string actorName = "Circle_" + std::to_string(++circleCount);
        auto DAm = EngineUtilities::MakeShared<Actor>(actorName);

        if (!DAm.isNull()) {
            DAm->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
            DAm->getComponent<ShapeFactory>()->setFillColor(sf::Color::Yellow);

            DAm->getComponent<Transform>()->setPosition(sf::Vector2f(280.0f, 460.0f));
            DAm->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
            DAm->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

            m_actores.push_back(DAm);
            std::cout << "Actor creado: " << actorName << ", total de actores en m_actors: " << m_actores.size() << std::endl;

            // Agregar mensaje de notificación
            noty->addMessage(ConsoleErrorType::NORMAL, "Circle Actor created with name: " + actorName);
        }
    }
    ImGui::PopID();
    ImGui::Separator();

    ImGui::PushID("Button2");
    if (ImGui::Button("Create Rectangle Actor")) {
        std::string actorName = "Rectangle_" + std::to_string(++rectangleCount);
        auto DAm = EngineUtilities::MakeShared<Actor>(actorName);

        if (!DAm.isNull()) {
            DAm->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
            DAm->getComponent<ShapeFactory>()->setFillColor(sf::Color::Red);

            DAm->getComponent<Transform>()->setPosition(sf::Vector2f(280.0f, 460.0f));
            DAm->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
            DAm->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

            m_actores.push_back(DAm);
            std::cout << "Actor creado: " << actorName << ", total de actores en m_actors: " << m_actores.size() << std::endl;

            // Agregar mensaje de notificación
            noty->addMessage(ConsoleErrorType::NORMAL, "Rectangle Actor created with name: " + actorName);
        }
    }
    ImGui::PopID();
    ImGui::Separator();

    ImGui::PushID("Button3");
    if (ImGui::Button("Create Triangle Actor")) {
        std::string actorName = "Triangle_" + std::to_string(++triangleCount);
        auto DAm = EngineUtilities::MakeShared<Actor>(actorName);

        if (!DAm.isNull()) {
            DAm->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
            DAm->getComponent<ShapeFactory>()->setFillColor(sf::Color::Black);

            DAm->getComponent<Transform>()->setPosition(sf::Vector2f(280.0f, 460.0f));
            DAm->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
            DAm->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

            m_actores.push_back(DAm);
            std::cout << "Actor creado: " << actorName << ", total de actores en m_actors: " << m_actores.size() << std::endl;

            // Agregar mensaje de notificación
            noty->addMessage(ConsoleErrorType::NORMAL, "Triangle Actor created with name: " + actorName);
        }
    }
    ImGui::PopID();
    ImGui::End();
}
