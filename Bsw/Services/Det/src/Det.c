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

/* Version de la release y del modulo contra las que se escribio esta
   implementacion. Se comparan con las que publica Det.h: si alguien sustituye
   la cabecera por otra version y olvida actualizar esta implementacion, la
   compilacion se detiene en lugar de producir un binario incoherente. */
#define DET_C_AR_RELEASE_MAJOR_VERSION    20u
#define DET_C_AR_RELEASE_MINOR_VERSION    11u
#define DET_C_SW_MAJOR_VERSION            1u
#define DET_C_SW_MINOR_VERSION            0u

#if (DET_AR_RELEASE_MAJOR_VERSION != DET_C_AR_RELEASE_MAJOR_VERSION) || \
    (DET_AR_RELEASE_MINOR_VERSION != DET_C_AR_RELEASE_MINOR_VERSION)
    #error "Det.c y Det.h pertenecen a releases distintas de AUTOSAR."
#endif

#if (DET_SW_MAJOR_VERSION != DET_C_SW_MAJOR_VERSION) || \
    (DET_SW_MINOR_VERSION != DET_C_SW_MINOR_VERSION)
    #error "Det.c y Det.h pertenecen a versiones distintas del modulo."
#endif

/*==================================================================================================
 *  Tipos privados
 *
 *  No se publican en Det.h: describen como guarda este modulo lo que recibe, y
 *  ningun otro modulo necesita conocerlo.
 *================================================================================================*/

/** @brief Notificacion conservada, con los cuatro datos que recibe la API. */
typedef struct
{
    uint16 ModuleId;    /**< Modulo que notifico, segun el BSW Module List. */
    uint8  InstanceId;  /**< Instancia del modulo. */
    uint8  ApiId;       /**< Identificador de servicio de la funcion que notifico. */
    uint8  ErrorId;     /**< Identificador del error notificado. */
} Det_RegistroType;

/*==================================================================================================
 *  Variables del modulo
 *
 *  Estado de inicializacion y registro del ultimo error notificado. Se declaran
 *  con las macros de abstraccion del compilador y la clase DET_VAR_CLEARED,
 *  entre las palabras clave de seccion de Det_MemMap.h.
 *================================================================================================*/

#define DET_START_SEC_VAR_CLEARED
#include "Det_MemMap.h"

/** Estado de inicializacion del modulo. La clase DET_VAR_CLEARED la deja a cero
 *  en cada reset, que es lo que exige SRS_BSW_00406 para que valga FALSE antes
 *  de llamar a cualquier API. De ella depende SWS_Det_00024. */
static VAR(boolean, DET_VAR_CLEARED) Det_Inicializado;

/** Notificaciones conservadas. El tamano lo fija DET_ERROR_BUFFER_SIZE en
 *  Det_Cfg.h y determina cuanta RAM ocupa el modulo. */
static VAR(Det_RegistroType, DET_VAR_CLEARED) Det_Registro[DET_ERROR_BUFFER_SIZE];

#define DET_STOP_SEC_VAR_CLEARED
#include "Det_MemMap.h"

/*==================================================================================================
 *  Funciones
 *
 *  Capitulo 8.1.3 de la especificacion.
 *================================================================================================*/

#define DET_START_SEC_CODE
#include "Det_MemMap.h"

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
 * @serviceid   DET_INIT_SERVICE_ID
 *
 * @par Requisitos
 *      SWS_Det_00019  el modulo provee esta funcion.
 *      SWS_Det_00020  cada llamada deja el modulo en un estado inicial definido,
 *                     por lo que el registro se limpia aunque ya estuviera
 *                     inicializado.
 */
FUNC(void, DET_CODE) Det_Init(P2CONST(Det_ConfigType, AUTOMATIC, DET_APPL_CONST) ConfigPtr)
{
    uint8_least Indice;

    /* Det_ConfigType no transporta ningun dato: el capitulo 10 clasifica toda
       la configuracion del modulo como de tiempo de precompilacion. El
       parametro existe porque SRS_BSW_00414 lo exige, y se descarta de forma
       explicita para dejar constancia de que no usarlo es deliberado. */
    (void)ConfigPtr;

    for (Indice = 0u; Indice < DET_ERROR_BUFFER_SIZE; Indice++)
    {
        Det_Registro[Indice].ModuleId   = 0u;
        Det_Registro[Indice].InstanceId = 0u;
        Det_Registro[Indice].ApiId      = 0u; 
        Det_Registro[Indice].ErrorId    = 0u;
    }

    Det_Inicializado = TRUE;
}

