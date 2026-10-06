/**
 * @file Platform_Types.h
 * @brief Tipos fundamentales de la plataforma para la implementacion educativa AUTOSAR.
 *
 * Esta interfaz sigue la Specification of Platform Types de AUTOSAR. Los
 * tamanos se han elegido para el compilador ARM usado por el STM32F446
 * (Cortex-M4 de 32 bits).
 */
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/* Tipos logicos y enteros de ancho fijo. */
typedef unsigned char       boolean;
typedef signed char         sint8;
typedef unsigned char       uint8;
typedef signed short        sint16;
typedef unsigned short      uint16;
typedef signed int          sint32;
typedef unsigned int        uint32;
typedef signed long long    sint64;
typedef unsigned long long  uint64;

typedef unsigned char       uint8_least;
typedef signed char         sint8_least;
typedef unsigned short      uint16_least;
typedef signed short        sint16_least;
typedef unsigned int        uint32_least;
typedef signed int          sint32_least;

typedef float               float32;
typedef double              float64;

typedef void*               VoidPtr;
typedef const void*         ConstVoidPtr;


/* Caracteristicas de la CPU Cortex-M4 del STM32F446. */
#define CPU_TYPE_8           (8u)
#define CPU_TYPE_16          (16u)
#define CPU_TYPE_32          (32u)
#define CPU_TYPE_64          (64u)

#define MSB_FIRST            (0u)
#define LSB_FIRST            (1u)
#define HIGH_BYTE_FIRST      (0u)
#define LOW_BYTE_FIRST       (1u)

#define CPU_TYPE             CPU_TYPE_32
#define CPU_BIT_ORDER        LSB_FIRST
#define CPU_BYTE_ORDER       LOW_BYTE_FIRST

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

#endif /* PLATFORM_TYPES_H */

