
---
# IR Grid 5 Click

> [IR Grid 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6764) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6764&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the IR Grid 5 Click board by 
reading and displaying the sensor temperature as well as the 
object temperature image from the 32x24 pixel array.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGrid5

### Example Key Functions

- `irgrid5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void irgrid5_cfg_setup ( irgrid5_cfg_t *cfg );
```

- `irgrid5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t irgrid5_init ( irgrid5_t *ctx, irgrid5_cfg_t *cfg );
```

- `irgrid5_default_cfg` This function executes a default configuration of IR Grid 5 Click board.
```c
err_t irgrid5_default_cfg ( irgrid5_t *ctx );
```

- `irgrid5_get_device_id` This function reads the device ID from the IR Grid 5 EEPROM.
```c
err_t irgrid5_get_device_id ( irgrid5_t *ctx, uint16_t *device_id );
```

- `irgrid5_get_fw_version` This function reads the firmware version from the IR Grid 5 flash memory.
```c
err_t irgrid5_get_fw_version ( irgrid5_t *ctx, uint8_t *fw_ver );
```

- `irgrid5_get_measurement` This function reads object temperature image and sensor internal temperatures from the IR Grid 5 device.
```c
err_t irgrid5_get_measurement ( irgrid5_t *ctx, float *obj_image, float *sensor_temp );
```

### Application Init

> Initializes the log interface and the IR Grid 5 Click driver.
Reads and displays the device ID and firmware version.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid5_cfg_t irgrid5_cfg;  /**< Click config object. */

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
    irgrid5_cfg_setup( &irgrid5_cfg );
    IRGRID5_MAP_MIKROBUS( irgrid5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgrid5_init( &irgrid5, &irgrid5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGRID5_ERROR == irgrid5_default_cfg ( &irgrid5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint16_t device_id[ 4 ] = { 0 };
    if ( IRGRID5_OK == irgrid5_get_device_id ( &irgrid5, device_id ) )
    {
        log_printf ( &logger, " Device ID: %.4X%.4X%.4X%.4X\r\n", 
                     device_id[ 0 ], device_id[ 1 ], device_id[ 2 ], device_id[ 3 ] );
    }

    uint8_t fw_ver[ 3 ] = { 0 };
    if ( IRGRID5_OK == irgrid5_get_fw_version ( &irgrid5, fw_ver ) )
    {
        log_printf ( &logger, " FW version: %u.%u.%u\r\n", 
                     ( uint16_t ) fw_ver[ 0 ], ( uint16_t ) fw_ver[ 1 ], ( uint16_t ) fw_ver[ 2 ] );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the sensor internal temperature and the object temperature image 
from the pixel array and displays them on the USB UART terminal every 500ms.

```c
void application_task ( void )
{
    float sensor_temp = 0;
    float obj_image[ IRGRID5_NUM_PIXELS ] = { 0 };
    if ( IRGRID5_OK == irgrid5_get_measurement ( &irgrid5, obj_image, &sensor_temp ) )
    {
        log_printf( &logger, " Sensor temperature: %.1f degC\r\n", sensor_temp );
        log_printf( &logger, "--- Object temperature image ---\r\n" );
        for ( uint16_t pixel_cnt = 0; pixel_cnt < IRGRID5_NUM_PIXELS; pixel_cnt++ ) 
        {
            log_printf( &logger, "%.1f ", obj_image[ pixel_cnt ] );
            if ( 31 == ( pixel_cnt % 32 ) ) 
            {
                log_printf( &logger, "\r\n" );
            }
        }
        log_printf( &logger, "--------------------------------\r\n" );
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
