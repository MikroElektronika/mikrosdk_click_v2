
---
# ROTARY Y Click

> [ROTARY Y Click](https://www.mikroe.com/?pid_product=MIKROE-1825) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1825&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> The demo application controls led on Click with rotary on board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RotaryY

### Example Key Functions

- `rotaryy_cfg_setup` Config Object Initialization function.
```c
void rotaryy_cfg_setup ( rotaryy_cfg_t *cfg );
```

- `rotaryy_init` Initialization function.
```c
err_t rotaryy_init ( rotaryy_t *ctx, rotaryy_cfg_t *cfg );
```

- `rotaryy_generic_transfer` ROTARY B data transfer function.
```c
void rotaryy_generic_transfer ( rotaryy_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );
```

- `rotaryy_turn_on_led_by_position` Function turn on led by position
```c
void rotaryy_turn_on_led_by_position ( rotaryy_t *ctx, uint8_t led_position );
```

- `rotaryy_button_push` Function return 1 if button is pushed and return 0 if not
```c
uint8_t rotaryy_button_push ( rotaryy_t *ctx );
```

### Application Init

> Initializes SPI driver, set initial states, set RST logic high and performs device configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryy_cfg_t rotaryy_cfg;  /**< Click config object. */

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

    rotaryy_cfg_setup( &rotaryy_cfg );
    ROTARYY_MAP_MIKROBUS( rotaryy_cfg, MIKROBUS_1 );
    err_t init_flag  = rotaryy_init( &rotaryy, &rotaryy_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    
    led_data = 0x0001;
    old_state = 0;
    new_state = 1;
    old__rot_state = 0;
    new_rotate_state = 1;
}
```

### Application Task

> Show functionality of Rotary Y Click, rotating and turn on/off led's, using the SPI interface.

```c
void application_task ( void ) 
{
    rotaryy_turn_on_led_by_data( &rotaryy, led_data );

//     Push button
    if ( rotaryy_button_push( &rotaryy ) ) {
        new_state = 1;
        if ( new_state == 1 && old_state == 0 ) {
            old_state = 1;
            led_state = ( led_state + 1 ) % 5;
            if ( led_state == 4 ) {
                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryy_turn_on_led_by_data( &rotaryy, 0xAAAA );
                    Delay_ms ( 100 );
                    rotaryy_turn_on_led_by_data( &rotaryy, 0x5555 );
                    Delay_ms ( 100 );
                }

                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryy_turn_on_led_by_position( &rotaryy, old_state );
                    Delay_ms ( 100 );
                }

                led_state = 0;
                led_data = rotaryy_get_led_data( led_state );
            }
            else {
                led_data = rotaryy_get_led_data( led_state );
            }
        }
    }
    else {
        old_state = 0;
    }

//     Rotate Clockwise and CounterClockwise
    if ( rotaryy_get_eca_state( &rotaryy ) == rotaryy_get_ecb_state( &rotaryy ) ) {
        old__rot_state = 0;
        start_status = rotaryy_get_eca_state( &rotaryy ) && rotaryy_get_ecb_state( &rotaryy );
    }
    else {
        new_rotate_state = 1;
        if ( new_rotate_state != old__rot_state ) {
            old__rot_state = 1;
            if ( start_status != rotaryy_get_eca_state( &rotaryy ) ) {
                led_data = ( led_data << 1 ) | ( led_data >> 15 );
            }
            else {
                led_data = ( led_data >> 1 ) | ( led_data << 15 );
            }
        }
    }
}
```

### Note

> In orther to use all of the Clicks functionality, pull down INT pin.

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
