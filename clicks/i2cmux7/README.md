\mainpage Main Page

---
# I2C MUX 7 click

> I2C MUX 7 Click is a compact add-on board representing a bidirectional selector dedicated to applications with I2C slave address conflicts. This board features the PI4MSD5V9547, an octal bidirectional translating multiplexer controlled by the I2C-bus from Texas Instruments. Only one SCL/SDA channel can be selected at a time, determined by the contents of the programmable control register. The board powers up with Channel 0 connected, allowing immediate communication between the Master and downstream devices on that channel.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cmux7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/i2c-mux-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the I2C MUX 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2C MUX 7 Click driver.

#### Standard key functions :

- `i2cmux7_cfg_setup` Config Object Initialization function.
```c
void i2cmux7_cfg_setup ( i2cmux7_cfg_t *cfg );
```

- `i2cmux7_init` Initialization function.
```c
err_t i2cmux7_init ( i2cmux7_t *ctx, i2cmux7_cfg_t *cfg );
```

- `i2cmux7_default_cfg` Click Default Configuration function.
```c
err_t i2cmux7_default_cfg ( i2cmux7_t *ctx );
```

#### Example key functions :

- `i2cmux7_set_channel` This function sets the desired channel active and configures its slave address.
```c
err_t i2cmux7_set_channel ( i2cmux7_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr );
```

- `i2cmux7_read_channel` This function reads the currently selected channel value.
```c
err_t i2cmux7_read_channel ( i2cmux7_t *ctx, uint8_t *ch_sel );
```

- `i2cmux7_generic_read` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
err_t i2cmux7_generic_read ( i2cmux7_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

## Example Description

> This example demonstrates the use of I2C MUX 7 click board by reading the
device ID of a 6DOF IMU 11 and Compass 3 click boards connected to the channels 0 and 7 respectfully.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cmux7_cfg_t i2cmux7_cfg;  /**< Click config object. */

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
    i2cmux7_cfg_setup( &i2cmux7_cfg );
    I2CMUX7_MAP_MIKROBUS( i2cmux7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cmux7_init( &i2cmux7, &i2cmux7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    i2cmux7_reset_device ( &i2cmux7 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the device ID of the connected click boards.
Channel 0 : 6DOF IMU 11 click [slave address: 0x0E; reg: 0x00; id: 0x2D],
Channel 7 : Compass 3 click   [slave address: 0x30; reg: 0x2F; id: 0x0C].
All data is being logged on the USB UART where you can check the device ID.

```c
void application_task ( void )
{
    uint8_t channel, device_id;
    if ( I2CMUX7_OK == i2cmux7_set_channel ( &i2cmux7, DEVICE0_POSITION, DEVICE0_SLAVE_ADDRESS ) )
    {
        if ( I2CMUX7_OK == i2cmux7_read_channel ( &i2cmux7, &channel ) )
        {
            log_printf( &logger, " --- Channel %u --- \r\n", ( uint16_t ) ( channel & I2CMUX7_CHANNEL_NUM_MASK ) );
        }
        if ( I2CMUX7_OK == i2cmux7_generic_read ( &i2cmux7, DEVICE0_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X \r\n\n", ( char * ) DEVICE0_NAME, ( uint16_t ) device_id );
        }
        Delay_ms ( 1000 );
    }
    if ( I2CMUX7_OK == i2cmux7_set_channel ( &i2cmux7, DEVICE1_POSITION, DEVICE1_SLAVE_ADDRESS ) )
    {
        if ( I2CMUX7_OK == i2cmux7_read_channel ( &i2cmux7, &channel ) )
        {
            log_printf( &logger, " --- Channel %u --- \r\n", ( uint16_t ) ( channel & I2CMUX7_CHANNEL_NUM_MASK ) );
        }
        if ( I2CMUX7_OK == i2cmux7_generic_read ( &i2cmux7, DEVICE1_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X \r\n\n", ( char * ) DEVICE1_NAME, ( uint16_t ) device_id );
        }
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CMUX7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
