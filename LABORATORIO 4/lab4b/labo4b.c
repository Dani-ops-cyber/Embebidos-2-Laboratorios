///////////////////////////////////////////EJERCICIO 2 SEGUNDA PARTE LABORATORIO 4%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//     Haz una secuencia decimal con los LEDs de usuario que cambie cada 2 segundos.
// LIBRERIAS
#include <stdint.h>  // datos enteros como uint32_t y uint8_t
#include <stdbool.h> // uso de tipos booleanos (true/false)
#include "inc/hw_memmap.h"  // efinir las direcciones de los periféricos
#include "driverlib/gpio.h"  // controlar los pines GPIO 
#include "driverlib/sysctl.h"  // configuración del sistema y reloj, permite definir la FRECUENCIA de la CPU
#include "driverlib/timer.h"  // Control de temporizadores para generar interrupciones y manejar eventos basados en tiempo
#include "driverlib/interrupt.h"  // Habilitación de interrupciones
#include "inc/hw_ints.h"  // Define interrupciones de hardware específicas de la Tiva

uint32_t time = 2; // 2 seconds pause
uint32_t FS = 120000000;  
uint8_t led_state = 0;

void Timerlab4(void);

// PARA LOS ERRORES
#ifdef DEBUG
void
error(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

// PROGRAMA PRINCIPAL
int main(void)
{
    // Configurando el sistema del reloj para que corra a 120 MHz
    SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480, 120000000);
    
    // Habilita los puertos GPIO de los LEDs de usuario
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); // LED 1 y LED 2
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // LED 3 y LED 4
    
    // Configura Timer 0A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    
    TimerLoadSet(TIMER0_BASE, TIMER_A, FS * time); // Establece el tiempo de 2 segundos
    
    IntMasterEnable();  // Habilita interrupciones del procesador
    
    IntEnable(INT_TIMER0A);  // Habilita la interrupción del temporizador
    
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    
    TimerEnable(TIMER0_BASE, TIMER_A);  // Activa el temporizador

    // Verifica si los periféricos están habilitados
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}

    // Configura los pines de salida para los LEDs de usuario
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0); // LEDs
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); 
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4); 
    
    
    //BUVLE PRINCIPAL
    while(1) {
    }
}

// Función de interrupción del temporizador

void Timerlab4(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_A); // Limpia la interrupción del temporizador

    // Enciende el LED basado en led_state
    switch (led_state) {
        case 0:
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); // Enciende LED 1
            break;
        case 1:
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); // Mantiene LED 1 encendido
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende LED 2
            break;
        case 2:
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); // Mantiene LED 1 encendido
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // Mantiene LED 2 encendido
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); // Enciende LED 3
            break;
        case 3:
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); // Mantiene LED 1 encendido
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // Mantiene LED 2 encendido
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // Mantiene LED 3 encendido
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); // Enciende LED 4
            break;
        case 4:
            // Apaga todos los LEDs y reinicia la secuencia
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0);
            break;
        default:
            break;
    }

    // Incrementa el estado de los LEDs
    led_state = (led_state + 1) % 5; // Vuelve a cero después de 4
}



