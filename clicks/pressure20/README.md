\mainpage Main Page

---
# Pressure 20 Click

> Pressure 20 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the ICP-20100, a high-accuracy digital barometric pressure and temperature sensor from TDK InvenSense. The ICP-20100 is based on MEMS capacitive technology with ultra-low noise, low power consumption, and temperature stability alongside programmable output: all-pressure, all-temperature, or pressure and temperature output. It converts output data into a 20-bit digital value and sends the information via a configurable host interface that supports SPI and I2C serial communications. It measures pressure from 30kPa up to 110kPa with an accuracy of ±20Pa over a wide operating temperature range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure20_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pressure-20-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure 20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure 20 Click driver.

#### Standard key functions :

- `pressure20_cfg_setup` Config Object Initialization function.
```c
void pressure20_cfg_setup ( pressure20_cfg_t *cfg );
```

- `pressure20_init` Initialization function.
```c
err_t pressure20_init ( pressure20_t *ctx, pressure20_cfg_t *cfg );
```

- `pressure20_default_cfg` Click Default Configuration function.
```c
err_t pressure20_default_cfg ( pressure20_t *ctx );
```

#### Example key functions :

- `pressure20_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pressure20_get_int_pin ( pressure20_t *ctx );
```

- `pressure20_clear_interrupts` This function reads and clears the interrupt status register.
```c
err_t pressure20_clear_interrupts ( pressure20_t *ctx );
```

- `pressure20_read_data` This function reads the pressure [mBar] and temperature [Celsius] data.
```c
err_t pressure20_read_data ( pressure20_t *ctx, float *pressure, float *temperature );
```

## Example Description

> This example demonstrates the use of Pressure 20 Click board by reading and displaying the pressure and temperature data on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure20_cfg_t pressure20_cfg;  /**< Click config object. */

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
    pressure20_cfg_setup( &pressure20_cfg );
    PRESSURE20_MAP_MIKROBUS( pressure20_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure20_init( &pressure20, &pressure20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE20_ERROR == pressure20_default_cfg ( &pressure20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, clears the interrupts and than reads
the pressure [mBar] and temperature [Celsius] data and displays them on the USB UART
at the set output data rate (25Hz by default).

```c
void application_task ( void )
{
    // Wait for the data ready interrupt
    while ( pressure20_get_int_pin ( &pressure20 ) );
    float pressure, temperature;
    if ( ( PRESSURE20_OK == pressure20_clear_interrupts ( &pressure20 ) ) &&
         ( PRESSURE20_OK == pressure20_read_data ( &pressure20, &pressure, &temperature ) ) )
    {
        log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure );
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
