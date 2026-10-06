# MCAL AUTOSAR Classic para STM32F446RE

Implementación desde cero de una capa MCAL (*Microcontroller Abstraction Layer*)
siguiendo **AUTOSAR Classic Platform R20-11**, sobre una tarjeta Nucleo-F446RE
con STM32F446RET6 (Cortex-M4).

El objetivo del proyecto no es replicar un stack comercial, sino **traducir una
especificación AUTOSAR y un manual de referencia a código verificable**: cada
interfaz pública se justifica con un requisito del SWS correspondiente, y cada
acceso a registro con un capítulo del RM0390. Nada se escribe "porque funciona".

> **Estado: en desarrollo.** La tabla de abajo dice exactamente qué está hecho.
> Ningún módulo se marca como terminado hasta cumplir los criterios de aceptación
> definidos en la guía de implementación.

---

## Qué está implementado

| Componente | Estado | Cómo se verificó |
|---|---|---|
| `Common/Include/Platform_Types.h` | Implementado | 11 pruebas unitarias de tamaños, signo, `boolean`, `TRUE`/`FALSE` y orden de bytes, más aserciones estáticas que se evalúan en cada compilación. |
| `Common/Include/Compiler.h` | Implementado | 16/16 macros. Las cuatro variantes de puntero comprobadas por compilación: se verifica que cada una permita o rechace mover el puntero y escribir el dato, según exige su requisito. |
| `Platform/Device/Stm32f446xx_Registers.h` | Implementado | 9 pruebas unitarias de direcciones base, desplazamientos (`offsetof`) y tamaño total de las estructuras RCC y GPIO. Contrastado además contra `STM32F446.svd` de ST: 57 bases y 36 offsets, **0 discrepancias**. |
| `Bsw/Mcal/Mcu/include/Mcu_Types.h` | Tipos definidos | Los 8 tipos que exige SWS_MCUDriver R20-11. El módulo aún no está implementado. |
| `Common/Include/Compiler_Cfg.h`, `Std_Types.h`, `MemMap.h` | Pendientes | — |
| Resto del árbol MCAL y drivers complejos | Carpetas preparadas, sin implementar | — |

Los archivos vacíos del árbol **no son módulos a medias**: marcan el trabajo
pendiente y la estructura prevista.

---

## Estructura

```
├── Application/          Componentes de software (SWC). No acceden a registros.
├── Rte/                  Runtime Environment (artefactos generados).
├── Bsw/
│   ├── Mcal/             Drivers estandarizados: Mcu, Port, Dio, Adc, Spi, ...
│   ├── EcuAbstraction/   Abstracción de dispositivos externos a la ECU.
│   ├── Services/         Servicios del BSW (Det).
│   └── ComplexDrivers/   Periféricos sin API estándar en AUTOSAR (prefijo CDD_).
├── Common/Include/       Platform_Types, Compiler, Std_Types, MemMap.
├── Platform/             Código específico del STM32F446: registros, arranque, linker.
├── Config/               Configuración de la ECU.
├── test/                 Pruebas unitarias (host) y de integración (placa).
└── docs/                 Estándares de referencia, arquitectura y hoja de ruta.
```

El sentido de las dependencias es
`Application → RTE → BSW → MCAL → registros del STM32`.
La aplicación no incluye headers de `Bsw/Mcal` ni de `Platform/Device`, y los
registros solo se tocan desde el MCAL, el arranque o un *complex driver*
justificado.

---

## Compilación y herramientas

```bash
make          # Compila -> build/main.elf, .hex, .lst, .map
make flash    # Programa la placa por OpenOCD
make test     # Pruebas unitarias en el host (Ceedling + Unity) con cobertura
make lint     # Análisis estático (cppcheck)
make misra    # Reglas MISRA C:2012 (addon de cppcheck)
```

Toolchain: Arm GNU Toolchain 13.3 (`arm-none-eabi-gcc`, C11), OpenOCD 0.12,
Ceedling 1.0, cppcheck 2.19, gcovr 8.6.

