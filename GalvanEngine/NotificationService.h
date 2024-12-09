#pragma once
#include "Prerequisites.h"
#include <unordered_map>
#include <optional>

class NotificationService {
private:
    // Constructor privado para evitar instancias múltiples
    NotificationService() = default;

    // Eliminar constructor de copia y operador de asignación
    NotificationService(const NotificationService&) = delete;
    NotificationService& operator=(const NotificationService&) = delete;

public:
    // Accede a la instancia singleton mediante un unique_ptr
    static NotificationService& getInstance() {
        static NotificationService instance;
        return instance;
    }

    // Agrega un mensaje de notificación
    void addMessage(ConsolErrorType errType, const std::string& message) {
        m_programMessages[errType] = message;
    }

    // Muestra todos los mensajes en consola con colores
    void showAllMessages() const {
        for (const auto& pair : m_programMessages) {
            ImVec4 color = getColorForSeverity(pair.first);
            // Aquí podrías implementar una función para imprimir el color
            std::cout << "Code: " << pair.first << " - Message: " << pair.second << std::endl;
        }
    }

    // Obtiene un mensaje según el código de error, ahora usando std::optional
    std::optional<std::string> getMessage(ConsolErrorType errType) const {
        auto it = m_programMessages.find(errType);
        if (it != m_programMessages.end()) {
            return it->second;
        }
        return std::nullopt; // Retorna un valor nulo si no se encuentra
    }

    // Guarda los mensajes en un archivo con manejo de excepciones
    void saveMessagesToFile(const std::string& filename) const {
        try {
            std::ofstream file(filename);
            if (!file.is_open()) {
                throw std::ios_base::failure("No se pudo abrir el archivo para guardar los mensajes.");
            }

            for (const auto& pair : m_programMessages) {
                file << "Code: " << pair.first << " - Message: " << pair.second << "\n";
            }

            file.close();
            std::cout << "Mensajes guardados en el archivo: " << filename << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error al guardar los mensajes: " << e.what() << std::endl;
        }
    }

    // Obtiene las notificaciones almacenadas
    std::unordered_map<ConsolErrorType, std::string>& getNotifications() {
        return m_programMessages;
    }

private:
    // Obtiene un color para la notificación dependiendo del tipo de mensaje
    ImVec4 getColorForSeverity(ConsolErrorType errorType) const {
        switch (errorType) {
        case ConsolErrorType::NORMAL:
            return ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
        case ConsolErrorType::WARNING:
            return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        case ConsolErrorType::ERROR:
            return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        default:
            return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    // Mapa para almacenar los mensajes del programa
    std::unordered_map<ConsolErrorType, std::string> m_programMessages;
};
