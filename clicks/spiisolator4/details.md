
---
# SPI Isolator 4 Click

> SPI Isolator 4 Click is a compact add-on board that contains a digital isolator optimized for a serial peripheral interface. This board features the ADuM341E, a quad-channel 5kVRMS digital isolator from Analog Devices. This board features the ADuM341E, a quad-channel 5kVRMS digital isolator from Analog Devices. This isolation component provides outstanding performance by combining high speed, complementary metal-oxide-semiconductor (CMOS), and monolithic air core transformer technology. Its data channels are independent and available in various configurations with a withstand voltage rating of 5kVrms, and operate with the external supply voltage ranging from 2.25V to 5.5V, providing compatibility with lower voltage systems enabling voltage translation functionality across the isolation barrier.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spiisolator4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/spi-isolator-4-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the SPIIsolator4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SPIIsolator4 Click driver.

#### Standard key functions :

- `spiisolator4_cfg_setup` Config Object Initialization function.
```c
void spiisolator4_cfg_setup ( spiisolator4_cfg_t *cfg );
```

- `spiisolator4_init` Initialization function.
```c
err_t spiisolator4_init ( spiisolator4_t *ctx, spiisolator4_cfg_t *cfg );
```

- `spiisolator4_default_cfg` Click Default Configuration function.
```c
err_t spiisolator4_default_cfg ( spiisolator4_t *ctx );
```

#### Example key functions :

- `spiisolator4_generic_write` SPI Isolator 4 data writing function.
```c
err_t spiisolator4_generic_write ( spiisolator4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
```

- `spiisolator4_generic_read` SPI Isolator 4 data reading function.
```c
err_t spiisolator4_generic_read ( spiisolator4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

```

- `spiisolator4_set_enable` SPI Isolator 4 enable isolator function.
```c
err_t spiisolator4_set_enable ( spiisolator4_t *ctx, spiisolator4_enable_mode_t en_mode );
```

## Example Description

> This library contains API for the SPI Isolator 4 Click driver.
> This demo application shows an example of an SPI Isolator 4 Click wired 
> to the nvSRAM 4 Click for reading Device ID.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    spiisolator4_cfg_t spiisolator4_cfg;  /**< Click config object. */

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

    spiisolator4_cfg_setup( &spiisolator4_cfg );
    SPIISOLATOR4_MAP_MIKROBUS( spiisolator4_cfg, MIKROBUS_1 );
    err_t init_flag  = spiisolator4_init( &spiisolator4, &spiisolator4_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    spiisolator4_default_cfg ( &spiisolator4 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" ); 
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of an SPI Isolator 4 Click board™.
> Logs Device ID of the nvSRAM 4 Click wired to the SPI Isolator 4 board™.  
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    get_device_id( );
    log_printf( &logger, "  Device ID : 0x%.8LX\r\n", device_id ); 
    log_printf( &logger, "--------------------------\r\n" ); 
    Delay_ms ( 1000 );
}

```

## Additional Function
- `get_device_id` SPI Isolator 4 get device ID function.
```c
static void get_device_id ( void );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
