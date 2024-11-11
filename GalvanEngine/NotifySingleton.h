#pragma once
#include "Prerequisites.h"
#include "GUI.h"

/**
 * @class NotifySingleton
 * @brief Clase singleton para manejar notificaciones y mensajes de la consola.
 *
 * Esta clase permite registrar y mostrar mensajes clasificados por tipo de error (normal, advertencia, error).
 * El patrón singleton asegura que solo exista una instancia de esta clase.
 */
class NotifySingleton {
public:
    /**
     * @brief Constructor privado para evitar la instanciación directa de la clase.
     */
    NotifySingleton() {};

    /**
     * @brief Obtiene la instancia única del singleton de NotifySingleton.
     *
     * Si la instancia no existe, se crea una nueva.
     *
     * @return Puntero a la única instancia de NotifySingleton.
     */
    static NotifySingleton* getInstance() {
        if (m_instance != nullptr) {
            return m_instance;
        }
        else {
            m_instance = new NotifySingleton;
        }
        return m_instance;
    }

    /**
     * @brief Destructor por defecto.
     */
    ~NotifySingleton() = default;

    /**
     * @brief Registra un mensaje en el sistema de notificaciones.
     *
     * Este método almacena el mensaje en un mapa, agrupado por tipo de error.
     *
     * @param msgType Tipo de error del mensaje (NORMAL, WARNING, ERROR).
     * @param _msg El mensaje a registrar.
     */
    void
        addMessage(ConsoleErrorType msgType, const std::string& _msg) {
        m_programMessage[msgType].push_back(_msg); // Agregar el mensaje al vector
    }

    /**
     * @brief Envía las notificaciones registradas a la consola GUI.
     *
     * Este método se encarga de notificar a la GUI sobre los mensajes almacenados,
     * pasándolos al método console() de la clase GUI.
     *
     * @param msgType Tipo de error del mensaje.
     * @param _msg El mensaje a notificar.
     */
    void
        notify(ConsoleErrorType msgType,
               const std::string& _msg) {
        GUI* gui;
        gui->console(m_programMessage);
    }

    /**
     * @brief Devuelve el mapa de mensajes registrados.
     *
     * @return Mapa con los mensajes agrupados por tipo de error.
     */
    std::map<ConsoleErrorType, 
        std::vector<std::string>> showNotification() const {
        return m_programMessage;
    }

private:
    static NotifySingleton* m_instance; ///< Instancia única de la clase NotifySingleton.
                            std::map<ConsoleErrorType, 
                            std::vector<std::string>> m_programMessage; ///< Mapa para almacenar los mensajes clasificados por tipo de error.
};
