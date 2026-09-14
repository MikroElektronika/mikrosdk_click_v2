
---
# HOD CAP 2 Click

> [HOD CAP 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6926) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6926&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the HOD CAP 2 Click board for
reading capacitive sensor measurements from four sensing channels and
one reference channel. The application also displays the device unique ID.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HODCAP2

### Example Key Functions

- `hodcap2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void hodcap2_cfg_setup ( hodcap2_cfg_t *cfg );
```

- `hodcap2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t hodcap2_init ( hodcap2_t *ctx, hodcap2_cfg_t *cfg );
```

- `hodcap2_default_cfg` This function executes a default configuration of HOD CAP 2 Click board.
```c
err_t hodcap2_default_cfg ( hodcap2_t *ctx );
```

- `hodcap2_read_measurement` This function performs a single measurement on the selected table, stops the measurement process, and reads the result register value.
```c
err_t hodcap2_read_measurement ( hodcap2_t *ctx, uint8_t table, uint16_t *data_out );
```

### Application Init

> Initializes the logger and HOD CAP 2 Click driver, applies the default configuration, and reads the device unique ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hodcap2_cfg_t hodcap2_cfg;  /**< Click config object. */

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
    hodcap2_cfg_setup( &hodcap2_cfg );
    HODCAP2_MAP_MIKROBUS( hodcap2_cfg, MIKROBUS_POSITION_HODCAP2 );
    if ( SPI_MASTER_ERROR == hodcap2_init( &hodcap2, &hodcap2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HODCAP2_ERROR == hodcap2_default_cfg ( &hodcap2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf ( &logger, " Unique ID: 0x%.4X%.4X%.4X\r\n", 
                 hodcap2.unique_id[ 0 ], hodcap2.unique_id[ 1 ], hodcap2.unique_id[ 2 ] );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads measurement data from all four sensor channels and the reference channel and logs the results to the serial terminal.

```c
void application_task ( void )
{
    uint16_t sen0 = 0;
    uint16_t sen1 = 0;
    uint16_t sen2 = 0;
    uint16_t sen3 = 0;
    uint16_t ref_data = 0;

    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_1, &sen0 ) )
    {
        log_printf ( &logger, " SEN0: %u\r\n", sen0 );
    }
    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_2, &sen1 ) )
    {
        log_printf ( &logger, " SEN1: %u\r\n", sen1 );
    }
    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_3, &sen2 ) )
    {
        log_printf ( &logger, " SEN2: %u\r\n", sen2 );
    }
    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_4, &sen3 ) )
    {
        log_printf ( &logger, " SEN3: %u\r\n", sen3 );
    }
    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_5, &ref_data ) )
    {
        log_printf ( &logger, " REF: %u\r\n\n", ref_data );
    }

    Delay_ms ( 500 );
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
