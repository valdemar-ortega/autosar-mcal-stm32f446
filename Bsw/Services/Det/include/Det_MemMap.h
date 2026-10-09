/**
 * @file    Det_MemMap.h
 * @brief   Mapeo de secciones de memoria del modulo Det.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Memory Mapping.
 *          Permite que Det declare en que seccion deben colocarse su codigo,
 *          sus constantes y sus variables sin conocer el script del enlazador
 *          ni la sintaxis del compilador. El modulo define una palabra clave e
 *          incluye esta cabecera:
 *
 *              #define DET_START_SEC_CODE
 *              #include "Det_MemMap.h"
 *                  ... declaraciones ...
 *              #define DET_STOP_SEC_CODE
 *              #include "Det_MemMap.h"
 *
 *          El nombre del archivo lo fija SWS_MemMap_00002: una cabecera por
 *          modulo, con el prefijo de implementacion por delante.
 *
 * @note    ESTE ARCHIVO NO LLEVA GUARDA DE INCLUSION, a proposito. Se incluye
 *          una vez por cada apertura y cierre de seccion, y cada inclusion debe
 *          volver a evaluarse. Una guarda del tipo #ifndef DET_MEMMAP_H lo
 *          dejaria inservible tras la primera vez.
 *
 * @par Estrategia actual: nula y documentada
 *      El script del enlazador no define todavia secciones por modulo, de modo
 *      que las palabras clave se reconocen, se anulan y no emiten ninguna
 *      directiva. El mecanismo existe y el modulo ya lo usa; cuando el
 *      enlazador soporte secciones propias solo cambia este archivo. No se
 *      declaran secciones que el enlazador no sepa colocar.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-08
 *
 * @par Trazabilidad
 *      SWS_MemMap_00002  nombre {Mip}_MemMap.h
 *      SWS_MemMap_00005  mecanismo de seleccion por palabra clave
 *      SWS_MemMap_00015  la seccion se activa si la macro se define antes
 *      SWS_MemMap_00016  una seleccion afecta a un solo tipo de objeto
 *      SWS_MemMap_00023  no se incluye dentro del cuerpo de una funcion
 *      SWS_MemMap_00026  soporte de apertura y cierre de cada seccion
 *      SWS_MemMap_00036  error si la palabra clave no esta soportada
 */

/*==================================================================================================
 *  Seccion de codigo
 *
 *  DET_START_SEC_CODE y DET_STOP_SEC_CODE.
 *================================================================================================*/



/*==================================================================================================
 *  Seccion de constantes
 *
 *  DET_START_SEC_CONST y DET_STOP_SEC_CONST.
 *================================================================================================*/



/*==================================================================================================
 *  Seccion de variables
 *
 *  DET_START_SEC_VAR_CLEARED y DET_STOP_SEC_VAR_CLEARED, con la politica de
 *  inicializacion como parte del nombre.
 *================================================================================================*/



/*==================================================================================================
 *  Palabra clave no reconocida
 *
 *  SWS_MemMap_00036: una seccion que esta realizacion no soporta debe provocar
 *  un error de compilacion en lugar de dejar el objeto donde no corresponde.
 *================================================================================================*/
