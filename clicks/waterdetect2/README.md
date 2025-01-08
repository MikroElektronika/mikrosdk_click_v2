
---
# Water Detect 2 Click

> [Water Detect 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5820) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5820&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains API for Water Detect 2 Click driver.
> Water Detect 2 Click is used for detecting water and other electroconductive liquids.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WaterDetect2

### Example Key Functions

- `waterdetect2_cfg_setup` Config Object Initialization function.
```c
void waterdetect2_cfg_setup ( waterdetect2_cfg_t *cfg );
```

- `waterdetect2_init` Initialization function.
```c
err_t waterdetect2_init ( waterdetect2_t *ctx, waterdetect2_cfg_t *cfg );
```

- `waterdetect2_default_cfg` Click Default Configuration function.
```c
void waterdetect2_default_cfg ( waterdetect2_t *ctx );
```

- `waterdetect2_get_fluid_status` Water Detect 2 get fluid status function.
```c
uint8_t waterdetect2_get_fluid_status ( waterdetect2_t *ctx );
```

- `waterdetect2_enable` Water Detect 2 enable function.
```c
void waterdetect2_enable ( waterdetect2_t *ctx );
```

- `waterdetect2_disable` Water Detect 2 disable function.
```c
void waterdetect2_disable ( waterdetect2_t *ctx );
```

### Application Init

> Initializes driver and performs the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waterdetect2_cfg_t waterdetect2_cfg;  /**< Click config object. */

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
    waterdetect2_cfg_setup( &waterdetect2_cfg );
    WATERDETECT2_MAP_MIKROBUS( waterdetect2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == waterdetect2_init( &waterdetect2, &waterdetect2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    waterdetect2_default_cfg( &waterdetect2 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads fluid presence status and determines if there is fluid presence or not.

```c
void application_task ( void ) 
{
    uint8_t fluid_status = waterdetect2_get_fluid_status( &waterdetect2 );
    if ( fluid_status != fluid_status_old )
    {
        if ( WATERDETECT2_FLUID_DETECTED == fluid_status )
        {
            log_printf( &logger, " Fluid present! \r\n" );
        }
        else
        {
            log_printf( &logger, " No fluid present. \r\n" );
        }
        log_printf( &logger, "------------------- \r\n" );
        fluid_status_old = fluid_status;
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
