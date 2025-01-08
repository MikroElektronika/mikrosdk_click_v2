
---
# Speed Sense Click

> [Speed Sense Click](https://www.mikroe.com/?pid_product=MIKROE-5977) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5977&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains the API for the Speed Sense Click driver 
> for the speed and direction signal state detection for every magnetic pole pair.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SpeedSense

### Example Key Functions

- `speedsense_cfg_setup` Config Object Initialization function.
```c
void speedsense_cfg_setup ( speedsense_cfg_t *cfg );
```

- `speedsense_init` Initialization function.
```c
err_t speedsense_init ( speedsense_t *ctx, speedsense_cfg_t *cfg );
```

- `speedsense_get_speed` This function reads the state of the CHA pin used for speed output protocols.
```c
uint8_t speedsense_get_speed ( speedsense_t *ctx );
```

- `speedsense_get_direction` This function reads the state of the CHB pin used for direction output protocols.
```c
uint8_t speedsense_get_direction ( speedsense_t *ctx );
```

### Application Init

> Initialization of GPIO and log UART.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speedsense_cfg_t speedsense_cfg;  /**< Click config object. */

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
    speedsense_cfg_setup( &speedsense_cfg );
    SPEEDSENSE_MAP_MIKROBUS( speedsense_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == speedsense_init( &speedsense, &speedsense_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the Speed Sense Click board. 
> The demo application displays the direction of movement and rotation speed (rotations per minute) 
> of the ring magnet with three pairs of rotating poles positioned in the sensor operating range.

```c
void application_task ( void ) 
{
    uint8_t direction = 0, speed = 0;
    speed = speedsense_get_speed( &speedsense );
    direction = speedsense_get_direction( &speedsense );

    if ( start_measure & speed )
    {
        signal_duration = time_cnt - start_timer;
        start_timer = time_cnt;
        
        if ( SPEEDSENSE_DIR_STATE_FWD == direction )
        {
            log_printf( &logger, " Direction: Forward\r\n" );
        }
        else
        {
            log_printf( &logger, " Direction: Reverse\r\n" );
        }
        log_printf( &logger, " Speed: %.2f rpm\r\n", SPEEDSENSE_CALC_RMP / signal_duration );
        log_printf( &logger, " Duration: %lu ms\r\n", signal_duration );
        log_printf( &logger, " Time: %lu  ms\r\n", time_cnt );
        log_printf( &logger, "-----------------------\r\n" );
        start_measure = SPEEDSENSE_STOP_MEASURE;
    }
    else if ( ( !start_measure ) & ( !speed ) )
    {
        start_measure = SPEEDSENSE_START_NEW_MEASURE;
    }

    time_cnt++;
    Delay_ms ( 1 );
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
