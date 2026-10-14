/**
 * @file    Compiler.h
 * @brief   Abstraccion del compilador para los modulos BSW del STM32F446.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Compiler Abstraction.
 *          Las macros de este archivo aislan al codigo de los modulos BSW de
 *          las palabras clave propias de cada compilador: el modulo escribe
 *          siempre la misma forma y solo este archivo cambia al portar el
 *          proyecto a otro compilador o arquitectura.
 *
 *          Realizacion para Arm GNU Toolchain (arm-none-eabi-gcc, C11) sobre
 *          Cortex-M4. El espacio de direcciones es plano y de 32 bits, por lo
 *          que no existen calificadores de distancia (near/far): las clases de
 *          memoria (memclass) y de puntero (ptrclass) se reciben y se expanden
 *          a vacio. Sus valores concretos se configuran en Compiler_Cfg.h.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-04
 *
 * @par Trazabilidad
 *      Definiciones generales: SWS_COMPILER_00046, 00059, 00051, 00057, 00060.
 *      Funciones:              SWS_COMPILER_00001, 00061, 00063.
 *      Punteros:               SWS_COMPILER_00006, 00013, 00031, 00032,
 *                              00039, 00065.
 *      Constantes:             SWS_COMPILER_00023.
 *      Variables:              SWS_COMPILER_00026.
 */
#ifndef COMPILER_H
#define COMPILER_H

/* Parametros memclass y ptrclass especificos de cada modulo.
   SWS_COMPILER_00055; ver tambien el ejemplo completo del capitulo 7.1.5. */
#include "Compiler_Cfg.h"


/*==================================================================================================
 *  Definiciones generales
 *
 *  Capitulo 8.2.1 de la especificacion.
 *================================================================================================*/

/** Clase de memoria de las variables locales y de los punteros declarados
 *  dentro de una funcion. Se pasa como segundo argumento a P2VAR, P2CONST y
 *  sus variantes siempre que el puntero sea un parametro o una local, porque
 *  en ese caso vive en la pila y no en una seccion propia.
 *  Definicion vacia obligatoria (SWS_COMPILER_00046). */
#define AUTOMATIC

/** Clase de memoria para el interior de una definicion de tipo. Se usa cuando
 *  una de las macros de puntero aparece dentro de un typedef o de un miembro
 *  de estructura, donde no se puede indicar donde reside el puntero mismo.
 *  Definicion vacia obligatoria (SWS_COMPILER_00059). */
#define TYPEDEF

/** Puntero nulo del proyecto. Se usa en lugar de NULL para no depender de las
 *  cabeceras de la biblioteca estandar, que un MCAL no debe incluir.
 *  (SWS_COMPILER_00051). */
#define NULL_PTR                ((void*) 0)

/** Abstraccion de la palabra clave inline. Una funcion definida en una
 *  cabecera con INLINE necesita que exactamente una unidad de traduccion
 *  proporcione su definicion externa; de lo contrario el enlazador no la
 *  encuentra. En la practica conviene LOCAL_INLINE (SWS_COMPILER_00057). */
#define INLINE                  inline

/** Abstraccion de inline con ambito de archivo. Es la forma correcta para
 *  funciones pequenas definidas en una cabecera: cada unidad de traduccion
 *  obtiene su copia privada y no hay colision al enlazar. Dejarla vacia
 *  produciria definiciones externas duplicadas, y MISRA C:2012 regla 8.10
 *  exige ademas que toda funcion inline sea static (SWS_COMPILER_00060). */
#define LOCAL_INLINE            static inline

/*==================================================================================================
 *  Definiciones de funcion
 *
 *  Capitulo 8.2.2. Envuelven el tipo de retorno de toda funcion del BSW y
 *  permiten situar su codigo en una seccion de memoria concreta.
 *================================================================================================*/

/** Declaracion y definicion de cualquier funcion del BSW.
 *  @param rettype   tipo que devuelve la funcion.
 *  @param memclass  clase de memoria del codigo, normalmente <MIP>_CODE.
 *  Uso: FUNC(void, DET_CODE) Det_Start(void)   (SWS_COMPILER_00001). */
#define FUNC(rettype,memclass) rettype

/** Funcion que devuelve un puntero a dato de solo lectura. No confundir con
 *  P2CONST: aqui el puntero es el valor de retorno, no un parametro.
 *  Uso: FUNC_P2CONST(uint8, MCU_APPL_CONST, MCU_CODE) Mcu_GetTabla(void)
 *  (SWS_COMPILER_00061). */
