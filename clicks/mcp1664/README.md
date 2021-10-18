\mainpage Main Page
 
---
# MCP1664 click

MCP1664 click contains 4 high-power white LEDs. It carries the MCP1664, a high-voltage step-up LED driver from Microchip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mcp1664_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mcp1664-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Mcp1664 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mcp1664 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mcp1664_cfg_setup ( mcp1664_cfg_t *cfg ); 
 
- Initialization function.
> MCP1664_RETVAL mcp1664_init ( mcp1664_t *ctx, mcp1664_cfg_t *cfg );

#### Example key functions :

- Start PWM module.
> void mcp1664_pwm_start ( mcp1664_t *ctx );
 
- Stop PWM module.
> void mcp1664_pwm_stop ( mcp1664_t *ctx );

## Examples Description

> This application turn on and turn off white LEDs.

**The demo application is composed of two sections :**

### Application Init 

> Enables GPIO and PWM, sets the frequency and duty cycle and enables PWM.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp1664_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp1664_cfg_setup( &cfg );
    MCP1664_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp1664_init( &mcp1664, &cfg );

    mcp1664_set_duty_cycle( &mcp1664, duty_cycle );
    mcp1664_pwm_start( &mcp1664 );
    Delay_ms( 1000 );
    log_printf( &logger, "------------------ \r\n" );
    log_printf( &logger, "  MCP1664  Click   \r\n" );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is a example which demonstrates the use of MCP1664 Click board.
> It shows how to enable the device and gradualy increase the duty cycle.

```c

void application_task ( void )
{
    //  Task implementation.
    
    if ( duty_cycle > mcp1664.pwm_period )
    {
        duty_cycle = 5000;
    }
    
    mcp1664_set_duty_cycle ( &mcp1664, duty_cycle );
    duty_cycle += 50;
    Delay_100ms();

    log_printf( &logger,  "  Duty cycle is : %d  \r\n", duty_cycle );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp1664

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
