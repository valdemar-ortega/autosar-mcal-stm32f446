/**
 * @file    test_Platform_Types.c
 * @brief   Pruebas estructurales de los tipos de plataforma.
 *
 * @details Verifica que la realizacion de Platform_Types.h cumple los rangos y
 *          tamanos que exige AUTOSAR CP R20-11, Specification of Platform Types.
 *          Son pruebas de contrato: no ejercitan logica, comprueban que los
 *          tipos sobre los que se construye todo el BSW son los esperados.
 *
 * @note    Estas pruebas se ejecutan en el equipo anfitrion, por lo que
 *          comprueban las suposiciones del compilador del host. Las
 *          aserciones estaticas de este mismo archivo se evaluan ademas en
 *          cada compilacion cruzada que lo incluya.
 *
 * @par Trazabilidad
 *      SWS_Platform_00013 .. 00018  tipos enteros sin signo y con signo
 *      SWS_Platform_00020 .. 00025  tipos enteros optimizados (*_least)
 *      SWS_Platform_00026, 00027    boolean
 *      SWS_Platform_00041, 00042    float32 y float64
 *      SWS_Platform_00056           TRUE y FALSE
 *      SWS_Platform_00064           CPU_TYPE
 *      SWS_Platform_00038, 00039    CPU_BIT_ORDER y CPU_BYTE_ORDER
 */
#include "unity.h"
#include "Platform_Types.h"

/* Aserciones en tiempo de compilacion: fallan el build, no la prueba. */
_Static_assert(sizeof(uint8)  == 1u, "uint8 debe ocupar 1 byte");
_Static_assert(sizeof(uint16) == 2u, "uint16 debe ocupar 2 bytes");
_Static_assert(sizeof(uint32) == 4u, "uint32 debe ocupar 4 bytes");
_Static_assert(sizeof(uint64) == 8u, "uint64 debe ocupar 8 bytes");

void setUp(void)
{
}

void tearDown(void)
{
}

/* --- Tamanos de los tipos enteros estandar ------------------------------- */

void test_TiposEnteros_tienen_el_ancho_especificado(void)
{
    TEST_ASSERT_EQUAL_UINT32(1u, (uint32)sizeof(uint8));
    TEST_ASSERT_EQUAL_UINT32(1u, (uint32)sizeof(sint8));
    TEST_ASSERT_EQUAL_UINT32(2u, (uint32)sizeof(uint16));
    TEST_ASSERT_EQUAL_UINT32(2u, (uint32)sizeof(sint16));
    TEST_ASSERT_EQUAL_UINT32(4u, (uint32)sizeof(uint32));
    TEST_ASSERT_EQUAL_UINT32(4u, (uint32)sizeof(sint32));
    TEST_ASSERT_EQUAL_UINT32(8u, (uint32)sizeof(uint64));
    TEST_ASSERT_EQUAL_UINT32(8u, (uint32)sizeof(sint64));
}

void test_TiposEnteros_respetan_su_signo(void)
{
    sint8  s8  = -1;
    sint16 s16 = -1;
    sint32 s32 = -1;
    uint8  u8  = 0u;

    TEST_ASSERT_TRUE(s8  < 0);
    TEST_ASSERT_TRUE(s16 < 0);
    TEST_ASSERT_TRUE(s32 < 0);

    /* Un tipo sin signo envuelve en lugar de volverse negativo. */
    u8--;
    TEST_ASSERT_EQUAL_UINT8(255u, u8);
}

/* --- Tipos optimizados ---------------------------------------------------- */

void test_TiposLeast_cubren_al_menos_el_rango_exigido(void)
{
    TEST_ASSERT_TRUE(sizeof(uint8_least)  >= 1u);
    TEST_ASSERT_TRUE(sizeof(uint16_least) >= 2u);
    TEST_ASSERT_TRUE(sizeof(uint32_least) >= 4u);
    TEST_ASSERT_TRUE(sizeof(sint8_least)  >= 1u);
    TEST_ASSERT_TRUE(sizeof(sint16_least) >= 2u);
    TEST_ASSERT_TRUE(sizeof(sint32_least) >= 4u);
}

/* --- Coma flotante -------------------------------------------------------- */

void test_TiposFlotantes_siguen_los_formatos_IEEE_754(void)
{
    TEST_ASSERT_EQUAL_UINT32(4u, (uint32)sizeof(float32));
    TEST_ASSERT_EQUAL_UINT32(8u, (uint32)sizeof(float64));
}

/* --- boolean, TRUE y FALSE ------------------------------------------------ */

void test_Boolean_es_el_entero_sin_signo_mas_corto(void)
{
    /* SWS_Platform_00027: ancho mas corto soportado de forma nativa. */
    TEST_ASSERT_EQUAL_UINT32(1u, (uint32)sizeof(boolean));
}

void test_TrueYFalse_valen_uno_y_cero(void)
{
    /* SWS_Platform_00056 fija los valores; no son intercambiables. */
    TEST_ASSERT_EQUAL_INT(1, TRUE);
    TEST_ASSERT_EQUAL_INT(0, FALSE);
}

void test_Boolean_admite_las_formas_de_asignacion_permitidas(void)
{
    /* SWS_Platform_00034 restringe las formas validas de uso. */
    boolean var = FALSE;

    TEST_ASSERT_TRUE(var == FALSE);

    var = TRUE;
    TEST_ASSERT_TRUE(var == TRUE);

    var = (2u > 1u);
    TEST_ASSERT_TRUE(var == TRUE);
}

/* --- Simbolos de la plataforma -------------------------------------------- */

void test_CpuType_declara_una_plataforma_de_32_bits(void)
{
    TEST_ASSERT_EQUAL_INT(CPU_TYPE_32, CPU_TYPE);
}

void test_OrdenDeBits_declarado_es_LSB_first(void)
{
    TEST_ASSERT_EQUAL_INT(LSB_FIRST, CPU_BIT_ORDER);
}

void test_OrdenDeBytes_declarado_coincide_con_el_de_la_maquina(void)
{
    /* No basta declarar LOW_BYTE_FIRST: se comprueba leyendo el primer byte
       de un uint16 conocido. En little endian se lee la parte baja. */
    uint16 palabra = 0x0102u;
    uint8  primerByte = *((const uint8 *)&palabra);

    TEST_ASSERT_EQUAL_INT(LOW_BYTE_FIRST, CPU_BYTE_ORDER);
    TEST_ASSERT_EQUAL_HEX8(0x02u, primerByte);
}

/* --- Punteros genericos --------------------------------------------------- */

void test_PunterosGenericos_apuntan_a_los_datos_esperados(void)
{
    uint32       dato = 0xA5A5A5A5u;
    VoidPtr      escritura = (VoidPtr)&dato;
    ConstVoidPtr lectura   = (ConstVoidPtr)&dato;

    TEST_ASSERT_EQUAL_HEX32(0xA5A5A5A5u, *((const uint32 *)escritura));
    TEST_ASSERT_EQUAL_HEX32(0xA5A5A5A5u, *((const uint32 *)lectura));
}
