
---
# USB-C Sink 4 click

> USB-C Sink 4 Click is a compact add-on board designed to enable devices to draw power through the USB Type-C interface. This board features the CYPD3178, a USB Type-C power sink controller from Infineon. This Click board™ includes a controller with an integrated USB Type-C transceiver, load switch control with soft start, and system-level fault protection. It has configurable charging protocols, voltage negotiation, and an unpopulated SAFE 5V header for an alternate power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbcsink4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-c-sink-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the USB-C Sink 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USB-C Sink 4 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of a USB-C Sink 4 Click board 
> by setting DC power requests and control for Type-C connector-equipped devices (TCD).

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSink4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
