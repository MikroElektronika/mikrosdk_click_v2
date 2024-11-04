\mainpage Main Page

---
# FTDI Click

> FTDI Click is a compact add-on board that provides a high-speed USB to a serial interface converter. This board features the FT2232H, a 5th-generation high-speed USB 2.0 to a serial UART/I2C/SPI interface converter from FTDI. The entire USB protocol is handled on the chip (FTDI USB drivers required), making this board ideal for various USB applications. Besides a selectable interface and a standalone operation possibility, it also includes an EEPROM which contains the USB configuration descriptors for the FT2232H and one DA converter for additional reference in user-configurable applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ftdi_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ftdi-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : UART type


# Software Support

We provide a library for the FTDI Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for FTDI Click driver.

#### Standard key functions :

- `ftdi_cfg_setup` Config Object Initialization function.
```c
void ftdi_cfg_setup ( ftdi_cfg_t *cfg );
```

- `ftdi_init` Initialization function.
```c
err_t ftdi_init ( ftdi_t *ctx, ftdi_cfg_t *cfg );
```

#### Example key functions :

- `ftdi_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t ftdi_generic_write ( ftdi_t *ctx, uint8_t *data_in, uint16_t len );
```

- `ftdi_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t ftdi_generic_read ( ftdi_t *ctx, uint8_t *data_out, uint16_t len );
```

## Example Description

> This example demonstrates the use of FTDI Click by echoing back all the received messages.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ftdi_cfg_t ftdi_cfg;  /**< Click config object. */

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
    ftdi_cfg_setup( &ftdi_cfg );
    FTDI_MAP_MIKROBUS( ftdi_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ftdi_init( &ftdi, &ftdi_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Any data which the host PC sends to the Virtual COM Port (for example, typed into the terminal 
window in UART Terminal) will be sent over USB to the Click board and then it will be read and 
echoed back by the MCU to the PC where the terminal program will display it. The data will also
be displayed on the USB UART.

```c
void application_task ( void )
{
    uint8_t rx_data = 0;
    if ( ftdi_generic_read ( &ftdi, &rx_data, 1 ) > 0 )
    {
        ftdi_generic_write ( &ftdi, &rx_data, 1 );
        log_printf( &logger, "%c", rx_data );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.FTDI

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
