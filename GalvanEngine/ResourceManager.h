#pragma once
#include "Prerequisites.h"
#include "Texture.h"
#include "Services/NotificationService.h"

class
    ResourceManager {
private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    /**
     * @brief Deshabilitar el copiado y la asignación
     */
    ResourceManager(const ResourceManager&) = delete; // Copiado
    ResourceManager& operator=(const ResourceManager&) = delete; // Asignación

public:
    /**
     * @brief Singleton para tener una instancia única de la clase
     */
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    /**
     * @brief Carga una textura desde un archivo y la almacena en el administrador
     * @param fileName Nombre del archivo de la textura
     * @param extension Extensión del archivo de la textura
     */
    bool
        loadTexture(const std::string& fileName, const std::string& extension) {
        // Verificar que la textura haya cargado
        if (m_textures.find(fileName) != m_textures.end()) {
            return true;
        }
        EngineUtilities::TSharedPointer<Texture> texture = EngineUtilities::MakeShared<Texture>(fileName, extension);
        m_textures[fileName] = texture;
    }

    /**
     * @brief Obtiene una textura cargada por su nombre
     * @param fileName Nombre del archivo de la textura
     */
    EngineUtilities::TSharedPointer<Texture>
        getTexture(const std::string& fileName) {
        NotificationService& notifier = NotificationService::getInstance();

        // Verificar que haya una textura xon ese nombre
        auto it = m_textures.find(fileName);
        if (it != m_textures.end()) {
            return it->second;
        }

        std::cout << "Texture not found: " << fileName << std::endl;
        notifier.addMessage(ConsolErrorType::WARNING, "Texture not found: " + fileName);
        EngineUtilities::TSharedPointer<Texture> texture = EngineUtilities::MakeShared<Texture>("Default", "png");
        m_textures["Default"] = texture;
        return texture;
    }

private:
    /**
     * @brief Contenedor tipo mapa de las texturas almacenadas
     */
    std::unordered_map<std::string, EngineUtilities::TSharedPointer<Texture>> m_textures;
};
