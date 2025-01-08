
---
# 4x4 Key Click

> [4x4 Key Click](https://www.mikroe.com/?pid_product=MIKROE-1889) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1889&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

>
> This is a example which demonstrates the use of 4x4 Key Click board. 
> Detects and logs whether any of the buttons is pressed.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.4x4Key

### Example Key Functions

- `c4x4key_cfg_setup` Config Object Initialization function. 
```c
void c4x4key_cfg_setup ( c4x4key_cfg_t *cfg );
``` 
 
- `c4x4key_init` Initialization function. 
```c
err_t c4x4key_init ( c4x4key_t *ctx, c4x4key_cfg_t *cfg );
```

- `c4x4key_default_cfg` Click Default Configuration function. 
```c
void c4x4key_default_cfg ( c4x4key_t *ctx );
```

- `c4x4key_get_data` Get 16-bit data function. 
```c
uint16_t c4x4key_get_data ( c4x4key_t *ctx );
```
 
- `c4x4key_get_btn_position` Get position pressed button function. 
```c
uint8_t c4x4key_get_btn_position ( c4x4key_t *ctx );
```

### Application Init

>
> Configuring Clicks and log objects.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c4x4key_cfg_t cfg;

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
    log_printf( &logger, "- Application Init -\r\n" );
    log_printf( &logger, "--------------------\r\n" );

    //  Click initialization.

    c4x4key_cfg_setup( &cfg );
    C4X4KEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4x4key_init( &c4x4key, &cfg );
    
    btn_data_old = 0;
    
    log_printf( &logger, "   4x4 Key Click\r\n" );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "  Press any button\r\n" );
    log_printf( &logger, "--------------------\r\n" );
}
```

### Application Task

>
> This is a example which demonstrates the use of 4x4 Key Click board.
> Detects and logs whether any of the buttons is pressed.
> Results are being sent to the Usart Terminal
> where you can track their changes.
> All data logs on usb uart when the button is triggered.
> 

```c
void application_task ( void )
{
    uint16_t btn_data;
    
    btn_data = c4x4key_get_data( &c4x4key );

    if ( btn_data_old != btn_data )
    {
        if ( btn_data == C4X4KEY_BUTTON_0 )
        {
            log_printf( &logger, "         0\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_1 )
        {
            log_printf( &logger, "         1\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_2 )
        {
            log_printf( &logger, "         2\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_3 )
        {
            log_printf( &logger, "         3\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_4 )
        {
            log_printf( &logger, "         4\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_5 )
        {
            log_printf( &logger, "         5\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_6 )
        {
            log_printf( &logger, "         6\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_7 )
        {
            log_printf( &logger, "         7\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_8 )
        {
            log_printf( &logger, "         8\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_9 )
        {
            log_printf( &logger, "         9\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_A )
        {
            log_printf( &logger, "         A\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_B )
        {
            log_printf( &logger, "         B\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_C )
        {
            log_printf( &logger, "         C\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_D )
        {
            log_printf( &logger, "         D\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_STAR )
        {
            log_printf( &logger, "         *\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_HASH )
        {
            log_printf( &logger, "         #\r\n" );
        }

        btn_data_old = btn_data;
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
