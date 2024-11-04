\mainpage Main Page

---
# I2C Isolator 7 Click

> I2C Isolator 7 Click is a compact add-on board that offers completely isolated bidirectional communication. This board features the ADuM1252, an ultra-low power, bidirectional I2C isolator from Analog Devices. It can isolate I2C bidirectional data transfer of up to 2MHz SCL and bidirectional SCL for advanced bus topologies, and it supports clock stretching and multiple controllers across the isolation barrier. It also features the enhanced hot-swappable side 2 IO.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cisolator7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/i2c-isolator-7-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the I2C Isolator 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2C Isolator 7 Click driver.

#### Standard key functions :

- `i2cisolator7_cfg_setup` Config Object Initialization function.
```c
void i2cisolator7_cfg_setup ( i2cisolator7_cfg_t *cfg );
```

- `i2cisolator7_init` Initialization function.
```c
err_t i2cisolator7_init ( i2cisolator7_t *ctx, i2cisolator7_cfg_t *cfg );
```

#### Example key functions :

- `i2cisolator7_generic_write` This function shall generate a START signal, followed by len number of writes from data_in.
```c
err_t i2cisolator7_generic_write ( i2cisolator7_t *ctx, uint8_t *data_in, uint8_t len );
```

- `i2cisolator7_generic_read` This function shall generate a START signal, followed by len number of reads from the bus placing the data in data_out.
```c
err_t i2cisolator7_generic_read ( i2cisolator7_t *ctx, uint8_t *data_out, uint8_t len );
```

- `i2cisolator7_write_then_read` This function performs a write operation followed by a read operation on the bus by using I2C serial interface.
```c
err_t i2cisolator7_write_then_read ( i2cisolator7_t *ctx, uint8_t *data_in, uint8_t len_write_data, uint8_t *data_out, uint8_t len_read_data );
```

## Example Description

> This demo application shows an example of an I2C Isolator 7 Click 
> wired to the PRESS Click board™ for reading device ID (Who am I).
> The library also includes an I2C writing and reading functions.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the PRESS Click board™ slave address.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator7_cfg_t i2cisolator7_cfg;  /**< Click config object. */

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
    i2cisolator7_cfg_setup( &i2cisolator7_cfg );
    I2CISOLATOR7_MAP_MIKROBUS( i2cisolator7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator7_init( &i2cisolator7, &i2cisolator7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( I2CISOLATOR7_ERROR == i2cisolator7_set_slave_address( &i2cisolator7, PRESS_DEVICE_ADDRESS ) )
    {
        log_error( &logger, " Set I2C Slave address ERROR." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the I2C Isolator 7 Click board™.
> Logs device ID values of the PRESS Click board™ 
> wired to the I2C Isolator 7 Click board™.

```c
void application_task ( void ) 
{
    uint8_t device_id = 0;
    uint8_t reg = PRESS_REG_WHO_AM_I;
    if ( I2CISOLATOR7_OK == i2cisolator7_write_then_read( &i2cisolator7, &reg, 1, &device_id, 1 ) )
    {
        if ( PRESS_WHO_AM_I == device_id )
        {
            log_printf( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
            log_printf( &logger, "---------------------\r\n" );
        }
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
