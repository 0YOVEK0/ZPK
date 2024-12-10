# ZPK - Graphics Engine

ZPK es el inicio de un motor gráfico diseñado para la creación y manipulación de figuras a través de actores. Este proyecto incorpora tecnologías modernas como **SFML 2.6.1**, un **Entity Component System (ECS)** para una arquitectura modular y escalable, y una interfaz de usuario interactiva basada en **IMGUI**, ofreciendo herramientas robustas para el desarrollo gráfico. Además, el motor cuenta con un **servicio de notificación de errores** para facilitar la depuración y mejorar la experiencia de desarrollo.

**Documentación del código realizada con la ayuda de ChatGPT.**

## Requisitos

- **Sistema Operativo**: Windows, macOS o Linux  
- **Lenguaje**: C++ (con soporte para CMake)  
- **Dependencias adicionales**:  
  - [SFML 2.6.1](https://www.sfml-dev.org/): Para el manejo de gráficos, audio y entrada/salida  
  - [IMGUI](https://github.com/ocornut/imgui): Para la interfaz gráfica de usuario  
  - CMake: Para gestionar la construcción del proyecto  

## Características

- **ECS (Entity Component System)**: Arquitectura flexible y escalable para manejar entidades y sus componentes de manera eficiente.
- **Interfaz de usuario con IMGUI**: Para crear herramientas de desarrollo y depuración de manera rápida y fácil.
- **Servicio de notificación de errores**: Facilita la identificación y notificación de errores, ayudando a los desarrolladores a depurar y manejar problemas en tiempo de ejecución. Las notificaciones se presentan en la interfaz gráfica para una visibilidad inmediata.

## Instalación

1. Clona el repositorio:  
   ```bash
   git clone https://github.com/0YOVEK0/zpk.git
   cd zpk
