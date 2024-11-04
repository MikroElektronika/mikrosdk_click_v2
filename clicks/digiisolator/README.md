\mainpage Main Page

---
# DIGI Isolator Click

> DIGI Isolator Click is a compact add-on board that provides electrical isolation 
> and signal conditioning for the serial peripheral interface and a UART interface. 
> This board features two DCL540C01, high-speed, quad-channel digital isolators from Toshiba Semiconductor. 
> Depending on the usage, this CMOS isolator can achieve data rates of up to 150Mbps, 
> while withstanding up to 5kVrms voltage. DIGI Isolator Click is designed to isolate two additional IO pins 
> besides SPI and UART interfaces.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digiisolator_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/digi-isolator-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : UART/SPI/ADC type


# Software Support

We provide a library for the DIGI Isolator Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI Isolator Click driver.

#### Standard key functions :

- `digiisolator_cfg_setup` Config Object Initialization function.
```c
void digiisolator_cfg_setup ( digiisolator_cfg_t *cfg );
```

- `digiisolator_init` Initialization function.
```c
err_t digiisolator_init ( digiisolator_t *ctx, digiisolator_cfg_t *cfg );
```

#### Example key functions :

- `digiisolator_spi_transfer` DIGI Isolator SPI transfer function.
```c
err_t digiisolator_spi_transfer ( digiisolator_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len );
```

- `digiisolator_uart_write` DIGI Isolator UART data writing function.
```c
err_t digiisolator_uart_write ( digiisolator_t *ctx, char *data_in, uint16_t len );
```

- `digiisolator_get_d1_pin_voltage` DIGI Isolator read D1 pin voltage level function.
```c
err_t digiisolator_get_d1_pin_voltage ( digiisolator_t *ctx, float *data_out );
```

## Example Description

> This example demonstrates the use of the DIGI Isolator Click board 
> by reading and writing data by using SPI and UART serial interface 
> and reading results of AD conversion.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI, UART and ADC module and log UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiisolator_cfg_t digiisolator_cfg;  /**< Click config object. */

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
    digiisolator_cfg_setup( &digiisolator_cfg );
    DIGIISOLATOR_MAP_MIKROBUS( digiisolator_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == digiisolator_init( &digiisolator, &digiisolator_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> At the start, the demo application reads and checks the manufacturer ID and 
> device ID of the connected Flash 11 Click board by using SPI serial interface. 
> After that, sends a "MikroE" message, reads the received data, 
> and parses it by using UART serial interface in loopback mode. 
> And finally, the demo app reads the results of the AD conversion of the D1 (AN) pin. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t cmd_get_id[ 6 ] = { FLASH11_CMD_GET_ID };
    static uint8_t read_id[ 6 ] = { 0 };
    static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    static float voltage = 0;
    
    if ( DIGIISOLATOR_OK == digiisolator_spi_transfer( &digiisolator, &cmd_get_id[ 0 ], &read_id[ 0 ], 6 ) )
    {
        if ( ( FLASH11_MANUFACTURER_ID == read_id[ 4 ] ) && ( FLASH11_DEVICE_ID == read_id[ 5 ] ) )
        {
            log_printf( &logger, " SPI\r\n" );
            log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) read_id[ 4 ] );
            log_printf( &logger, " Device ID: 0x%.2X    \r\n", ( uint16_t ) read_id[ 5 ] );
            log_printf( &logger, " -----------------------\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
    
    if ( 0 < digiisolator_uart_write( &digiisolator, DEMO_MESSAGE, strlen( DEMO_MESSAGE ) ) )
    {
        if ( 0 < digiisolator_uart_read( &digiisolator, app_buf, strlen( DEMO_MESSAGE ) ) )
        {
            log_printf( &logger, " UART\r\n" );
            log_printf( &logger, "%s", app_buf );
            memset( app_buf, 0, PROCESS_BUFFER_SIZE );
            log_printf( &logger, " -----------------------\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
    
    if ( DIGIISOLATOR_OK == digiisolator_get_d1_pin_voltage ( &digiisolator, &voltage ) ) 
    {
        log_printf( &logger, " ADC\r\n" );
        log_printf( &logger, " Voltage : %.3f[V]\r\n", voltage );
        log_printf( &logger, " -----------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIIsolator

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
