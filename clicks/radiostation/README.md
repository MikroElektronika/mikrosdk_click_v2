
---
# RadioStation Click

> [RadioStation Click](https://www.mikroe.com/?pid_product=MIKROE-2822) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2822&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> RadioStation Click can be used to broadcast the music via the FM radio band 
> ( which operates in the frequency range of 76MHz to 108MHz ).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RadioStation

### Example Key Functions

- `radiostation_cfg_setup` Config Object Initialization function. 
```c
void radiostation_cfg_setup ( radiostation_cfg_t *cfg );
``` 
 
- `radiostation_init` Initialization function. 
```c
err_t radiostation_init ( radiostation_t *ctx, radiostation_cfg_t *cfg );
```

- `radiostation_default_cfg` Click Default Configuration function. 
```c
void radiostation_default_cfg ( radiostation_t *ctx );
```

- Returns status information about the Audio Signal Quality and current FM transmit frequency. 
 1 byte for return status (same as return value) and 4 bytes for ASQ status.
> uint8_t radiostation_get_asq_status ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t *ret_vals ) ;
 
- `radiostation_power_up` Powers up the chip with default settings. This function should be executed before sending any commands to the chip. 
```c
uint8_t radiostation_power_up ( radiostation_t *ctx, radiostation_cmd_t *cmd );
```

- `radiostation_get_tune_status` Returns status information which is set by radiostation_get_tune_measure, radiostation_set_tune_frequency or radiostation_set_tune_power. 1 byte for return status (same as return value) and 7 bytes for tune status. 
```c
uint8_t radiostation_get_tune_status ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t clear_stc_status_bit, uint8_t *ret_vals );
```

### Application Init

> Initialization driver enable's - I2C and sets transmit_frequency.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    radiostation_cfg_t cfg;

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

    radiostation_cfg_setup( &cfg, true );
    RADIOSTATION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    radiostation_init( &radiostation, &cfg );

    radiostation.transmit_frequency = 10000; 
    radiostation.status = 0xFF;

    radiostation_default_cfg( &radiostation, &radiostation_cmd );
}
```

### Application Task

> In this example Radio Station Click is receiving signal from audio connector and broadcasting 
> it on 100.00 MHz frequency. 

```c
void application_task ( void )
{
    radiostation_get_asq_status( &radiostation, &radiostation_cmd, &buff[ 0 ] );
    Delay_ms ( 50 );
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
