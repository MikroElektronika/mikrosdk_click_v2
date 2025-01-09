
---
# Temp-Log 2 Click

> [Temp-Log 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3004) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3004&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

>
> This example demonstrates the use of the Temp-Log 2 Click board.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog2

### Example Key Functions

- `templog2_cfg_setup` Configuration Object Setup function. 
```c
void templog2_cfg_setup ( templog2_cfg_t *cfg );
```
 
- `templog2_init` Click Initialization function. 
```c
err_t templog2_init ( templog2_t *ctx, templog2_cfg_t *cfg );
```

- `templog2_default_cfg` Click Default Configuration function. 
```c
void templog2_default_cfg ( templog2_t *ctx );
```

- `templog2_write_reg` Write Register function. 
```c
err_t templog2_write_reg ( templog2_t *ctx, uint8_t reg_addr, uint16_t transfer_data );
```
 
- `templog2_read_reg` Read Register function. 
```c
err_t templog2_read_reg ( templog2_t *ctx, uint8_t reg_addr, uint16_t *data_out );
```

- `templog2_read_temp` Read Temperature function. 
```c
float templog2_read_temp ( templog2_t *ctx );
```

### Application Init

>
> Initializes peripherals and pins.
> Initializes I2C driver and performs device configuration.
> Sets total active conversion time to 250 ms and 8 average samples.
> Also sets Shutdown Mode as default mode, and after device reset puts device
> in Continuous Conversion Mode.
> High limit status will be set when temperature cross over the determined
> high limit temperature value.
> Low limit status will be set when temperature falls below the determined
> low limit temperature value.
>

```c
void application_init( void )
{
    templog2_cfg_t templog2_cfg;
    log_cfg_t log_cfg;

    //  Click initialization.
    templog2_cfg_setup( &templog2_cfg );
    TEMPLOG2_MAP_MIKROBUS( templog2_cfg, MIKROBUS_1 );
    templog2_init( &templog2, &templog2_cfg );

    //  Click default configuration.
    templog2_default_config( &templog2 );

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
    log_info( &logger, "----  Temp-Log 2 Application Init Done  ----\r\n" );
}
```

### Application Task

>
> Reads temperature value calculated to Celsius degrees.
>

```c
void application_task( void )
{
    float temperature;
    uint8_t temp_status;
    uint8_t cnt;

    temp_status = templog2_data_ready( &templog2 );

    if (temp_status & _TEMPLOG2_DATA_READY_MASK)
    {
        temperature = templog2_read_temp( &templog2 );

        log_printf( &logger, " > Temperature : %.2f\r\n", temperature );

        if (temp_status & _TEMPLOG2_LOW_LIMIT_MASK)
        {
            log_printf( &logger, " LOW LIMIT DETECTED!\r\n" );
        }

        if (temp_status & _TEMPLOG2_HIGH_LIMIT_MASK)
        {
            log_printf( &logger, " HIGH LIMIT DETECTED!\r\n" );
        }
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
