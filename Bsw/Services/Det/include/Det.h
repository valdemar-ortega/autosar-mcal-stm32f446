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
/**
 * @brief   Configuracion del modulo Det.
 *
 * @details El contenido de esta estructura es dependiente de la implementacion:
 *          la especificacion exige el tipo pero no fija sus miembros.
 *
 *          En esta realizacion no transporta nada. El capitulo 10 clasifica
 *          todos los parametros de configuracion del modulo como de tiempo de
 *          precompilacion, y ninguno como link time ni post-build, de modo que
 *          todos residen en Det_Cfg.h y no queda dato alguno que deba viajar
 *          hasta Det_Init.
 *
 *          La estructura existe de todas formas porque SRS_BSW_00414 exige que
 *          toda funcion de inicializacion reciba un puntero a su configuracion
 *          como parametro unico, de manera que todos los modulos del BSW se
 *          inicialicen de la misma forma.
 *
 *          El miembro de relleno esta porque el lenguaje C no admite
 *          estructuras sin miembros. Cuando algun parametro del modulo pase a
 *          ser configurable despues de compilar, ocupara su lugar.
 */
typedef struct
{
    uint8 Reserved;  /**< Relleno sin uso. Ver la nota de esta estructura. */
} Det_ConfigType;


/*==================================================================================================
 *  Identificadores de servicio
 *
 *  Valor que cada API pasa como ApiId al notificar un error. Capitulo 8.1.3.
 *================================================================================================*/
 
#define DET_INIT_SERVICE_ID                        0x00u
#define DET_REPORT_ERROR_SERVICE_ID                0x01u
#define DET_START_SERVICE_ID                       0x02u
#define DET_GET_VERSION_INFO_SERVICE_ID            0x03u
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



FUNC(void, DET_CODE) Det_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DET_APPL_DATA) versioninfo);

#endif /* DET_H */
