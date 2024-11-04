\mainpage Main Page

---
# Proximity 21 Click

> Proximity 21 Click is a compact add-on board for high-precision proximity sensing and short-range distance measurements. This board features the VL53L4ED, a Time-of-Flight (ToF) proximity sensor from STMicroelectronics, known for its extended temperature capability and accuracy. This sensor provides a field of view (FoV) of 18°, measuring distances from 1mm up to 1300mm in standard conditions and up to 1150mm in extended temperature environments, with reliable performance even in ambient light conditions up to 5klx. The Click board™ features a unique Click Snap design, making the main IC area movable for versatile implementation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity21_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity 21 Click driver.

#### Standard key functions :

- `proximity21_cfg_setup` Config Object Initialization function.
```c
void proximity21_cfg_setup ( proximity21_cfg_t *cfg );
```

- `proximity21_init` Initialization function.
```c
err_t proximity21_init ( proximity21_t *ctx, proximity21_cfg_t *cfg );
```

- `proximity21_default_cfg` Click Default Configuration function.
```c
err_t proximity21_default_cfg ( proximity21_t *ctx );
```

#### Example key functions :

- `proximity21_get_gpio1_pin` This function returns the GPIO1 (interrupt) pin logic state.
```c
uint8_t proximity21_get_gpio1_pin ( proximity21_t *ctx );
```

- `proximity21_get_result` This function gets the results reported by the sensor.
```c
err_t proximity21_get_result ( proximity21_t *ctx, proximity21_data_t *results );
```

- `proximity21_clear_interrupt` This function clears the data ready interrupt.
```c
err_t proximity21_clear_interrupt ( proximity21_t *ctx );
```

## Example Description

> This example demonstrates the use of Proximity 21 Click board by reading and displaying the target distance in millimeters on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity21_cfg_t proximity21_cfg;  /**< Click config object. */

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
    proximity21_cfg_setup( &proximity21_cfg );
    PROXIMITY21_MAP_MIKROBUS( proximity21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity21_init( &proximity21, &proximity21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY21_ERROR == proximity21_default_cfg ( &proximity21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for a data ready interrupt, then reads the measurement results and logs
the target distance (millimeters) and signal quality (the higher the value the better the signal quality) to the USB UART.

```c
void application_task ( void )
{
    proximity21_data_t results;
    // Wait for a data ready interrupt
    while ( proximity21_get_gpio1_pin ( &proximity21 ) );

    if ( PROXIMITY21_OK == proximity21_get_result ( &proximity21, &results ) )
    {
        log_printf( &logger, " Distance [mm]: %u\r\n", results.distance_mm );
        log_printf( &logger, " Signal [kcps/SPAD]: %u\r\n\n", results.signal_per_spad_kcps );
        proximity21_clear_interrupt ( &proximity21 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
