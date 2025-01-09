
---
# 7seg Click

> [7seg Click](https://www.mikroe.com/?pid_product=MIKROE-1201) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1201&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> Example code consist of two sections: AppInit and AppTask,
> and shows number or character on 7seg display.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.7seg

### Example Key Functions

- `c7seg_cfg_setup` Config Object Initialization function. 
```c
void c7seg_cfg_setup ( c7seg_cfg_t *cfg );
``` 
 
- `c7seg_init` Initialization function. 
```c
err_t c7seg_init ( c7seg_t *ctx, c7seg_cfg_t *cfg );
```

- `c7seg_default_cfg` Click Default Configuration function. 
```c
void c7seg_default_cfg ( c7seg_t *ctx );
```

- `c7seg_display_mode` This function sets display state for 7seg Click. 
```c
void c7seg_display_mode ( c7seg_t *ctx, uint8_t display_mode );
```
 
- `c7seg_write_data_number` This function writes left and right number on 7seg display. 
```c
void c7seg_write_data_number ( c7seg_t *ctx, uint8_t left_number, uint8_t right_number );
```

- `c7seg_write_data_character` This function writes left and right character on 7seg display. 
```c
void c7seg_write_data_character ( c7seg_t *ctx, char left_char, char right_char );
```

### Application Init

>
> Application Init performs Logger and Click Initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c7seg_cfg_t cfg;

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
    log_printf( &logger, "-- Application  Init --\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    c7seg_cfg_setup( &cfg );
    C7SEG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7seg_init( &c7seg, &cfg );
    
    c7seg_default_cfg ( &c7seg );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Application Task shows functionality of the 7seg Click,
> shows number or character on left and right display.
> 

```c
void application_task ( void )
{
    uint8_t counter;

    c7seg_display_mode( &c7seg, C7SEG_DISPLAY_ON );
    Delay_ms ( 1000 );
    
    for ( counter = 0; counter < 9; counter ++ )
    {
        c7seg_write_data_number( &c7seg, counter, counter + 1 );
        Delay_ms ( 1000 );
    }
    Delay_ms ( 1000 );

    for ( counter = 65; counter < 90; counter ++ )
    {
        c7seg_write_data_character( &c7seg, counter, counter + 1 );
        Delay_ms ( 1000 );
    }
    Delay_ms ( 1000 );

    c7seg_display_mode( &c7seg, C7SEG_DISPLAY_OFF );
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
