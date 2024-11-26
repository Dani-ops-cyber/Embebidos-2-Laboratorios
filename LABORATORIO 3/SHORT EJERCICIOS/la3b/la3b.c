//Ejemplo 2: 
//Escribe un código para encender los LEDs PN0 y PF0, luego encender los LEDs PN1 y PF4, 
//y luego apagar los LEDs en la misma secuencia.

////////////LIBRERIAS////////////////////////////////////////////////////////////

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
////////////////////////////////////FUNCION PRINCIPAL/////////////////////////////////////////////////////
int main(void) {
    // Habilitación del periférico GPIO para los LEDs en el puerto N
    // Enable GPIO port N, F and J
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    
    // Verificar si el periférico está habilitado
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) 
    {
    }
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
    // Configuración de los pines como salida digital N + F
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0); 
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1); 
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    
    // Bucle infinito
    while(1) {
        // Encender el LED en PN0
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        
        // Esperar 1 segundo
        SysCtlDelay((120000000 / 3)*0.1);  // Delay de 1 segundo 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
        
        
        // Esperar 1 segundo
        SysCtlDelay((120000000 / 3)*0.1);  // Delay de 1 segundo
        
        // Apagar ambos LEDs
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
        
        SysCtlDelay((120000000 / 3)*0.1);  // Delay de 1 segundo
        
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
        
        // Esperar 1 segundo antes de repetir
        SysCtlDelay((120000000 / 3)*0.1);  // Delay de 1 segundo
    }
}

