
---
# Pressure 17 Click

> Pressure 17 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the BM1390GLV-Z, a high-precision piezoresistive pressure sensor from Rohm Semiconductor. The BM1390GLV-Z comes with a configurable host interface that supports I2C serial communication and measures pressure in a range from 300hPa up to 1300hPa with an accuracy of ±1hPa.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pressure-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Pressure 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure 17 Click driver.

#### Standard key functions :

- `pressure17_cfg_setup` Config Object Initialization function.
```c
void pressure17_cfg_setup ( pressure17_cfg_t *cfg );
```

- `pressure17_init` Initialization function.
```c
err_t pressure17_init ( pressure17_t *ctx, pressure17_cfg_t *cfg );
```

- `pressure17_default_cfg` Click Default Configuration function.
```c
err_t pressure17_default_cfg ( pressure17_t *ctx );
```

#### Example key functions :

- `pressure17_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pressure17_get_int_pin ( pressure17_t *ctx );
```

- `pressure17_read_data` This function checks if the data is ready and then reads the pressure and temperature raw data and converts them to millibar and Celsius respectfully.
```c
err_t pressure17_read_data ( pressure17_t *ctx, float *pressure, float *temperature );
```

- `pressure17_write_register` This function writes a data byte to the selected register by using I2C serial interface.
```c
err_t pressure17_write_register ( pressure17_t *ctx, uint8_t reg, uint8_t data_in );
```

## Example Description

> This example demonstrates the use of Pressure 17 Click board by reading and displaying the pressure and temperature data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure17_cfg_t pressure17_cfg;  /**< Click config object. */

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
    pressure17_cfg_setup( &pressure17_cfg );
    PRESSURE17_MAP_MIKROBUS( pressure17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pressure17_init( &pressure17, &pressure17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE17_ERROR == pressure17_default_cfg ( &pressure17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt and then reads the pressure [mbar] and temperature [C] data
and displays the results on the USB UART approximately every 200ms.

```c
void application_task ( void )
{
    if ( !pressure17_get_int_pin ( &pressure17 ) )
    {
        float pressure, temperature;
        if ( PRESSURE17_OK == pressure17_read_data ( &pressure17, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.2f mbar\r\n Temperature: %.2f C\r\n\n", pressure, temperature );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
