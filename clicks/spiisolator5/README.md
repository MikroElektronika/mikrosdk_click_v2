\mainpage Main Page

---
# SPI Isolator 5 Click

> SPI Isolator 5 Click is a compact add-on board with a digital isolator optimized for a serial peripheral interface. This board features the DCL541A01, a high-speed quad-channel digital isolator from Toshiba Semiconductor. Outstanding performance characteristics of the DCL541A01 are achieved by Toshiba CMOS technology and the magnetic coupling structure. In addition, they comply with UL 1577 safety-related certification, have a withstand voltage rating of 5kVrms, and operate with the external supply voltage ranging from 2.25V to 5.5V, providing compatibility with lower voltage systems enabling voltage translation functionality across the isolation barrier.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spiisolator5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/spi-isolator-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the SPI Isolator 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SPI Isolator 5 Click driver.

#### Standard key functions :

- `spiisolator5_cfg_setup` Config Object Initialization function.
```c
void spiisolator5_cfg_setup ( spiisolator5_cfg_t *cfg );
```

- `spiisolator5_init` Initialization function.
```c
err_t spiisolator5_init ( spiisolator5_t *ctx, spiisolator5_cfg_t *cfg );
```

#### Example key functions :

- `spiisolator5_write` SPI Isolator 5 data writing function.
```c
err_t spiisolator5_write ( spiisolator5_t *ctx, uint8_t *data_in, uint8_t len ) 
```

- `spiisolator5_read` SPI Isolator 5 data reading function.
```c
err_t spiisolator5_read ( spiisolator5_t *ctx, uint8_t *data_out, uint8_t len_out ) 
```

- `spiisolator5_transfer` SPI Isolator 5 transfer function.
```c
err_t spiisolator5_transfer ( spiisolator5_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len )
```

## Example Description

> This example demonstrates the use of SPI Isolator 5 Click board 
> by reading the manufacturer ID and device ID 
> of the connected Flash 11 Click board.

**The demo application is composed of two sections :**

### Application Init

> The initialization of SPI module, log UART, and additional pins.
> After the driver init, the app performs enabling a device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator5_cfg_t spiisolator5_cfg;  /**< Click config object. */

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
    spiisolator5_cfg_setup( &spiisolator5_cfg );
    SPIISOLATOR5_MAP_MIKROBUS( spiisolator5_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator5_init( &spiisolator5, &spiisolator5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    spiisolator5_enable( &spiisolator5 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and checks the manufacturer ID and 
> device ID of the connected Flash 11 Click board. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t cmd_get_id[ 6 ] = { FLASH11_CMD_GET_ID };
    static uint8_t read_id[ 6 ] = { 0 };
    if ( SPIISOLATOR5_OK == spiisolator5_transfer( &spiisolator5, &cmd_get_id[ 0 ], &read_id[ 0 ], 6 ) )
    {
        if ( ( FLASH11_MANUFACTURER_ID == read_id[ 4 ] ) && ( FLASH11_DEVICE_ID == read_id[ 5 ] ) )
        {
            log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) read_id[ 4 ] );
            log_printf( &logger, " Device ID: 0x%.2X    \r\n", ( uint16_t ) read_id[ 5 ] );
            log_printf( &logger, " -----------------------\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
