
---
# Haptic 4 Click

> [Haptic 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6045) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6045&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Haptic 4 Click board by controlling
  the attached motor vibration level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Haptic4

### Example Key Functions

- `haptic4_cfg_setup` Config Object Initialization function.
```c
void haptic4_cfg_setup ( haptic4_cfg_t *cfg );
```

- `haptic4_init` Initialization function.
```c
err_t haptic4_init ( haptic4_t *ctx, haptic4_cfg_t *cfg );
```

- `haptic4_default_cfg` Click Default Configuration function.
```c
err_t haptic4_default_cfg ( haptic4_t *ctx );
```

- `haptic4_check_communication` This function checks the communication by reading and verifying the chip ID.
```c
err_t haptic4_check_communication ( haptic4_t *ctx );
```

- `haptic4_set_vibration_level` This function sets the motor vibration level.
```c
err_t haptic4_set_vibration_level ( haptic4_t *ctx, float level );
```

- `haptic4_get_vibration_level` This function reads the motor vibration level.
```c
err_t haptic4_get_vibration_level ( haptic4_t *ctx, float *level );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic4_cfg_t haptic4_cfg;  /**< Click config object. */

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
    haptic4_cfg_setup( &haptic4_cfg );
    HAPTIC4_MAP_MIKROBUS( haptic4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == haptic4_init( &haptic4, &haptic4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC4_ERROR == haptic4_default_cfg ( &haptic4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the motor vibration level every 2 seconds between MAX and MIN, 
  and displays the currently set level on the USB UART.

```c
void application_task ( void ) 
{
    float vibration_level;
    if ( HAPTIC4_OK == haptic4_set_vibration_level ( &haptic4, HAPTIC4_VIBRATION_LEVEL_MAX ) )
    {
        if ( HAPTIC4_OK == haptic4_get_vibration_level ( &haptic4, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( HAPTIC4_OK == haptic4_set_vibration_level ( &haptic4, HAPTIC4_VIBRATION_LEVEL_MIN ) )
    {
        if ( HAPTIC4_OK == haptic4_get_vibration_level ( &haptic4, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
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
