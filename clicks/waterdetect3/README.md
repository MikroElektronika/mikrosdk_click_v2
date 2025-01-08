
---
# Water Detect 3 Click

> [Water Detect 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5848) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5848&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Water Detect 3 Click board by
  detecting if water is present on the sensor part of the Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WaterDetect3

### Example Key Functions

- `waterdetect3_cfg_setup` Config Object Initialization function.
```c
void waterdetect3_cfg_setup ( waterdetect3_cfg_t *cfg );
```

- `waterdetect3_init` Initialization function.
```c
err_t waterdetect3_init ( waterdetect3_t *ctx, waterdetect3_cfg_t *cfg );
```

- `waterdetect3_get_int` Water Detect 3 interrupt pin reading function.
```c
uint8_t waterdetect3_get_int ( waterdetect3_t *ctx );
```

### Application Init

> Initializes the driver and configures hardware for the detection.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waterdetect3_cfg_t waterdetect3_cfg;  /**< Click config object. */

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
    waterdetect3_cfg_setup( &waterdetect3_cfg );
    WATERDETECT3_MAP_MIKROBUS( waterdetect3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == waterdetect3_init( &waterdetect3, &waterdetect3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Turn potentiometer VR1 all the way to the right.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Place a few drops of water onto the sensor.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Turn potentiometer VR1 to the left until the detect LED turns off.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    while ( WATERDETECT3_PIN_STATE_HIGH == waterdetect3_get_int( &waterdetect3 ) );
    
    log_printf( &logger, " Device is ready.\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Detects if any water is present on the sensor part.

```c
void application_task ( void ) 
{
    if ( WATERDETECT3_PIN_STATE_HIGH == waterdetect3_get_int( &waterdetect3 ) )
    {
        log_printf( &logger, " Water detected.\r\n" );
        Delay_ms ( 1000 );
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
