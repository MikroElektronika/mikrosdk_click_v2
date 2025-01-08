
---
# PIR 3 Click

> [PIR 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6290) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6290&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PIR 3 Click board by reading and displaying the peak hold tracking data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PIR3

### Example Key Functions

- `pir3_cfg_setup` Config Object Initialization function.
```c
void pir3_cfg_setup ( pir3_cfg_t *cfg );
```

- `pir3_init` Initialization function.
```c
err_t pir3_init ( pir3_t *ctx, pir3_cfg_t *cfg );
```

- `pir3_default_cfg` Click Default Configuration function.
```c
err_t pir3_default_cfg ( pir3_t *ctx );
```

- `pir3_set_detection_level` This function sets the detection threshold level in the ctx->config structure.
```c
void pir3_set_detection_level ( pir3_t *ctx, uint8_t detlvl );
```

- `pir3_write_config` This function writes a config structure to the sensor by using I2C serial interface.
```c
err_t pir3_write_config ( pir3_t *ctx );
```

- `pir3_read_peak_hold` This function reads a 12-bit signed peak hold data by using I2C serial interface.
```c
err_t pir3_read_peak_hold ( pir3_t *ctx, int16_t *peak_hold );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pir3_cfg_t pir3_cfg;  /**< Click config object. */

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
    pir3_cfg_setup( &pir3_cfg );
    PIR3_MAP_MIKROBUS( pir3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pir3_init( &pir3, &pir3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIR3_ERROR == pir3_default_cfg ( &pir3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the peak hold tracking data every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    int16_t peak_hold = 0;
    if ( PIR3_OK == pir3_read_peak_hold ( &pir3, &peak_hold ) )
    {
        log_printf( &logger, " PEAK HOLD: %d\r\n\n", peak_hold );
        Delay_ms ( 100 );
    }
}
```

### Note

> In order to establish communication with the sensor, some of the supported MCUs may require
the I2C lines to be pulled up additionally either with the external or internal weak pull-up resistor.

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
