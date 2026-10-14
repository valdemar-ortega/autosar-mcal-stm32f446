# Registro de desviaciones MISRA C:2012

Proyecto: MCAL AUTOSAR Classic R20-11 sobre STM32F446RE.
Analizador: cppcheck 2.19 con el addon MISRA, invocado por `make misra`.

Este documento clasifica y justifica cada hallazgo que el analizador reporta.
Ningún hallazgo queda sin clasificar, y **ninguno se silencia en el código**: el
objetivo es que `make misra` siga mostrándolos y que su número coincida con la
suma de este registro.

## Alcance y límites de esta declaración

El texto íntegro de MISRA C:2012 está sujeto a licencia y no forma parte de
este repositorio. Las categorías que se indican abajo proceden de la
clasificación pública de cada directriz y **deben confirmarse contra el
documento original** antes de usarlas en cualquier declaración formal.

Que `make misra` reporte solo los hallazgos aquí registrados **no constituye
una declaración de conformidad MISRA**. Según MISRA Compliance:2020 harían
falta además un plan de aplicación de directrices y un resumen de conformidad,
que este proyecto no tiene.

---

## Resumen

| Desviación | Regla | Categoría | Nº | Ámbito |
|---|---|---|---|---|
| DEV-001 | 2.5 | Advisory | 77 | Cabeceras comunes y de configuración |
| DEV-002 | 2.3 | Advisory | 16 | `Platform_Types.h`, `Std_Types.h` |
| DEV-003 | 20.7 | Required | 9 | `Compiler.h` |
| DEV-004 | 20.5 | Advisory | 7 | `Det_MemMap.h` |
| DEV-005 | 20.1 | Advisory | 4 | `Det.c` |
| DEV-006 | 8.7 | Advisory | 4 | `Det.c` |
| DEV-007 | 10.4 | Required | 1 | `Det.c` |
| ABIERTO-001 | 11.4, 12.2, 17.8 | — | 7 | `app/main.c` |

**Total: 125.** De ellos, 118 son desviaciones justificadas y 7 son hallazgos
abiertos sobre código provisional.

---

## DEV-001 — Regla 2.5: macro definida y no utilizada

**Categoría:** Advisory · **Hallazgos:** 77

**Ámbito:** `Compiler_Cfg.h` (22), `Platform_Types.h` (19), `Std_Types.h` (14),
`Compiler.h` (11), `Det_Cfg.h` (6), `Det.h` (5).

**Justificación.** Son cabeceras de biblioteca: publican el juego completo de
macros que define el estándar, con independencia de que una unidad de
traducción concreta use solo algunas. `Platform_Types.h` declara `CPU_TYPE_8`,
`CPU_TYPE_16` y `CPU_TYPE_64` aunque esta plataforma sea de 32 bits, porque
`SWS_Platform_00064` define los cuatro como valores admitidos de `CPU_TYPE`.
`Compiler_Cfg.h` declara las clases de memoria de módulos que todavía no están
implementados. Eliminar una macro para satisfacer la regla rompería la
conformidad con AUTOSAR.

**Riesgo:** ninguno. Una macro no utilizada no genera código.

**Mitigación.** Cada símbolo se corresponde con un requisito citado en el
comentario de su declaración, de modo que es comprobable que ninguno es
residuo de una versión anterior.

---

## DEV-002 — Regla 2.3: tipo declarado y no utilizado

**Categoría:** Advisory · **Hallazgos:** 16

**Ámbito:** `Platform_Types.h` (15), `Std_Types.h` (1).

**Justificación.** Misma razón que DEV-001 aplicada a tipos. `Platform_Types.h`
publica los diecinueve tipos de `SWS_Platform_00013` a `SWS_Platform_00042`
porque los módulos del BSW deben disponer de todos ellos; que el analizador
examine una unidad de traducción que solo usa cuatro no los hace prescindibles.

**Riesgo:** ninguno. Un `typedef` no utilizado no ocupa memoria.

**Mitigación.** Los tamaños y el signo de los diecinueve tipos se verifican en
`test/unit/test_Platform_Types.c`, de modo que ninguno queda sin comprobar
aunque el analizador los considere sin uso.

---

## DEV-003 — Regla 20.7: argumentos de macro sin paréntesis

**Categoría:** Required · **Hallazgos:** 9 · **Ámbito:** `Compiler.h`

**Justificación.** La regla exige encerrar entre paréntesis las expresiones que
resultan de expandir un parámetro de macro. En las macros de abstracción del
compilador los parámetros **no son expresiones, sino tipos y calificadores**:

```c
#define FUNC(rettype, memclass)            rettype
#define P2CONST(ptrtype, memclass, ptrclass)  const ptrtype *
```

Escribir `(rettype)` convertiría la declaración en una expresión de cast y el
código dejaría de compilar. La forma de estas macros la fija el capítulo 8.2 de
Specification of Compiler Abstraction y no admite variación.

**Riesgo:** el habitual de una macro sin paréntesis es que una expresión
compuesta se agrupe de forma inesperada. Aquí no aplica: los argumentos son
nombres de tipo, no expresiones aritméticas.

**Mitigación.** Las dieciséis macros se verifican por compilación en una unidad
que las usa todas, y las cuatro variantes de puntero se comprueban una a una
contra el comportamiento que exige su requisito.

---

## DEV-004 — Regla 20.5: uso de `#undef`

