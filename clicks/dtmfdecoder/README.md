
---
# DTMF Decoder Click

> [DTMF Decoder Click](https://www.mikroe.com/?pid_product=MIKROE-4579) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4579&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example shows the basic tone capture of DTMF frequencies, decoding and representing them on the UART LOG.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DTMFDecoder

### Example Key Functions

- `dtmfdecoder_cfg_setup` Config Object Initialization function.
```c
void dtmfdecoder_cfg_setup ( dtmfdecoder_cfg_t *cfg );
```

- `dtmfdecoder_init` Initialization function.
```c
err_t dtmfdecoder_init ( dtmfdecoder_t *ctx, dtmfdecoder_cfg_t *cfg );
```

- `dtmfdecoder_default_cfg` Click Default Configuration function.
```c
void dtmfdecoder_default_cfg ( dtmfdecoder_t *ctx );
```

- `dtmfdecoder_tone_read` This function reads a last registered tone and returns decoded data in character format.
```c
uint8_t dtmfdecoder_tone_read ( dtmfdecoder_t *ctx );
```

- `dtmfdecoder_delayed_steering_check` This function checks the state of the StD pin.
```c
uint8_t dtmfdecoder_delayed_steering_check ( dtmfdecoder_t *ctx );
```

- `dtmfdecoder_powerdown_off` This function powers up the device and along with the oscillator.
```c
void dtmfdecoder_powerdown_off ( dtmfdecoder_t *ctx );
```

### Application Init

> Initializes I2C and UART LOG drivers and powers on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    dtmfdecoder_cfg_t dtmfdecoder_cfg;  /**< Click config object. */

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

    dtmfdecoder_cfg_setup( &dtmfdecoder_cfg );
    DTMFDECODER_MAP_MIKROBUS( dtmfdecoder_cfg, MIKROBUS_1 );
    err_t init_flag = dtmfdecoder_init( &dtmfdecoder, &dtmfdecoder_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dtmfdecoder_default_cfg ( &dtmfdecoder );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks the delayed steering for incoming tones and decoding them on the UART LOG. Holding the same key will recognize multiple tone generation, the tone register delay constant can be set to adjust the tolerance.

```c
void application_task ( void ) 
{
    uint8_t result;
    
    if ( dtmfdecoder_delayed_steering_check( &dtmfdecoder ) ) {
        result = dtmfdecoder_tone_read( &dtmfdecoder );
        log_printf( &logger, " Detected key tone:\t%c\r\n", result );
        Delay_ms ( tone_register_delay );
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
