
---
# I2C Isolator 6 click

> I2C Isolator 6 Click is a compact add-on board that offers completely isolated bidirectional communication. 
> This board features the ADUM2250, a two-channel, 5kVRMS I2C digital isolator from Analog Devices. 
> The ADUM2250 provides two bidirectional channels, supporting a completely isolated I2C interface 
> that eliminates the need for splitting I2C signals into separate transmit and receive signals 
> for use with standalone optocouplers. It supports data rates from DC up to 1MHz 
> and has a hot swap circuitry to prevent data glitches.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cisolator6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/i2c-isolator-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the I2C Isolator 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2C Isolator 6 Click driver.

#### Standard key functions :

- `i2cisolator6_cfg_setup` Config Object Initialization function.
```c
void i2cisolator6_cfg_setup ( i2cisolator6_cfg_t *cfg );
```

- `i2cisolator6_init` Initialization function.
```c
err_t i2cisolator6_init ( i2cisolator6_t *ctx, i2cisolator6_cfg_t *cfg );
```

#### Example key functions :

- `i2cisolator6_write` I2C Isolator 6 I2C writing function.
```c
err_t i2cisolator6_write ( i2cisolator6_t *ctx, uint8_t *data_in, uint8_t len );
```

- `i2cisolator6_read` I2C Isolator 6 I2C reading function.
```c
err_t i2cisolator6_read ( i2cisolator6_t *ctx, uint8_t *data_out, uint8_t len );
```

- `i2cisolator6_write_then_read` I2C Isolator 6 I2C write then read function.
```c
err_t i2cisolator6_write_then_read ( i2cisolator6_t *ctx, uint8_t *data_in, uint8_t len_write_data, uint8_t *data_out, uint8_t len_read_data );
```

## Example Description

> This library contains API for the I2C Isolator 6 Click driver.
> This demo application shows an example of an I2C Isolator 6 Click 
> wired to the Accel 21 Click for reading device ID.
> The library also includes an I2C writing and reading functions.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module, log UART.
> After the driver init, the app sets Accel 21 Click I2C Slave address.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator6_cfg_t i2cisolator6_cfg;  /**< Click config object. */

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
    i2cisolator6_cfg_setup( &i2cisolator6_cfg );
    I2CISOLATOR6_MAP_MIKROBUS( i2cisolator6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator6_init( &i2cisolator6, &i2cisolator6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( I2CISOLATOR6_ERROR == i2cisolator6_set_slave_address( &i2cisolator6, ACCEL21_DEVICE_ADDRESS_GND ) )
    {
        log_error( &logger, " Set I2C Slave address ERROR." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the I2C Isolator 6 Click board™.
> Logs device ID values of the Accel 21 Click 
> wired to the I2C Isolator 6 Click board™.

```c
void application_task ( void ) 
{
    static uint8_t device_id = 0;
    static uint8_t reg = ACCEL21_REG_WHO_AM_I;
    if ( I2CISOLATOR6_OK == i2cisolator6_write_then_read( &i2cisolator6, &reg, 1, &device_id, 1 ) )
    {
        if ( ACCEL21_DEVICE_ID == device_id )
        {
            log_printf( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
            log_printf( &logger, "---------------------\r\n" );
        }
    }
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
