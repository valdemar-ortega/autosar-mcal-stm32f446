/**
 * @file Stm32f446xx_Registers.h
 * @brief Mapa de direcciones base y estructuras de registros del STM32F446.
 *
 * @details Los miembros de cada estructura conservan el orden y los offsets
 * definidos por RM0390. Este header es privado de la capa dependiente del
 * dispositivo; no debe incluirse desde Application, Rte ni headers publicos
 * de MCAL.
 * @note La fuente de verdad para direcciones, offsets y acceso a registros es
 * RM0390, no este archivo.
 */
#ifndef STM32F446XX_REGISTERS_H
#define STM32F446XX_REGISTERS_H

#include "Platform_Types.h"

/** @name Memoria y regiones generales */
/** @{ */

#define PERIPH_BASE            (0x40000000UL) /*!< Inicio de la region de perifericos. */
/** @} */

/** @name Bases de buses de perifericos */
/** @{ */
#define APB1PERIPH_BASE        (PERIPH_BASE + 0x00000000UL) /*!< Inicio de APB1. */
#define APB2PERIPH_BASE        (PERIPH_BASE + 0x00010000UL) /*!< Inicio de APB2. */
#define AHB1PERIPH_BASE        (PERIPH_BASE + 0x00020000UL) /*!< Inicio de AHB1. */
#define AHB2PERIPH_BASE        (PERIPH_BASE + 0x10000000UL) /*!< Inicio de AHB2. */
/** @} */

/* Perifericos APB1. */
#define TIM2_BASE              (APB1PERIPH_BASE + 0x0000UL) /*!< TIM2 base address */
#define TIM3_BASE              (APB1PERIPH_BASE + 0x0400UL) /*!< TIM3 base address */
#define TIM4_BASE              (APB1PERIPH_BASE + 0x0800UL) /*!< TIM4 base address */
#define TIM5_BASE              (APB1PERIPH_BASE + 0x0C00UL) /*!< TIM5 base address */
#define TIM6_BASE              (APB1PERIPH_BASE + 0x1000UL) /*!< TIM6 base address */
#define TIM7_BASE              (APB1PERIPH_BASE + 0x1400UL) /*!< TIM7 base address */
#define TIM12_BASE             (APB1PERIPH_BASE + 0x1800UL) /*!< TIM12 base address */
#define TIM13_BASE             (APB1PERIPH_BASE + 0x1C00UL) /*!< TIM13 base address */
#define TIM14_BASE             (APB1PERIPH_BASE + 0x2000UL) /*!< TIM14 base address */
#define RTC_BASE               (APB1PERIPH_BASE + 0x2800UL) /*!< RTC base address */
#define WWDG_BASE              (APB1PERIPH_BASE + 0x2C00UL) /*!< WWDG base address */
#define IWDG_BASE              (APB1PERIPH_BASE + 0x3000UL) /*!< IWDG base address */
#define SPI2_BASE              (APB1PERIPH_BASE + 0x3800UL) /*!< SPI2 base address */
#define SPI3_BASE              (APB1PERIPH_BASE + 0x3C00UL) /*!< SPI3 base address */
#define SPDIFRX_BASE           (APB1PERIPH_BASE + 0x4000UL) /*!< SPDIFRX base address */
#define USART2_BASE            (APB1PERIPH_BASE + 0x4400UL) /*!< USART2 base address */
#define USART3_BASE            (APB1PERIPH_BASE + 0x4800UL) /*!< USART3 base address */
#define UART4_BASE             (APB1PERIPH_BASE + 0x4C00UL) /*!< UART4 base address */
#define UART5_BASE             (APB1PERIPH_BASE + 0x5000UL) /*!< UART5 base address */
#define I2C1_BASE              (APB1PERIPH_BASE + 0x5400UL) /*!< I2C1 base address */
#define I2C2_BASE              (APB1PERIPH_BASE + 0x5800UL) /*!< I2C2 base address */
#define I2C3_BASE              (APB1PERIPH_BASE + 0x5C00UL) /*!< I2C3 base address */
#define FMPI2C1_BASE           (APB1PERIPH_BASE + 0x6000UL) /*!< FMPI2C1 base address */
#define CAN1_BASE              (APB1PERIPH_BASE + 0x6400UL) /*!< CAN1 base address */
#define CAN2_BASE              (APB1PERIPH_BASE + 0x6800UL) /*!< CAN2 base address */
#define CEC_BASE               (APB1PERIPH_BASE + 0x6C00UL) /*!< CEC base address */
#define PWR_BASE               (APB1PERIPH_BASE + 0x7000UL) /*!< PWR base address */
#define DAC_BASE               (APB1PERIPH_BASE + 0x7400UL) /*!< DAC base address */

