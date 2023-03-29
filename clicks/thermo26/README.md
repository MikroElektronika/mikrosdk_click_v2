\mainpage Main Page

---
# Thermo 26 click

> Thermo 26 Click is a compact add-on board that accurately measures temperature. 
> This board features the STS31-DIS, a high-accuracy digital temperature sensor from Sensirion. 
> Characterized by its high accuracy (up to ±0.2°C typical) and high resolution of 0.01°C, 
> the STS31-DIS provides temperature data to the host controller with a configurable I2C interface. 
> It relies on the industry-proven CMOSens® technology, providing increased intelligence, reliability, 
> and improved accuracy specifications, including enhanced signal processing, 
> user-selectable I2C addresses, and up to 1 MHz communication speeds.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo26_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-26-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo 26 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 26 Click driver.

#### Standard key functions :

- `thermo26_cfg_setup` Config Object Initialization function.
```c
void thermo26_cfg_setup ( thermo26_cfg_t *cfg );
```

- `thermo26_init` Initialization function.
```c
err_t thermo26_init ( thermo26_t *ctx, thermo26_cfg_t *cfg );
```

#### Example key functions :

- `thermo26_read_serial_num` This function reads the 32-bit unique serial number.
```c
err_t thermo26_read_serial_num ( thermo26_t *ctx, uint32_t *serial_num );
```

- `thermo26_start_measurement` This function starts the measurements by sending the specified command.
```c
err_t thermo26_start_measurement ( thermo26_t *ctx, uint16_t cmd );
```

- `thermo26_read_temperature` This function reads the temperature raw data measurements and converts it to degrees Celsius.
```c
err_t thermo26_read_temperature ( thermo26_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Thermo 26 click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the device, and after that reads the serial number and starts the periodic measurements at 2 mps with high repeatability.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo26_cfg_t thermo26_cfg;  /**< Click config object. */

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
    thermo26_cfg_setup( &thermo26_cfg );
    THERMO26_MAP_MIKROBUS( thermo26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo26_init( &thermo26, &thermo26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    thermo26_reset_device ( &thermo26 );
    
    uint32_t serial_num;
    if ( THERMO26_ERROR == thermo26_read_serial_num ( &thermo26, &serial_num ) )
    {
        log_error( &logger, " Read serial number." );
        for ( ; ; );
    }
    log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    
    if ( THERMO26_ERROR == thermo26_start_measurement ( &thermo26, THERMO26_CMD_PERIODIC_2_MPS_REP_HIGH ) )
    {
        log_error( &logger, " Start measurement." );
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
    if ( THERMO26_OK == thermo26_read_temperature ( &thermo26, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f\r\n\n", temperature );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo26

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
