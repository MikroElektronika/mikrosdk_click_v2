
---
# Bargraph 2 Click

> [Bargraph 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3021) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3021&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> The example starts off with the initalisation and configuration of the logger and Click modules and later on showcases different ways of lighting LED diodes on the Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Bargraph2

### Example Key Functions

- `bargraph2_cfg_setup` Config Object Initialization function. 
```c
void bargraph2_cfg_setup ( bargraph2_cfg_t *cfg );
``` 
 
- `bargraph2_init` Initialization function. 
```c
err_t bargraph2_init ( bargraph2_t *ctx, bargraph2_cfg_t *cfg );
```

- `bargraph2_led_green` This function turns on the green LED diode of the chosen segment. 
```c
void bargraph2_led_green ( bargraph2_t *ctx, uint8_t index );
```
 
- `bargraph2_leds_green` This function turns on green LED diodes from the starting index to the end index. 
```c
void bargraph2_leds_green ( bargraph2_t *ctx, int start_index, int end_index );
```

- `bargraph2_lights_out` This function turns off all the LED diodes. 
```c
void bargraph2_lights_out ( bargraph2_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    bargraph2_cfg_t cfg;

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

    bargraph2_cfg_setup( &cfg );
    BARGRAPH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bargraph2_init( &bargraph2, &cfg );
}
```

### Application Task

> This function shows the user how to light single and multiple LED diodes.

```c
void application_task ( )
{
    uint8_t cnt; 
        
    // Single LED switch
    
    for ( cnt = 1; cnt <= 10 ; cnt++ )
    {
        bargraph2_led_green( &bargraph2, cnt );
        Delay_ms ( 200 );
        bargraph2_led_red( &bargraph2, 10 - ( cnt - 1 ) );
        Delay_ms ( 200 );
    }
    
    bargraph2_lights_out ( &bargraph2 );

    // Multiple LED switch

    bargraph2_leds_green ( &bargraph2, 1, 10 );
    Delay_ms ( 1000 );
    bargraph2_leds_red ( &bargraph2, 1, 10 );
    Delay_ms ( 1000 );
    bargraph2_leds_yellow ( &bargraph2, 1, 10 );
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
