/**
 * @file    Det.c
 * @brief   Implementacion del Default Error Tracer.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Default Error Tracer.
 *          Conserva en memoria el ultimo error de desarrollo notificado por
 *          cualquier modulo del BSW, de modo que quede accesible desde el
 *          depurador.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-08
 *
 * @par Trazabilidad
 *      Capitulos 7.1 a 7.4 de la especificacion.
 */

/*==================================================================================================
 *  Archivos incluidos
 *================================================================================================*/

#include "Det.h"

/*==================================================================================================
 *  Comprobacion de version
 *
 *  La cabecera y la implementacion deben pertenecer a la misma version del
 *  modulo y haberse escrito contra la misma release de AUTOSAR. La
 *  comprobacion se hace con #if y detiene la compilacion con #error.
 *================================================================================================*/



/*==================================================================================================
 *  Variables del modulo
 *
 *  Estado de inicializacion y registro del ultimo error notificado. Se declaran
 *  con las macros de abstraccion del compilador y la clase DET_VAR_CLEARED,
 *  entre las palabras clave de seccion de Det_MemMap.h.
 *================================================================================================*/



/*==================================================================================================
 *  Funciones
 *
 *  Capitulo 8.1.3 de la especificacion.
 *================================================================================================*/


