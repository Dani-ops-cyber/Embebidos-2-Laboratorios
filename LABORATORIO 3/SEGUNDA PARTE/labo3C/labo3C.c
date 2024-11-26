
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EJERCICIO 2 PARTE 3%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Usando los 4 LEDs de usuario y los 2 interruptores de usuario integrados en Tiva, desarrolla un contador 
// binario con todos los valores mostrados en la tabla 1, siguiendo las siguientes características:

//- Cuando se presiona el interruptor 1, el contador binario aumenta.
//- Cuando se presiona el interruptor 2, el contador binario disminuye.
//- Los 4 LEDs de usuario representan los valores binarios.
//- Cuando el contador alcanza el valor 15, no debe seguir aumentando.
//- Cuando el contador llega al valor 0, no debe seguir disminuyendo.
//- Almacena el valor decimal en una variable entera llamada "counter".


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
// %%%%%%%%%%%%%%%%%%%%%%%% FUNCION PARA NUESTRO DELAY %%%%%

void delay(uint32_t s){
SysCtlDelay((120000000/3)*s);
}
// %%%%%%%%%%%%%%%%%%%%%%%% FUNCION PARA EVITAR REBOTE %%%%%

void debounce() {
SysCtlDelay(200000); // 0.05 segundos
}


#ifdef DEBUG
void
error(char *pcFilename, uint32_t ui32Line)
{
while(1);
}
#endif


int main(void)
{
// Configure system clock to run at 120 MHz

SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
SYSCTL_CFG_VCO_480, 120000000);
// Enable GPIO port F,N and J
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
// Verifica si el peroférico está habilitado
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
{
}
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
{
}
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
{
}

//
// Enable the GPIO pin for the LED (PN0). Set the direction as output, and
// enable the GPIO pin for digital function.
//
GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);

//pARA LOS DOS BOTONES
GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_1);
GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

//Iniciamos el contador 
int cont = 0;
bool button_j0_last_state = true;
bool button_j1_last_state = true;
while(1){
bool button_j0_state = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0; //lectura de boton

// Si el estado del botón J0 ha cambiado
if (button_j0_state != button_j0_last_state) {

SysCtlDelay(200000); 

// Leer el estado del botón J0 
bool button_j0_state_debounced = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0;

// Si el estado del botón J0 sigue siendo bajo, aumenta el contadorsito
if (button_j0_state_debounced) {
cont++;
}
// Actualizar el último estado del botón J0
button_j0_last_state = button_j0_state;
}
// Realizar el mismo procedimiento para el botón J1
bool button_j1_state = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == 0;
if (button_j1_state != button_j1_last_state) {
debounce();
bool button_j1_state_debounced = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == 0;
if (button_j1_state_debounced) {
cont--;
}
button_j1_last_state = button_j1_state;
}
// Restricción para asegurar que cont esté dentro de ciertos límites
if (cont < 0) {
cont = 0;
} else if (cont > 15) {
cont = 15;
}
if(cont==0){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0X00);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);
}
else if(cont==1){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}

else if(cont==2){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0X00);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
}
else if(cont==3){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0X00);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}
else if(cont==4){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00);

GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);
}
else if(cont==5){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);

GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}
else if(cont==6){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);

GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0X0);
}
else if(cont==7){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);

GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}
else if(cont==8){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
}

else if(cont==9){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}
else if(cont==10){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
}
else if(cont==11){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}
else if(cont==12){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
}
else if(cont==13){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}
else if(cont==14){
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
}
else {
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);

}

}
}


