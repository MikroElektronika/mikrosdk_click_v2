
---
# GainAMP 2 Click

> [GainAMP 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2859) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2859&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is programmable gain amplifier

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GainAmp2

### Example Key Functions

- `gainamp2_cfg_setup` Config Object Initialization function. 
```c
void gainamp2_cfg_setup ( gainamp2_cfg_t *cfg );
``` 
 
- `gainamp2_init` Initialization function. 
```c
err_t gainamp2_init ( gainamp2_t *ctx, gainamp2_cfg_t *cfg );
```

- `gainamp2_set_channel_gain` Set the channel gain. 
```c
void gainamp2_set_channel_gain ( gainamp2_t *ctx, uint8_t channel, uint8_t gain );
```
 
- `gainamp2_get_voltage` Return voltage measured from VOUT pin. 
```c
float gainamp2_get_voltage ( gainamp2_t *ctx );
```

- `gainamp2_write_Command` Send Command. 
```c
void gainamp2_write_Command (  gainamp2_t *ctx, uint8_t instruction, uint8_t input  );
```

### Application Init

> Initializes and sets GainAMP 2 Click channel 0 to amplify the signal 2 times

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gainamp2_cfg_t cfg;

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

    gainamp2_cfg_setup( &cfg );
    GAINAMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gainamp2_init( &gainamp2, &cfg );
    
    gainamp2_set_channel_gain ( &gainamp2, GAINAMP2_CH0, GAINAMP2_GAIN_2X );
    log_printf( &logger,"Channel 0 - aplified 2x \r\n" ); 
}
```

### Application Task

> Displays the voltage measured from VOUT pin

```c
void application_task ( void )
{
    log_printf( &logger,"Voltage at VOUT: %f \r\n", gainamp2_get_voltage( &gainamp2 ) );
    log_printf( &logger,"------------------------------- \r\n " );
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
