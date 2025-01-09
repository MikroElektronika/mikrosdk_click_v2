
---
# Led ring R  Click

> [Led ring R Click](https://www.mikroe.com/?pid_product=MIKROE-2153) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2153&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> LED ring  R Click is a mikroBUS&trade; add-on board with a ring of 32 red LEDs driven. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedringR

### Example Key Functions

- `ledringr_cfg_setup` Config Object Initialization function. 
```c
void ledringr_cfg_setup ( ledringr_cfg_t *cfg );
``` 
 
- `ledringr_init` Initialization function. 
```c
err_t ledringr_init ( ledringr_t *ctx, ledringr_cfg_t *cfg );
```

- `ledringr_generic_transfer` Generic transfer function. 
```c
void ledringr_generic_transfer ( ledringr_t *ctx, spi_master_transfer_data_t *block );
```

- `ledringr_write_data` Generic write function. 
```c
void ledringr_write_data ( ledringr_t *ctx, uint32_t data_to_write );
```
 
- `ledringr_turn_on_led` Turn On LED by position. 
```c
void ledringr_turn_on_led ( ledringr_t *ctx, uint8_t led_position );
```

- `ledringr_led_ring_set` Set led. 
```c
void ledringr_led_ring_set ( ledringr_t *ctx );
```

### Application Init

> Initializes SPI driver and performs device configuration. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ledringr_cfg_t cfg;

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

    ledringr_cfg_setup( &cfg );
    LEDRINGR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledringr_init( &ledringr, &cfg );
}
```

### Application Task

> Show functionality of Led_Ring_R Click, rotating and turn on/off led's, using the SPI interface. 

```c
void application_task ( void )
{
    uint32_t ring_led_on = 0x00000001;
    uint8_t ring_led_counter;
    uint8_t number_led;

    ledringr_led_ring_set( &ledringr );

    for ( ring_led_counter = 32; ring_led_counter > 0; ring_led_counter--)
    {
        ledringr_turn_on_led( &ledringr, ring_led_counter );
        Delay_100ms( );
    }

    Delay_100ms( );

    while ( ring_led_on < 0xFFFFFFFF )
    {
        ledringr_write_data( &ledringr, ring_led_on );
        ring_led_on = ring_led_on | (ring_led_on << 1);
        Delay_100ms( );
    }
    ledringr_write_data( &ledringr, ring_led_on );

    while ( ring_led_on > 0x00000001 )
    {
        ledringr_write_data( &ledringr, ring_led_on );
        ring_led_on = ring_led_on >> 1;
        Delay_100ms( );
    }
    ledringr_write_data( &ledringr, ring_led_on );

    Delay_100ms( );

    ring_led_on = 0x11111111;
    for ( ring_led_counter = 0; ring_led_counter < 32; ring_led_counter++ )
    {
        ledringr_write_data( &ledringr, ring_led_on );

        ring_led_on *= 2;

        if ( ring_led_on == 0x88888888 )
        {
            ring_led_on = 0x11111111;
        }
            
        Delay_100ms( );
    }
    
    for ( ring_led_counter = 0; ring_led_counter < 16; ring_led_counter++ )
    {
        ledringr_write_data( &ledringr, 0xAAAAAAAA );
        Delay_100ms( );
        
        ledringr_write_data( &ledringr, 0x55555555 );
        Delay_100ms( );
    }

    ledringr_led_ring_reset( &ledringr );

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
