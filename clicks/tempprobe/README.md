
---
# Temp Probe Click

> [Temp Probe Click](https://www.mikroe.com/?pid_product=MIKROE-4301) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4301&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Temp Probe Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempProbe

### Example Key Functions

- `tempprobe_cfg_setup` Config Object Initialization function.
```c
void tempprobe_cfg_setup ( tempprobe_cfg_t *cfg );
```

- `tempprobe_init` Initialization function.
```c
err_t tempprobe_init ( tempprobe_t *ctx, tempprobe_cfg_t *cfg );
```

- `tempprobe_default_cfg` Click Default Configuration function.
```c
err_t tempprobe_default_cfg ( tempprobe_t *ctx );
```

- `tempprobe_write_word` Word Write function.
```c
err_t tempprobe_write_word ( tempprobe_t *ctx, uint16_t reg_addr, uint32_t data_in );
```

- `tempprobe_read_bytes` Byte Read function.
```c
err_t tempprobe_read_bytes( tempprobe_t *ctx, uint16_t reg_addr, uint8_t *data_out, uint8_t n_bytes );
```

- `tempprobe_read_temp` Temperature Read function.
```c
uint8_t tempprobe_read_temp ( tempprobe_t *ctx, uint16_t sel_channel, float *data_out );
```

### Application Init

> Initializes SPI interface and performs a  device configuration for properly working and  configures the desired channels.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempprobe_cfg_t tempprobe_cfg;  /**< Click config object. */

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
    tempprobe_cfg_setup( &tempprobe_cfg );
    TEMPPROBE_MAP_MIKROBUS( tempprobe_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == tempprobe_init( &tempprobe, &tempprobe_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    tempprobe_reset( &tempprobe );
    Delay_ms ( 300 );
    if ( TEMPPROBE_ERROR == tempprobe_default_cfg( &tempprobe ) ) 
    {
        log_error( &logger, " Config Error " );
        for ( ; ; );
    }
    Delay_ms ( 300 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measure temperatures from all sensors and display the measurements on the serial port.

```c
void application_task ( void ) 
{
    float temperature_k = 0;
    float temperature_pn = 0;
    tempprobe_write_byte( &tempprobe, TEMPPROBE_REG_COMM_STATUS, TEMPPROBE_START_CONV );
    while ( TEMPPROBE_NO_BUSY_STATE != tempprobe_check_busy( &tempprobe ) );

    tempprobe_read_temp( &tempprobe, TEMPPROBE_REG_PN_JUNCTION_CONV_RES, &temperature_pn );
    log_printf( &logger, " PN-Junction: %.2f C\r\n", temperature_pn );
    tempprobe_read_temp( &tempprobe, TEMPPROBE_REG_THERMO_K_CONV_RES, &temperature_k );
    log_printf( &logger, " Thermo K:    %.2f C\r\n", temperature_k );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
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
