
---
# LightRanger 14 Click

> [LightRanger 14 Click](https://www.mikroe.com/?pid_product=MIKROE-6747) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6747&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2025.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the LightRanger 14 Click board by
initializing the device, loading the firmware and configuration, and then 
reading and displaying distance measurement results. Each measurement frame 
contains distance data (in millimeters) and a confidence value. Data is displayed
only if confidence exceeds a threshold, otherwise it is marked as invalid. 
The example also logs the device information such as firmware version, chip version, 
and serial number.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger14

### Example Key Functions

- `lightranger14_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void lightranger14_cfg_setup ( lightranger14_cfg_t *cfg );
```

- `lightranger14_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t lightranger14_init ( lightranger14_t *ctx, lightranger14_cfg_t *cfg );
```

- `lightranger14_default_cfg` This function executes a default configuration of LightRanger 14 Click board.
```c
err_t lightranger14_default_cfg ( lightranger14_t *ctx );
```

- `lightranger14_start_measurement` This function starts measurement by writing the measure command to the command register.
```c
err_t lightranger14_start_measurement ( lightranger14_t *ctx );
```

- `lightranger14_read_results` This function reads the measurement results frame including header, payload, and footer.
```c
err_t lightranger14_read_results ( lightranger14_t *ctx, uint8_t *frame_data, uint16_t len );
```

- `lightranger14_stop_measurement` This function stops measurement by writing the stop command to the command register.
```c
err_t lightranger14_stop_measurement ( lightranger14_t *ctx );
```

### Application Init

> Initializes the log interface, sets up the LightRanger 14 Click driver,
loads the default configuration for 8x8 measurement map, and prints device information.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger14_cfg_t lightranger14_cfg;  /**< Click config object. */

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
    lightranger14_cfg_setup( &lightranger14_cfg );
    LIGHTRANGER14_MAP_MIKROBUS( lightranger14_cfg, MIKROBUS_1 );
    err_t init_flag = lightranger14_init( &lightranger14, &lightranger14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER14_OK != lightranger14_default_cfg ( &lightranger14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf ( &logger, " Firmware Application Version: %u.%u.%u.%u\r\n", 
                 ( uint16_t ) lightranger14.info.app_ver[ 0 ],
                 ( uint16_t ) lightranger14.info.app_ver[ 1 ],
                 ( uint16_t ) lightranger14.info.app_ver[ 2 ],
                 ( uint16_t ) lightranger14.info.app_ver[ 3 ] );
    log_printf ( &logger, " Chip Version: %u.%u\r\n", 
                 ( uint16_t ) lightranger14.info.chip_ver[ 0 ],
                 ( uint16_t ) lightranger14.info.chip_ver[ 1 ] );
    log_printf ( &logger, " Serial Number: 0x%.8LX\r\n", lightranger14.info.serial_num );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready interrupt, clears the interrupt flags, and then 
reads and logs the distance frame results with confidence filtering. 
The chip temperature and status flags are also displayed.

```c
void application_task ( void )
{
    uint8_t frame_data[ LIGHTRANGER14_FRAME_PAYLOAD_SIZE ] = { 0 };

    // Wait for data ready interrupt
    while ( lightranger14_get_int_pin ( &lightranger14 ) );
    
    if ( LIGHTRANGER14_OK == lightranger14_clear_interrupts ( &lightranger14 ) )
    {
        if ( LIGHTRANGER14_OK == lightranger14_read_results ( &lightranger14, frame_data, sizeof ( frame_data ) ) )
        {
            lightranger14_log_results ( &lightranger14 );
        }
        else
        {
            log_error( &logger, " Read results." );
        }
    }
    else
    {
        log_error( &logger, " Clear interrupts." );
    }
}
```

### Note

> Measurement data updates approximately every 500 ms.
Refer to LIGHTRANGER14_DEFAULT_LOAD_CONFIG and LIGHTRANGER14_MAP_x macros
to set the measurement zone map to 8x8 (default), 16x16, 32x32, or 48x32.

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
