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
 *
 *  Cada bloque reconoce su palabra clave, la anula y no emite directiva alguna.
 *  El #undef es imprescindible: sin el, la palabra seguiria definida en la
 *  siguiente inclusion y la seccion no se cerraria nunca.
 *================================================================================================*/

#ifdef DET_START_SEC_CODE
    #undef DET_START_SEC_CODE
    /* Sin directiva: el enlazador no define todavia una seccion de codigo para
       este modulo. Aqui iria la apertura, por ejemplo #pragma section. */
    #define DET_SECCION_RECONOCIDA
#endif

#ifdef DET_STOP_SEC_CODE
    #undef DET_STOP_SEC_CODE
    /* Sin directiva: cierre de la seccion de codigo. */
    #define DET_SECCION_RECONOCIDA
#endif

/*==================================================================================================
 *  Seccion de constantes
 *
 *  DET_START_SEC_CONST y DET_STOP_SEC_CONST.
 *================================================================================================*/

#ifdef DET_START_SEC_CONST
    #undef DET_START_SEC_CONST
    #define DET_SECCION_RECONOCIDA
#endif

#ifdef DET_STOP_SEC_CONST
    #undef DET_STOP_SEC_CONST
    #define DET_SECCION_RECONOCIDA
#endif

/*==================================================================================================
 *  Seccion de variables
 *
 *  DET_START_SEC_VAR_CLEARED y DET_STOP_SEC_VAR_CLEARED, con la politica de
 *  inicializacion como parte del nombre. CLEARED significa que la variable se
 *  pone a cero en cada reset, que es lo que exige SRS_BSW_00406 para la
 *  bandera de inicializacion del modulo.
 *================================================================================================*/

#ifdef DET_START_SEC_VAR_CLEARED
    #undef DET_START_SEC_VAR_CLEARED
    #define DET_SECCION_RECONOCIDA
#endif

#ifdef DET_STOP_SEC_VAR_CLEARED
    #undef DET_STOP_SEC_VAR_CLEARED
    #define DET_SECCION_RECONOCIDA
#endif

/*==================================================================================================
 *  Palabra clave no reconocida
 *
 *  SWS_MemMap_00036: una seccion que esta realizacion no soporta debe provocar
 *  un error de compilacion en lugar de dejar el objeto donde no corresponde.
 *
 *  Si ningun bloque anterior reconocio la palabra clave, DET_SECCION_RECONOCIDA
 *  no se ha definido y la inclusion se detiene aqui.
 *================================================================================================*/

#ifndef DET_SECCION_RECONOCIDA
    #error "Det_MemMap.h: palabra clave de seccion no soportada por esta realizacion."
#endif

#undef DET_SECCION_RECONOCIDA
