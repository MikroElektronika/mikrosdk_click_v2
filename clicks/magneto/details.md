

---
# MAGNETO click

MAGNETO Click carries contactless magnetic angle position sensor which delivers precise angle measurements down to 0.05º in 14-bit resolution.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Magneto Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Magneto Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void magneto_cfg_setup ( magneto_cfg_t *cfg ); 
 
- Initialization function.
> MAGNETO_RETVAL magneto_init ( magneto_t *ctx, magneto_cfg_t *cfg );

- Click Default Configuration function.
> void magneto_default_cfg ( magneto_t *ctx );

#### Example key functions :

- This function read and returns the value of the state register.
> uint16_t magneto_get_state ( magneto_t *ctx );
 
- This function read the 16-bit data from register then calculate and convert to float angle value from 0deg to 360deg.
> float magneto_calculate_angle ( magneto_t *ctx );

## Examples Description

> 
> Example presents precise angle measurements down to 0.05º in 14-bit resolution.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    magneto_cfg_setup( &cfg );
    MAGNETO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto_init( &magneto, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----- MAGNETO Click ---- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    if ( magneto_get_state( &magneto ) != 1 )
    {
        log_printf( &logger, " -- Initialization done --\r\n" );
    }
    else
    {
        log_printf( &logger, " -------- ERROR ! --------\r\n" );
    }

    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> Magneto Click communicates with register via SPI by write and read from register and calculate float angle value. 
> Results are being sent to the UART Terminal where you can track their changes. 
> All data logs on USB UART for aproximetly every 2 sec.
> 

```c

void application_task ( void )
{
    angle_value = magneto_calculate_angle( &magneto );
    log_printf( &logger, "  [ANGLE] : %0.3f \r\n", angle_value );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto

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
