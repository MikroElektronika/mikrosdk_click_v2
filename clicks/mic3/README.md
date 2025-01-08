
---
# MIC 3 Click

> [MIC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4136) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4136&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This is an example that demonstrates the use of the MIC 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MIC3

### Example Key Functions

- `mic3_cfg_setup` Config Object Initialization function.
```c
void mic3_cfg_setup ( mic3_cfg_t *cfg );
```

- `mic3_init` Initialization function.
```c
err_t mic3_init ( mic3_t *ctx, mic3_cfg_t *cfg );
```

- `mic3_default_cfg` Click Default Configuration function.
```c
err_t mic3_default_cfg ( mic3_t *ctx );
```

- `mic3_shd_pin_set` MIC 3 SHD pin setting function.
```c
void mic3_shd_pin_set ( mic3_t *ctx, uint8_t state ); 
```

### Application Init

> Initialization of SHD to output and log module, maping GPIO for Mikrobus1, and seting SHD pin to HIGH state.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mic3_cfg_t mic3_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    mic3_cfg_setup( &mic3_cfg );
    MIC3_MAP_MIKROBUS( mic3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == mic3_init( &mic3, &mic3_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    mic3_default_cfg ( &mic3 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Turning microphone on for the 5 seconds, then turning it off for 5 seconds.

```c
void application_task ( void ) 
{
    log_printf( &logger, " - Microphone is turned on  - \r\n" );
    mic3_shd_pin_set( &mic3, MIC3_PIN_STATE_HIGH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " - Microphone is turned off  - \r\n" );
    mic3_shd_pin_set( &mic3, MIC3_PIN_STATE_LOW );
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
