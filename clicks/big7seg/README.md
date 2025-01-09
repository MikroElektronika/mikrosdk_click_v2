
---
# BIG 7-SEG Click

> [BIG 7-SEG Click](https://www.mikroe.com/?pid_product=MIKROE-2269) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2269&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application sets seven-segment leds on the display.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Big7Seg

### Example Key Functions

- `big7seg_cfg_setup` Config Object Initialization function. 
```c
void big7seg_cfg_setup ( big7seg_cfg_t *cfg );
``` 
 
- `big7seg_init` Initialization function. 
```c
err_t big7seg_init ( big7seg_t *ctx, big7seg_cfg_t *cfg );
```

- `big7seg_display_off` Turn OFF BIG 7-SEG display. 
```c
void big7seg_display_off( big7seg_t *ctx );
```
 
- `big7seg_write_data_number` Function write number. 
```c
void big7seg_write_data_number( big7seg_t *ctx, uint8_t display_number );
```

- `big7seg_write_data_character` Function write character. 
```c
void big7seg_write_data_character( big7seg_t *ctx, char display_char );
```

### Application Init

> Driver initializaion and turning on the display
> by setting PWM pin to logic 1 and prepare to communcation via SPI.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    big7seg_cfg_t cfg;

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

    big7seg_cfg_setup( &cfg );
    BIG7SEG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    big7seg_init( &big7seg, &cfg );

    big7seg_set7seg( &big7seg );
    Delay_100ms( );
}
```

### Application Task

> This example shows functionality of the BIG 7-SEG R Click,
> shows number or character on display.

```c
void application_task ( )
{
    uint8_t counter;

    big7seg_reset7seg( &big7seg );
    big7seg_display_on( &big7seg );
    Delay_1sec( );

    big7seg_write_data( &big7seg, 0x40 );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'B' );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'I' );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'G' );
    Delay_1sec( );
    big7seg_write_data( &big7seg, 0x08 );
    Delay_1sec( );
    big7seg_write_data_number( &big7seg, 7 );
    Delay_1sec( );
    big7seg_write_data( &big7seg, 0x40 );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'S' );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'E' );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'G' );
    Delay_1sec( );
    
    big7seg_write_data( &big7seg, 0x00 );
    Delay_1sec( );
    for ( counter = 65; counter < 91; counter ++ )
    {
        big7seg_write_data_character(  &big7seg, counter );
        Delay_1sec( );
    }

    big7seg_display_off( &big7seg );
    Delay_1sec( );
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
