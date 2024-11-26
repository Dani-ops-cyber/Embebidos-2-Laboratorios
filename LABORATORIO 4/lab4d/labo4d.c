//////                             EJERCICIO 4 LABORATORIO 4 //////

// 4.-Modifica el ejercicio del contador binario del laboratorio 3 para usar temporizadores. Cada secuencia debería cambiar 
//    sin necesidad de botones y con un intervalo de 1,5 segundos. Luego, añade una nueva funcionalidad: cuando se presione un 
//    botón, cambia el intervalo de tiempo a 3 segundos.

// LIBRERIAS
#include <stdint.h>  
#include <stdbool.h> 
#include "inc/hw_memmap.h"  
#include "driverlib/gpio.h"  
#include "driverlib/sysctl.h"  
#include "driverlib/timer.h"  
#include "driverlib/interrupt.h"  
#include "inc/hw_ints.h"  

uint32_t time = 2; // 2 segundos de pausa inicial
uint32_t FS = 120000000;  
uint8_t led_state = 0;
bool buttonPressed = false; // Variable para detectar el estado del botón

void Timerlab4(void);
void ButtonIntHandler(void);

int main(void)
{
    // Configurando el sistema del reloj para que corra a 120 MHz
    SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480, 120000000);
    
    // Habilita los puertos GPIO de los LEDs de usuario
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); // LED 1 y LED 2
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // LED 3 y LED 4
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); // Botón de usuario

    // Configura los pines de salida para los LEDs de usuario
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0); 
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); 
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4); 

    // Configura el pin GPIO para el botón de usuario en PJ0
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); // Habilita resistencia pull-up
    
    // Habilita la interrupción por GPIO para el botón
    GPIOIntRegister(GPIO_PORTJ_BASE, ButtonIntHandler);  // Asigna la función de interrupción
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);  // Configura la interrupción en el flanco de bajada
    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_0);  // Habilita la interrupción para el pin

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
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)) {}

    // Bucle principal
    while(1) {
        // El programa sigue ejecutándose normalmente
    }
}

// Función de interrupción del temporizador
void Timerlab4(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_A); // Limpia la interrupción del temporizador

    // Enciende o apaga los LEDs basados en led_state (contador binario)
    if (led_state & 0x01) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); // Enciende LED 1
    } else {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0); // Apaga LED 1
    }

    if (led_state & 0x02) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende LED 2
    } else {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0); // Apaga LED 2
    }

    if (led_state & 0x04) {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); // Enciende LED 3
    } else {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0); // Apaga LED 3
    }

    if (led_state & 0x08) {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende LED 4
    } else {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // Apaga LED 4
    }

    // Incrementa el estado de los LEDs
    led_state = (led_state + 1) % 16; // Vuelve a cero después de 15
}
// Función de interrupción para el botón
void ButtonIntHandler(void)
{
    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0); // Limpia la interrupción del botón
    
    // Alterna el tiempo entre 2 y 5 segundos
    if (time == 2) {
        time = 5;
    } else {
        time = 2;
    }

    // Actualiza el temporizador con el nuevo tiempo
    TimerLoadSet(TIMER0_BASE, TIMER_A, FS * time);
}

