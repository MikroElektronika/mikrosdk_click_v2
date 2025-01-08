
---
# FM Click

> [FM Click](https://www.mikroe.com/?pid_product=MIKROE-1431) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1431&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click represent FM radio tuner which supports worldwide FM band (76 – 108 MHz)
> and has a set of features such as automatic frequency and gain control, seek tuning and volume control.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fm

### Example Key Functions

- `fm_cfg_setup` Config Object Initialization function. 
```c
void fm_cfg_setup ( fm_cfg_t *cfg );
``` 
 
- `fm_init` Initialization function. 
```c
err_t fm_init ( fm_t *ctx, fm_cfg_t *cfg );
```

- `fm_default_cfg` Click Default Configuration function. 
```c
void fm_default_cfg ( fm_t *ctx );
```

- `fm_get_received_signal_strength_indicator` This function reads recived signal strength indicatior. 
```c
uint8_t fm_get_received_signal_strength_indicator ( fm_t *ctx );
```
 
- `fm_get_channel_frequency` This function calculates current channel frequency based on band and space settings. 
```c
float fm_get_channel_frequency ( fm_t *ctx );
```

- `fm_get_channel` This function reads CHANNEL bits from READCHAN register. 
```c
uint16_t fm_get_channel ( fm_t *ctx );
```

### Application Init

> Initializing I2C driver, powering up device, setting basic settings for Europe, 
> setting values of seek threshold, volume, snr threshold and impulse detection threshold.
> Seek and memorize 5 radio stations with a signal strength above the set limit.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fm_cfg_t cfg;

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

    fm_cfg_setup( &cfg );
    FM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fm_init( &fm, &cfg );
    
    Delay_ms ( 500 );
    fm_default_cfg( &fm );

    memory = 0;
    mute = 0;
    fm_case_mute( &fm );
     
    for ( cnt = 0; cnt < 5;  )
    {
        log_printf( &logger, "seeking...\r\n" );
        do 
        {
            received_signal_strength_indicator = 0;
            fm_case_seek( &fm );
        }
        while ( received_signal_strength_indicator < SIGNAL_STRENGTH_LOWER_LIMIT ); //rssi value
        
        log_printf( &logger, "station found\r\n" );
        log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );
        log_printf( &logger, "channel frequency: %.2f MHz\r\n", channel_frequency );
        fm_case_memorize( );
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms ( 100 );
        cnt++;
    }  
    
    mute = 1;
    fm_case_mute( &fm );
    log_printf( &logger, "playing memorized stations...\r\n\r\n" );
}
```

### Application Task

> Tunes all memorized stations. Switches the stations each 10 seconds.

```c
void application_task ( void )
{ 
    fm_case_station_1( &fm );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
       
    fm_case_station_2( &fm );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    fm_case_station_3( &fm );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    fm_case_station_4( &fm );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    fm_case_station_5( &fm );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
