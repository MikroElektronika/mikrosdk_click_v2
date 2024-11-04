\mainpage Main Page

---
# I2C MUX 6 Click

> I2C MUX 6 Click is a compact add-on board representing a bidirectional selector dedicated to I2C slave address conflicts applications. This board features the PCA9518, an expandable five-channel bidirectional buffer controlled by the I2C-bus from Texas Instruments. The PCA9518 overcomes the restriction of maximum bus capacitance by separating and buffering the I2C data (SDA) and clock (SCL) lines into multiple groups of 400pF I2C channels. It provides activation of the desired channel via a given Enable pin and permits extension of the I2C-bus, through an onboard expansion header, by buffering both the data (SDA) and the clock (SCL) lines enabling virtually an unlimited number of buses of 400pF.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cmux6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/i2c-mux-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the I2C MUX 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2C MUX 6 Click driver.

#### Standard key functions :

- `i2cmux6_cfg_setup` Config Object Initialization function.
```c
void i2cmux6_cfg_setup ( i2cmux6_cfg_t *cfg );
```

- `i2cmux6_init` Initialization function.
```c
err_t i2cmux6_init ( i2cmux6_t *ctx, i2cmux6_cfg_t *cfg );
```

- `i2cmux6_default_cfg` Click Default Configuration function.
```c
err_t i2cmux6_default_cfg ( i2cmux6_t *ctx );
```

#### Example key functions :

- `i2cmux6_set_channel` This function sets the desired channel active and configures its slave address.
```c
err_t i2cmux6_set_channel ( i2cmux6_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr );
```

- `i2cmux6_generic_write` This function writes a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
err_t i2cmux6_generic_write ( i2cmux6_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );
```

- `i2cmux6_generic_read` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
err_t i2cmux6_generic_read ( i2cmux6_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

## Example Description

> This example demonstrates the use of I2C MUX 6 Click board by reading the device ID of a 6DOF IMU 11 and Compass 3 Click boards connected to the channels 1 and 4 respectfully.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cmux6_cfg_t i2cmux6_cfg;  /**< Click config object. */

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
    i2cmux6_cfg_setup( &i2cmux6_cfg );
    I2CMUX6_MAP_MIKROBUS( i2cmux6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cmux6_init( &i2cmux6, &i2cmux6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the device ID of the connected Click boards.
Channel 1 : 6DOF IMU 11 Click [slave address: 0x0E; reg: 0x00; id: 0x2D],
Channel 4 : Compass 3 Click   [slave address: 0x30; reg: 0x2F; id: 0x0C].
All data is being logged on the USB UART where you can check the device ID.

```c
void application_task ( void )
{
    uint8_t device_id;
    if ( I2CMUX6_OK == i2cmux6_set_channel ( &i2cmux6, DEVICE0_POSITION, DEVICE0_SLAVE_ADDRESS ) )
    {
        log_printf( &logger, "\r\n Active Channel: - " );
        for ( uint8_t cnt = 0; cnt < 4; cnt++ )
        {
            if ( ( DEVICE0_POSITION ) & ( 1 << cnt ) )
            {
                log_printf( &logger, "%u - ", ( uint16_t ) ( cnt + 1 ) );
            }
        }
        if ( I2CMUX6_OK == i2cmux6_generic_read ( &i2cmux6, DEVICE0_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, "\r\n %s - Device ID: 0x%.2X\r\n", ( char * ) DEVICE0_NAME, ( uint16_t ) device_id );
        }
        Delay_ms ( 1000 );
    }
    if ( I2CMUX6_OK == i2cmux6_set_channel ( &i2cmux6, DEVICE1_POSITION, DEVICE1_SLAVE_ADDRESS ) )
    {
        log_printf( &logger, "\r\n Active Channel: - " );
        for ( uint8_t cnt = 0; cnt < 4; cnt++ )
        {
            if ( ( DEVICE1_POSITION ) & ( 1 << cnt ) )
            {
                log_printf( &logger, "%u - ", ( uint16_t ) ( cnt + 1 ) );
            }
        }
        if ( I2CMUX6_OK == i2cmux6_generic_read ( &i2cmux6, DEVICE1_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, "\r\n %s - Device ID: 0x%.2X\r\n", ( char * ) DEVICE1_NAME, ( uint16_t ) device_id );
        }
        Delay_ms ( 1000 );
    }
}
```

## Note

> Make sure to provide 3v3 power supply on VCC-I2C pin.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CMUX6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
