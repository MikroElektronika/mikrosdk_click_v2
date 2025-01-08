
---
# Knob Click

> [Knob Click](https://www.mikroe.com/?pid_product=MIKROE-3299) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3299&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo application displays different types of LED controls and encoder position readings.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Knob

### Example Key Functions

- `knob_cfg_setup` Config Object Initialization function. 
```c
void knob_cfg_setup ( knob_cfg_t *cfg );
``` 
 
- `knob_init` Initialization function. 
```c
err_t knob_init ( knob_t *ctx, knob_cfg_t *cfg );
```

- `knob_default_cfg` Click Default Configuration function. 
```c
void knob_default_cfg ( knob_t *ctx );
```

- `knob_get_encoder_position` Functions for get Encoder position. 
```c
void knob_get_encoder_position ( knob_t *ctx, int32_t *position, uint8_t *dir );
```
 
- `knob_set_led_state` Functions for set led state(PWM on the LED). 
```c
void knob_set_led_state ( knob_t *ctx, uint8_t led, uint8_t state );
```

- `knob_get_sw_button_state` Functions for get SW pin(switch button) state. 
```c
uint8_t knob_get_sw_button_state ( knob_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    knob_cfg_t cfg;

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

    knob_cfg_setup( &cfg );
    KNOB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    knob_init( &knob, &cfg );

    knob_reset( &knob );
    Delay_ms ( 300 );

    knob_default_cfg( &knob );
}
```

### Application Task

> The Task application has 3 test modes:
>  - The first example is setting BRIGHTNESS on all LEDs.
>  - Other examples put the LED in the position read from the encoder.
>  - The third example sets the LED to be read while the encoder registers the clockwise movement
>    and turn off those LEDs that the encoder reads when moving in a counterclockwise direction.
>  - The example is changed by pressing the SW button

```c
void application_task ( void )
{
    uint8_t cnt;
    uint8_t direction;

    //  Task implementation.

    knob_get_encoder_position( &knob, &new_position, &direction );

    if ( knob_get_sw_button_state( &knob ) == 0 )
    {
        sw_state++;
        if ( sw_state >= 3 ) sw_state = 0;

        knob_set_brightness( &knob, KNOB_BRIGHTNESS_ALL_LED, 0x00 );
        Delay_ms ( 300 );
    }

    // Logs position

    if ( new_position != old_position )
    {
        log_printf( &logger, "** EnCoder position : %d ", new_position );
    }
    old_position = new_position;

    switch ( sw_state )
    {
        // Brightness

        case 0:
        {
            cnt++;
            if ( cnt > 127 )
            {
                cnt = 0;
            }
            knob_set_brightness( &knob, KNOB_BRIGHTNESS_ALL_LED, cnt );
            Delay_ms ( 15 );

            break;
        }

        // Encoder with one led

        case 1:
        {
            if ( new_position > 24 )
            {
                knob_set_encoder_start_position( &knob, 1 );
            }
            if ( new_position < 1 )
            {
                knob_set_encoder_start_position( &knob, 24 );
            }

            if (direction == 1)
            {
                knob_set_led_state( &knob, new_position, KNOB_LED_ON );
                knob_set_led_state( &knob, new_position - 1, KNOB_LED_OFF );
            }
            else
            {
                knob_set_led_state( &knob, new_position, KNOB_LED_ON );
                knob_set_led_state( &knob, new_position + 1, KNOB_LED_OFF );
            }
            Delay_1ms();
            break;
        }

        // Encoder with all led

        case 2:
        {
            if ( new_position > 24 )
            {
                knob_set_encoder_start_position( &knob, 1 );
            }
            if ( new_position < 1 )
            {
                knob_set_encoder_start_position( &knob, 24 );
            }

            if ( direction == 1 )
            {
                knob_set_led_state( &knob, new_position, KNOB_LED_ON );
            }
            else
            {
                knob_set_led_state( &knob, new_position + 1, KNOB_LED_OFF);
            }
            Delay_1ms();
            break;
        }
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
