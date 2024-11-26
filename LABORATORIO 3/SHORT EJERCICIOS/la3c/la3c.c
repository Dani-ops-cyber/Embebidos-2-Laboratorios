
//Ejemplo 3: 
//Escribe un código que encienda el LED de usuario PN1 si el interruptor de usuario PJ1 está presionado.


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
///////////////////////////////////////////////////////////////////////////////////////

//FUNCION PRINCIPAL///////////////////////////////////////////////

int main(void) {
    // Habilitación del periférico GPIO para los LEDs en el puerto N
    // Enable GPIO port N, F and J
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); //hBILITACION DE LOS PUERTOS GPIO N
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);  //HABILITACION DE LOS PUERTOS GPIO J BOTON SIRVE PARA LOS DOS BOTONES
    
    // Verificar si el periférico está habilitado
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))  //VERIFICACION DE LOS PERIFERICOS HABILITADOS LED
    {
    }    
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))   //VERIFICACION DE LOS PERIFERICOS HABILITADOS BOTON  ///sIRMPRE
    {
    }
    
    // Configuración de los pines PIN 1 LED como salida digital

    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1); // PN1 como salida

    //// Configuración de los pines DEL BOTON COMO ENTRADA Y CONFIGURACION PULL UP
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    // Bucle infinito
    while(1) {
    
    if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0) {
        // Encender el LED en PN1
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
     }else{
     GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
     }
     
    }
}

