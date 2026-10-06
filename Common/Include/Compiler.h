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


#define AUTOMATIC               
#define TYPEDEF                 
#define NULL_PTR                ((void*) 0)
#define INLINE                  inline
#define LOCAL_INLINE            static inline
 
#define FUNC(rettype,memclass) rettype
#define FUNC_P2CONST(rettype,ptrclass,memclass) const rettype *
#define FUNC_P2VAR(rettype,ptrclass,memclass) rettype *
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *  
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype *const
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)
#define CONSTP2FUNC(rettype, ptrclass, fctname)  rettype (*const fctname)
#define CONST(consttype, memclass) const consttype
#define VAR(vartype, memclass) vartype 

#endif /* COMPILER_H */
