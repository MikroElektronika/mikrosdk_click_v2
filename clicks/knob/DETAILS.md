
 

---
# Knob click

Knob click features a combination of high-quality quadrature rotary encoder, and a LED ring composed of 24 individual green LEDs. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/knobg_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/knob-g-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Knob Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Knob Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void knob_cfg_setup ( knob_cfg_t *cfg ); 
 
- Initialization function.
> KNOB_RETVAL knob_init ( knob_t *ctx, knob_cfg_t *cfg );

- Click Default Configuration function.
> void knob_default_cfg ( knob_t *ctx );


#### Example key functions :

- Functions for get Encoder position
> void knob_get_encoder_position ( knob_t *ctx, int32_t *position, uint8_t *dir );
 
- Functions for set led state(PWM on the LED)
> void knob_set_led_state ( knob_t *ctx, uint8_t led, uint8_t state );

- Functions for get SW pin(switch button) state
> uint8_t knob_get_sw_button_state( knob_t *ctx );

## Examples Description

> The demo application displays different types of LED controls and encoder position readings.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

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
    Delay_ms( 300 );

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
        Delay_ms( 300 );
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
            Delay_ms( 15 );

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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Knob

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---