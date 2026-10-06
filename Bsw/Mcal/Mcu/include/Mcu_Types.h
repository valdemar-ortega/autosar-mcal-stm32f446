/**
 * @file Mcu_Types.h
 * @brief Tipos de datos para el módulo Mcu.
 * @author Valdemar
 * @date 2026-08-15
 * @version 1.0
 */
#ifndef MCU_TYPES_H
#define MCU_TYPES_H

#include "Std_Types.h"

/**@brief
 * Specifies the identification (ID) for a clock setting, which is 
 * configured in the configuration structure
 */ 
typedef uint8 Mcu_ClockType;

/**@brief
 * This type specifies the identification (ID) for a MCU mode, 
 * which is configured in the configuration structure.
 */
typedef uint8 Mcu_ModeType;

/**@brief
 * This type specifies the identification (ID) for a RAM section, 
 * which is configured in the configuration structure.  
 */
typedef uint8 Mcu_RamSectionType;

/**@brief
 * This type specifies the reset reason in raw register format 
 * read from a reset status register.
 */
typedef uint32 Mcu_RawResetType;

/**@brief
 * This is a status value returned by the function 
 * Mcu_GetPllStatus of the MCU module.
 */
typedef enum
{
    MCU_PLL_LOCKED           = 0x00u, /*!< PLL is locked*/
    MCU_PLL_UNLOCKED         = 0x01u, /*!< PLL is unlocked*/
    MCU_PLL_STATUS_UNDEFINED = 0x02u, /*!< PLL Status is unknown*/
}Mcu_PllStatusType;

/**@brief
 * This is the type of the reset enumerator containing the subset 
 * of reset types. It is not required that all reset types are 
 * supported by hardware.
 */
typedef enum
{
    MCU_POWER_ON_RESET  = 0x00u,    /*!<Power On Reset (default)*/
    MCU_WATCHDOG_RESET  = 0x01u,    /*!<Internal Watchdog Timer Reset*/
    MCU_SW_RESET        = 0x02u,    /*!<Software Reset*/
    MCU_RESET_UNDEFINED = 0x03u     /*!<Reset is undefined*/
}Mcu_ResetType;

/**@brief
 * This is the Ram State data type returned by the function Mcu_GetRamState
 * of the Mcu module. It is not required that all RAM state types are 
 * supported by the hardware.
 */
typedef enum
{
    MCU_RAMSTATE_INVALID = 0x00u, /*!< Ram content is not valid or unknown (default).*/
    MCU_RAMSTATE_VALID    = 0x01u, /*!< Ram content is valid */
    
}Mcu_RamStateType;

/**
 * @brief Configuracion de relojes perifericos para una seleccion de reloj.
 * @details Cada mascara se aplica al registro RCC de habilitacion indicado.
 */
typedef struct
{
    uint32 Ahb1PeripheralClockMask; /*!< Bits que se escriben en RCC_AHB1ENR. */
    uint32 Ahb2PeripheralClockMask; /*!< Bits que se escriben en RCC_AHB2ENR. */
    uint32 Apb1PeripheralClockMask; /*!< Bits que se escriben en RCC_APB1ENR. */
    uint32 Apb2PeripheralClockMask; /*!< Bits que se escriben en RCC_APB2ENR. */
} Mcu_ClockConfigType;

/**
 * @brief Configuracion de un modo MCU soportado por esta implementacion.
 * @details Inicialmente se utilizara unicamente el modo normal de ejecucion.
 */
typedef struct
{
    Mcu_ModeType ModeId; /*!< Identificador del modo configurado. */
} Mcu_ModeConfigType;

/**
 * @brief Datos requeridos para inicializar una seccion RAM.
 * @details Se utilizan posteriormente por Mcu_InitRamSection.
 */
typedef struct
{
    uint8 *BaseAddress;  /*!< Primera direccion de la seccion RAM. */
    uint32 Size;         /*!< Tamano de la seccion en bytes. */
    uint8 DefaultValue;  /*!< Valor inicial para cada byte de la seccion. */
    uint8 WriteSize;     /*!< Tamano de escritura configurado, en bytes. */
} Mcu_RamSectionConfigType;

/**@brief
 * A pointer to such a structure is provided to the MCU 
 * initialization routines for configuration.
 */
typedef struct
{
    const Mcu_ClockConfigType *ClockSettings; /*!< Arreglo de configuraciones de reloj. */
    uint8 ClockSettingsCount;                 /*!< Número de elementos de ClockSettings. */

    const Mcu_ModeConfigType *Modes;          /*!< Arreglo de modos MCU configurados. */
    uint8 ModeCount;                          /*!< Número de elementos de Modes. */

    const Mcu_RamSectionConfigType *RamSections; /*!< Arreglo de secciones RAM configuradas. */
    uint8 RamSectionCount;                    /*!< Número de elementos de RamSections. */
} Mcu_ConfigType;

#endif /* MCU_TYPES_H */
