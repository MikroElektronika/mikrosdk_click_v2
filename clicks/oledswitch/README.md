
---
# OLED Switch Click

> [OLED Switch Click](https://www.mikroe.com/?pid_product=MIKROE-2449) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2449&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to configure and use the OLED Switch Click. This Click is a 
> combination of a button and a full color organic LED display. Displays settings are first
> loaded onto the chip and after that you can show any 64x48 pixel image on the display. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OledSwitch

### Example Key Functions

- `oledswitch_cfg_setup` Config Object Initialization function. 
```c
void oledswitch_cfg_setup ( oledswitch_cfg_t *cfg );
``` 
 
- `oledswitch_init` Initialization function. 
```c
err_t oledswitch_init ( oledswitch_t *ctx, oledswitch_cfg_t *cfg );
```

- `oledswitch_default_cfg` Click Default Configuration function. 
```c
void oledswitch_default_cfg ( oledswitch_t *ctx );
```

- `` This function writes to control and configuration registers on the chip. 
```c
oledswitch_reg_write  ( oledswitch_t *ctx, uint8_t *write_buf, uint8_t len );
```
 
- `oledswitch_digital_write_pwm` This function sets the digital output signal for the PWM pin. 
```c
void oledswitch_digital_write_pwm ( oledswitch_t *ctx, uint8_t signal );
```

- `oledswitch_digital_write_rst` This function sets the digital output signal for the RST pin. 
```c
void oledswitch_digital_write_rst ( oledswitch_t *ctx, uint8_t signal );
```

### Application Init

> This function initializes and configures the Click modules. In order for the
> Click to work properly, you need to configure display and power settings. 
> The full initialization of the chip is done in the default_cfg(...) function.

```c
void application_init ( )
{
    oledswitch_cfg_t cfg;
    
    //  Click initialization.

    oledswitch_cfg_setup( &cfg );
    OLEDSWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oledswitch_init( &oledswitch, &cfg );
    oledswitch_default_cfg( &oledswitch, OLEDSWITCH_BUFFER_SIZE_SMALL );
}
```

### Application Task

> This function shows the user how to display images on the OLED screen. Every image you'd
> like to display needs to have a resolution of 64x48 and be stored in a 6144 cell array. 

```c
void application_task ( )
{
    oledswitch_draw_image( &oledswitch, array_red, OLEDSWITCH_IMG_SIZE_NORMAL );
    Delay_1sec( );

    oledswitch_draw_image( &oledswitch, array_green, OLEDSWITCH_IMG_SIZE_NORMAL );
    Delay_1sec( );

    oledswitch_draw_image( &oledswitch, array_blue, OLEDSWITCH_IMG_SIZE_NORMAL );
    Delay_1sec( );
}
```

### Note

> Every pixel on the OLED screen is displayed at the time of writing to the chip (PWM 1).
> Displaying speed can be directly controled by adding delays in the for loop section of 
> the draw_image(...) function. 

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