#define FUNC_P2CONST(rettype,ptrclass,memclass) const rettype *

/** Funcion que devuelve un puntero a dato modificable.
 *  Uso: FUNC_P2VAR(uint8, MCU_APPL_DATA, MCU_CODE) Mcu_GetEstado(void)
 *  (SWS_COMPILER_00063). */
#define FUNC_P2VAR(rettype,ptrclass,memclass) rettype *

/*==================================================================================================
 *  Definiciones de puntero
 *
 *  Capitulo 8.2.3. La eleccion depende de dos preguntas independientes: si el
 *  puntero puede moverse, y si el dato apuntado puede escribirse.
 *
 *      P2VAR         el puntero se mueve   el dato se escribe
 *      P2CONST       el puntero se mueve   el dato es de solo lectura
 *      CONSTP2VAR    el puntero es fijo    el dato se escribe
 *      CONSTP2CONST  el puntero es fijo    el dato es de solo lectura
 *
 *  En un parametro de funcion, memclass es siempre AUTOMATIC: describe donde
 *  vive el puntero, que en ese caso es la pila.
 *================================================================================================*/

/** Puntero movible a dato modificable. Es el caso de un bufer que la funcion
 *  rellena.
 *  @param ptrtype   tipo del dato apuntado.
 *  @param memclass  clase de memoria del puntero mismo.
 *  @param ptrclass  clase de memoria del dato apuntado, normalmente
 *                   <MIP>_APPL_DATA.
 *  Uso: P2VAR(uint8, AUTOMATIC, DET_APPL_DATA) Destino  (SWS_COMPILER_00006). */
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

/** Puntero movible a dato de solo lectura. Es el caso del ConfigPtr que recibe
 *  toda funcion de inicializacion.
 *  Uso: P2CONST(Det_ConfigType, AUTOMATIC, DET_APPL_CONST) ConfigPtr
 *  (SWS_COMPILER_00013). */
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

/** Puntero fijo a dato modificable. Para una direccion que no cambia nunca,
 *  como el bloque de registros de un periferico.
 *  Uso: CONSTP2VAR(Stm32_GpioRegisterType, PORT_CONST, REGSPACE) Puerto
 *  (SWS_COMPILER_00031). */
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

/** Puntero fijo a dato de solo lectura. Para una tabla de configuracion en
 *  flash cuya direccion tampoco cambia  (SWS_COMPILER_00032). */
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype *const

/** Definicion de un tipo puntero a funcion. Se usa siempre dentro de un
 *  typedef, y la lista de parametros se escribe fuera de la macro.
 *  @param fctname  nombre del tipo que se esta definiendo.
 *  Uso: typedef P2FUNC(void, MCU_APPL_CODE, Mcu_NotifType)(void);
 *  Sirve para guardar callbacks: notificaciones de Gpt, de Icu o de fallo de
 *  reloj de Mcu  (SWS_COMPILER_00039). */
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)

/** Tipo puntero constante a funcion: el destino se fija al definirlo y no se
 *  puede reasignar despues  (SWS_COMPILER_00065). */
#define CONSTP2FUNC(rettype, ptrclass, fctname)  rettype (*const fctname)

/*==================================================================================================
 *  Definiciones de constante y de variable
 *
 *  Capitulos 8.2.4 y 8.2.5. Envuelven los objetos de ambito de archivo del
 *  modulo, no las variables locales, que no necesitan clase de memoria.
 *================================================================================================*/

/** Declaracion y definicion de una constante del modulo. Para tablas de
 *  configuracion y valores fijos que residen en flash.
 *  Uso: CONST(uint8, MCU_CONST) Mcu_Tabla[2]  (SWS_COMPILER_00023). */
#define CONST(consttype, memclass) const consttype

/** Declaracion y definicion de una variable del modulo. La clase incluye la
 *  politica de inicializacion: <MIP>_VAR_CLEARED se pone a cero en cada reset,
 *  <MIP>_VAR_NO_INIT nunca se toca.
 *  Uso: VAR(boolean, DET_VAR_CLEARED) Det_Inicializado  (SWS_COMPILER_00026). */
#define VAR(vartype, memclass) vartype

#endif /* COMPILER_H */