/* Perifericos APB2. */
#define TIM1_BASE              (APB2PERIPH_BASE + 0x0000UL) /*!< TIM1 base address */
#define TIM8_BASE              (APB2PERIPH_BASE + 0x0400UL) /*!< TIM8 base address */
#define USART1_BASE            (APB2PERIPH_BASE + 0x1000UL) /*!< USART1 base address */
#define USART6_BASE            (APB2PERIPH_BASE + 0x1400UL) /*!< USART6 base address */
#define ADC1_BASE              (APB2PERIPH_BASE + 0x2000UL) /*!< ADC1 base address */
#define ADC2_BASE              (APB2PERIPH_BASE + 0x2100UL) /*!< ADC2 base address */
#define ADC3_BASE              (APB2PERIPH_BASE + 0x2200UL) /*!< ADC3 base address */
#define ADC123_COMMON_BASE     (APB2PERIPH_BASE + 0x2300UL) /*!< ADC123_COMMON base address */
#define SDIO_BASE              (APB2PERIPH_BASE + 0x2C00UL) /*!< SDIO base address */
#define SPI1_BASE              (APB2PERIPH_BASE + 0x3000UL)  /*!< SPI1 base address */
#define SPI4_BASE              (APB2PERIPH_BASE + 0x3400UL) /*!< SPI4 base address */
#define SYSCFG_BASE            (APB2PERIPH_BASE + 0x3800UL) /*!< SYSCFG base address */
#define EXTI_BASE              (APB2PERIPH_BASE + 0x3C00UL) /*!< EXTI base address */
#define TIM9_BASE              (APB2PERIPH_BASE + 0x4000UL) /*!< TIM9 base address */
#define TIM10_BASE             (APB2PERIPH_BASE + 0x4400UL) /*!< TIM10 base address */
#define TIM11_BASE             (APB2PERIPH_BASE + 0x4800UL) /*!< TIM11 base address */
#define SAI1_BASE              (APB2PERIPH_BASE + 0x5800UL) /*!< SAI1 base address */
#define SAI2_BASE              (APB2PERIPH_BASE + 0x5C00UL) /*!< SAI2 base address */

/* Perifericos AHB1. */
#define GPIOA_BASE             (AHB1PERIPH_BASE + 0x0000UL) /*!< GPIOA base address */
#define GPIOB_BASE             (AHB1PERIPH_BASE + 0x0400UL) /*!< GPIOB base address */
#define GPIOC_BASE             (AHB1PERIPH_BASE + 0x0800UL) /*!< GPIOC base address */
#define GPIOD_BASE             (AHB1PERIPH_BASE + 0x0C00UL) /*!< GPIOD base  address */
#define GPIOE_BASE             (AHB1PERIPH_BASE + 0x1000UL) /*!< GPIOE base address */
#define GPIOF_BASE             (AHB1PERIPH_BASE + 0x1400UL) /*!< GPIOF base address */     
#define GPIOG_BASE             (AHB1PERIPH_BASE + 0x1800UL) /*!< GPIOG base address */
#define GPIOH_BASE             (AHB1PERIPH_BASE + 0x1C00UL) /*!< GPIOH base address */
#define CRC_BASE               (AHB1PERIPH_BASE + 0x3000UL) /*!< CRC base address */
#define RCC_BASE               (AHB1PERIPH_BASE + 0x3800UL) /*!< RCC base address */
#define FLASH_R_BASE           (AHB1PERIPH_BASE + 0x3C00UL) /*!< FLASH_R base address */
#define BKPSRAM_BASE           (AHB1PERIPH_BASE + 0x4000UL) /*!< BKPSRAM base address */
#define DMA1_BASE              (AHB1PERIPH_BASE + 0x6000UL) /*!< DMA1 base address */        
#define DMA2_BASE              (AHB1PERIPH_BASE + 0x6400UL) /*!< DMA2 base address */
#define USB_OTG_HS_PERIPH_BASE (AHB1PERIPH_BASE + 0x20000UL) /*!< USB OTG HS base address */

