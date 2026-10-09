/**
 * @file    Det.h
 * @brief   Interfaz publica del Default Error Tracer.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Default Error Tracer.
 *          El Det recibe los errores de desarrollo que detectan los modulos del
 *          BSW cuando comprueban sus parametros de entrada, y los pone a
 *          disposicion de quien depura. No corrige nada ni altera el flujo del
 *          modulo que lo llama: solo deja constancia.
 *
 *          Alcance de esta realizacion: inicializacion, arranque y notificacion
 *          de errores de desarrollo. Los errores de ejecucion y los fallos
 *          transitorios, asi como los callouts configurables del capitulo
 *          8.1.5, quedan fuera por ahora; el proyecto no tiene DEM ni DLT a los
 *          que reenviarlos.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-08
 *
 * @par Trazabilidad
 *      SWS_Det_00008  Det_Init, identificador de servicio 0x00
 *      SWS_Det_00009  Det_ReportError, identificador de servicio 0x01
 *      SWS_Det_00025  Det_Start, identificador de servicio 0x02
 *      SWS_Det_00021  Det_GetVersionInfo, identificador de servicio 0x03
 *      SRS_BSW_00406  la variable de estado vale cero antes de cualquier API
 */
#ifndef DET_H
#define DET_H

/*==================================================================================================
 *  Archivos incluidos
 *================================================================================================*/

#include "Std_Types.h"
#include "Det_Cfg.h"

/*==================================================================================================
 *  Informacion publicada
 *
 *  BSWGeneral capitulo 10.3. El identificador de modulo y el prefijo Det
 *  proceden de AUTOSAR_TR_BSWModuleList.
 *================================================================================================*/
#define DET_VENDOR_ID                     0u    /* Sin identificador asignado en la lista de proveedores de AUTOSAR. */
#define DET_MODULE_ID                     15u
#define DET_AR_RELEASE_MAJOR_VERSION      20u
#define DET_AR_RELEASE_MINOR_VERSION      11u
#define DET_AR_RELEASE_REVISION_VERSION   0u
#define DET_SW_MAJOR_VERSION              1u
#define DET_SW_MINOR_VERSION              0u
#define DET_SW_PATCH_VERSION              0u


/*==================================================================================================
 *  Definiciones de tipos
 *
 *  Capitulo 8.1.2 de la especificacion.
 *================================================================================================*/
typedef struct Det_ConfigType  /**< Estructura que describe la configuracion del Det. */
{

} Det_ConfigType;


/*==================================================================================================
 *  Identificadores de servicio
 *
 *  Valor que cada API pasa como ApiId al notificar un error. Capitulo 8.1.3.
 *================================================================================================*/



/*==================================================================================================
 *  Prototipos de funcion
 *
 *  Capitulo 8.1.3. Las funciones se declaran con las macros de abstraccion del
 *  compilador y la clase de memoria DET_CODE.
 *================================================================================================*/

/**
 * @brief   Inicializa el modulo Det con la configuracion indicada.
 *
 * @param[in] ConfigPtr  Puntero a la configuracion del modulo.
 *
 * @return  void
 *
 * @pre     Ninguna. Es la primera funcion del modulo que puede llamarse.
 * @post    El modulo queda inicializado y admite notificaciones de error.
 *
 * @reentrancy  No reentrante.
 * @sync        Sincrona.
 * @serviceid   0x00
 *
 * @par Requisitos
 *      SWS_Det_00008
 */
FUNC(void, DET_CODE) Det_Init(P2CONST(Det_ConfigType, AUTOMATIC, DET_APPL_CONST) ConfigPtr);

FUNC(void, DET_CODE) Det_Start(void);

FUNC(Std_ReturnType, DET_CODE) Det_ReportError(uint16 ModuleId,
                                               uint8  InstanceId,
                                               uint8  ApiId,
                                               uint8  ErrorId);

FUNC(Std_ReturnType, DET_CODE) Det_ReportRuntimeError(uint16 ModuleId,
                                                      uint8  InstanceId,
                                                      uint8  ApiId,
                                                      uint8  ErrorId);

FUNC(Std_ReturnType, DET_CODE) Det_ReportTransientFault(uint16 ModuleId,
                                                        uint8  InstanceId,
                                                        uint8  ApiId,
                                                        uint8  FaultId);

FUNC(void, DET_CODE) Det_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DET_APPL_DATA) versioninfo);

#endif /* DET_H */
