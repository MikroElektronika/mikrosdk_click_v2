\mainpage Main Page

---
# 1-Wire I2C click

> 1-Wire I2C click carries DS28E17 1-Wire-to-I2C master bridge from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/1wirei2c_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/1-wire-i2c-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : One Wire type


# Software Support

We provide a library for the 1-Wire I2C Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 1-Wire I2C Click driver.

#### Standard key functions :

- `c1wirei2c_cfg_setup` Config Object Initialization function.
```c
void c1wirei2c_cfg_setup ( c1wirei2c_cfg_t *cfg );
```

- `c1wirei2c_init` Initialization function.
```c
err_t c1wirei2c_init ( c1wirei2c_t *ctx, c1wirei2c_cfg_t *cfg );
```

- `c1wirei2c_default_cfg` Click Default Configuration function.
```c
err_t c1wirei2c_default_cfg ( c1wirei2c_t *ctx );
```

#### Example key functions :

- `c1wirei2c_reset_device` This function resets the device by toggling the RST pin state.
```c
void c1wirei2c_reset_device ( c1wirei2c_t *ctx );
```

- `c1wirei2c_write_data` This function addresses and writes 1-255 bytes to an I2C slave without completing the transaction with a stop.
```c
err_t c1wirei2c_write_data ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len );
```

- `c1wirei2c_read_data_stop` This function is used to address and read 1-255 bytes from an I2C slave in one transaction.
```c
err_t c1wirei2c_read_data_stop ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_out, uint8_t len );
```

## Example Description

> This example demonstrates the use of 1-Wire I2C click board by reading the temperature measurement from connected Thermo 4 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1wirei2c_cfg_t c1wirei2c_cfg;  /**< Click config object. */

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
    c1wirei2c_cfg_setup( &c1wirei2c_cfg );
    C1WIREI2C_MAP_MIKROBUS( c1wirei2c_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == c1wirei2c_init( &c1wirei2c, &c1wirei2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1WIREI2C_ERROR == c1wirei2c_default_cfg ( &c1wirei2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement from connected Thermo 4 click board and displays the results on the USB UART once per second.

```c
void application_task ( void )
{
    float temperature = 0;
    uint8_t reg_data[ 2 ] = { 0 };
    uint8_t reg_addr = DEVICE_REG_TEMPERATURE;
    if ( ( C1WIREI2C_OK == c1wirei2c_write_data ( &c1wirei2c, DEVICE_SLAVE_ADDRESS, &reg_addr, 1 ) ) && 
         ( C1WIREI2C_OK == c1wirei2c_read_data_stop ( &c1wirei2c, DEVICE_SLAVE_ADDRESS, reg_data, 2 ) ) )
    {
        temperature = ( ( ( int16_t ) ( ( ( uint16_t ) reg_data[ 0 ] << 8 ) | 
                                                       reg_data[ 1 ] ) ) >> 5 ) * DEVICE_TEMPERATURE_RES;
        log_printf( &logger, "\r\n%s - Temperature: %.3f degC\r\n", ( char * ) DEVICE_NAME, temperature );
    }
    else
    {
        log_error( &logger, "%s - no communication!\r\n", ( char * ) DEVICE_NAME );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.1WireI2C

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
