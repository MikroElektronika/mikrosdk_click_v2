
---
# AM/FM 2 Click

> [AM FM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5793) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5793&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the AM/FM 2 Click board&trade;.
> The app represents a radio tuner that supports worldwide AM/FM bands 
> and has features such as automatic frequency control, seek station, and volume control.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AMFM2

### Example Key Functions

- `amfm2_cfg_setup` Config Object Initialization function.
```c
void amfm2_cfg_setup ( amfm2_cfg_t *cfg );
```

- `amfm2_init` Initialization function.
```c
err_t amfm2_init ( amfm2_t *ctx, amfm2_cfg_t *cfg );
```

- `amfm2_default_cfg` Click Default Configuration function.
```c
err_t amfm2_default_cfg ( amfm2_t *ctx );
```

- `amfm2_seek_station` AM/FM 2 seek station function.
```c
err_t amfm2_seek_station ( amfm2_t *ctx, uint8_t *rsp );
```

- `amfm2_tuning_freq` AM/FM 2 tuning frequency function.
```c
err_t amfm2_tuning_freq ( amfm2_t *ctx, float frequency, uint8_t *rsp );
```

- `amfm2_get_tuning_freq` AM/FM 2 get tuning frequency function.
```c
err_t amfm2_get_tuning_freq ( amfm2_t *ctx, float *frequency );
```

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration 
> and searches and memorizes for a valid frequency of the 5 radio stations.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    amfm2_cfg_t amfm2_cfg;  /**< Click config object. */

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
    amfm2_cfg_setup( &amfm2_cfg );
    AMFM2_MAP_MIKROBUS( amfm2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == amfm2_init( &amfm2, &amfm2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMFM2_ERROR == amfm2_default_cfg ( &amfm2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, " Begins searching for a valid frequency...\r\n" );
    log_printf( &logger, "--------------------\r\n" );
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( AMFM2_OK == amfm2_seek_station( &amfm2, &rsp_status ) )
        {
            if ( AMFM2_RSP_STATUS_CTS & rsp_status )
            {
                log_printf( &logger, " The search is done.\r\n" );
                if ( AMFM2_OK == amfm2_get_tuning_freq( &amfm2, &mem_station_freq[ n_cnt ] ) )
                {
                    log_printf( &logger, " Frequency: %.2f MHz \r\n", mem_station_freq[ n_cnt ] );
                    log_printf( &logger, "- - - - - - - - - - \r\n" );
                    Delay_ms ( 100 );
                }
            }
        }
    }
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 100 );
    
    if ( AMFM2_OK == amfm2_set_volume( &amfm2, AMFM2_SET_VOLUME_MAX, &rsp_status ) )
    {
        log_printf( &logger, " Set max volume \r\n" );
        Delay_ms ( 100 );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the AM/FM 2 Click board&trade;.
> The application switches all 5 previously memorized radio frequencies every 10 seconds.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( AMFM2_OK == amfm2_tuning_freq( &amfm2, mem_station_freq[ n_cnt ], &rsp_status ) )
        {
            log_printf( &logger, " FM Station %d \r\nFrequency: %.2f MHz\r\n", 
                       ( uint16_t ) ( n_cnt + 1 ), mem_station_freq[ n_cnt ] );
            log_printf( &logger, "--------------------\r\n" );
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
