/**
 * @file  main.c
 * @brief Arranque provisional: parpadeo del LED LD2 (PA5) de la Nucleo-F446RE
 *        por acceso directo a registros.
 *
 * @details Codigo transitorio, previo a la capa MCAL. Se mantiene para que el
 *          proyecto produzca un binario ejecutable mientras se implementan los
 *          modulos Mcu, Port y Dio. Al completarse esos modulos, el control del
 *          LED pasa a un componente de aplicacion y este acceso directo a
 *          registros se retira: la arquitectura del proyecto no permite que la
 *          capa de aplicacion toque registros del microcontrolador.
 */
#include <stdint.h>

/* Direcciones base (Manual de referencia RM0390, STM32F446) */
#define RCC_BASE   ( 0x40023800u )
#define GPIOA_BASE ( 0x40020000u )

/* Registros usados */
#define RCC_AHB1ENR ( *(volatile uint32_t *)( RCC_BASE + 0x30u ) )   /* Habilita reloj de GPIOx */
#define GPIOA_MODER ( *(volatile uint32_t *)( GPIOA_BASE + 0x00u ) ) /* Modo del pin */
#define GPIOA_ODR   ( *(volatile uint32_t *)( GPIOA_BASE + 0x14u ) ) /* Salida */

#define LED_PIN ( 5u ) /* LD2 de la Nucleo-F446RE esta en PA5 */

static void delay( uint32_t cnt );

int main( void )
{
    /* Habilita el reloj del puerto GPIOA (bit 0 de AHB1ENR) */
    RCC_AHB1ENR |= ( 1u << 0u );

    /* Configura PA5 como salida de proposito general (MODER5 = 01) */
    GPIOA_MODER &= ~( 3u << ( LED_PIN * 2u ) );
    GPIOA_MODER |= ( 1u << ( LED_PIN * 2u ) );

    for( ;; )
    {
        GPIOA_ODR ^= ( 1u << LED_PIN ); /* Conmuta el LED */
        delay( 500000u );
    }

    return 0;
}

static void delay( uint32_t cnt )
{
    while( cnt > 0u )
    {
        cnt--;
    }
}
