/**
 * @file    Platform_Types.h
 * @brief   Tipos dependientes de la plataforma para el MCAL del STM32F446.
 *
 * @details Implementa AUTOSAR CP R20-11, Specification of Platform Types.
 *          Es la cabecera base de todo el BSW: no depende de ninguna otra y
 *          define los tipos de ancho fijo sobre los que se construyen el resto
 *          de modulos, de modo que ninguno declara variantes propias.
 *
 *          Realizacion para Arm GNU Toolchain (arm-none-eabi-gcc, C11) sobre
 *          Cortex-M4: palabra natural de 32 bits, aritmetica en complemento a
 *          dos y ordenacion little endian. Los anchos estan comprobados en
 *          test/unit/test_Platform_Types.c.
 *
 * @author  Jesus Valdemar Ortega
 * @date    2026-10-07
 *
 * @par Trazabilidad
 *      Enteros estandar:      SWS_Platform_00013 .. 00018
 *      Enteros optimizados:   SWS_Platform_00020 .. 00025
 *      boolean:               SWS_Platform_00026, 00027, 00034, 00060
 *      Coma flotante:         SWS_Platform_00041, 00042
 *      Punteros genericos:    SWS_Platform_91001, 91002
 *      CPU_TYPE:              SWS_Platform_00064
 *      Orden de bits y bytes: SWS_Platform_00038, 00039, 00048 .. 00051
 *      TRUE y FALSE:          SWS_Platform_00054, 00055, 00056
 *      Complemento a dos:     SWS_Platform_00061
 */
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*==================================================================================================
 *  Informacion publicada
 *
 *  Identificacion del modulo y version de la release contra la que se escribio
 *  esta cabecera, segun AUTOSAR_SWS_BSWGeneral capitulo 10.3. Permite que un
 *  modulo compruebe con #if que compila contra la version de tipos que espera.
 *================================================================================================*/

#define PLATFORM_VENDOR_ID                   0u    /* Sin identificador asignado en la lista de proveedores de AUTOSAR. */
#define PLATFORM_MODULE_ID                   199u
#define PLATFORM_AR_RELEASE_MAJOR_VERSION    20u
#define PLATFORM_AR_RELEASE_MINOR_VERSION    11u
#define PLATFORM_AR_RELEASE_REVISION_VERSION 0u
#define PLATFORM_SW_MAJOR_VERSION            1u
#define PLATFORM_SW_MINOR_VERSION            0u
#define PLATFORM_SW_PATCH_VERSION            0u

/*==================================================================================================
 *  Tipos enteros y logico
 *
 *  Capitulo 8.2 de la especificacion. Los tipos con signo emplean complemento
 *  a dos, unica representacion admitida (SWS_Platform_00061).
 *================================================================================================*/

/** Tipo logico. Se usa solo con TRUE y FALSE; sobre el no se aplican
 *  operadores aritmeticos ni de bits (SWS_Platform_00034). Se realiza como
 *  entero sin signo del ancho mas corto que soporta la plataforma de forma
 *  nativa, y al que se pueden aplicar punteros (SWS_Platform_00027, 00060). */
typedef unsigned char       boolean;

typedef signed char         sint8;   /**< Entero con signo de 8 bits:  -128 .. 127. */
typedef unsigned char       uint8;   /**< Entero sin signo de 8 bits:  0 .. 255. */
typedef signed short        sint16;  /**< Entero con signo de 16 bits: -32768 .. 32767. */
typedef unsigned short      uint16;  /**< Entero sin signo de 16 bits: 0 .. 65535. */
typedef signed int          sint32;  /**< Entero con signo de 32 bits. */
typedef unsigned int        uint32;  /**< Entero sin signo de 32 bits. */
typedef signed long long    sint64;  /**< Entero con signo de 64 bits. */
typedef unsigned long long  uint64;  /**< Entero sin signo de 64 bits. */

