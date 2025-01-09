
---
# HAPTIC 3 Click

> [HAPTIC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5087) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5087&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of HAPTIC 3 Click board by controlling the attached motor vibration level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HAPTIC3

### Example Key Functions

- `haptic3_cfg_setup` Config Object Initialization function.
```c
void haptic3_cfg_setup ( haptic3_cfg_t *cfg );
```

- `haptic3_init` Initialization function.
```c
err_t haptic3_init ( haptic3_t *ctx, haptic3_cfg_t *cfg );
```

- `haptic3_default_cfg` Click Default Configuration function.
```c
err_t haptic3_default_cfg ( haptic3_t *ctx );
```

- `haptic3_set_vibration_level` This function sets the motor vibration level.
```c
err_t haptic3_set_vibration_level ( haptic3_t *ctx, float level );
```

- `haptic3_get_vibration_level` This function reads the motor vibration level.
```c
err_t haptic3_get_vibration_level ( haptic3_t *ctx, float *level );
```

- `haptic3_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t haptic3_write_register ( haptic3_t *ctx, uint8_t reg, uint8_t data_in );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic3_cfg_t haptic3_cfg;  /**< Click config object. */

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
    haptic3_cfg_setup( &haptic3_cfg );
    HAPTIC3_MAP_MIKROBUS( haptic3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == haptic3_init( &haptic3, &haptic3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC3_ERROR == haptic3_default_cfg ( &haptic3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the motor vibration level every 2 seconds from MAX to MIN, and displays the currently set level on the USB UART.

```c
void application_task ( void )
{
    float vibration_level;
    if ( HAPTIC3_OK == haptic3_set_vibration_level ( &haptic3, HAPTIC3_VIBRATION_LEVEL_MAX ) )
    {
        if ( HAPTIC3_OK == haptic3_get_vibration_level ( &haptic3, &vibration_level ) )
        {
            log_printf( &logger, " Vibration level: %.3f \r\n\n", vibration_level );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( HAPTIC3_OK == haptic3_set_vibration_level ( &haptic3, HAPTIC3_VIBRATION_LEVEL_MIN ) )
    {
        if ( HAPTIC3_OK == haptic3_get_vibration_level ( &haptic3, &vibration_level ) )
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
