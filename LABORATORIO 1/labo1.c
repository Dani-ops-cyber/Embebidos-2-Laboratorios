

//****************************LABORATORIO 1 PRUEBA DE FUNCIONAMIENTO TIVA

#include <stdint.h>           //DECLARACION DE VARIABLES ENTERAS DE 32 BITS enteros uint
#include <stdbool.h>          // Declaracion de variables booleanas igual de 32 bits
#include "inc/hw_memmap.h"    //Definicion de direccion de perifericos de la TIVA
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"  //controladores y timers de las salidas y entradas GPIO



/////////////////////////////////Codigo de error, si ocurre algo malo, detiene el programa /////////////////////////////////////
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////PROGRAMA PRINCIPAL/////////////////////////////////////////////////////////////////
int
main(void)
{
    //volatile uint32_t ui32Loop;

    // Habilitacion del periferico GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    
    // Verificar si el periferico esta habiltado
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    ///////////////////////////////////////////////////
    
    
    
    // Enable the GPIO pin for the LED (PN1).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    
    // Bucle infinito.
    while(1)
    {
        // Encendido de led de usuario
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        SysCtlDelay((120000000*0.1)/3); // 1 segundo de delay
        // Apagado del led
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
        SysCtlDelay((120000000*0.1)/3);  // 1 segundo de delay


    }
}
