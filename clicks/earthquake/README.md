
---
# Earthquake Click

> [Earthquake Click](https://www.mikroe.com/?pid_product=MIKROE-2561) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2561&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> Intializes I2C module, LOG and GPIO structure, sets INT and PWM pins as 
> input and sets CS pin as output.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Earthquake

### Example Key Functions

- `earthquake_cfg_setup` Config Object Initialization function.
```c
void earthquake_cfg_setup ( earthquake_cfg_t *cfg ); 
```

- `earthquake_init` Initialization function.
```c
err_t earthquake_init ( earthquake_t *ctx, earthquake_cfg_t *cfg );
```

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
