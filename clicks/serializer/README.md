
---
# Serializer Click

> [Serializer Click](https://www.mikroe.com/?pid_product=MIKROE-4925) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4925&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of a Serializer Click board by reading the state of all inputs and displaying the results on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Serializer

### Example Key Functions

- `serializer_cfg_setup` Config Object Initialization function.
```c
void serializer_cfg_setup ( serializer_cfg_t *cfg );
```

- `serializer_init` Initialization function.
```c
err_t serializer_init ( serializer_t *ctx, serializer_cfg_t *cfg );
```

- `serializer_get_flt_pin` This function returns the fault pin logic state.
```c
uint8_t serializer_get_flt_pin ( serializer_t *ctx );
```

- `serializer_read_input` This function reads the input data by using SPI serial interface, and then checks the data integrity by verifying the CRC byte.
```c
err_t serializer_read_input ( serializer_t *ctx, uint8_t *data_out );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    serializer_cfg_t serializer_cfg;  /**< Click config object. */

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
    serializer_cfg_setup( &serializer_cfg );
    SERIALIZER_MAP_MIKROBUS( serializer_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == serializer_init( &serializer, &serializer_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the state of all inputs and displays the results on the USB UART approximately once per second. Also, if there's any fault indication detected, it will be displayed accordingly.

```c
void application_task ( void )
{
    uint8_t input_data = 0;
    err_t status = serializer_read_input ( &serializer, &input_data );
    
    if ( SERIALIZER_ERROR != status )
    {
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )
        {
            log_printf( &logger, " IN%u: %s\r\n", ( uint16_t ) cnt + 1, 
                                                  ( char * ) ( ( input_data & ( 1 << cnt ) ) ? "High" : "Low" ) );
        }
        if ( status & SERIALIZER_STATUS_UNDERVOLTAGE )
        {
            log_info( &logger, "Undervoltage fault" );
        }
        if ( status & SERIALIZER_STATUS_OVERTEMPERATURE )
        {
            log_info( &logger, "Overtemperature fault" );
        }
        log_printf( &logger, "\r\n" );
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
