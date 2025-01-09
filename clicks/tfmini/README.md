
---
# TFmini Click

> [TFmini Click](https://www.mikroe.com/?pid_product=MIKROE-4974) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4974&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of TFmini Click board by reading the measurements from the attached TFmini-S or TFmini Plus sensors.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TFmini

### Example Key Functions

- `tfmini_cfg_setup` Config Object Initialization function.
```c
void tfmini_cfg_setup ( tfmini_cfg_t *cfg );
```

- `tfmini_init` Initialization function.
```c
err_t tfmini_init ( tfmini_t *ctx, tfmini_cfg_t *cfg );
```

- `tfmini_default_cfg` Click Default Configuration function.
```c
err_t tfmini_default_cfg ( tfmini_t *ctx );
```

- `tfmini_get_firmware_version` This function reads the sensor firmware version.
```c
err_t tfmini_get_firmware_version ( tfmini_t *ctx, uint32_t *fw_version );
```

- `tfmini_get_measurement` This function reads the output data frame and obtains the distance, strength and temperature values from it.
```c
err_t tfmini_get_measurement ( tfmini_t *ctx, int16_t *distance, int16_t *strength, float *temperature );
```

- `tfmini_send_frame` This function sends a command frame to the sensor.
```c
err_t tfmini_send_frame ( tfmini_t *ctx, tfmini_frame_t frame );
```

### Application Init

> Initializes the driver and the Click board, and reads the firmware version of the attached sensor.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    tfmini_cfg_t tfmini_cfg;  /**< Click config object. */

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
    tfmini_cfg_setup( &tfmini_cfg );
    TFMINI_MAP_MIKROBUS( tfmini_cfg, MIKROBUS_1 );
    tfmini_drv_interface_selection ( &tfmini_cfg, TFMINI_DRV_SEL_UART );
    if ( TFMINI_OK != tfmini_init( &tfmini, &tfmini_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TFMINI_OK != tfmini_default_cfg ( &tfmini ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t fw_version = 0;
    if ( TFMINI_OK == tfmini_get_firmware_version ( &tfmini, &fw_version ) )
    {
        log_printf( &logger, " FW Version: 0x%.6LX\r\n", fw_version );
    }
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the target distance, signal strength and the internal sensor temperature every 100ms approximately, and displays the results on the USB UART.

```c
void application_task ( void )
{
    int16_t distance = 0, strength = 0;
    float temperature = 0;
    if ( TFMINI_OK == tfmini_get_measurement ( &tfmini, &distance, &strength, &temperature ) ) 
    {
        log_printf( &logger, " Target distance: %d cm\r\n", distance );
        log_printf( &logger, " Signal strength: %d\r\n", strength );
        log_printf( &logger, " Sensor temperature: %.2f C\r\n\n", temperature );
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
