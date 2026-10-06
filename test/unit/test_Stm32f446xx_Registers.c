/**
 * @file    test_Stm32f446xx_Registers.c
 * @brief   Pruebas estructurales del mapa de registros del STM32F446.
 *
 * @details Comprueba que las direcciones base y la disposicion de las
 *          estructuras de registros coinciden con RM0390. Una estructura con un
 *          hueco reservado mal dimensionado compila sin aviso y escribe en el
 *          registro equivocado en la placa; estas pruebas detectan ese error en
 *          el equipo anfitrion, antes de programar nada.
 *
 * @note    Solo se calculan desplazamientos y tamanos. No se accede a ninguna
 *          direccion de periferico, que en el host no existe.
 *
 * @par Referencia
 *      RM0390 rev. 6, tabla "Register boundary addresses" para las bases;
 *      capitulo 6.3 (RCC register map) y 8.4 (GPIO register map) para los
 *      desplazamientos.
 */
#include <stddef.h>
#include "unity.h"
#include "Stm32f446xx_Registers.h"

/* El tamano total de cada estructura fija el ultimo registro mas su ancho.
   Si un hueco reservado cambia, estas aserciones detienen la compilacion. */
_Static_assert(sizeof(Stm32_RccRegisterType)  == 0x98u, "mapa de RCC alterado");
_Static_assert(sizeof(Stm32_GpioRegisterType) == 0x28u, "mapa de GPIO alterado");

void setUp(void)
{
}

void tearDown(void)
{
}

/* --- Direcciones base ----------------------------------------------------- */

void test_BasesDeBus_coinciden_con_RM0390(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x40000000u, PERIPH_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40000000u, APB1PERIPH_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40010000u, APB2PERIPH_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40020000u, AHB1PERIPH_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x50000000u, AHB2PERIPH_BASE);
}

void test_BasesDeGpio_son_consecutivas_cada_1K(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x40020000u, GPIOA_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40020400u, GPIOB_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40020800u, GPIOC_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40020C00u, GPIOD_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40021000u, GPIOE_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40021400u, GPIOF_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40021800u, GPIOG_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40021C00u, GPIOH_BASE);
}

void test_BasesUsadas_por_los_primeros_modulos(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x40023800u, RCC_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40023C00u, FLASH_R_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40007000u, PWR_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40013800u, SYSCFG_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40006400u, CAN1_BASE);
    TEST_ASSERT_EQUAL_HEX32(0x40006800u, CAN2_BASE);
}

/* --- Disposicion de los registros GPIO ------------------------------------ */

void test_RegistrosGpio_estan_en_su_desplazamiento(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x00u, offsetof(Stm32_GpioRegisterType, MODER));
    TEST_ASSERT_EQUAL_HEX32(0x04u, offsetof(Stm32_GpioRegisterType, OTYPER));
    TEST_ASSERT_EQUAL_HEX32(0x08u, offsetof(Stm32_GpioRegisterType, OSPEEDR));
    TEST_ASSERT_EQUAL_HEX32(0x0Cu, offsetof(Stm32_GpioRegisterType, PUPDR));
    TEST_ASSERT_EQUAL_HEX32(0x10u, offsetof(Stm32_GpioRegisterType, IDR));
    TEST_ASSERT_EQUAL_HEX32(0x14u, offsetof(Stm32_GpioRegisterType, ODR));
    TEST_ASSERT_EQUAL_HEX32(0x18u, offsetof(Stm32_GpioRegisterType, BSRR));
    TEST_ASSERT_EQUAL_HEX32(0x1Cu, offsetof(Stm32_GpioRegisterType, LCKR));
    /* AFR[0] es AFRL (0x20) y AFR[1] es AFRH (0x24). */
    TEST_ASSERT_EQUAL_HEX32(0x20u, offsetof(Stm32_GpioRegisterType, AFR));
    TEST_ASSERT_EQUAL_HEX32(0x28u, (uint32)sizeof(Stm32_GpioRegisterType));
}

/* --- Disposicion de los registros RCC ------------------------------------- */

