#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"
#include "Transform.h"

class
    Actor : Entity {
public:
    Actor() = default;

    /*
    * @brief Constructor con parámetro del nombre del actor
    */
    Actor(std::string actorName);

    /*
    * @brief Destructor virtual por defecto
    */
    virtual
        ~Actor() = default;

    /*
    * @brief Actualiza al actor
    * @param deltaTime El tiempo transcurrrido desde la última actualización
    */
    void
        update(float deltaTime) override;

    /*
    * @brief Renderiza al actor
    * @param window Contexto del dispositivo para operaciones gráficas
    */
    void
        render(Window& window) override;

    /**
     * @brief Destruye el actor y libera los recursos asociados.
     */
    void
        destroy();

    /**
     * @brief Función para obtener únicamente el nombre del actor
     */
    std::string
        getName() const;

    /**
     * @brief Permite la modificación del nombre del actor
     */
    void
        setName(const std::string& newName);

    /*
    * @brief Obtiene un componente específico del actor
    * @tparam T Tipo de componente que se va a obtener
    * @return Puntero compartido al componente, o nullptr si no se encuentra
    */
    template <typename T>
    EngineUtilities::TSharedPointer<T>
        getComponent();

private:
    std::string m_name = "Actor";
};

/*
  * El propósito de esta función es buscar y devolver yn componente específico de un
  * actor utilizando el tipo de componente específico como argumentos de la plantilla.
  * Si el componente no se encuentra, la función devuelve nullptr.
  */
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
    for (auto& component : components) {
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent) {
            return specificComponent;
        }
    }
    // Devuelve un TSharedPointer vacío si no se encuentra el componente
    return EngineUtilities::TSharedPointer<T>();
}