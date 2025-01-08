
---
# BATT-MON Click

> [BATT-MON Click](https://www.mikroe.com/?pid_product=MIKROE-3741) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3741&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is battery charger.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BattMon

### Example Key Functions

- `battmon_cfg_setup` Config Object Initialization function. 
```c
void battmon_cfg_setup ( battmon_cfg_t *cfg );
``` 
 
- `battmon_init` Initialization function. 
```c
err_t battmon_init ( battmon_t *ctx, battmon_cfg_t *cfg );
```

- `battmon_default_cfg` Click Default Configuration function. 
```c
void battmon_default_cfg ( battmon_t *ctx );
```

- `battmon_get_data` Data Get function. 
```c
float battmon_get_data( battmon_t *ctx, uint8_t data_addr );
```
 
- `battmon_get_alm_pin` ALM Pin Get function. 
```c
uint8_t battmon_get_alm_pin( battmon_t *ctx );
```

- `battmon_reset_conv_cnt` Conversion Counter Reset function. 
```c
void battmon_reset_conv_cnt( battmon_t *ctx );
```

### Application Init

> Initializes I2C serial interface, reads the part ID and
> performs a device configuration and alarm setting.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    battmon_cfg_t cfg;

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

    battmon_cfg_setup( &cfg );
    BATTMON_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    battmon_init( &battmon, &cfg );

    Delay_ms ( 500 );

    battmon_read_bytes( &battmon, BATTMON_REG_ID, &reg_read, 1 );
    log_printf( &logger, " ** Part ID: 0x%d \r\n", (uint16_t) reg_read );

    battmon_default_cfg( &battmon );
    
    log_printf( &logger, "** BattMon initialization done ** \r\n" );
    log_printf( &logger, "********************************* \r\n" );
}
```

### Application Task

> Checks the conversion counter value and when conversion was done
> reads data calculated to the properly unit and checks the alarm status.
> All results will be sent to the uart terminal.

```c
void application_task ( void )
{
    char cels_symbol[ 3 ] = { 176, 'C', 0 };
    float data_read;
    uint16_t conv_cnt;

    conv_cnt = battmon_get_data( &battmon, BATTMON_REG_COUNTER );

    if ( ( ( conv_cnt % 4 ) == 0 ) && ( conv_cnt > 0 ) )
    {
        data_read = battmon_get_data( &battmon, BATTMON_REG_SOC );
        log_printf( &logger, "** Gas Gauge Relative SOC : %.2f %% \r\n ", data_read );
    
        data_read = battmon_get_data( &battmon, BATTMON_REG_CURRENT );
        log_printf( &logger, "** Battery Current : %.2f mA \r\n", data_read );

        
        data_read = battmon_get_data( &battmon, BATTMON_REG_VOLTAGE );
        log_printf( &logger, "** Battery Voltage : %.2f mV \r\n", data_read );
        
        if ( ( conv_cnt % 16 ) == 0 )
        {
            data_read = battmon_get_data( &battmon, BATTMON_REG_TEMPERATURE );
            battmon_reset_conv_cnt( &battmon );
            log_printf( &logger, "** Temperature :  %.2f %s\r\n", data_read, cels_symbol );
        }
        
        reg_read = battmon_check_clear_alarm( &battmon );

        if ( ( reg_read & BATTMON_ALM_SOC_DET_MASK ) != BATTMON_LOG_LOW )
        {
            log_printf( &logger,  "** Low-SOC Condition! \r\n" );
        }
        if ( ( reg_read & BATTMON_ALM_VOLT_DET_MASK ) != BATTMON_LOG_LOW )
        {
            log_printf( &logger,  "** Low-Voltage Condition! \r\n" ); 
        }
        
        log_printf( &logger, "********************************* \r\n" );
        Delay_ms ( 1000 );
    }
    else
    {
        Delay_ms ( 200 );
    }
}
```

### Note

> Voltage and current conversion will be done after 4 seconds.
> Temperature conversion will be done after 16 seconds.
> After temperature reading the conversion counter will be cleared.
> Clearing the alarm while the corresponding low-voltage or low-SOC condition is still in progress 
> does not generate another interrupt. This condition must disappear first and must be detected again 
> before another interrupt (ALM pin driven low or alarm interrupt bits are set high) is generated for this alarm.
> Another alarm condition, if not yet triggered, can still generate an interrupt.
> Input voltage must be in the range from 2.7V to 4.5V.
> Maximal battery current is 5A.

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
