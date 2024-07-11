
---
# Proximity 19 click

> Proximity 19 Click is a compact add-on board designed for precise proximity sensing in various applications. This board features the RPR-0720, a digital optical proximity sensor from ROHM Semiconductor. The RPR-0720 integrates an infrared VCSEL (IrVCSEL) and an IC with an I2C interface, featuring a detection range adjustable from 1 to 15mm and an ambient light canceling function. The board uses a 2-wire I2C interface for communication, supporting up to 400kHz frequency clock, allowing control over sensor functions such as operating mode, interrupt system, and offset/threshold adjustments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity19_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-19-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity 19 Click driver.

#### Standard key functions :

- `proximity19_cfg_setup` Config Object Initialization function.
```c
void proximity19_cfg_setup ( proximity19_cfg_t *cfg );
```

- `proximity19_init` Initialization function.
```c
err_t proximity19_init ( proximity19_t *ctx, proximity19_cfg_t *cfg );
```

- `proximity19_default_cfg` Click Default Configuration function.
```c
err_t proximity19_default_cfg ( proximity19_t *ctx );
```

#### Example key functions :

- `proximity19_get_distance` This function reads the distance measured by the sensor in millimeters by using the I2C serial interface.
```c
err_t proximity19_get_distance ( proximity19_t *ctx, float *distance );
```

- `proximity19_set_ps_gain` This function adjusts the gain of the sensor's sensitivity to light reception.
```c
err_t proximity19_set_ps_gain ( proximity19_t *ctx, uint8_t ps_gain );
```

- `proximity19_set_period` This function sets the desired data measurement period value.
```c
err_t proximity19_set_period ( proximity19_t *ctx, uint8_t period );
```

## Example Description

> This example demonstrates the use of the Proximity 19 click board 
> by measuring and displaying the distance data.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity19_cfg_t proximity19_cfg;  /**< Click config object. */

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
    proximity19_cfg_setup( &proximity19_cfg );
    PROXIMITY19_MAP_MIKROBUS( proximity19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity19_init( &proximity19, &proximity19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY19_ERROR == proximity19_default_cfg ( &proximity19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo app measures the distance between the sensor and the object in millimeters 
> and displays the result approximately every 100 milliseconds.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float distance = 0;
    if ( PROXIMITY19_OK == proximity19_get_distance( &proximity19, &distance ) )
    {
        log_printf( &logger, " Distance: %.2f [mm] \r\n\n", distance );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