/* Perifericos AHB2 y bloques con regiones dedicadas. */
#define USB_OTG_FS_PERIPH_BASE (AHB2PERIPH_BASE + 0x0000UL) /*!< USB OTG FS base address */
#define DCMI_BASE              (AHB2PERIPH_BASE + 0x50000UL) /*!< DCMI base address */
#define QSPI_R_BASE            (0xA0001000UL) /*!< Base de registros de QuadSPI. */
#define FMC_R_BASE             (0xA0000000UL) /*!< Base de registros de FMC. */

/**
 * @brief Distribucion de los registros de un puerto GPIO.
 * @details RM0390, tabla "GPIO register map". La misma estructura se usa
 * para GPIOA a GPIOH; la instancia se selecciona por su direccion base.
 */
typedef struct
{
    volatile uint32 MODER;    /*!< Modo de cada pin; offset 0x00. */
    volatile uint32 OTYPER;   /*!< Tipo de salida de cada pin; offset 0x04. */
    volatile uint32 OSPEEDR;  /*!< Velocidad de salida de cada pin; offset 0x08. */
    volatile uint32 PUPDR;    /*!< Pull-up/pull-down de cada pin; offset 0x0C. */
    volatile uint32 IDR;      /*!< Datos de entrada del puerto; offset 0x10. */
    volatile uint32 ODR;      /*!< Datos de salida del puerto; offset 0x14. */
    volatile uint32 BSRR;     /*!< Set/reset atomico de bits; offset 0x18. */
    volatile uint32 LCKR;     /*!< Bloqueo de configuracion; offset 0x1C. */
    volatile uint32 AFR[2];   /*!< Funcion alternativa baja/alta; offsets 0x20 y 0x24. */
} Stm32_GpioRegisterType;

/**
 * @brief Distribucion de los registros Reset and Clock Control (RCC).
 * @details RM0390, tabla "RCC register map". Los miembros RESERVED preservan
 * los offsets fisicos y no se deben utilizar.
 */
