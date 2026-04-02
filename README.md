# SpaceWar

SpaceWar es un juego desarrollado en C++ utilizando la librería SFML.
Este proyecto busca, promover la curiosidad para mejorar el aprendizaje sobre técnicas, diseño, abstracción e implementación del uso de dicho lenguaje de una forma recreativa.

## Características

- **Lenguaje y estándar:** C++20
- **Gráficos y audio:** SFML 3
- **Multiplataforma:** gracias a CMake, puede compilarse en Windows, Linux y macOS con distintos generadores (Visual Studio, Ninja, MinGW Makefiles, MSYS Makefiles, Unix Makefiles, etc.)
- **Gestión de memoria:** uso de `std::unique_ptr` y RAII.
- **Aleatoriedad:** `std::mt19937`, `std::uniform_real_distribution`, entre otros, para simular comportamiento autónomo de enemigos (*pseudo-bots*).
- **Patrón de diseño:** *Factory Method* para instanciación de enemigos.
- **Arquitectura:** modular y orientada a objetos.

## Controles por defecto
Pueden modificarse a conveniencia desde el código fuente.
| Tecla | Acción |
|:-:|-|
| `A` `W` `D` `S` | Movimiento P1 |
| `T` | Disparo P1 |
| `Left` `Up` `Right` `Down` | Movimiento P2 |
| `RShift` | Disparo P2 |
| `J` / `K` o `Down` / `Up` | Seleccionar cantidad de jugadores (en modo menú) |
| `Enter` | Empezar / reiniciar juego (en modo menú, 'gameover' o 'victory') |
| `Esc` | Salir del juego |

## Requerimientos

1. `SFML 3` o superior, puede revisar la versión con:

   - En Arch Linux:

     ```bash
     pkg-config --modversion sfml-all
     ```
     
   - En Windows:
     
       - Si instalaste SFML con VCPKG:
         
           ```bash
           // En PowerShell
           vcpkg list | Select-String sfml
           // En CMD
           vcpkg list | findstr sfml
           ```
           
       - Si instalaste SFML con MSYS2:
         
           ```bash
           pacman -Qs sfml
           ```
     
2. Herramienta `Cmake` versión 3.30 o superior, puede revisar con:

    ```bash
    cmake --version
    ```
    Puede utilizar GNU Make configurando un archivo Makefile personalizado, pero naturalmente este proyecto ya está configurado para una compilación rápida
    con CMake.
     
3. Estándar de leguaje `C++20`, el archivo CMakeLists.txt llamará automáticamente a dicho estándar y lo utilizará para la compilación.

## Compilación

1. Crear el directorio `build`:
   
   ```bash
   mkdir build
   ```

2. Iniciar generación:

   - En UNIX/Linux:

     ```bash
     cmake -B build
     ```
  
   - En Windows:

     - Con VCPKG:
  
       ```bash
       cmake -B build -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
       ```
       
       Si `[path to vcpkg]` contiene algún espacio, envolver toda la variable con comillas, `"-DCMAKE_TOOLCHAIN_FILE=[...].../vcpkg.cmake"`
       
     - Entorno MSYS2:

       ```bash
       cmake -B build
       ```

       Si se elije el generador de Visual Studio automáticamente, entonces especificar algún generador viable para MSYS2 `cmake -B build -G <generador>`
       como por ejemplo `"MSYS Makefiles"`, `"MinGW Makefiles"` o `Ninja`.
    
3. Iniciar compilación:

   ```bash
   cmake --build build
   ```

## Ejecución

   - En UNIX/Linux:

     ```bash
     ./build/spacewar
     ```

   - En Windows:

     - Con VCPKG:

       ```bash
       ./Debug/spacewar
       ```

     - Entorno MSYS2:

       ```bash
       ./buld/spacewar
       ```

   > [!IMPORTANT]
   > Deberá correr el ejecutable desde la raíz del proyecto, de lo contrario la salida resultará en un error general del programa, ya que no será capaz de          encontrar las rutas a los recursos (fonts, textures, sounds) del juego.

## Contribuciones

   ¡Contribuciones son bienvenidas! Si tienes ideas para mejorar este proyecto, por favor, abre un issue o una pull request.

---

¡Esperamos que disfrutes jugando o aprendiendo de este juego! Si tienes alguna pregunta o sugerencia, no dudes en contactarme. ¡Dominate SpaceWar!
