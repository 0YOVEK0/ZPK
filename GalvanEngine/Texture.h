#pragma once
#include "Prerequisites.h"
#include "Component.h"

/**
 * @class Texture
 * @brief Componente que gestiona la carga y almacenamiento de una textura.
 *
 * La clase `Texture` permite cargar una imagen desde un archivo y manejarla como un recurso de textura en el sistema.
 * Hereda de la clase `Component` para integrarse con el sistema de componentes.
 */
class Texture : public Component {
public:
    /**
     * @brief Constructor por defecto.
     */
    Texture() = default;

    /**
     * 
     *
     * Este constructor intenta cargar una textura a partir de un nombre de archivo y extensión.
     * Si la carga falla, se intenta cargar una textura por defecto ("ErrorTexture.jpg").
     *
     * @param textureName Nombre del archivo de la textura sin la extensión.
     * @param extension Extensión del archivo (por ejemplo, "png", "jpg").
     */
    Texture(std::string textureName, std::string extension) : m_textureName(textureName),
        m_extension(extension),
        Component(ComponentType::TEXTURE) {
        if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
            std::cout << "Error de carga de textura" << std::endl;
            // Cargar una textura por defecto si falla la primera carga
            m_textureName = "ErrorTexture";
            m_extension = "jpg";
            if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
                std::cout << "Error de carga de textura" << std::endl;
            }
        }
    }

    /**
     * @brief Destructor virtual por defecto.
     */
    virtual
        ~Texture() = default;

    /**
     * @brief Obtiene la textura cargada.
     * @return Referencia a la textura cargada (`sf::Texture`).
     */
    sf::Texture& getTexture() {
        return m_texture;
    }

private:
    std::string m_textureName; ///< Nombre del archivo de la textura.
    std::string m_extension; ///< Extensión del archivo de la textura.
    sf::Texture m_texture; ///< Objeto de textura de SFML que almacena la textura cargada.
};

