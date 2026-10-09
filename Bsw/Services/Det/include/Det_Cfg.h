/**
 * @file    Det_Cfg.h
 * @brief   Configuracion precompilada del Default Error Tracer.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Default Error Tracer,
 *          capitulo 10. Recoge los parametros que se fijan antes de compilar y
 *          que deciden que partes del modulo existen en el binario.
 *
 *          Un simbolo desactivado no debe limitarse a saltar codigo: la API
 *          correspondiente no se declara ni se define, de modo que su uso
 *          accidental falla al compilar y no en la placa.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-08
 *
 * @par Trazabilidad
 *      Capitulo 10.1.1, contenedores DetGeneral y DetConfigSet.
 */
#ifndef DET_CFG_H
#define DET_CFG_H

/*==================================================================================================
 *  Archivos incluidos
 *================================================================================================*/

#include "Std_Types.h"

/*==================================================================================================
 *  Opciones generales
 *
 *  Contenedor DetGeneral. Cada opcion se activa con STD_ON o se desactiva con
 *  STD_OFF; los simbolos proceden de Std_Types.h.
 *================================================================================================*/



/*==================================================================================================
 *  Dimensionado
 *
 *  Tamanos fijados en tiempo de compilacion, como el numero de errores que el
 *  modulo conserva en memoria.
 *================================================================================================*/



#endif /* DET_CFG_H */
