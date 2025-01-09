
---
# DIGI Isolator Click

> [DIGI Isolator Click](https://www.mikroe.com/?pid_product=MIKROE-5178) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5178&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : UART/SPI/ADC type

# Software Support

## Example Description

> This example demonstrates the use of the DIGI Isolator Click board 
> by reading and writing data by using SPI and UART serial interface 
> and reading results of AD conversion.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIIsolator

### Example Key Functions

- `digiisolator_cfg_setup` Config Object Initialization function.
```c
void digiisolator_cfg_setup ( digiisolator_cfg_t *cfg );
```

- `digiisolator_init` Initialization function.
```c
err_t digiisolator_init ( digiisolator_t *ctx, digiisolator_cfg_t *cfg );
```

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
