
---
# LightRanger 12 Click

> [LightRanger 12 Click](https://www.mikroe.com/?pid_product=MIKROE-6465) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6465&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of LightRanger 12 Click board by reading and displaying 8x8 zones measurements on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger12

### Example Key Functions

- `lightranger12_cfg_setup` Config Object Initialization function.
```c
void lightranger12_cfg_setup ( lightranger12_cfg_t *cfg );
```

- `lightranger12_init` Initialization function.
```c
err_t lightranger12_init ( lightranger12_t *ctx, lightranger12_cfg_t *cfg );
```

- `lightranger12_default_cfg` Click Default Configuration function.
```c
err_t lightranger12_default_cfg ( lightranger12_t *ctx );
```

- `lightranger12_get_int_pin` This function returns the INT (interrupt) pin logic state.
```c
uint8_t lightranger12_get_int_pin ( lightranger12_t *ctx );
```

- `lightranger12_get_resolution` This function gets the current resolution (4x4 or 8x8).
```c
err_t lightranger12_get_resolution ( lightranger12_t *ctx, uint8_t *resolution );
```

- `lightranger12_get_ranging_data` This function gets the ranging data, using the selected output and the resolution.
```c
err_t lightranger12_get_ranging_data ( lightranger12_t *ctx, lightranger12_results_data_t *results );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger12_cfg_t lightranger12_cfg;  /**< Click config object. */

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
    lightranger12_cfg_setup( &lightranger12_cfg );
    LIGHTRANGER12_MAP_MIKROBUS( lightranger12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger12_init( &lightranger12, &lightranger12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER12_ERROR == lightranger12_default_cfg ( &lightranger12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads all zone measurements approximately every 200ms and logs them to the USB UART as an 8x8 map.
The silicon temperature measurement in degrees Celsius is also displayed.

```c
void application_task ( void )
{
    err_t error_flag = LIGHTRANGER12_OK;
    lightranger12_results_data_t results;
    uint8_t resolution = 0;
    uint8_t map_side = 0;

    // Wait for a data ready interrupt
    while ( lightranger12_get_int_pin ( &lightranger12 ) );

    error_flag |= lightranger12_get_resolution ( &lightranger12, &resolution );
    error_flag |= lightranger12_get_ranging_data ( &lightranger12, &results );
    if ( LIGHTRANGER12_OK == error_flag )
    {
        map_side = ( LIGHTRANGER12_RESOLUTION_4X4 == resolution ) ? 4 : 8;
        log_printf ( &logger, "----------------------- %ux%u MAP (mm) -----------------------\r\n", 
                    ( uint16_t ) map_side, ( uint16_t ) map_side );
        for ( uint8_t cnt_0 = 1; cnt_0 <= map_side; cnt_0++ )
        {
            for ( uint8_t cnt_1 = 1; cnt_1 <= map_side; cnt_1++ )
            {
                // Checking the zone measurement validity (5 & 9 means ranging OK)
                if ( ( 5 == results.target_status[ cnt_0 * map_side - cnt_1 ] ) ||
                     ( 9 == results.target_status[ cnt_0 * map_side - cnt_1 ] ) )
                {
                    log_printf ( &logger, "%d\t", results.distance_mm[ cnt_0 * map_side - cnt_1 ] );
                }
                else
                {
                    log_printf ( &logger, "NOK\t" );
                }
            }
            log_printf ( &logger, "\r\n" );
            Delay_ms ( 5 );
        }
        log_printf ( &logger, "Silicon temperature : %d degC\r\n", ( int16_t ) results.silicon_temp_degc );
        log_printf ( &logger, "------------------------------------------------------------\r\n\n" );
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
