
---
# IR Sense 7 Click

> [IR Sense 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6993) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6993&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the IR Sense 7 Click board for
measuring ambient and object temperature using an infrared sensor.
The application reads sensor data from RAM and calculates temperature values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRSense7

### Example Key Functions

- `irsense7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void irsense7_cfg_setup ( irsense7_cfg_t *cfg );
```

- `irsense7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t irsense7_init ( irsense7_t *ctx, irsense7_cfg_t *cfg );
```

- `irsense7_default_cfg` This function executes a default configuration of IR Sense 7 Click board.
```c
err_t irsense7_default_cfg ( irsense7_t *ctx );
```

- `irsense7_read_ram` This function reads measurement data from RAM.
```c
err_t irsense7_read_ram ( irsense7_t *ctx );
```

- `irsense7_calculate_amb_temp` This function calculates the ambient temperature using RAM data and calibration constants.
```c
float irsense7_calculate_amb_temp ( irsense7_t *ctx );
```

- `irsense7_calculate_obj_temp` This function calculates the object temperature using RAM data, calibration constants, and iterative correction.
```c
float irsense7_calculate_obj_temp ( irsense7_t *ctx );
```

### Application Init

> Initializes the logger and IR Sense 7 Click driver, applies the default
configuration, and reads device identification and EEPROM data.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense7_cfg_t irsense7_cfg;  /**< Click config object. */

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
    irsense7_cfg_setup( &irsense7_cfg );
    IRSENSE7_MAP_MIKROBUS( irsense7_cfg, MIKROBUS_POSITION_IRSENSE7 );
    if ( I2C_MASTER_ERROR == irsense7_init( &irsense7, &irsense7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRSENSE7_ERROR == irsense7_default_cfg ( &irsense7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Unique ID: 0x%.4X%.4X%.4X\r\n", 
                irsense7.ee_data[ IRSENSE7_IDX_ID2 ], 
                irsense7.ee_data[ IRSENSE7_IDX_ID1 ], 
                irsense7.ee_data[ IRSENSE7_IDX_ID0 ] );
    log_printf( &logger, " Product Code: 0x%.4X\r\n", 
                irsense7.ee_data[ IRSENSE7_IDX_EE_PRODUCT_CODE ] );
    log_printf( &logger, " EEPROM Version: 0x%.4X\r\n", 
                irsense7.ee_data[ IRSENSE7_IDX_EE_VERSION ] );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads sensor data and calculates ambient and object
temperatures, then logs the results to the serial terminal.

```c
void application_task ( void )
{
    if ( IRSENSE7_OK == irsense7_read_ram ( &irsense7 ) )
    {
        log_printf ( &logger, " Ambient temp: %.2f\r\n", irsense7_calculate_amb_temp ( &irsense7 ) );
        log_printf ( &logger, " Object temp: %.2f\r\n\n", irsense7_calculate_obj_temp ( &irsense7 ) );
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
