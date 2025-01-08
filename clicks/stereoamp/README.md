
---
# StereoAmp Click

> [StereoAmp Click](https://www.mikroe.com/?pid_product=MIKROE-2454) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2454&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This example shows how to initialize amplifiers and set volume control registers on the fly.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StereoAmp

### Example Key Functions

- `stereoamp_cfg_setup` Config Object Initialization function. 
```c
void stereoamp_cfg_setup ( stereoamp_cfg_t *cfg );
``` 
 
- `stereoamp_init` Initialization function. 
```c
err_t stereoamp_init ( stereoamp_t *ctx, stereoamp_cfg_t *cfg );
```

- `stereoamp_default_cfg` Click Default Configuration function. 
```c
void stereoamp_default_cfg ( stereoamp_t *ctx );
```

- `stereoamp_set_power_on` This function set the power On of both channels by write to the Mode Control register address of LM48100Q-Q1 chip on StereoAmp Click board. 
```c
void stereoamp_set_power_on ( stereoamp_t *ctx );
```
 
- `stereoamp_set_volume` This function set the volume of both channels to the Volume Control register address of LM48100Q-Q1 chip on StereoAmp Click board. 
```c
void stereoamp_set_volume ( stereoamp_t *ctx, uint8_t volume );
```

### Application Init

>
> Application Init perfroms Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    stereoamp_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 500 );

    //  Click initialization.

    stereoamp_cfg_setup( &cfg );
    STEREOAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stereoamp_init( &stereoamp, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ---  StereoAmp Click --- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    stereoamp_default_cfg( &stereoamp );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "         Power  On        \r\n" );
    stereoamp_set_power_on( &stereoamp );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "     Set Volume: -80dB    \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_NEG_80dB );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "       Enable Fault       \r\n" );
    stereoamp_enable_fault( &stereoamp );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "     Enable Diagnostic    \r\n" );
    stereoamp_enable_diagnostic( &stereoamp );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 500 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " -----  Play  Music ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

>
> This examples first set volume level 20 of 31 ( gain: 1,5 dB ) for 10 seconds. 
> After that, we increase the volume to level 10 ( gain: -13,5 dB ) for the next 10 seconds. 
> Results are being sent to the UART Terminal where you can track their changes.
> 

```c
void application_task ( void )
{
    log_printf( &logger, "        Gain 1.5 dB        \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_1_5dB );
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
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "        Gain -13.5 dB      \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_NEG_13_5dB );
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
    log_printf( &logger, "--------------------------\r\n" );
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
