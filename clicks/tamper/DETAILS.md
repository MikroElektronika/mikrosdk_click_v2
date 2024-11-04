
---
# Tamper Click

Tamper Click is equipped with SDS001, a low profile side-actuated detect switch, made by C&K company. This is a high-quality, low-current detection switch, which is designed in a form of a push button. The switch itself is very small - only 2mm of switch overtravel length, which coupled with its low actuation force, makes it ideal for using it as a contact detector in various applications - consumer electronics devices, medical devices, smart card detection and similar applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tamper_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/tamper-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Tamper Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Tamper Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void tamper_cfg_setup ( tamper_cfg_t *cfg ); 
 
- Initialization function.
> TAMPER_RETVAL tamper_init ( tamper_t *ctx, tamper_cfg_t *cfg );


#### Example key functions :

- Function showes the state of the switch.
> uint8_t tamper_state ( tamper_t *ctx );

## Examples Description

> Tamper Click is equipped with side-actuated detect switch. The switch itself acts as 
> a push button and has 2 Normally Open terminals, which get shorted when the force is applied. 
> The applied pressure closes the circuit, connecting the VCC routed to the first pin 
> of the switch with the INT pin on the mikroBUS. The microcontroller is then able to detect 
> a high logical level on the INT pin and the desired task can then be executed.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO and also starts write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    tamper_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    tamper_cfg_setup( &cfg );
    TAMPER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tamper_init( &tamper, &cfg );
}
  
```

### Application Task

> This is an example which demonstrates the use of Tamper Click board.
> It detects whether the state of switch on Tamper Click is changes to open or to closed.
> Results are being sent to the Usart Terminal where you can keep track of their changes.

```c

void application_task ( void )
{
    switch_state = tamper_state( &tamper );
    
    if ( switch_state == 1 && switch_state_old == 0 )
    {
        log_printf( &logger, "      Closed     \r\n" );
        log_printf( &logger, "- - - - - - - - -\r\n" );
        switch_state_old = 1;
    }

    if ( switch_state == 0 && switch_state_old == 1 )
    {
        log_printf( &logger, "       Open      \r\n" );
        log_printf( &logger, "- - - - - - - - -\r\n" );
        switch_state_old = 0;
    }
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Tamper

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
