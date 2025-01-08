
---
# Headphone AMP Click

> [Headphone AMP Click](https://www.mikroe.com/?pid_product=MIKROE-4766) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4766&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains API for the Headphone AMP Click driver.
> This demo application shows use of a Headphone AMP Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeadphoneAMP

### Example Key Functions

- `headphoneamp_cfg_setup` Config Object Initialization function.
```c
void headphoneamp_cfg_setup ( headphoneamp_cfg_t *cfg );
```

- `headphoneamp_init` Initialization function.
```c
err_t headphoneamp_init ( headphoneamp_t *ctx, headphoneamp_cfg_t *cfg );
```

- `headphoneamp_default_cfg` Click Default Configuration function.
```c
void headphoneamp_default_cfg ( headphoneamp_t *ctx );
```

- `headphoneamp_set_sound_volume` Headphone AMP set sound volume function.
```c
err_t headphoneamp_set_sound_volume ( headphoneamp_t *ctx, uint8_t sound_volume );
```

- `headphoneamp_volume_up` Headphone AMP set sound volume up function.
```c
err_t headphoneamp_volume_up ( headphoneamp_t *ctx );
```

- `headphoneamp_volume_down` Headphone AMP set sound volume down function.
```c
err_t headphoneamp_volume_down ( headphoneamp_t *ctx );
```

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization the app set default settings, 
> performs power-up sequence, sets a the sound volume of -12 dB.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    headphoneamp_cfg_t headphoneamp_cfg;  /**< Click config object. */

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

    headphoneamp_cfg_setup( &headphoneamp_cfg );
    HEADPHONEAMP_MAP_MIKROBUS( headphoneamp_cfg, MIKROBUS_1 );
    if ( headphoneamp_init( &headphoneamp, &headphoneamp_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    headphoneamp_default_cfg ( &headphoneamp );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Performs Power-up\r\n" );
    headphoneamp_power_up( &headphoneamp );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Set volume gain -12dB\r\n", HEADPHONEAMP_SOUND_VOLUME_NEG_12_dB );
    headphoneamp_set_sound_volume( &headphoneamp, HEADPHONEAMP_SOUND_VOLUME_NEG_12_dB ); 
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> This is an example that shows the use of Headphone AMP Click board&trade;.
> The app performs circles the volume from -12 dB to 3 dB back and forth,
> increase/decrement by 3dB.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        log_printf( &logger, "    Turning volume up\r\n" );
        headphoneamp_volume_up ( &headphoneamp ); 
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );    
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        log_printf( &logger, "   Turning volume down\r\n" );
        headphoneamp_volume_down ( &headphoneamp ); 
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );    
    }
       
    log_printf( &logger, "-------------------------\r\n" );
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
