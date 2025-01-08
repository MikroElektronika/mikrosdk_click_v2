
---
# Touch Key 4 Click

> [TouchKey 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2965) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2965&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo performs touch & release detection functionality of the Click. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchKey4

### Example Key Functions

- `touchkey4_cfg_setup` Config Object Initialization function. 
```c
void touchkey4_cfg_setup ( touchkey4_cfg_t *cfg );
``` 
 
- `touchkey4_init` Initialization function. 
```c
err_t touchkey4_init ( touchkey4_t *ctx, touchkey4_cfg_t *cfg );
```

- `touchkey4_default_cfg` Click Default Configuration function. 
```c
void touchkey4_default_cfg ( touchkey4_t *ctx );
```

- `touchkey4_detect_touch` This function detects touch on sensor inputs and checks is touch detected or released. 
```c
void touchkey4_detect_touch ( touchkey4_t *ctx, uint8_t *input_sens );
```

- `touchkey4_set_active_mode` This function puts device in Active mode and enables desired inputs in Active mode. 
```c
void touchkey4_set_active_mode ( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1,const uint8_t en_input2, const uint8_t en_input3 );
```

- `touchkey4_set_standby_mode` This function puts device in Standby mode and enables desired inputs in Standby mode. 
```c
void touchkey4_set_standby_mode ( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1, const uint8_t en_input2, const uint8_t en_input3 );
```

### Application Init

> Device and driver initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey4_cfg_t cfg;

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

    touchkey4_cfg_setup( &cfg );
    TOUCHKEY4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey4_init( &touchkey4, &cfg );

    Delay_ms ( 1000 );
    
    touchkey4_default_cfg( &touchkey4 );
    log_info( &logger, "---- Configured and ready ----" );
}
```

### Application Task

> Calls function to check touch detection (is interrupt occured) and shows message on 
> USB UART if touch is detected or if touch is released on enabled inputs.

```c
void application_task ( void )
{
    touchkey4_detect_touch( &touchkey4, sensor_results );
    for ( cnt = 0; cnt < 3; cnt++ )
    {
        if ( sensor_results[ cnt ] == 1 )
        {
            if ( cnt == 0 )
            {
                log_info( &logger, "Input 1 is touched\r\n" );
            }
            else if ( cnt == 1 )
            {
                log_info( &logger, "Input 2 is touched\r\n" );
            }
            else
            {
                log_info( &logger, "Input 3 is touched\r\n" );
            }
        }
        else if ( sensor_results[ cnt ] == 2 )
        {
            if ( cnt == 0 )
            {
                log_info( &logger, "Input 1 is released\r\n" );
            }
            else if ( cnt == 1 )
            {
                log_info( &logger, "Input 2 is released\r\n" );
            }
            else
            {
                log_info( &logger, "Input 3 is released\r\n" );
            }
        }
    }
    Delay_ms ( 300 );
}
```

### Note

> TouchKey 4 is configured to work in Combo mode (Active and Standby mode). Input 1 is
> enabled in Active mode, input 3 is enabled in Standby mode, and input 2 is enabled to
> work in both modes. In this example the interrupt will be generated when touch is
> detected and when touch is released. 
> Standby mode should be used when fewer sensor inputs are enabled, and when
> they are programmed to have more sensitivity.
> Somethimes it is neccessary to cycle the board power supply if Click doesn't work. 


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
