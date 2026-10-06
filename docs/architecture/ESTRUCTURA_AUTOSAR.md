# Estructura educativa AUTOSAR Classic

Este workspace separa el software siguiendo las capas principales de AUTOSAR
Classic. No contiene una implementación certificada de AUTOSAR ni sustituye
las herramientas de configuración de un proveedor.

## Directorios

- `Application/Swc/`: componentes de software de aplicación. No deben acceder
  directamente a registros del microcontrolador.
- `Application/Composition/`: composición y conexiones conceptuales entre SWC.
- `Rte/Generated/`: artefactos generados del Runtime Environment. No deben
  editarse manualmente cuando exista un generador.
- `Bsw/Services/`: servicios del Basic Software.
- `Bsw/EcuAbstraction/`: abstracción de dispositivos externos de la ECU.
- `Bsw/Mcal/`: drivers dependientes del STM32 (`Mcu`, `Port`, `Dio`, etc.).
- `Bsw/ComplexDrivers/`: acceso especial a hardware que no encaje en el MCAL.
- `Config/EcuC/`: configuración fuente legible por humanos.
- `Config/Generated/`: configuración generada; no debe editarse manualmente.
- `Common/Include/`: tipos y definiciones comunes, por ejemplo
  `Platform_Types.h`, `Std_Types.h` y `Compiler.h`.
- `Platform/Device/`: archivos específicos del STM32F446.
- `Platform/Startup/`: código de arranque y tabla de vectores.
- `Platform/Linker/`: scripts del enlazador y mapa de memoria.
- `Integration/Test/`: pruebas realizadas sobre el firmware integrado.
- `test/unit/`: pruebas unitarias ejecutadas en el equipo anfitrión.
- `test/mocks/`: dobles y mocks usados por las pruebas.
- `test/integration/`: pruebas de integración automatizadas.
- `docs/standards/`: notas y referencias a AUTOSAR, MISRA y documentos de ST.
- `tools/scripts/`: herramientas auxiliares; no contiene código del producto.

## Dependencias permitidas

El sentido normal de las llamadas es:

`Application -> RTE -> BSW -> MCAL -> registros del STM32`

La aplicación no incluye headers de `Bsw/Mcal` ni de `Platform/Device`.
Los registros solo se acceden desde MCAL, startup o un Complex Driver
justificado.

## Estado de migración

La carpeta `app/` actual se conserva temporalmente como ejemplo bare-metal
funcional. Los archivos `startup_stm32f446xx.s`, `linker.ld` y
`STM32F446.svd` también permanecen en la raíz para no romper el makefile.

La migración debe hacerse por etapas:

1. Preparar tipos comunes y convenciones del compilador.
2. Crear la configuración de `Mcu`, `Port` y `Dio`.
3. Encapsular el acceso a registros dentro de MCAL.
4. Crear un SWC para el comportamiento del LED.
5. Añadir una RTE educativa que conecte el SWC con `Dio`.
6. Adaptar el makefile y, solo entonces, retirar `app/`.

## Convenciones

- Los archivos generados van únicamente en carpetas `Generated/`.
- El código generado no se corrige manualmente: se corrige su fuente o
  configuración.
- Cada módulo tiene `include/`, `src/` y `config/` cuando empiece a contener
  código; no se crean anticipadamente si siguen vacíos.
- Las desviaciones de MISRA deben documentarse y justificarse.
- AUTOSAR define interfaces y comportamiento; el mapa de registros del
  STM32F446 se obtiene de RM0390 y de los headers CMSIS/ST.
