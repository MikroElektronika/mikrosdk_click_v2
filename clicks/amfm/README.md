
---
# AMFM Click

> [AM FM Click](https://www.mikroe.com/?pid_product=MIKROE-3800) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3800&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This app simulate RADIO RECEIVER.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AmFm

### Example Key Functions

- `amfm_cfg_setup` Config Object Initialization function.
```c
void amfm_cfg_setup ( amfm_cfg_t *cfg );
```
 
- `amfm_init` Initialization function.
```c
err_t amfm_init ( amfm_t *ctx, amfm_cfg_t *cfg );
```

- `amfm_default_cfg` Click Default Configuration function.
```c
void amfm_default_cfg ( amfm_t *ctx );
```

- `amfm_tune_up` This function increments current frequency for 10 KHz.
```c
uint8_t amfm_tune_up ( amfm_t *ctx );
```
 
- `amfm_set_volume` This function sets volume level in range: 0 - 63.
```c
uint8_t amfm_set_volume ( amfm_t *ctx, uint8_t volume );
```

- `amfm_get_stc` This function checks STC bit state.
```c
uint8_t amfm_get_stc ( amfm_t *ctx );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    amfm_cfg_t cfg;

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

    amfm_cfg_setup( &cfg );
    AMFM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    amfm_init( &amfm, &cfg );

    Delay_ms ( 100 );
    status = amfm_init_device( &amfm );
    if ( 0 == status )
    {
        log_printf( &logger, "> > > app init done < < <\r\n" );
    }
    else if ( 1 == status )
    {
        log_printf( &logger, "> > >    timeout    < < <\r\n" );
    }
    Delay_ms ( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms ( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms ( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms ( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms ( 1000 );
    
    amfm_case_seek( &amfm );
    amfm_case_memorize( );
    Delay_ms ( 1000 );
    
    amfm_case_plus( &amfm );
    Delay_ms ( 1000 );
}
```

### Application Task

> Several additional functions are executed and printed over the terminal.

```c
void application_task ( void )
{
    amfm_case_station_1( &amfm );
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
       
    amfm_case_station_2( &amfm );
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
    
    amfm_case_station_3( &amfm );
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
    
    amfm_case_station_4( &amfm );
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
    
    amfm_case_station_5( &amfm );
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
