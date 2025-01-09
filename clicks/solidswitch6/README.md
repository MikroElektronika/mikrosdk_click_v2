
---
# SolidSwitch 6 Click

> [SolidSwitch 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6089) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6089&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the SolidSwitch 6 Click driver
> and demonstrate uses of the high-side switch controller with intelligent fuse protection.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch6

### Example Key Functions

- `solidswitch6_cfg_setup` Config Object Initialization function.
```c
void solidswitch6_cfg_setup ( solidswitch6_cfg_t *cfg );
```

- `solidswitch6_init` Initialization function.
```c
err_t solidswitch6_init ( solidswitch6_t *ctx, solidswitch6_cfg_t *cfg );
```

- `solidswitch6_default_cfg` Click Default Configuration function.
```c
err_t solidswitch6_default_cfg ( solidswitch6_t *ctx );
```

- `solidswitch6_get_vout` This function reads the raw ADC value and converts it to a proportional voltage level using the SPI serial interface.
```c
err_t solidswitch6_get_vout ( solidswitch6_t *ctx, float *vout );
```

- `solidswitch6_set_control` This function writes control registers to configure the switch controller using the SPI serial interface.
```c
err_t solidswitch6_set_control ( solidswitch6_t *ctx, solidswitch6_ctrl_t ctrl );
```

- `solidswitch6_get_device_temp` This function reads the raw ADC value and converts it to device temperature in degrees Celsius using the SPI serial interface.
```c
err_t solidswitch6_get_device_temp ( solidswitch6_t *ctx, float *tj );
```

### Application Init

> The initialization of the SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch6_cfg_t solidswitch6_cfg;  /**< Click config object. */
    
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
    solidswitch6_cfg_setup( &solidswitch6_cfg );
    SOLIDSWITCH6_MAP_MIKROBUS( solidswitch6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch6_init( &solidswitch6, &solidswitch6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH6_ERROR == solidswitch6_default_cfg ( &solidswitch6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ______________________\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the device temperature 
> and voltage level of the current sense amplifier, NTC, and output voltage measurement.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float app_buf = 0;
    if ( SOLIDSWITCH6_OK == solidswitch6_get_device_temp( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " Temperature: %.2f [degC]\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vntc( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " NTC: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vout( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " Vout: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vds( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " VDS: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    log_printf( &logger, " ______________________\r\n" );
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
