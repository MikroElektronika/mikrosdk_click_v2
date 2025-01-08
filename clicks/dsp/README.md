
---
# DSP Click

> [DSP Click](https://www.mikroe.com/?pid_product=MIKROE-4431) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4431&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application controls reverb and multi-effects Digital Multi-Effects DSP 
> provides different sound performance of the DSP Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dsp

### Example Key Functions

> Config Object Initialization function.
```c
void dsp_cfg_setup ( dsp_cfg_t *cfg );
```

> Initialization function.
```c
err_t dsp_init ( dsp_t *ctx, dsp_cfg_t *cfg );
```

> Click Default Configuration function.
```c
void dsp_default_cfg ( dsp_t *ctx );
```

> DSP reverb and multi-effects setting function.
```c
dsp_retval_t dsp_set_effect ( dsp_t *ctx, uint8_t effects );
```

> DSP power on the device function.
```c
void dsp_power_on ( dsp_t *ctx );
```

> DSP reset the device function.
```c
void dsp_reset ( dsp_t *ctx );
```

### Application Init

> Initializes GPIO driver, set the default configuration and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dsp_cfg_t dsp_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dsp_cfg_setup( &dsp_cfg );
    DSP_MAP_MIKROBUS( dsp_cfg, MIKROBUS_1 );
    if ( dsp_init( &dsp, &dsp_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dsp_default_cfg ( &dsp );   
    log_info( &logger, " Application Task \r\n" );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "           DSP Click           \r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "     Digital Multi-Effects     \r\n" );
}
```

### Application Task

> This is an example that shows the use of a DSP Click board.
> In this example, we change different sound effects
> such as multiple reverbs, echo, phaser, chorus, flanger, etc. every 10 sec.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "-------------------------------\r\n" );
    dsp_set_effect( &dsp, effects );
    display_effects( );
    
    effects++;
    if ( effects > DSP_SET_EFFECT_DELAY1 ) {
        effects = DSP_SET_EFFECT_MEDIUM;
    }

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
