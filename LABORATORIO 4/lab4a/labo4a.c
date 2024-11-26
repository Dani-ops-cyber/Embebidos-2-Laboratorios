//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EJERCICIO 1 PARTE 2 LABORATORIO 4
// Parpadea el LED de usuario PN1 con interrupciones de temporizador en la Tiva. Inicialmente, haz que el LED parpadee 
// cada segundo, luego modifica el código para que parpadee cada 2 segundos y finalmente cambia el código para que 
// parpadee cada 5 segundos.

// LIBRERÍAS

#include <stdint.h>  // Proporciona tipos de datos enteros como uint32_t y uint8_t, útiles para variables de tamaño específico
#include <stdbool.h> // Permite el uso de tipos booleanos (true/false)
#include "inc/hw_memmap.h"  // Mapa de memoria de hardware, necesario para definir las direcciones de los periféricos
#include "driverlib/gpio.h"  // Librería para controlar los pines GPIO (puertos de entrada/salida)
#include "driverlib/sysctl.h"  // Librería para la configuración del sistema y reloj, permite definir la frecuencia de la CPU
#include "driverlib/timer.h"  // Control de temporizadores para generar interrupciones y manejar eventos basados en tiempo
#include "driverlib/interrupt.h"  // Permite el manejo y la habilitación de interrupciones
#include "inc/hw_ints.h"  // Define las interrupciones de hardware específicas de la Tiva

// VARIABLES GLOBALES

uint32_t time = 1;  // Tiempo en segundos para el temporizador, inicializado en 1 segundo
uint32_t FS = 120000000;  // Frecuencia del sistema (120 MHz), utilizada para calcular el tiempo en el temporizador

// PROTOTIPO DE LA FUNCIÓN DE INTERRUPCIÓN
void Timerlab4(void);  // Prototipo de la función que maneja las interrupciones del temporizador

// %%%%%%%%%%%%%%%%%%%%%%%% PROGRAMA PRINCIPAL %%%%%%%%%%%%%%%%%%%%%%%%
int main(void)
{
    // Configuración del reloj del sistema para que corra a 120 MHz.
    // Se utilizan un cristal externo de 25 MHz, el oscilador principal y el PLL (Phase Locked Loop)
    SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480, 120000000);
    
    // Habilitar el puerto GPIO N (donde está conectado el LED de usuario PN1)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    // Configuración del temporizador 0A en modo periódico (el temporizador se reinicia automáticamente después de cada ciclo)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);  // Habilita el temporizador 0
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);  // Configura el temporizador en modo periódico
    TimerLoadSet(TIMER0_BASE, TIMER_A, FS * time);  // Carga el valor de cuenta en el temporizador (frecuencia del sistema * tiempo deseado)

    // Habilitar las interrupciones a nivel de procesador
    IntMasterEnable();  // Habilita las interrupciones globales
    
    // Habilitar la interrupción del temporizador 0A
    IntEnable(INT_TIMER0A);  // Habilita la interrupción específica del temporizador 0A
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);  // Habilita la interrupción de "timeout" 
    
    // Iniciar el temporizador
    TimerEnable(TIMER0_BASE, TIMER_A);  // Habilita el temporizador 0A para que comience a contar

    // Verifica que el periférico GPIO N esté listo antes de usarlo
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {
    }

    // PN1 como salida 
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);

    // Bucle principal
    while (1) {
    }
}

// %%%%%%%%%%%%%%%%%%%%%%%% FUNCIÓN DE INTERRUPCIÓN %%%%%%%%%%%%%%%%%%%%%%%%
void Timerlab4(void)
{
    // Limpiar la interrupción del temporizador (esto es necesario para que el temporizador pueda generar futuras interrupciones)
    TimerIntClear(TIMER0_BASE, TIMER_A);
    
    // Alternar el estado del LED (encender/apagar)
    static bool led_state = false;  // Variable que guarda el estado del LED entre interrupciones
    
    // Si el LED está encendido, apágalo; si está apagado, enciéndelo
    if (led_state) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);  // Encender LED
    } else {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);  // Apagar LED
    }
    
    // Cambiar el estado para la próxima vez que ocurra la interrupción
    led_state = !led_state;
}

