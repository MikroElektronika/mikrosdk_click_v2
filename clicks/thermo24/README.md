\mainpage Main Page

---
# Thermo 24 click

> Thermo 24 Click is a compact add-on board that contains the 4th generation temperature sensing solution from Sensirion. This board features the STS40, a high-accuracy ultra-low-power temperature sensor. The STS40 integrates a digital temperature sensor with a 16-bit analog-to-digital converter (ADC), a data processing circuit, and serial interface logic functions in one package. Characterized by its high accuracy (up to ±0.2°C typical) and high resolution of 0.01°C, this temperature sensor provides temperature data to the host controller with a configurable I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo24_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-24-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo 24 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 24 Click driver.

#### Standard key functions :

- `thermo24_cfg_setup` Config Object Initialization function.
```c
void thermo24_cfg_setup ( thermo24_cfg_t *cfg );
```

- `thermo24_init` Initialization function.
```c
err_t thermo24_init ( thermo24_t *ctx, thermo24_cfg_t *cfg );
```

#### Example key functions :

- `thermo24_soft_reset` This function performs the software reset by sending the soft reset command by using I2C serial interface.
```c
err_t thermo24_soft_reset ( thermo24_t *ctx );
```

- `thermo24_read_serial` This function reads the 4-byte chip serial number by using I2C serial interface.
```c
err_t thermo24_read_serial ( thermo24_t *ctx, uint32_t *serial_num );
```

- `thermo24_read_temperature` This function reads the temperature in Celsius with the specified measurement precision.
```c
err_t thermo24_read_temperature ( thermo24_t *ctx, uint8_t precision, float *temperature );
```

## Example Description

> This example demonstrates the use of Thermo 24 click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, then performs the software reset of the click board and reads and displays its serial number.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo24_cfg_t thermo24_cfg;  /**< Click config object. */

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
    thermo24_cfg_setup( &thermo24_cfg );
    THERMO24_MAP_MIKROBUS( thermo24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo24_init( &thermo24, &thermo24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO24_ERROR == thermo24_soft_reset ( &thermo24 ) )
    {
        log_error( &logger, " Software reset." );
        for ( ; ; );
    }

    uint32_t serial_num;
    if ( THERMO24_OK == thermo24_read_serial ( &thermo24, &serial_num ) )
    {
        log_printf ( &logger, " Serial Number: 0x%.8LX\r\n", serial_num );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement in Celsius and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO24_OK == thermo24_read_temperature ( &thermo24, THERMO24_MEASURE_PRECISION_HIGH, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo24

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
