\mainpage Main Page
 
 

---
# Earthquake Click

Earthquake Click carries D7S, the world’s smallest high-precision seismic sensor from Omron.

The Click is designed to run on either 3.3V or 5V power supply. It communicates with the target MCU over I2C interface, with additional functionality provided by the following pins on the mikroBUS™ line: PWM, INT, CS.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/earthquake_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/earthquake-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Earthquake Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Earthquake Click driver.

#### Standard key functions :

- `earthquake_cfg_setup` Config Object Initialization function.
```c
void earthquake_cfg_setup ( earthquake_cfg_t *cfg ); 
```

- `earthquake_init` Initialization function.
```c
EARTHQUAKE_RETVAL earthquake_init ( earthquake_t *ctx, earthquake_cfg_t *cfg );
```

#### Example key functions :

- `earthquake_proc_notify` Shutoff output function.
```c
uint8_t earthquake_proc_notify ( earthquake_t *ctx );
```

- `earthquake_read_status` Read status function.
```c
uint8_t earthquake_read_status ( earthquake_t *ctx );
```

- `earthquake_read_si` Read SI function.
```c
uint16_t earthquake_read_si ( earthquake_t *ctx );
```

## Examples Description

> 
> Intializes I2C module, LOG and GPIO structure, sets INT and PWM pins as 
> input and sets CS pin as output.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Intializes of I2C driver and makes initial log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    earthquake_cfg_t cfg;

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
    earthquake_cfg_setup( &cfg );
    EARTHQUAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    earthquake_init( &earthquake, &cfg );
    Delay_ms ( 1000 );
    display_status( earthquake_read_status( &earthquake ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    earthquake_clear_memory( &earthquake );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "    Earthquake Click    \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
  
```

### Application Task

>
> This is an example that shows most of the functions that Earthquake Click
> has. Results are being sent to the Usart Terminal where you can track their 
> changes.
> 

```c

void application_task ( void )
{
    if ( earthquake_proc_notify( &earthquake ) )
    {
        log_printf( &logger, "  Earthquake detected!  \r\n" );
        log_printf( &logger, "------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );

        for ( cnt = 20; cnt > 0; cnt-- )
        {
            log_printf( &logger, " Status : " );
            display_status( earthquake_read_status( &earthquake ) );

            read_data = earthquake_read_si( &earthquake );
            log_printf( &logger, " Max SI : %d\r\n", read_data );
            log_printf( &logger, "------------------------ \r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }

        earthquake_clear_memory( &earthquake );
        log_printf( &logger, " Afterquake  processing \r\n" );
        log_printf( &logger, "     please wait...     \r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );

        log_printf( &logger, "------------------------\r\n" );
        log_printf( &logger, " Waiting for a quake... \r\n" );
        log_printf( &logger, "------------------------\r\n" );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Earthquake

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
