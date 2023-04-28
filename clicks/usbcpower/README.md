\mainpage Main Page

---
# USB-C Power click

> USB-C Power Click is a compact add-on board that provides a quick 
> and easy way to supply power without carrying multiple adapters or cables. 
> This board features the TPS25750S, a highly integrated USB Type-C and Power Delivery (PD) controller 
> with integrated power switches optimized for power applications from Texas Instruments. 
> The TPS25750S integrates fully managed power paths (5V/3A with 36mΩ sourcing switch) 
> with robust protection (reverse and inrush current as well as over/under voltage protection) 
> and control for external battery charger IC for a complete USB-C PD solution. Besides web-based GUI 
> and pre-configured firmware, the TPS25750S also has some GPIOs and LED indicators 
> that are user-defined for either status or control information.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbcpower_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-c-power-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the USB-C Power Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USB-C Power Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of the USB-C Power Click board™
> by configuring the PD controller to attempt to become a Power Source.

**The demo application is composed of two sections :**

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
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 100 );
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
    Delay_ms( 3000 );
}
```

## Note

> For the advanced configuration, use the TPS25750 Application Customization Tool:
> https://dev.ti.com/gallery/search/TPS25750_Application_Customization_Tool

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCPower

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