**Categoría:** Advisory · **Hallazgos:** 7 · **Ámbito:** `Det_MemMap.h`

**Justificación.** El mecanismo de mapeo de memoria **se basa en `#undef`**. El
módulo define una palabra clave de sección e incluye la cabecera; esta la
reconoce y debe anularla para que la siguiente inclusión parta de cero. Sin el
`#undef` la palabra seguiría definida y la sección no se cerraría nunca.

No es una elección de estilo: `SWS_MemMap_00005` y `SWS_MemMap_00026` exigen un
mecanismo de apertura y cierre por palabra clave, y en C no hay otra forma de
realizarlo.

**Riesgo:** el que persigue la regla es que se anule una macro definida en otro
sitio y se altere el comportamiento de código ajeno. Aquí los siete `#undef`
operan sobre símbolos que el propio mecanismo acaba de consumir, más el
centinela interno del archivo.

**Mitigación.** El archivo termina con un `#error` que detiene la compilación si
llega una palabra clave que no reconoce, de modo que un `#undef` olvidado se
manifiesta como fallo de compilación y no en silencio.

---

## DEV-005 — Regla 20.1: `#include` precedido de código

**Categoría:** Advisory · **Hallazgos:** 4 · **Ámbito:** `Det.c`

**Justificación.** La regla pide que los `#include` aparezcan al principio del
archivo. El mapeo de memoria lo impide por construcción: la cabecera de
secciones se incluye **en el punto exacto** donde empieza y acaba cada bloque
de objetos, que está necesariamente en mitad del archivo.

```c
#define DET_START_SEC_VAR_CLEARED
#include "Det_MemMap.h"
    ... las variables ...
#define DET_STOP_SEC_VAR_CLEARED
#include "Det_MemMap.h"
```

El ejemplo 7.9 del capítulo 7.3 de Specification of Memory Mapping muestra
exactamente esta disposición.

**Riesgo:** ninguno. La cabecera incluida no declara objetos ni tipos: solo
evalúa directivas del preprocesador.

**Mitigación.** La regla se respeta para todas las demás inclusiones: `Det.c`
incluye `Det.h` al principio del archivo y no incluye ninguna otra cabecera
fuera del mecanismo de secciones.

---

## DEV-006 — Regla 8.7: objeto con enlace externo usado en una sola unidad

**Categoría:** Advisory · **Hallazgos:** 4 · **Ámbito:** `Det.c`

**Justificación.** El analizador observa que las cuatro funciones de `Det` solo
se referencian dentro de `Det.c` y sugiere declararlas `static`. Es correcto en
el estado actual del proyecto y dejará de serlo en cuanto `Mcu` notifique su
primer error: son la **API pública** del módulo, declarada en `Det.h` y exigida
por el capítulo 8.1.3 de la especificación.

**Riesgo:** ninguno.

**Mitigación.** Las cuatro funciones están declaradas en la cabecera pública del
módulo, que es la prueba de que su enlace externo es deliberado. Lo que sí es
privado —el tipo del registro y las dos variables— se declara `static` en el
`.c` y no aparece en `Det.h`.

---

## DEV-007 — Regla 10.4: operandos de distinto tipo esencial

**Categoría:** Required · **Hallazgos:** 1 · **Ámbito:** `Det.c`

```c
if (Det_Inicializado == TRUE)
```

**Justificación.** Esta desviación es el resultado de una contradicción entre
los dos estándares que sigue el proyecto:

- `SWS_Platform_00056` obliga a definir `TRUE` como `1` a secas, que en C es una
  constante de tipo `signed int`.
- `SWS_Platform_00027` obliga a realizar `boolean` como un entero **sin signo**.
- `SWS_Platform_00034` obliga a que las comparaciones de un `boolean` se hagan
  contra `TRUE` o `FALSE`.

El resultado es una comparación entre un tipo esencialmente sin signo y una
constante esencialmente con signo, que es justo lo que prohíbe la regla 10.4.
Cumplir AUTOSAR implica desviarse de MISRA, y no hay forma de satisfacer ambos.

**Riesgo:** ninguno en la práctica. Los dos operandos valen 0 o 1 y la
conversión aritmética habitual no altera el resultado.

**Mitigación.** Se respeta `SWS_Platform_00034` de forma estricta: sobre
variables `boolean` no se aplican operadores aritméticos ni de bits, y las
comparaciones son únicamente contra `TRUE` y `FALSE`.

---

## ABIERTO-001 — Hallazgos sin desviación en `app/main.c`

**Reglas:** 11.4 (4), 12.2 (2), 17.8 (1) · **Hallazgos:** 7

**No son desviaciones: son hallazgos abiertos.** `app/main.c` contiene el
parpadeo provisional que accede a registros directamente, previo a la capa
MCAL. Las tres reglas señalan exactamente lo que ese código hace mal.

**Resolución prevista:** desaparecen al sustituir ese código por un componente
de aplicación que use `Dio`, una vez estén implementados `Mcu`, `Port` y `Dio`.
No se silencian mientras tanto, para que el analizador siga recordando que ese
archivo es temporal.

---

## Mantenimiento de este registro

Al añadir un módulo, comparar el número de hallazgos con el resumen de arriba.
Si aparece una clase nueva, decidir entre corregir el código o registrar la
desviación; lo que no se admite es dejar un hallazgo sin clasificar.

El mapa actual de hallazgos se obtiene con:

```
make misra
```
