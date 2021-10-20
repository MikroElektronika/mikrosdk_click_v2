\mainpage Main Page
 
---
# DC Motor 6 click

DC Motor 6 Click is a PWM chopper type brushed DC motor driver, labeled as TB67H451FNG.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor6_click.png">
</p>

[click Product page](https://www.mikroe.com/dc-motor-6-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Dcmotor6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dcmotor6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor6_cfg_setup ( dcmotor6_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR6_RETVAL dcmotor6_init ( dcmotor6_t *ctx, dcmotor6_cfg_t *cfg );

#### Example key functions :

- Set IN1 pin.
> void dcmotor6_set_in1_pin ( dcmotor6_t *ctx, uint8_t state );
 
- Set IN1 pin.
> void dcmotor6_set_in2_pin ( dcmotor6_t *ctx, uint8_t state );

- Set motor Direction.
> void dcmotor6_set_direction( dcmotor6_t *ctx, uint8_t dir );

## Examples Description

> This example demonstrates the use of DC Motor 6 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor6_cfg_t cfg;

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

    dcmotor6_cfg_setup( &cfg );
    DCMOTOR6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor6_init( &dcmotor6, &cfg );
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
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_FORWARD );
    Delay_ms( 5000 );
    log_printf( &logger, "Pull brake! \r\n" );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_BRAKE );
    Delay_ms( 2000 );
    log_printf( &logger, "The motor turns in reverse! \r\n" );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_REVERSE );
    Delay_ms( 5000 );
    log_printf( &logger, "The motor is disconnected (High-Z)! \r\n" );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_STOP );
    Delay_ms( 2000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dcmotor6

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