Los cuatro objetivos cubren el árbol AUTOSAR completo: `make` compila contra
`Common/Include`, `Platform/Device` y todos los módulos de `Bsw/`; `make test`
ejecuta las pruebas de `test/unit/` en el equipo anfitrión; y `lint` y `misra`
analizan `app/`, `Common/`, `Platform/` y `Bsw/`.

**Hallazgos abiertos:** `make misra` reporta 7 violaciones, todas en
`app/main.c` (reglas 11.4, 12.2 y 17.8). Son del parpadeo provisional que accede
a registros directamente, y desaparecen cuando `Mcu`, `Port` y `Dio` sustituyan
ese código. No se silencian mientras tanto.

---

## Método de trabajo

Dos fuentes independientes, y ninguna sustituye a la otra:

- **AUTOSAR** define interfaces, tipos, comportamiento, errores y configuración.
  Una API pública debe poder justificarse con un `SWS_<Modulo>_<número>`.
- **ST (RM0390)** define direcciones, registros, bits y secuencias. Una escritura
  a registro debe poder justificarse con un capítulo del manual.

Antes de programar un módulo se extrae de su especificación una ficha con las
dependencias, los tipos públicos, las funciones obligatorias y las opcionales
elegidas, los errores de desarrollo y de ejecución, las clases de configuración
(precompile, link-time, post-build), las interrupciones implicadas y las pruebas
previstas. El código se escribe después de esa ficha, no antes.

Un módulo no se considera terminado hasta que sus tipos y prototipos coinciden
con la release elegida, las opciones deshabilitadas no publican APIs, cada
registro usado tiene referencia al RM0390, las operaciones de
lectura-modificación-escritura consideran concurrencia, los errores llegan a
`Det`, las pruebas cubren estados y límites, y las desviaciones MISRA están
registradas.

---

## Hoja de ruta

1. **Base común** — `Compiler` ✅ · `Compiler_Cfg` · `Std_Types` · `MemMap` · `Det`
2. **Dispositivo** — mapa de registros ✅ · máscaras de bits · pruebas de offsets
3. **Arranque mínimo** — `Mcu` → `Port` → `Dio`
4. **Tiempo y formas de onda** — `Gpt` → `Pwm` → `Icu` → `Ocu`
5. **Comunicaciones** — `Spi` → `Lin` → `Can`
6. **Analógicos, memoria y supervisión** — `Adc` → `Wdg` → `Fls` → `RamTst`
7. **Complex drivers** — `CDD_Exti`, `CDD_Nvic`, `CDD_Dma`, `CDD_I2c`, `CDD_Dac`

El primer hito de firmware es `Mcu + Port + Dio`: el LED de la placa debe
encender sin que `main` toque un registro y sin que `Dio` configure pines.

---

## Documentos de referencia

- **AUTOSAR Classic Platform R20-11** — release fijada para todo el proyecto.
  No se mezclan documentos de otras releases.
- **RM0390** — manual de referencia del STM32F446.
- **DS10693** — datasheet del STM32F446xC/E (pinout y funciones alternativas).
- **PM0214** — manual de programación del Cortex-M4.
- **MISRA C:2012** — estándar de codificación.

Los PDF de los estándares no se versionan por licencia y tamaño; la lista y su
procedencia están en [`docs/standards/REFERENCIAS.md`](docs/standards/REFERENCIAS.md).

---

## Alcance y limitaciones

Este repositorio es un **proyecto de aprendizaje**. No es una implementación
certificada de AUTOSAR, no incluye un generador ECUC, no tiene evaluación formal
de conformidad MISRA ni evidencia ISO 26262, y no debe usarse en un vehículo.

Que `make misra` no reporte hallazgos no constituye por sí solo una declaración
de conformidad MISRA: eso requiere un plan de aplicación de directrices, un
registro de desviaciones y un resumen de conformidad.
