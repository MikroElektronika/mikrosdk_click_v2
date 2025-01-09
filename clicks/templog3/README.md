
---
# Temp-Log 3 Click

> [Temp-Log 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3326) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3326&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog3

### Example Key Functions

- `templog3_cfg_setup` Config Object Initialization function. 
```c
void templog3_cfg_setup ( templog3_cfg_t *cfg );
``` 
 
- `templog3_init` Initialization function. 
```c
err_t templog3_init ( templog3_t *ctx, templog3_cfg_t *cfg );
```

- `templog3_default_cfg` Click Default Configuration function. 
```c
void templog3_default_cfg ( templog3_t *ctx );
```

- `templog3_set_temp` Set Temperature function. 
```c
uint8_t templog3_set_temp ( templog3_t *ctx, uint8_t temp_sel, float temp_in );
```
 
- `templog3_eeprom_byte_write` EEPROM Single Write function. 
```c
void templog3_eeprom_byte_write ( templog3_t *ctx, uint8_t reg_addr, uint8_t data_in, uint8_t eeprom_mode );
```

- `templog3_eeprom_sequential_read` EEPROM Sequential Read function. 
```c
uint8_t templog3_eeprom_sequential_read ( templog3_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint16_t num_bytes );
```

### Application Init

> Initializes I2C interface and performs a device default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    templog3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    templog3_cfg_setup( &cfg );
    TEMPLOG3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog3_init( &templog3, &cfg );

    Delay_ms ( 500 );
    
    templog3_default_cfg( &templog3 );
    
    Delay_ms ( 200 );

    log_printf( &logger, "** Temp-Log 3 Click is initialized ** \r\n" );
}
```

### Application Task

> First ensures that the minimum conversion time is met, and then reads the
> ambient temperature calculated to the Celsius degrees, and logs the results to the USB UART.

```c
void application_task ( void )
{
    float temperature;
    uint8_t ret_status;

    templog3_wait_conv_done( &templog3 );

    ret_status = templog3_get_temp( &templog3, TEMPLOG3_TEMP_AMBIENT_REG, &temperature );

    log_printf( &logger, "**  Ambient temperature is : %.2f C  **\r\n", temperature );
    
    check_limit_status( ret_status );
    
    Delay_ms ( 300 );
}
```

### Note

> The temperature range that can be measured or written is from -40 to +125 Celsius degrees.
> The user can change the measured temperature resolution, but the range remains the same.
> The limit of the temperature resolution is always a 10bit, or 0.25 Celsius degrees.
> If user wants to enable the EEPROM Write Protection, the A0 pin on the device 
> must be set to the high voltage level.

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