/**
 * @brief   Senala al modulo que ya puede emplear sus recursos de arranque.
 *
 * @return  void
 *
 * @pre     Det_Init se ha ejecutado.
 *
 * @reentrancy  No reentrante.
 * @sync        Sincrona.
 * @serviceid   DET_START_SERVICE_ID
 *
 * @par Requisitos
 *      SWS_Det_00025  el modulo provee esta funcion.
 *
 * @note    Queda vacia de forma deliberada. La funcion existe para avisar al
 *          Det de que ya dispone de recursos que no estaban listos durante
 *          Det_Init, tipicamente una memoria no volatil donde conservar las
 *          notificaciones entre reinicios. Esta realizacion las guarda en RAM
 *          y no necesita ese aviso. La nota del capitulo 7.1 lo contempla:
 *          "In case the Default Error Tracer does not require a startup call
 *          the Det_Start function can be empty".
 */
FUNC(void, DET_CODE) Det_Start(void)
{
}

/**
 * @brief   Recibe la notificacion de un error de desarrollo.
 *
 * @param[in] ModuleId    Modulo que notifica, segun AUTOSAR_TR_BSWModuleList.
 * @param[in] InstanceId  Instancia del modulo, cero cuando solo hay una.
 * @param[in] ApiId       Identificador de servicio de la funcion que notifica.
 * @param[in] ErrorId     Identificador del error, definido por el modulo.
 *
 * @return  E_OK      la notificacion quedo registrada.
 * @return  E_NOT_OK  no se registro, por una de dos causas que esta
 *                    realizacion no distingue: el modulo no esta inicializado,
 *                    o el registro ya esta lleno. Std_ReturnType reserva los
 *                    valores 0x02 a 0x3F para codigos propios del modulo si
 *                    algun dia conviene separarlas.
 *
 * @pre     Ninguna. La funcion comprueba por si misma si el modulo esta listo.
 *
 * @reentrancy  Reentrante.
 * @sync        Sincrona.
 * @serviceid   DET_REPORT_ERROR_SERVICE_ID
 *
 * @par Requisitos
 *      SWS_Det_00024  si el modulo no esta inicializado, la funcion retorna de
 *                     inmediato sin ninguna otra accion: no invoca hooks, no
 *                     ejecuta nada propio y no registra el error.
 *      SWS_Det_00014  la funcion invoca los hooks configurados. Esta
 *                     realizacion no configura ninguno, de modo que no hay
 *                     nada que invocar.
 *
 * @note    Se conserva la primera notificacion, no la ultima: un error suele
 *          provocar otros en cascada, y la primera senala la causa.
 *
 * @warning Limitacion conocida. La especificacion declara esta funcion
 *          reentrante, pero escribir los cuatro campos del registro no es una
 *          operacion atomica. Si una interrupcion notifica mientras el bucle
 *          principal esta a mitad de la escritura, el registro puede quedar
 *          con campos de dos notificaciones distintas. La solucion es delimitar
 *          la escritura con una seccion exclusiva del planificador del BSW,
 *          que este proyecto todavia no tiene.
 */
FUNC(Std_ReturnType, DET_CODE) Det_ReportError(uint16 ModuleId,
                                               uint8  InstanceId,
                                               uint8  ApiId,
                                               uint8  ErrorId)
{
    Std_ReturnType Resultado = E_NOT_OK;
    uint8_least    Indice;

    if (Det_Inicializado == TRUE)
    {
        for (Indice = 0u; Indice < DET_ERROR_BUFFER_SIZE; Indice++)
        {
            /* Un ModuleId a cero marca la entrada libre. Ningun modulo del BSW
               Module List usa ese identificador, de modo que no colisiona con
               una notificacion real. La constante lleva el tipo del campo para
               que la comparacion no mezcle tipos esenciales (MISRA 10.4). */
            if (Det_Registro[Indice].ModuleId == (uint16)0u)
            {
                Det_Registro[Indice].ModuleId   = ModuleId;
                Det_Registro[Indice].InstanceId = InstanceId;
                Det_Registro[Indice].ApiId      = ApiId;
                Det_Registro[Indice].ErrorId    = ErrorId;

                Resultado = E_OK;
                break;
            }
        }
    }

    return Resultado;
}

/**
 * @brief   Entrega la version del modulo.
 *
 * @param[out] versioninfo  Estructura donde se escribe la version.
 *
 * @return  void
 *
 * @pre     Ninguna. No requiere que el modulo este inicializado.
 *
 * @reentrancy  Reentrante.
 * @sync        Sincrona.
 * @serviceid   DET_GET_VERSION_INFO_SERVICE_ID
 *
 * @note    Un puntero nulo es un error de quien llama, no de este modulo. La
 *          comprobacion evita escribir en la direccion cero, que en este
 *          microcontrolador corresponde a la tabla de vectores.
 */
FUNC(void, DET_CODE) Det_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DET_APPL_DATA) versioninfo)
{
    if (versioninfo != NULL_PTR)
    {
        versioninfo->vendorID         = DET_VENDOR_ID;
        versioninfo->moduleID         = DET_MODULE_ID;
        versioninfo->sw_major_version = DET_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = DET_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = DET_SW_PATCH_VERSION;
    }
}

#define DET_STOP_SEC_CODE
#include "Det_MemMap.h"

