/**
 * @file    Det_Cfg.h
 * @brief   Configuracion precompilada del Default Error Tracer.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Default Error Tracer,
 *          capitulo 10. Recoge los parametros que se fijan antes de compilar y
 *          que deciden que partes del modulo existen en el binario.
 *
 *          El capitulo 10 clasifica todos los parametros del modulo como de
 *          tiempo de precompilacion, y ninguno como link time ni post-build.
 *          Por eso toda la configuracion de Det reside aqui y Det_ConfigType
 *          no transporta nada.
 *
 *          Un simbolo desactivado no debe limitarse a saltar codigo: la API
 *          correspondiente no se declara ni se define, de modo que su uso
 *          accidental falla al compilar y no en la placa.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-12
 *
 * @par Trazabilidad
 *      Contenedor DetGeneral        capitulo 10, pagina 42
 *      Contenedor DetNotification   capitulo 10, paginas 43 y 44
 *      Contenedor DetConfigSet      capitulo 10, paginas 44 y 45
 */
#ifndef DET_CFG_H
#define DET_CFG_H

/*==================================================================================================
 *  Archivos incluidos
 *
 *  Std_Types.h aporta los simbolos STD_ON y STD_OFF con los que se activan y
 *  desactivan las opciones.
 *================================================================================================*/

#include "Std_Types.h"

/*==================================================================================================
 *  Opciones generales
 *
 *  Contenedor DetGeneral, pagina 42. Cada opcion vale STD_ON o STD_OFF.
 *
 *  DetVersionInfoApi decide si existe Det_GetVersionInfo. Si se desactiva, el
 *  prototipo de Det.h y la definicion de Det.c deben quedar fuera de la
 *  compilacion, no simplemente sin uso.
 *
 *  DetForwardToDlt decide si los errores se reenvian al modulo Dlt. Este
 *  proyecto no tiene Dlt.
 *================================================================================================*/

/** ECUC_Det_00003, multiplicidad 1, EcucBooleanParamDef.
 *  Activa la API de lectura de la version del modulo. Se habilita porque Det.h
 *  publica Det_GetVersionInfo y el modulo la define. */
#define DET_VERSION_INFO_API            STD_ON

/** ECUC_Det_00006, multiplicidad 0..1, EcucBooleanParamDef.
 *  Reenvio de cada notificacion al modulo Dlt mediante
 *  Dlt_DetForwardErrorTrace. Se deshabilita porque el proyecto no integra Dlt;
 *  activarlo exigiria la interfaz Dlt_Det, que no existe. */
#define DET_FORWARD_TO_DLT              STD_OFF

/*==================================================================================================
 *  Notificaciones
 *
 *  Contenedor DetNotification, paginas 43 y 44. Los tres parametros son de tipo
 *  EcucFunctionNameDef con multiplicidad 0..*: cada uno nombra las funciones
 *  ajenas al modulo a las que Det avisa, y puede haber varias o ninguna.
 *
 *  Esta realizacion no declara ninguna. Los simbolos existen, deshabilitados,
 *  para que la decision quede escrita y para que Det.c pueda compilar el mismo
 *  codigo con y sin ellas.
 *================================================================================================*/

/** ECUC_Det_00005, multiplicidad 0..*, EcucFunctionNameDef.
 *  Funciones de usuario invocadas desde Det_ReportError. Ninguna configurada. */
#define DET_ERROR_HOOK                  STD_OFF

/** ECUC_Det_00007, multiplicidad 0..*, EcucFunctionNameDef.
 *  Funciones invocadas desde Det_ReportRuntimeError. Ninguna configurada; el
 *  servicio queda fuera del alcance de esta realizacion. */
#define DET_REPORT_RUNTIME_ERROR_CALLOUT STD_OFF

/** ECUC_Det_00008, multiplicidad 0..*, EcucFunctionNameDef.
 *  Funciones invocadas desde Det_ReportTransientFault. Ninguna configurada; el
 *  servicio queda fuera del alcance de esta realizacion. */
#define DET_REPORT_TRANSIENT_FAULT_CALLOUT STD_OFF

/*==================================================================================================
 *  Filtrado por modulo
 *
 *  Contenedor DetConfigSet con DetModule y DetModuleInstance, paginas 44 y 45.
 *  Permite que Det atienda solo a determinados modulos e instancias.
 *
 *  Esta realizacion no filtra: conserva la notificacion de cualquier modulo,
 *  que es el comportamiento util mientras se depura un MCAL con pocos modulos.
 *================================================================================================*/

/** Filtrado por DetModuleId y DetInstanceId. Deshabilitado: se conservan las
 *  notificaciones de todos los modulos. */
#define DET_MODULE_FILTER               STD_OFF

/*==================================================================================================
 *  Dimensionado
 *
 *  Tamanos fijados en tiempo de compilacion. No proceden del estandar: son
 *  decisiones de esta realizacion y determinan cuanta RAM ocupa el modulo.
 *================================================================================================*/

/** Numero de notificaciones que el modulo conserva. Con una sola entrada basta
 *  para detener la ejecucion en el depurador y leer que modulo, que API y que
 *  error se notificaron; ampliarlo permitiria ver una secuencia a cambio de
 *  cuatro bytes por entrada. */
#define DET_ERROR_BUFFER_SIZE           1u

#endif /* DET_CFG_H */
