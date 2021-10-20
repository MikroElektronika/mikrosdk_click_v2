
---
# H-Bridge 7 click

H-Bridge 7 Click features flexible motor driver IC for a wide variety of applications, labeled as the DRV8876N. This Click board™ integrates an N-channel H-bridge, charge pump regulator, and protection circuitry. The charge pump improves efficiency by allowing for both high-side and low-side N-channels MOSFETs and 100% duty cycle support. This IC allows the H-Bridge 7 Click to achieve ultra-low quiescent current draw by shutting down most of the internal circuitry with his low-power sleep mode.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Hbridge7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Hbridge7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hbridge7_cfg_setup ( hbridge7_cfg_t *cfg ); 
 
- Initialization function.
> HBRIDGE7_RETVAL hbridge7_init ( hbridge7_t *ctx, hbridge7_cfg_t *cfg );


#### Example key functions :
 
- Set motor control.
> void hbridge7_motor_control ( hbridge7_t *ctx, uint8_t ctrl );

- Get Fault pin state.
> uint8_t hbridge7_get_fault_state ( hbridge7_t *ctx );

## Examples Description

> This example demonstrates the use of H-Bridge 7 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge7_cfg_t cfg;

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

    hbridge7_cfg_setup( &cfg );
    HBRIDGE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge7_init( &hbridge7, &cfg );
}
  
```

### Application Task

> Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
> and after that drives it in the reverse direction for 5 seconds, and finally, 
> disconnects the motor for 2 seconds. Each step will be logged on the USB UART where
> you can track the program flow.

```c

void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_FORWARD );
    Delay_ms( 5000 );
    
    log_printf( &logger, "Pull brake! \r\n" );
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_BRAKE );
    Delay_ms( 2000 );

    log_printf( &logger, "The motor turns in reverse! \r\n" );
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_REVERSE );
    Delay_ms( 5000 );

    log_printf( &logger, "The motor is disconnected (High-Z)!  \r\n" );
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_SLEEP );
    Delay_ms( 2000 );
}   

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Hbridge7

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
