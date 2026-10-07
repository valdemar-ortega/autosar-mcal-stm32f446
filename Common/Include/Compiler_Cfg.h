/**
 * @file    Compiler_Cfg.h
 * @brief   Clases de memoria y de puntero de cada modulo del BSW.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Compiler Abstraction,
 *          capitulo 7.1.4. Mientras Compiler.h define las macros, este archivo
 *          define los valores que esas macros reciben como parametros memclass
 *          y ptrclass. La nomenclatura es <PREFIX>_<CLASE>, donde <PREFIX> es
 *          la abreviatura del modulo en mayusculas (SWS_COMPILER_00040).
 *
 *          En Cortex-M4 con Arm GNU Toolchain el espacio de direcciones es
 *          plano, por lo que ninguna clase necesita calificadores y todas se
 *          definen vacias. Separarlas de todos modos permite reubicar el codigo
 *          o los datos de un modulo concreto cambiando solo este archivo.
 *
 *          Cada modulo declara unicamente las clases que usa, deducidas de las
 *          firmas de su capitulo "Function definitions". El archivo crece
 *          conforme se implementan modulos nuevos.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-06
 *
 * @par Trazabilidad
 *      SWS_COMPILER_00055  contenido de Compiler_Cfg.h
 *      SWS_COMPILER_00054  los elementos llevan la abreviatura del modulo
 *      SWS_COMPILER_00040  sintaxis de las clases de memoria y de puntero
 */
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/*==================================================================================================
 *  Mcu - MCU Driver
 *  Firmas de referencia: AUTOSAR_SWS_MCUDriver R20-11, capitulo 8.3.
 *================================================================================================*/

/** Codigo del modulo: las once funciones de Mcu.c. */
#define MCU_CODE

/** Constantes globales o estaticas del modulo, situadas en flash. */
#define MCU_CONST

/** Constantes de configuracion del modulo: los conjuntos de Mcu_Lcfg.c y
 *  Mcu_PBcfg.c a los que apunta Mcu_ConfigType. */
#define MCU_CONFIG_DATA

/** Variables puestas a cero en cada reset. La bandera de inicializacion del
 *  modulo usa esta clase para cumplir SRS_BSW_00406, que exige que valga 0
 *  antes de llamar a cualquier API. */
#define MCU_VAR_CLEARED

/** Punteros a constantes de la aplicacion: el parametro ConfigPtr de
 *  Mcu_Init, que apunta a una configuracion situada en ROM. */
#define MCU_APPL_CONST

/** Punteros a datos de la aplicacion: la seccion de RAM que rellena
 *  Mcu_InitRamSection y el destino de Mcu_GetVersionInfo. */
#define MCU_APPL_DATA

/*==================================================================================================
 *  Port - PORT Driver
 *  Firmas de referencia: AUTOSAR_SWS_PortDriver R20-11, capitulo 8.3.
 *================================================================================================*/

/** Codigo del modulo: Port_Init, Port_SetPinDirection, Port_SetPinMode,
 *  Port_RefreshPortDirection y Port_GetVersionInfo. */
#define PORT_CODE

/** Constantes globales o estaticas del modulo. */
#define PORT_CONST

/** Constantes de configuracion: la tabla que describe cada pin con su
 *  direccion, modo, resistencia y nivel inicial. */
#define PORT_CONFIG_DATA

/** Variables puestas a cero en cada reset: bandera de inicializacion
 *  (SRS_BSW_00406). */
#define PORT_VAR_CLEARED

/** Punteros a constantes de la aplicacion: el parametro ConfigPtr de
 *  Port_Init. */
#define PORT_APPL_CONST

/** Punteros a datos de la aplicacion: el parametro versioninfo de
 *  Port_GetVersionInfo, donde la funcion escribe el resultado. */
#define PORT_APPL_DATA

/*==================================================================================================
 *  Dio - DIO Driver
 *  Firmas de referencia: AUTOSAR_SWS_DIODriver R20-11, capitulo 8.3.
 *
 *  Dio no define funcion de inicializacion ni tipo de configuracion, de modo
 *  que no necesita bandera de inicializacion ni clase de variables: sus
 *  funciones solo leen y escriben pines que Port ya configuro.
 *================================================================================================*/

/** Codigo del modulo: lectura y escritura de canales, puertos y grupos. */
#define DIO_CODE

/** Constantes del modulo: la descripcion de canales, puertos y grupos de
 *  canales fijada en la configuracion. */
#define DIO_CONST

/** Punteros a constantes de la aplicacion: el parametro ChannelGroupIdPtr de
 *  Dio_ReadChannelGroup y Dio_WriteChannelGroup. */
#define DIO_APPL_CONST

/** Punteros a datos de la aplicacion: el parametro VersionInfo de
 *  Dio_GetVersionInfo. */
#define DIO_APPL_DATA

/*==================================================================================================
 *  Det - Default Error Tracer
 *  Firmas de referencia: AUTOSAR_SWS_DefaultErrorTracer R20-11, capitulo 8.
 *================================================================================================*/

/** Codigo del modulo: Det_Init, Det_Start, Det_ReportError,
 *  Det_ReportRuntimeError, Det_ReportTransientFault y Det_GetVersionInfo. */
#define DET_CODE

/** Constantes globales o estaticas del modulo. */
#define DET_CONST

/** Constantes de configuracion del modulo. */
#define DET_CONFIG_DATA

/** Variables puestas a cero en cada reset: estado del modulo y registro del
 *  ultimo error notificado. */
#define DET_VAR_CLEARED

/** Punteros a constantes de la aplicacion: el parametro ConfigPtr de
 *  Det_Init. */
#define DET_APPL_CONST

/** Punteros a datos de la aplicacion: el parametro versioninfo de
 *  Det_GetVersionInfo. */
#define DET_APPL_DATA

#endif /* COMPILER_CFG_H */
