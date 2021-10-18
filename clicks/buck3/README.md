\mainpage Main Page
  
---
# Buck 3 click

Buck 3 click is a very advanced synchronous step-down (buck) converter, which is designed to deliver noise and ripple-free voltage to highly sensitive applications, such as FPGA and high-performance DSP platforms.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-3-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Buck3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck3_cfg_setup ( buck3_cfg_t *cfg ); 
 
- Initialization function.
> BUCK3_RETVAL buck3_init ( buck3_t *ctx, buck3_cfg_t *cfg );

- Click Default Configuration function.
> void buck3_default_cfg ( buck3_t *ctx );


#### Example key functions :

- Function for setting device mode
> void buck3_set_device_state ( buck3_t *ctx, uint8_t state );
 
- Function reads state of PGD pin
> uint8_t buck3_get_power_good ( buck3_t *ctx );

## Examples Description

> This example demonstrates the use of Buck 3 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck3_cfg_t cfg;

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

    buck3_cfg_setup( &cfg );
    BUCK3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck3_init( &buck3, &cfg );

    buck3_default_cfg( &buck3 );
    log_info( &logger, "---- Buck 3 is activated ----" );
	Delay_1sec( );
}
```

### Application Task

> Checks the PGD pin state which signalize the undervoltage or overvoltage fault or
> the thermal shutdown condition. 
> If there's any of the above faults detected it logs a desired message on USB UART.

```c
void application_task ( void )
{
    uint8_t pg_state;

    //  Task implementation.
    
    pg_state = buck3_get_power_good( &buck3 );
	
    if ( pg_state == 0 )
    {
        log_info
        ( 
            &logger, 
            "---- Overvoltage or thermal shutdown detected ----" 
        );
    }
	Delay_1sec( );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck3

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
