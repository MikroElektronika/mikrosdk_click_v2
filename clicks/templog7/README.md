
---
# Temp-Log 7 Click

> [Temp-Log 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5598) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5598&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : One Wire type

# Software Support

## Example Description

> This example demonstrates the use of Temp-Log 7 Click board by reading the temperature in Celsius,
then writing the specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog7

### Example Key Functions

- `templog7_cfg_setup` Config Object Initialization function.
```c
void templog7_cfg_setup ( templog7_cfg_t *cfg );
```

- `templog7_init` Initialization function.
```c
err_t templog7_init ( templog7_t *ctx, templog7_cfg_t *cfg );
```

- `templog7_default_cfg` Click Default Configuration function.
```c
err_t templog7_default_cfg ( templog7_t *ctx );
```

- `templog7_read_temperature` This function starts the one shot measurement and reads the temperature value in Celsius.
```c
err_t templog7_read_temperature ( templog7_t *ctx, float *temperature );
```

- `templog7_write_eeprom` This function writes a desired number of data bytes to the EEPROM memory.
```c
err_t templog7_write_eeprom ( templog7_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len );
```

- `templog7_read_eeprom` This function reads a desired number of data bytes from the EEPROM memory.
```c
err_t templog7_read_eeprom ( templog7_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration which
clears the EEPROM memory, sets the temperature resolution to 16-bit, enables
alert interrupt and sets the temperature alerts to 5 degrees Celsius for low
and 40 degrees for high level. Other three IO pins are configured as INPUT.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    templog7_cfg_t templog7_cfg;  /**< Click config object. */

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
    templog7_cfg_setup( &templog7_cfg );
    TEMPLOG7_MAP_MIKROBUS( templog7_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == templog7_init( &templog7, &templog7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPLOG7_ERROR == templog7_default_cfg ( &templog7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature in degrees Celsius and the gpio state. After that writes
a desired number of bytes to the memory and then verifies if it is written
correctly by reading from the same memory location and displaying the memory
content. All data is displayed on the USB UART where you can track changes.

```c
void application_task ( void )
{
    uint8_t eeprom_data[ 64 ] = { 0 };
    uint8_t gpio_state = 0;
    float temperature = 0;
    if ( TEMPLOG7_OK == templog7_read_temperature ( &templog7, &temperature ) )
    {
        log_printf( &logger, "\r\n Temperature: %.2f C\r\n", temperature );
    }
    if ( TEMPLOG7_OK == templog7_read_gpio ( &templog7, &gpio_state ) )
    {
        log_printf( &logger, " GPIO state: 0x%.2X\r\n", ( uint16_t ) gpio_state );
    }
    if ( TEMPLOG7_OK == templog7_write_eeprom ( &templog7, STARTING_ADDRESS, DEMO_TEXT_MESSAGE, 
                                                    sizeof ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " EEPROM write: %s\r\n", ( uint8_t * ) DEMO_TEXT_MESSAGE );
    }
    if ( TEMPLOG7_OK == templog7_read_eeprom ( &templog7, STARTING_ADDRESS, eeprom_data, 
                                                   sizeof ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " EEPROM read: %s\r\n", eeprom_data );
    }
    if ( !templog7_get_alert_pin ( &templog7 ) )
    {
        log_info( &logger, " ALERT detected " );
    }
    Delay_ms ( 1000 );
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
