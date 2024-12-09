#include "UserInterface.h"
#include "Window.h"
#include "imgui_internal.h"

/**
 * @brief Configura el estilo y la apariencia de la interfaz gráfica.
 */
void
UserInterface::init() {
    // Setup GUI Style
    setupGUIStyle();
}

/**
 * @brief Actualiza la interfaz de usuario.
 */
void
UserInterface::update() {
}

/**
 * @brief Renderiza los elementos visuales de la UI en pantalla.
 */
void
UserInterface::render() {
}

/**
 * @brief Libera los recursos de la interfaz de usuario.
 */
void
UserInterface::destroy() {
}

/**
 * @brief Configura el estilo y los colores de la GUI mediante ImGUI
 */
void UserInterface::setupGUIStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // Ajuste de bordes para un aspecto más suave
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.WindowRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 4.0f;

    // Colores inspirados en el esquema de Xbox
    ImVec4 green = ImVec4(0.18f, 0.67f, 0.35f, 1.00f);       // Verde característico de Xbox
    ImVec4 greenHover = ImVec4(0.20f, 0.70f, 0.40f, 1.00f);   // Verde más brillante al hacer hover
    ImVec4 greenActive = ImVec4(0.12f, 0.55f, 0.30f, 1.00f);  // Verde oscuro al hacer clic

    ImVec4 black = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);        // Fondo oscuro
    ImVec4 lightGray = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);    // Gris para los bordes

    ImVec4* colors = style.Colors;

    // Fondo de la ventana oscuro
    colors[ImGuiCol_WindowBg] = black;

    // Títulos con un color verde más oscuro
    colors[ImGuiCol_TitleBg] = green;
    colors[ImGuiCol_TitleBgActive] = greenActive;
    colors[ImGuiCol_TitleBgCollapsed] = greenHover;

    // Bordes con gris oscuro
    colors[ImGuiCol_Border] = lightGray;

    // Elementos interactivos con mayor contraste
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = greenHover;
    colors[ImGuiCol_FrameBgActive] = greenActive;

    // Botones con un fondo gris oscuro y hover verde
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = greenHover;
    colors[ImGuiCol_ButtonActive] = greenActive;

    // Checkboxes y sliders en verde
    colors[ImGuiCol_CheckMark] = green;
    colors[ImGuiCol_SliderGrab] = green;
    colors[ImGuiCol_SliderGrabActive] = greenHover;

    // Headers
    colors[ImGuiCol_Header] = green;
    colors[ImGuiCol_HeaderHovered] = greenHover;
    colors[ImGuiCol_HeaderActive] = greenActive;

    // Líneas de gráficos en verde
    colors[ImGuiCol_PlotLines] = green;
    colors[ImGuiCol_PlotHistogram] = green;

    // Textos en blanco
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);  // Texto en blanco para un buen contraste
}
void
UserInterface::console(std::map<ConsolErrorType, std::string> programMessages) {
    ImGui::Begin("Console");
    for (const auto& pair : programMessages) {
        ImGui::Text("Code: %d - Message: %s", pair.first, pair.second.c_str());
    }
    ImGui::End();

}

void
UserInterface::hierarchy(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
    NotificationService& notifier = NotificationService::getInstance();

    ImGui::Begin("Hierarchy");

    for (int i = 0; i < actors.size(); ++i) {
        auto& actor = actors[i];
        if (actor.isNull()) continue;

        ImGui::PushID(i);
        std::string displayName = std::to_string(i) + " - " + actor->getName();
        if (ImGui::Selectable(displayName.c_str(), selectedActor == actor)) {
            selectedActor = actor;
        }
        ImGui::PopID();
    }

    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("Create Circle")) {
        auto circleAct = EngineUtilities::MakeShared<Actor>("Circle");
        if (!circleAct.isNull()) {
            circleAct->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);

            circleAct->getComponent<Transform>()->setTransform(Vector2(100.0f, 100.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

            actors.push_back(circleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + circleAct->getName() + "' created successfully.");
        }
    }

    if (ImGui::Button("Create Rectangle")) {
        auto ractangleAct = EngineUtilities::MakeShared<Actor>("Rectangle");
        if (!ractangleAct.isNull()) {
            ractangleAct->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);

            ractangleAct->getComponent<Transform>()->setTransform(Vector2(200.0f, 150.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(ractangleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + ractangleAct->getName() + "' created successfully.");
        }
    }

    if (ImGui::Button("Create Triangle")) {
        auto triangleAct = EngineUtilities::MakeShared<Actor>("Triangle");
        if (!triangleAct.isNull()) {
            triangleAct->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);

            triangleAct->getComponent<Transform>()->setTransform(Vector2(150.0f, 200.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(triangleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + triangleAct->getName() + "' created successfully.");
        }
    }

    ImGui::End();

    
}

/**
   * @brief Verifica si hay un actor seleccionado y, muestra las propiedades de transform
   */
void
UserInterface::inspector() {
   
    if (selectedActor.isNull()) {
        return;
    }

    ImGui::Begin("Inspector");

    // Muestra el nombre del actor
    char objectName[128];
    std::string name = selectedActor->getName();

    // Asegúrate de no exceder el tamaño del array
    if (name.size() < sizeof(objectName)) {
        std::copy(name.begin(), name.end(), objectName);
        objectName[name.size()] = '\0'; // Termina con null
    }

    // Campo para editar el nombre del objeto
    if (ImGui::InputText("Name", objectName, sizeof(objectName))) {
        // Si el usuario edita el nombre, actualiza el actor
        selectedActor->setName(std::string(objectName));
    }

    // Obtiene el componente Transform del actor
    auto transform = selectedActor->getComponent<Transform>();
    if (!transform.isNull()) {

        float* m_position = new float[2];
        float* m_rotation = new float[2];
        float* m_scale = new float[2];
        vec2Control("Position", selectedActor->getComponent<Transform>()->getPosData());
        vec2Control("Rotation", selectedActor->getComponent<Transform>()->getRotData());
        vec2Control("Scale", selectedActor->getComponent<Transform>()->getSclData());

       
    }

    ImGui::End();
}

void
UserInterface::vec2Control(const std::string& label, float* values, float resetValue, float columnWidth) {
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize)) values[0] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize)) values[1] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PopStyleVar();
    ImGui::Columns(1);

    ImGui::PopID();
}