# Referencias del proyecto

## Microcontrolador y placa

- RM0390: manual de referencia del STM32F446.
- DS10693: datasheet del STM32F446xC/E.
- PM0214: manual de programación del Cortex-M4.
- UM1724: manual de usuario de las placas Nucleo-64.

## AUTOSAR Classic

**Release seleccionada para el proyecto educativo: AUTOSAR Classic Platform R20-11.**

No se deben mezclar documentos de otra release sin registrar la decisión y su
impacto. La ruta de trabajo y la matriz de documentos por módulo se encuentran
en `docs/roadmap/GUIA_IMPLEMENTACION_MCAL_STM32F446.md`.

- General Specification of Basic Software Modules.
- Specification of MCU Driver.
- Specification of PORT Driver.
- Specification of DIO Driver.
- Specification of Platform Types.
- Specification of Standard Types.
- Specification of Compiler Abstraction.

Se debe seleccionar una sola release AUTOSAR para todo el proyecto y registrar
aquí la versión elegida antes de implementar módulos.

## Código seguro

- MISRA C:2012 con sus correcciones y enmiendas aplicables.
- Política de desviaciones MISRA del proyecto.

Los documentos oficiales de MISRA están sujetos a licencia. Un analizador
estático ayuda a verificar reglas, pero no reemplaza el estándar ni el proceso
formal de conformidad.