typedef struct
{
    volatile uint32 CR;           /*!< Control de reloj; offset 0x00. */
    volatile uint32 PLLCFGR;      /*!< Configuracion de PLL principal; offset 0x04. */
    volatile uint32 CFGR;         /*!< Configuracion de relojes; offset 0x08. */
    volatile uint32 CIR;          /*!< Interrupciones de reloj; offset 0x0C. */
    volatile uint32 AHB1RSTR;     /*!< Reset de perifericos AHB1; offset 0x10. */
    volatile uint32 AHB2RSTR;     /*!< Reset de perifericos AHB2; offset 0x14. */
    volatile uint32 AHB3RSTR;     /*!< Reset de perifericos AHB3; offset 0x18. */
    uint32 RESERVED0;             /*!< Reservado; offset 0x1C. */
    volatile uint32 APB1RSTR;     /*!< Reset de perifericos APB1; offset 0x20. */
    volatile uint32 APB2RSTR;     /*!< Reset de perifericos APB2; offset 0x24. */
    uint32 RESERVED1[2];          /*!< Reservado; offsets 0x28 a 0x2C. */
    volatile uint32 AHB1ENR;      /*!< Habilitacion de reloj AHB1; offset 0x30. */
    volatile uint32 AHB2ENR;      /*!< Habilitacion de reloj AHB2; offset 0x34. */
    volatile uint32 AHB3ENR;      /*!< Habilitacion de reloj AHB3; offset 0x38. */
    uint32 RESERVED2;             /*!< Reservado; offset 0x3C. */
    volatile uint32 APB1ENR;      /*!< Habilitacion de reloj APB1; offset 0x40. */
    volatile uint32 APB2ENR;      /*!< Habilitacion de reloj APB2; offset 0x44. */
    uint32 RESERVED3[2];          /*!< Reservado; offsets 0x48 a 0x4C. */
    volatile uint32 AHB1LPENR;    /*!< Reloj AHB1 en bajo consumo; offset 0x50. */
    volatile uint32 AHB2LPENR;    /*!< Reloj AHB2 en bajo consumo; offset 0x54. */
    volatile uint32 AHB3LPENR;    /*!< Reloj AHB3 en bajo consumo; offset 0x58. */
    uint32 RESERVED4;             /*!< Reservado; offset 0x5C. */
    volatile uint32 APB1LPENR;    /*!< Reloj APB1 en bajo consumo; offset 0x60. */
    volatile uint32 APB2LPENR;    /*!< Reloj APB2 en bajo consumo; offset 0x64. */
    uint32 RESERVED5[2];          /*!< Reservado; offsets 0x68 a 0x6C. */
    volatile uint32 BDCR;         /*!< Control del dominio de respaldo; offset 0x70. */
    volatile uint32 CSR;          /*!< Control y estado de reloj; offset 0x74. */
    uint32 RESERVED6[2];          /*!< Reservado; offsets 0x78 a 0x7C. */
    volatile uint32 SSCGR;        /*!< Generacion de espectro expandido; offset 0x80. */
    volatile uint32 PLLI2SCFGR;   /*!< Configuracion de PLLI2S; offset 0x84. */
    volatile uint32 PLLSAICFGR;   /*!< Configuracion de PLLSAI; offset 0x88. */
    volatile uint32 DCKCFGR;      /*!< Configuracion de relojes dedicados; offset 0x8C. */
    volatile uint32 CKGATENR;     /*!< Control de clock gating; offset 0x90. */
    volatile uint32 DCKCFGR2;     /*!< Segunda configuracion de relojes dedicados; offset 0x94. */
} Stm32_RccRegisterType;


/** @name Instancias tipadas de registros */
/** @{ */
#define GPIOA ((Stm32_GpioRegisterType *) GPIOA_BASE) /*!< Registros del puerto GPIOA. */
#define GPIOB ((Stm32_GpioRegisterType *) GPIOB_BASE) /*!< Registros del puerto GPIOB. */
#define GPIOC ((Stm32_GpioRegisterType *) GPIOC_BASE) /*!< Registros del puerto GPIOC. */
#define GPIOD ((Stm32_GpioRegisterType *) GPIOD_BASE) /*!< Registros del puerto GPIOD. */
#define GPIOE ((Stm32_GpioRegisterType *) GPIOE_BASE) /*!< Registros del puerto GPIOE. */
#define GPIOF ((Stm32_GpioRegisterType *) GPIOF_BASE) /*!< Registros del puerto GPIOF. */
#define GPIOG ((Stm32_GpioRegisterType *) GPIOG_BASE) /*!< Registros del puerto GPIOG. */
#define GPIOH ((Stm32_GpioRegisterType *) GPIOH_BASE) /*!< Registros del puerto GPIOH. */
#define RCC   ((Stm32_RccRegisterType *) RCC_BASE)     /*!< Registros Reset and Clock Control. */
/** @} */



#endif /* STM32F446XX_REGISTERS_H */
