/**
 * @file    Std_Types.h
 * @brief   Tipos y simbolos comunes a todos los modulos del BSW.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Standard Types.
 *          Reune en una sola cabecera los tipos dependientes de la plataforma
 *          y la abstraccion del compilador, de modo que un modulo del BSW solo
 *          necesita incluir este archivo para disponer de ambos.
 *
 *          Los modulos que forman parte de la pila de comunicacion incluyen
 *          ComStack_Types.h en su lugar, que a su vez incluye este archivo
 *          (SWS_Std_00030). El resto de modulos incluyen Std_Types.h.
 *
 *          Los tipos de los capitulos 8.1.3 a 8.1.7 (Std_TransformerError,
 *          Std_TransformerForward, Std_MessageTypeType,
 *          Std_MessageResultType y Std_ExtractProtocolHeaderFieldsType)
 *          pertenecen a los transformadores de la pila de comunicacion y no
 *          se declaran: este proyecto no los utiliza.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-06
 *
 * @par Trazabilidad
 *      SWS_Std_00005  Std_ReturnType
 *      SWS_Std_00006  E_OK, E_NOT_OK
 *      SWS_Std_00007  STD_HIGH, STD_LOW
 *      SWS_Std_00010  STD_ON, STD_OFF
 *      SWS_Std_00013  STD_ACTIVE, STD_IDLE
 *      SWS_Std_00015  Std_VersionInfoType
 *      SWS_Std_00030  estructura de inclusion
 */
#ifndef STD_TYPES_H
#define STD_TYPES_H

/*==================================================================================================
 *  Archivos incluidos
 *
 *  Platform_Types.h aporta los tipos de ancho fijo; Compiler.h, las macros de
 *  abstraccion del compilador. El sentido de la inclusion es siempre este y
 *  nunca el inverso.
 *================================================================================================*/

#include "Platform_Types.h"
#include "Compiler.h"

/*==================================================================================================
 *  Informacion publicada
 *
 *  Identificacion del modulo y version de la release contra la que se escribio
 *  esta cabecera, segun AUTOSAR_SWS_BSWGeneral capitulo 10.3. Permite que un
 *  modulo compruebe con #if que compila contra la version de tipos que espera.
 *================================================================================================*/

#define STD_VENDOR_ID                     0u    /* Sin identificador asignado en la lista de proveedores de AUTOSAR. */
#define STD_MODULE_ID                     197u
#define STD_AR_RELEASE_MAJOR_VERSION      20u
#define STD_AR_RELEASE_MINOR_VERSION      11u
#define STD_AR_RELEASE_REVISION_VERSION   0u
#define STD_SW_MAJOR_VERSION              1u
#define STD_SW_MINOR_VERSION              0u
#define STD_SW_PATCH_VERSION              0u



/*==================================================================================================
 *  Definiciones de tipos
 *
 *  Capitulo 8.1 de la especificacion.
 *================================================================================================*/
typedef uint8 Std_ReturnType;  /**< Tipo de retorno de las funciones del BSW. */
typedef struct Std_VersionInfoType  /**< Estructura que describe la version de un modulo. */
{
    uint16 vendorID;          /**< Identificador del proveedor del modulo. */
    uint16 moduleID;          /**< Identificador del modulo. */
    uint8 sw_major_version;   /**< Version mayor del modulo. */
    uint8 sw_minor_version;   /**< Version menor del modulo. */
    uint8 sw_patch_version;   /**< Version de parche del modulo. */
} Std_VersionInfoType;




/*==================================================================================================
 *  Definiciones de simbolos
 *
 *  Capitulo 8.2 de la especificacion. Valores logicos de retorno, de nivel
 *  fisico, de estado y de activacion de funciones opcionales.
 *================================================================================================*/

/* E_OK ya existe en OSEK, de modo que el simbolo se comparte. La guarda evita
   el choque de nombres y la redefinicion cuando el sistema operativo lo declara
   primero; E_NOT_OK queda fuera porque OSEK no lo define. Forma impuesta por
   SWS_Std_00006. */
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK        0x00u                  /**< La funcion termino correctamente. */
typedef unsigned char StatusType;          /* OSEK compliance */
#endif
#define E_NOT_OK    0x01u                  /**< La funcion encontro un error. */

#define STD_LOW     0x00u                  /**< Nivel fisico 0V. */
#define STD_HIGH    0x01u                  /**< Nivel fisico 5V o 3.3V. */

#define STD_IDLE    0x00u                  /**< Estado logico inactivo. */
#define STD_ACTIVE  0x01u                  /**< Estado logico activo. */

#define STD_OFF     0x00u                  /**< Funcion opcional desactivada. */
#define STD_ON      0x01u                  /**< Funcion opcional activada. */


#endif /* STD_TYPES_H */