/*==================================================================================================
 *  Tipos enteros optimizados
 *
 *  Capitulo 7.4 de la especificacion. Garantizan al menos el rango que indica
 *  su nombre, pero se realizan con el tipo de acceso mas rapido de la
 *  plataforma. Su uso previsto son contadores de bucle y argumentos de switch,
 *  donde el rango importa y el tamano en memoria no.
 *
 *  En Cortex-M4 el registro y el bus son de 32 bits: un contador mas estrecho
 *  obligaria al compilador a enmascarar el resultado en cada operacion, que es
 *  lo contrario de lo que persiguen estos tipos. Por eso los seis se realizan
 *  con la palabra nativa.
 *================================================================================================*/

typedef unsigned int        uint8_least;   /**< Sin signo, al menos 0 .. 255. */
typedef signed int          sint8_least;   /**< Con signo, al menos -128 .. 127. */
typedef unsigned int        uint16_least;  /**< Sin signo, al menos 0 .. 65535. */
typedef signed int          sint16_least;  /**< Con signo, al menos -32768 .. 32767. */
typedef unsigned int        uint32_least;  /**< Sin signo, al menos 32 bits. */
typedef signed int          sint32_least;  /**< Con signo, al menos 32 bits. */

/*==================================================================================================
 *  Tipos de coma flotante
 *
 *  Formatos binary32 y binary64 de IEEE 754-2008 (SWS_Platform_00041, 00042).
 *  El proyecto compila con -mfloat-abi=soft, de modo que las operaciones se
 *  resuelven por biblioteca aunque el Cortex-M4 disponga de unidad de coma
 *  flotante de precision simple.
 *================================================================================================*/

typedef float               float32;  /**< Coma flotante de 32 bits. */
typedef double              float64;  /**< Coma flotante de 64 bits. */

/*==================================================================================================
 *  Punteros genericos
 *
 *  SWS_Platform_91001 y 91002. VoidPtr se emplea en los buferes que una API
 *  devuelve al llamante; ConstVoidPtr, en los que recibe.
 *================================================================================================*/

typedef void *              VoidPtr;       /**< Puntero generico a dato modificable. */
typedef const void *        ConstVoidPtr;  /**< Puntero generico a dato de solo lectura. */

/*==================================================================================================
 *  Caracteristicas de la plataforma
 *
 *  Capitulo 8.3 de la especificacion.
 *================================================================================================*/

/** @name Valores admitidos por CPU_TYPE (SWS_Platform_00064) */
/** @{ */
#define CPU_TYPE_8           (8u)   /**< Procesador de 8 bits. */
#define CPU_TYPE_16          (16u)  /**< Procesador de 16 bits. */
#define CPU_TYPE_32          (32u)  /**< Procesador de 32 bits. */
#define CPU_TYPE_64          (64u)  /**< Procesador de 64 bits. */
/** @} */

/** @name Valores admitidos por CPU_BIT_ORDER (SWS_Platform_00038) */
/** @{ */
#define MSB_FIRST            (0u)   /**< El bit mas significativo es el primero. */
#define LSB_FIRST            (1u)   /**< El bit menos significativo es el primero. */
/** @} */

/** @name Valores admitidos por CPU_BYTE_ORDER (SWS_Platform_00039) */
/** @{ */
#define HIGH_BYTE_FIRST      (0u)   /**< En un uint16, el byte alto va primero. */
#define LOW_BYTE_FIRST       (1u)   /**< En un uint16, el byte bajo va primero. */
/** @} */

/** @name Plataforma de este proyecto: Cortex-M4 del STM32F446, little endian */
/** @{ */
#define CPU_TYPE             CPU_TYPE_32
#define CPU_BIT_ORDER        LSB_FIRST
#define CPU_BYTE_ORDER       LOW_BYTE_FIRST
/** @} */

/*==================================================================================================
 *  TRUE y FALSE
 *
 *  SWS_Platform_00056 fija esta forma literal, y SWS_Platform_00054 exige la
 *  comprobacion condicional para el caso de que el compilador ya los defina.
 *  Solo se emplean junto al tipo boolean (SWS_Platform_00055).
 *================================================================================================*/

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

#endif /* PLATFORM_TYPES_H */
