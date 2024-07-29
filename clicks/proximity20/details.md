
---
# Proximity 20 click

> Proximity 20 Click is a compact add-on board for short-range proximity sensing applications up to 200mm. This board features two VCNL36828P proximity sensors from Vishay Semiconductor. Key features include a 940nm VCSEL for immunity to a red glow, intelligent cancellation technology to minimize crosstalk, and a smart persistence scheme for reduced measurement response time.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity20_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-20-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity 20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity 20 Click driver.

#### Standard key functions :

- `proximity20_cfg_setup` Config Object Initialization function.
```c
void proximity20_cfg_setup ( proximity20_cfg_t *cfg );
```

- `proximity20_init` Initialization function.
```c
err_t proximity20_init ( proximity20_t *ctx, proximity20_cfg_t *cfg );
```

- `proximity20_default_cfg` Click Default Configuration function.
```c
err_t proximity20_default_cfg ( proximity20_t *ctx );
```

#### Example key functions :

- `proximity20_read_proximity` This function reads the proximity data from U2 and U3 sensors.
```c
err_t proximity20_read_proximity ( proximity20_t *ctx, uint16_t *ps_data_u2, uint16_t *ps_data_u3 );
```

- `proximity20_set_device_address` This function sets the device slave address.
```c
err_t proximity20_set_device_address ( proximity20_t *ctx, uint8_t dev_addr );
```

- `proximity20_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void proximity20_enable_device ( proximity20_t *ctx );
```

## Example Description

> This example demonstrates the use of Proximity 20 click board by reading and displaying the proximity data on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity20_cfg_t proximity20_cfg;  /**< Click config object. */

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
    proximity20_cfg_setup( &proximity20_cfg );
    PROXIMITY20_MAP_MIKROBUS( proximity20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity20_init( &proximity20, &proximity20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY20_ERROR == proximity20_default_cfg ( &proximity20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the proximity data from 2 sensors and displays the results on the USB UART every 200ms. The higher the proximity value, the closer the detected object.

```c
void application_task ( void )
{
    uint16_t ps_data_u2 = 0;
    uint16_t ps_data_u3 = 0;
    if ( PROXIMITY20_OK == proximity20_read_proximity ( &proximity20, &ps_data_u2, &ps_data_u3 ) )
    {
        log_printf ( &logger, " PS data [U2]: %u\r\n", ps_data_u2 );
        log_printf ( &logger, " PS data [U3]: %u\r\n\n", ps_data_u3 );
        Delay_ms ( 200 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
