# Makefile maestro del proyecto. Targets disponibles:
# - make / make all - Construye el proyecto (genera build/main.elf, .hex, .lst, .map)
# - make clean      - Elimina la carpeta build con todos los binarios generados
# - make flash      - Carga/flashea el programa a la tarjeta (Nucleo-F446RE via OpenOCD)
# - make open       - Abre una conexion SWD con la placa (servidor GDB)
# - make debug      - Inicia una sesion de debug con arm-none-eabi-gdb (requiere make open antes)
# - make test       - Ejecuta ceedling para unit testing con code coverage (reporte HTML)
# - make lint       - Analisis estatico del codigo con cppcheck
# - make misra      - Verifica el codigo contra las reglas MISRA C 2012 (addon de cppcheck)

# Nombre del proyecto
TARGET = main
# Unidades de compilacion del proyecto
SRCS  = main.c startup_stm32f446xx.s

# linker file
LINKER = linker.ld

# directorios con los archivos fuente a compilar (.c y .s)
SRC_PATHS  = app
SRC_PATHS += .

# directorios con archivos header (.h)
INC_PATHS  = app

# -------------------------------------------------------------------------------------------------
# Configuracion del toolchain y reglas de construccion
# -------------------------------------------------------------------------------------------------
TOOLCHAIN = arm-none-eabi
CPU = -mcpu=cortex-m4 -mthumb -mfloat-abi=soft

# banderas para el compilador
CFLAGS  = $(CPU)
CFLAGS += -O0                        # Compila sin optimizacion (O0, O1, O2, O3, Os)
CFLAGS += -g3                        # Nivel de informacion de debug (g1, g2, g3)
CFLAGS += -ffunction-sections        # Crea una seccion separada por funcion
CFLAGS += -fdata-sections            # Crea una seccion separada por dato
CFLAGS += -fno-builtin               # No reconoce funciones built-in sin el prefijo '__builtin_'
CFLAGS += -std=c11                   # Compila con C11
CFLAGS += -Wall                      # Habilita los warnings
CFLAGS += -pedantic                  # Comprobaciones ANSI estrictas
CFLAGS += -Wstrict-prototypes        # Advierte si una funcion se declara sin tipos de argumentos
CFLAGS += -fsigned-char              # char es tratado como signed
CFLAGS += -fdiagnostics-color=always # Salida de terminal con color
CFLAGS += -fomit-frame-pointer       # No mantiene el frame pointer en funciones que no lo necesitan
CFLAGS += -fverbose-asm              # Comentarios adicionales en el ensamblador generado
CFLAGS += -MMD -MP

# Banderas del ensamblador
AFLAGS = $(CPU)

# Banderas del linker
LFLAGS  = $(CPU)
LFLAGS += -Wl,--gc-sections
LFLAGS += --specs=rdimon.specs          # linkeo con semihosting
LFLAGS += --specs=nano.specs            # version nano de stdlib
LFLAGS += -Wl,-Map=build/$(TARGET).map  # Genera un map file

# banderas para cppcheck
LNFLAGS  = --inline-suppr           # comentarios para suprimir warnings del lint
LNFLAGS += --quiet                  # Muestra solo informacion util
LNFLAGS += --std=c11                # hace las comprobaciones contra C11
LNFLAGS += --template=gcc           # Muestra advertencias en estilo gcc
LNFLAGS += --force                  # Evalua todas las sentencias #if
LNFLAGS += --platform=unix32        # Revisa contra una plataforma unix32
LNFLAGS += --error-exitcode=1       # retorna error si hay algun hallazgo
LNFLAGS += --cppcheck-build-dir=build/lint

# sustitucion de prefijos
OBJS = $(SRCS:%.c=build/obj/%.o)
OBJS := $(OBJS:%.s=build/obj/%.o)
DEPS = $(OBJS:%.o=%.d)

# Establece variables de directorios de source y header
VPATH = $(SRC_PATHS)
INCLS = $(addprefix -I ,$(INC_PATHS))

#---Construir proyecto----------------------------------------------------------------------------
all : build $(TARGET)

$(TARGET) : $(addprefix build/, $(TARGET).elf)
	$(TOOLCHAIN)-objcopy -Oihex $< build/$(TARGET).hex
	$(TOOLCHAIN)-objdump -S $< > build/$(TARGET).lst
	$(TOOLCHAIN)-size --format=berkeley $<

build/$(TARGET).elf : $(OBJS)
	$(TOOLCHAIN)-gcc $(LFLAGS) -T $(LINKER) -o $@ $^

build/obj/%.o : %.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLS) $(SYMBOLS) -o $@ -c $<

build/obj/%.o : %.s
	$(TOOLCHAIN)-as $(AFLAGS) -o $@ -c $<

-include $(DEPS)

.PHONY : build clean flash open debug test lint misra

#---Crea el directorio para los binarios generados-------------------------------------------------
build :
	mkdir -p build/obj build/lint

#---Borra la carpeta con los binarios generados----------------------------------------------------
clean :
	rm -rf build

#---Flashea la imagen al microcontrolador----------------------------------------------------------
flash :
	openocd -f board/st_nucleo_f4.cfg -c "program build/$(TARGET).hex verify reset" -c shutdown

#---Abre una conexion de debug (servidor GDB)------------------------------------------------------
open :
	openocd -f board/st_nucleo_f4.cfg

#---Sesion de debug por GDB; requiere el servidor OpenOCD levantado con make open-----------------
debug :
	$(TOOLCHAIN)-gdb build/$(TARGET).elf -iex "set auto-load safe-path /"

#---Ejecuta unit testing con code coverage usando ceedling-----------------------------------------
test :
	ceedling clobber gcov:all

#---Analisis estatico con cppcheck-----------------------------------------------------------------
lint : build
	cppcheck $(LNFLAGS) --enable=warning,style app/

#---Verificacion de reglas MISRA C 2012 con el addon de cppcheck-----------------------------------
misra : build
	cppcheck $(LNFLAGS) --addon=misra app/
