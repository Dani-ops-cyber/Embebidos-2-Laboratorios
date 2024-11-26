
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EJERCICIO 2 PARTE 2%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Usando los 4 LEDs de usuario, genera una secuencia en bucle con un mínimo de 4 estados. Cada estado 
// debe estar activo durante 2 segundos antes de cambiar; usa SysCtlDelay. 


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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    
    // Verificar si el periférico está habilitado
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))  //VERIFICACION DE LOS PERIFERICOS HABILITADOS LED N
    {
    }    
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))  //VERIFICACION DE LOS PERIFERICOS HABILITADOS LED F
    {
    }  

    
    // Configuración de los pines PIN 1 LED como salida digital

    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);

    // Bucle infinito
    while(1) {
    
        // Encender el LED en PN1
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); //ACTIVAMOS LED 1
        SysCtlDelay((120000000 / 3)*0.2);  //DELAY DE 1 SEGUNDO
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);  //ACTIVAMOS LED 2
        SysCtlDelay((120000000 / 3)*0.2);  
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);  //ACTIVAMOS LED 3
        SysCtlDelay((120000000 / 3)*0.2);  
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);  //ACTIVAMOS LED 4
        SysCtlDelay((120000000 / 3)*0.2); 
        
        //APAGAMOS TODOS LOS LEDSITOS
        
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
        SysCtlDelay((120000000 / 3)*0.2); 
       
    }
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Sys
// utilizando la velocidad maxima de la tarjeta tiva, para la funcion de delay SysCtlDelay , 
//se divide entre 3 porque es la cantidad de veces en las que cumple un ciclo, este valor nos da un segundo de retardo , 
//sin embargo de forma empirirca vemos un funcionamiento mas eficiente al multiplicar por 0.1 para un segundo y 0.2 
//para dos segundos
