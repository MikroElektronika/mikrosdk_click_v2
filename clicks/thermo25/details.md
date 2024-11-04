
---
# Thermo 25 Click

> Thermo 25 Click is a compact add-on board that accurately measures temperature. This board features the TMP127-Q1, a high-precision digital temperature sensor from Texas Instruments. This SPI-configurable factory-calibrated temperature sensor has a high accuracy of 0.8°C, supporting an ambient temperature range from -55°C to 175°C. It features a 14-bit signed temperature resolution (0.03125 °C per LSB) while operating over a supply range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo25_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-25-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Thermo 25 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 25 Click driver.

#### Standard key functions :

- `thermo25_cfg_setup` Config Object Initialization function.
```c
void thermo25_cfg_setup ( thermo25_cfg_t *cfg );
```

- `thermo25_init` Initialization function.
```c
err_t thermo25_init ( thermo25_t *ctx, thermo25_cfg_t *cfg );
```

#### Example key functions :

- `thermo25_check_communication` This function sets the operating mode to shutdown, then reads and verifies the device ID, and switches back to the continuous mode.
```c
err_t thermo25_check_communication ( thermo25_t *ctx );
```

- `thermo25_read_temperature` This function reads the temperature measurements in degrees Celsius.
```c
err_t thermo25_read_temperature ( thermo25_t *ctx, float *temperature );
```

- `thermo25_set_mode` This function sets the device operating mode to shutdown or continuous mode by using SPI serial interface.
```c
err_t thermo25_set_mode ( thermo25_t *ctx, uint8_t mode );
```

## Example Description

> This example demonstrates the use of Thermo 25 Click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and checks the communication by setting the operating mode to shutdown, reading and verifying the device ID, and switching back to the continuous mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo25_cfg_t thermo25_cfg;  /**< Click config object. */

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
    thermo25_cfg_setup( &thermo25_cfg );
    THERMO25_MAP_MIKROBUS( thermo25_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermo25_init( &thermo25, &thermo25_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO25_ERROR == thermo25_check_communication ( &thermo25 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO25_OK == thermo25_read_temperature ( &thermo25, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo25

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
