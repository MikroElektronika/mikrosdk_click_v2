
---
# AudioAMP 11 Click

> [AudioAMP 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5584) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5584&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the AudioAMP 11 Click driver.
> This demo application shows use of a AudioAMP 11 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAMP11

### Example Key Functions

- `audioamp11_cfg_setup` Config Object Initialization function.
```c
void audioamp11_cfg_setup ( audioamp11_cfg_t *cfg );
```

- `audioamp11_init` Initialization function.
```c
err_t audioamp11_init ( audioamp11_t *ctx, audioamp11_cfg_t *cfg );
```

- `audioamp11_default_cfg` Click Default Configuration function.
```c
err_t audioamp11_default_cfg ( audioamp11_t *ctx );
```

- `audioamp11_enable_device` AudioAMP 11 enable device function.
```c
void audioamp11_enable_device ( audioamp11_t *ctx );
```

- `audioamp11_check_gain` AudioAMP 11 check gain function.
```c
err_t audioamp11_check_gain ( audioamp11_t *ctx, uint8_t *gain );
```

- `audioamp11_set_output_volume_level` AudioAMP 11 set output volume level function.
```c
err_t audioamp11_set_output_volume_level ( audioamp11_t *ctx, uint8_t volume_data );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization the app set default settings, 
> performs power-up sequence, sets the volume level to 0.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp11_cfg_t audioamp11_cfg;  /**< Click config object. */

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
    audioamp11_cfg_setup( &audioamp11_cfg );
    AUDIOAMP11_MAP_MIKROBUS( audioamp11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == audioamp11_init( &audioamp11, &audioamp11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AUDIOAMP11_ERROR == audioamp11_default_cfg ( &audioamp11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the AudioAMP 11 Click board&trade;.
> If GAIN SEL switches are set to 12dB, the app performs circles 
> switching the volume from -20.5 dB to 12 dB.
> If the GAIN SEL switches are different, the app sets the volume level to 31 (maximum).
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    uint8_t gain_level = 0;
    uint8_t volume_level = 0;
    
    audioamp11_check_gain( &audioamp11, &gain_level );
    log_printf( &logger, " Gain set to %d dB\r\n", AUDIOAMP11_CALC_GAIN_CONFIG( gain_level ) );
    
    if ( AUDIOAMP11_GAINDEC_12dB == gain_level )
    {
        float volume_table[ 32 ] = { OUTPUT_VOLUME_12dB };
        audioamp11_set_output_volume_level( &audioamp11, vol_ctrl );
        Delay_ms ( 100 );
        
        if ( vol_ctrl > AUDIOAMP11_GS_12dB_VOLCTRL_12dB )
        {
            vol_ctrl--;
        }
        else
        {
            vol_ctrl = AUDIOAMP11_GS_12dB_VOLCTRL_m20_5dB;
        }
        
        audioamp11_get_output_volume_level( &audioamp11, &volume_level );
        log_printf( &logger, " Volume set to  %.1f dB\r\n", volume_table[ volume_level ] );
    }
    else
    {
        audioamp11_set_output_volume_level( &audioamp11, AUDIOAMP11_VOLUME_LEVEL_31 );
        audioamp11_get_output_volume_level( &audioamp11, &volume_level );        
    }
    
    log_printf( &logger, " Volume Level %d: ", ( uint16_t ) ( AUDIOAMP11_VOLUME_LEVEL_0 - volume_level ) );
    for ( uint8_t n_cnt = 0; n_cnt < ( AUDIOAMP11_VOLUME_LEVEL_0 - volume_level ); n_cnt++ )
    {
        log_printf( &logger, "|" );    
    }
    log_printf( &logger, "\r\n----------------------\r\n" );
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