void test_RegistrosRcc_de_control_y_configuracion(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x00u, offsetof(Stm32_RccRegisterType, CR));
    TEST_ASSERT_EQUAL_HEX32(0x04u, offsetof(Stm32_RccRegisterType, PLLCFGR));
    TEST_ASSERT_EQUAL_HEX32(0x08u, offsetof(Stm32_RccRegisterType, CFGR));
    TEST_ASSERT_EQUAL_HEX32(0x0Cu, offsetof(Stm32_RccRegisterType, CIR));
}

void test_RegistrosRcc_de_reset_conservan_el_hueco_reservado(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x10u, offsetof(Stm32_RccRegisterType, AHB1RSTR));
    TEST_ASSERT_EQUAL_HEX32(0x14u, offsetof(Stm32_RccRegisterType, AHB2RSTR));
    TEST_ASSERT_EQUAL_HEX32(0x18u, offsetof(Stm32_RccRegisterType, AHB3RSTR));
    /* 0x1C esta reservado: APB1RSTR debe caer en 0x20, no en 0x1C. */
    TEST_ASSERT_EQUAL_HEX32(0x20u, offsetof(Stm32_RccRegisterType, APB1RSTR));
    TEST_ASSERT_EQUAL_HEX32(0x24u, offsetof(Stm32_RccRegisterType, APB2RSTR));
}

void test_RegistrosRcc_de_habilitacion_de_reloj(void)
{
    /* Los que necesitan Mcu, Port y Dio para dar reloj a los puertos. */
    TEST_ASSERT_EQUAL_HEX32(0x30u, offsetof(Stm32_RccRegisterType, AHB1ENR));
    TEST_ASSERT_EQUAL_HEX32(0x34u, offsetof(Stm32_RccRegisterType, AHB2ENR));
    TEST_ASSERT_EQUAL_HEX32(0x38u, offsetof(Stm32_RccRegisterType, AHB3ENR));
    TEST_ASSERT_EQUAL_HEX32(0x40u, offsetof(Stm32_RccRegisterType, APB1ENR));
    TEST_ASSERT_EQUAL_HEX32(0x44u, offsetof(Stm32_RccRegisterType, APB2ENR));
}

void test_RegistrosRcc_de_bajo_consumo(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x50u, offsetof(Stm32_RccRegisterType, AHB1LPENR));
    TEST_ASSERT_EQUAL_HEX32(0x54u, offsetof(Stm32_RccRegisterType, AHB2LPENR));
    TEST_ASSERT_EQUAL_HEX32(0x58u, offsetof(Stm32_RccRegisterType, AHB3LPENR));
    TEST_ASSERT_EQUAL_HEX32(0x60u, offsetof(Stm32_RccRegisterType, APB1LPENR));
    TEST_ASSERT_EQUAL_HEX32(0x64u, offsetof(Stm32_RccRegisterType, APB2LPENR));
}

void test_RegistrosRcc_finales_y_tamano_total(void)
{
    TEST_ASSERT_EQUAL_HEX32(0x70u, offsetof(Stm32_RccRegisterType, BDCR));
    TEST_ASSERT_EQUAL_HEX32(0x74u, offsetof(Stm32_RccRegisterType, CSR));
    TEST_ASSERT_EQUAL_HEX32(0x80u, offsetof(Stm32_RccRegisterType, SSCGR));
    TEST_ASSERT_EQUAL_HEX32(0x84u, offsetof(Stm32_RccRegisterType, PLLI2SCFGR));
    TEST_ASSERT_EQUAL_HEX32(0x88u, offsetof(Stm32_RccRegisterType, PLLSAICFGR));
    TEST_ASSERT_EQUAL_HEX32(0x8Cu, offsetof(Stm32_RccRegisterType, DCKCFGR));
    TEST_ASSERT_EQUAL_HEX32(0x90u, offsetof(Stm32_RccRegisterType, CKGATENR));
    TEST_ASSERT_EQUAL_HEX32(0x94u, offsetof(Stm32_RccRegisterType, DCKCFGR2));
    TEST_ASSERT_EQUAL_HEX32(0x98u, (uint32)sizeof(Stm32_RccRegisterType));
}
