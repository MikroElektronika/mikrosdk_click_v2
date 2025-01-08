
---
# USB-C Sink 4 Click

> [USB-C Sink 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6174) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6174&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of a USB-C Sink 4 Click board 
> by setting DC power requests and control for Type-C connector-equipped devices (TCD).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSink4

### Example Key Functions

- `usbcsink4_cfg_setup` Config Object Initialization function.
```c
void usbcsink4_cfg_setup ( usbcsink4_cfg_t *cfg );
```

- `usbcsink4_init` Initialization function.
```c
err_t usbcsink4_init ( usbcsink4_t *ctx, usbcsink4_cfg_t *cfg );
```

- `usbcsink4_default_cfg` Click Default Configuration function.
```c
err_t usbcsink4_default_cfg ( usbcsink4_t *ctx );
```

- `usbcsink4_get_type_c_status` This function reads the reports of the status of the Type-C port by using the I2C serial interface.
```c
err_t usbcsink4_get_type_c_status ( usbcsink4_t *ctx, usbcsink4_type_c_status_t *type_c_status );
```

- `usbcsink4_get_bus_voltage` This function reads the live voltage on the VBUS supply for the specified port using the I2C serial interface.
```c
err_t usbcsink4_get_bus_voltage ( usbcsink4_t *ctx, float *vbus_v );
```

- `usbcsink4_get_event_status` This function reads the reports of the event status to know what has happened on the Type-C/PD port using the I2C serial interface.
```c
err_t usbcsink4_get_event_status ( usbcsink4_t *ctx, usbcsink4_event_status_t *event_status );
```

### Application Init

> The initialization of the I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink4_cfg_t usbcsink4_cfg;  /**< Click config object. */

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
    usbcsink4_cfg_setup( &usbcsink4_cfg );
    USBCSINK4_MAP_MIKROBUS( usbcsink4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == usbcsink4_init( &usbcsink4, &usbcsink4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCSINK4_ERROR == usbcsink4_default_cfg ( &usbcsink4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo app displays the reports of the Type-C port, active legacy charging mode status, 
> and live voltage measurements on the VBUS supply for the specified port.

```c
void application_task ( void ) 
{
    usbcsink4_display_type_c_status( );
    Delay_ms ( 100 );

    usbcsink4_display_chrg_mode( );
    Delay_ms ( 100 );

    usbcsink4_display_bus_voltage( );
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
