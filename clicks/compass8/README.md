\mainpage Main Page

---
# Compass 8 Click

> Compass 8 Click is a compact add-on board designed for precise compass applications. This board features the AK09919, a 3-axis electronic compass IC from AKM Semiconductor. The AK09919 is based on high-sensitivity Hall sensor technology for detecting terrestrial magnetism across the X, Y, and Z axes, has multiple operational modes, a built-in oscillator, and a Power On Reset circuit. It also includes a magnetic sensor overflow monitor and a 16-sample FIFO data buffer for efficient data handling.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/compass8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/compass-8-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Compass 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Compass 8 Click driver.

#### Standard key functions :

- `compass8_cfg_setup` Config Object Initialization function.
```c
void compass8_cfg_setup ( compass8_cfg_t *cfg );
```

- `compass8_init` Initialization function.
```c
err_t compass8_init ( compass8_t *ctx, compass8_cfg_t *cfg );
```

- `compass8_default_cfg` Click Default Configuration function.
```c
err_t compass8_default_cfg ( compass8_t *ctx );
```

#### Example key functions :

- `compass8_get_magnetic_data` This function reads the raw magnetic sensor measurement data and calculates magnetic flux density [microTesla] using the I2C serial interface.
```c
err_t compass8_get_magnetic_data ( compass8_t *ctx, compass8_axes_t *axis );
```

- `compass8_set_operation_mode` This function sets the desired sensor operation mode by using the I2C serial interface.
```c
err_t compass8_set_operation_mode ( compass8_t *ctx, uint8_t op_mode );
```

- `compass8_sw_reset` This function performs software reset by using the I2C serial interface.
```c
err_t compass8_sw_reset ( compass8_t *ctx );
```

## Example Description

> This library contains API for the Compass 8 Click driver.
> The library initializes and defines the I2C drivers to 
> write and read data from registers, as well as the default 
> configuration for reading measurement data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass8_cfg_t compass8_cfg;  /**< Click config object. */

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
    compass8_cfg_setup( &compass8_cfg );
    COMPASS8_MAP_MIKROBUS( compass8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == compass8_init( &compass8, &compass8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COMPASS8_ERROR == compass8_default_cfg ( &compass8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Compass 8 Click board.
> Measures and displays magnetic flux density in microtesla (uT) for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    compass8_axes_t axis; 
    if ( COMPASS8_OK == compass8_get_magnetic_data( &compass8, &axis ) ) 
    {
        log_printf( &logger, " X-axis: %.2f uT\r\n", axis.x );
        log_printf( &logger, " Y-axis: %.2f uT\r\n", axis.y );
        log_printf( &logger, " Z-axis: %.2f uT\r\n", axis.z );      
        log_printf( &logger,  "--------------------\r\n" );
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
