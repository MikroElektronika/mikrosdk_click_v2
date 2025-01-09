
---
# USB-C Power Click

> [USB-C Power Click](https://www.mikroe.com/?pid_product=MIKROE-5682) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5682&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the USB-C Power Click board&trade;
> by configuring the PD controller to attempt to become a Power Source.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCPower

### Example Key Functions

- `usbcpower_cfg_setup` Config Object Initialization function.
```c
void usbcpower_cfg_setup ( usbcpower_cfg_t *cfg );
```

- `usbcpower_init` Initialization function.
```c
err_t usbcpower_init ( usbcpower_t *ctx, usbcpower_cfg_t *cfg );
```

- `usbcpower_default_cfg` Click Default Configuration function.
```c
err_t usbcpower_default_cfg ( usbcpower_t *ctx );
```

- `usbcpower_get_status`  USB-C Power gets status function.
```c
err_t usbcpower_get_status ( usbcpower_t *ctx, usbcpower_status_t *status )
```

- `usbcpower_get_pwr_status` USB-C Power gets PWR status function.
```c
err_t usbcpower_get_pwr_status ( usbcpower_t *ctx, usbcpower_pwr_status_t *pwr_status );
```

- `usbcpower_start_patch_burst_mode` USB-C Power starts the patch burst mode function.
```c
err_t usbcpower_start_patch_burst_mode ( usbcpower_t *ctx, usbcpower_pbms_cfg_t pbms_cfg, uint32_t *response );
```

### Application Init

> The initialization of I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration,
> depending on PD Device Mode, the app performs the patch bundle update tasks
> for loading a patch bundle in burst mode to the PD controller.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcpower_cfg_t usbcpower_cfg;  /**< Click config object. */

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
    usbcpower_cfg_setup( &usbcpower_cfg );
    USBCPOWER_MAP_MIKROBUS( usbcpower_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == usbcpower_init( &usbcpower, &usbcpower_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCPOWER_ERROR == usbcpower_default_cfg ( &usbcpower ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    usbcpower_set_patch_mode( &usbcpower, &response );
    if ( USBCPOWER_RSP_OK != response )
    {
        log_error( &logger, " Go to Patch Mode." );
        for ( ; ; );
    }
    
    uint8_t device_mode[ 6 ] = { 0 };
    usbcpower_get_device_mode( &usbcpower, &device_mode );
    log_printf( &logger, " PD Device Mode: %s\r\n", &device_mode[ 1 ] );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The application display status information about 
> the PD controller data role and power of the connection.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( USBCPOWER_OK == usbcpower_get_status( &usbcpower, &status ) )
    {
        if ( USBCPOWER_OK == usbcpower_get_pwr_status( &usbcpower, &pwr_status ) )
        {
            usbcpower_display_status( );
            log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
            usbcpower_display_pwr_status( );
            log_printf( &logger, "-----------------------------\r\n" );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> For the advanced configuration, use the TPS25750 Application Customization Tool:
> https://dev.ti.com/gallery/search/TPS25750_Application_Customization_Tool

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
