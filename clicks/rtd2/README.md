
---
# RTD 2 Click

> [RTD 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4282) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4282&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> RTD 2 Click board is commonly used for measuring ambient temperature from the PT100 3-wire temperature probe.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtd2

### Example Key Functions

- `rtd2_cfg_setup` Config Object Initialization function.
```c
void rtd2_cfg_setup ( rtd2_cfg_t *cfg ); 
```

- `rtd2_init` Initialization function.
```c
err_t rtd2_init ( rtd2_t *ctx, rtd2_cfg_t *cfg );
```

- `rtd2_default_cfg` Click Default Configuration function.
```c
void rtd2_default_cfg ( rtd2_t *ctx );
```

- `rtd2_check_new_data_ready` The function check new data ready of the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With Programmable Gain Amplifier (PGA) For Sensor Measurement on the RTD 2 Click board.
```c
uint8_t rtd2_check_new_data_ready ( rtd2_t *ctx );
```

- `rtd2_get_temperature` The function read output data and return ambient temperature from the PT100 3-wire temperature probe wired to the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With Programmable Gain Amplifier (PGA) For Sensor Measurement on the RTD 2 Click board.
```c
float rtd2_get_temperature ( rtd2_t *ctx );
```

- `rtd2_enable_start` The function enables ADC conversion of the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With Programmable Gain Amplifier (PGA) For Sensor Measurement on the RTD 2 Click.
```c
void rtd2_enable_start ( rtd2_t *ctx, uint8_t en_start );
```

### Application Init

> Initializes the driver, performs a hardware reset, and sets the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtd2_cfg_t cfg;

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
    rtd2_cfg_setup( &cfg );
    RTD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtd2_init( &rtd2, &cfg );
    Delay_ms ( 200 );

    log_printf( &logger, "----- Hardware Reset ------\r\n" );
    rtd2_hw_reset( &rtd2 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-- Default configuration --\r\n" );
    rtd2_default_cfg( &rtd2 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Start Measurement    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads an ambient temperature measured by the PT100 3-wire temperature probe connected to the RTD 2 Click board, and logs the results on the USB UART each second.

```c
void application_task ( void )
{
    if ( rtd2_check_new_data_ready( &rtd2 ) == RTD2_NEW_DATA_IS_READY )
    {
        temperature = rtd2_get_temperature( &rtd2 );
        log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
        log_printf( &logger, "--------------------------\r\n");
        Delay_ms ( 1000 );
    }
    else
    {
        rtd2_enable_start( &rtd2, RTD2_START_CONVERSION_DISABLE );
        Delay_ms ( 1000 );
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
