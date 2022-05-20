
---
# USB to I2C 2 click

> USB to I2C 2 Click is a compact add-on board that contains a general-purpose USB to I2C serial interface. This board features the FT201X, a full-speed USB to I2C protocol converter from FTDI. The FT201X converts USB2.0 full-speed to an I2C serial interface capable of operating up to 3.4MBit/s, with low power consumption (typical 8mA). The entire USB protocol is handled on the chip itself, where no USB-specific firmware programming is required. It also has a fully-integrated 2048 byte Multi-Time-Programmable (MTP) memory for storing device descriptors and CBUS I/O user-desirable configuration. This Click board™ includes the complete FT-X series feature set and enables USB to be added into a system design quickly and easily over an I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbtoi2c2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-to-i2c-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the USB to I2C 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USB to I2C 2 Click driver.

#### Standard key functions :

- `usbtoi2c2_cfg_setup` Config Object Initialization function.
```c
void usbtoi2c2_cfg_setup ( usbtoi2c2_cfg_t *cfg );
```

- `usbtoi2c2_init` Initialization function.
```c
err_t usbtoi2c2_init ( usbtoi2c2_t *ctx, usbtoi2c2_cfg_t *cfg );
```

- `usbtoi2c2_default_cfg` Click Default Configuration function.
```c
err_t usbtoi2c2_default_cfg ( usbtoi2c2_t *ctx );
```

#### Example key functions :

- `usbtoi2c2_write_data` This function writes a desired number of data bytes by using I2C serial interface.
```c
err_t usbtoi2c2_write_data ( usbtoi2c2_t *ctx, uint8_t *tx_buf, uint8_t tx_len );
```

- `usbtoi2c2_read_data` This function reads a desired number of data bytes by using I2C serial interface.
```c
err_t usbtoi2c2_read_data ( usbtoi2c2_t *ctx, uint8_t *rx_buf, uint8_t rx_len );
```

- `usbtoi2c2_reset_device` This function resets the device by toggling the RST pin state.
```c
void usbtoi2c2_reset_device ( usbtoi2c2_t *ctx );
```

## Example Description

> This example demonstrates the use of USB to I2C 2 click by echoing back all the received messages.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbtoi2c2_cfg_t usbtoi2c2_cfg;  /**< Click config object. */

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
    usbtoi2c2_cfg_setup( &usbtoi2c2_cfg );
    USBTOI2C2_MAP_MIKROBUS( usbtoi2c2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == usbtoi2c2_init( &usbtoi2c2, &usbtoi2c2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBTOI2C2_ERROR == usbtoi2c2_default_cfg ( &usbtoi2c2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Any data which the host PC sends to the Virtual COM Port (for example, typed into the terminal 
window in UART Terminal) will be sent over USB to the click board and then it will be read and 
echoed back by the MCU to the PC where the terminal program will display it.

```c
void application_task ( void )
{
    uint8_t rx_data = 0;
    if ( USBTOI2C2_OK == usbtoi2c2_read_data ( &usbtoi2c2, &rx_data, 1 ) )
    {
        if ( USBTOI2C2_OK == usbtoi2c2_write_data ( &usbtoi2c2, &rx_data, 1 ) )
        {
            log_printf( &logger, "%c", rx_data );
        }
    }
}
```

## Note

> Make sure to download and install appropriate VCP drivers on the host PC.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBtoI2C2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
