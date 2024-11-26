//Ejemplo 1: 
//Escribe un código que encienda el LED PN0, espere 1 segundo y encienda el LED PN1, luego apague ambos LEDs.


#include <stdint.h>           // Declaración de variables enteras de 32 bits uint
#include <stdbool.h>          // Declaración de variables booleanas de 32 bits
#include "inc/hw_memmap.h"    // Definición de direcciones de periféricos de la TIVA
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"  // Controladores y timers de las salidas y entradas GPIO

// Código de error, si ocurre algo malo, detiene el programa
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
    while(1);
}
#endif

int main(void) {
    // Habilitación del periférico GPIO para los LEDs en el puerto N
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    
    // Verificar si el periférico está habilitado
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {
    }
    
    // Configuración de los pines PN0 y PN1 como salida digital
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0); // PN0 como salida
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1); // PN1 como salida
    
    // Bucle infinito
    while(1) {
        // Encender el LED 
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        
        // Esperar 1 segundo
        SysCtlDelay((120000000 / 3)*0.1);  // Delay de 1 segundo 
        
        // Encender el LED en PN1 (sin apagar PN0)
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        
        // Esperar 1 segundo
        SysCtlDelay((120000000 / 3)*0.1);  // Delay de 1 segundo
        
        // Apagar ambos LEDs
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
        
        // Esperar 1 segundo antes de repetir
        SysCtlDelay((120000000 / 3)*0.1);  // Delay de 1 segundo
    }
}

