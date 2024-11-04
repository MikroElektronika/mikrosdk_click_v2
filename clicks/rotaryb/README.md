\mainpage Main Page

---
# ROTARY B Click

Rotary B Click carries a 15-pulse incremental rotary encoder with detents, surrounded by a ring of 16 blue LEDs. It’s a perfect solution for adding a precision input knob to your design. The encoder outputs A and B signals (out of phase to each other); the knob also acts as a push-button which sends an interrupt to the target board MCU. The LED ring is controlled through SPI lines (CS, SCK, MISO, MOSI). Rotary Click™ can be used with either a 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rotaryb_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rotary-b-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the RotaryB Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RotaryB Click driver.

#### Standard key functions :

- `rotaryb_cfg_setup` Config Object Initialization function.
```c
void rotaryb_cfg_setup ( rotaryb_cfg_t *cfg );
```

- `rotaryb_init` Initialization function.
```c
ROTARYB_RETVAL rotaryb_init ( rotaryb_t *ctx, rotaryb_cfg_t *cfg );
```

#### Example key functions :

- `rotaryb_generic_transfer` ROTARY B data transfer function.
```c
void rotaryb_generic_transfer ( rotaryb_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );
```

- `rotaryb_turn_on_led_by_position` Function turn on led by position
```c
void rotaryb_turn_on_led_by_position ( rotaryb_t *ctx, uint8_t led_position );
```

- `rotaryb_button_push` Function return 1 if button is pushed and return 0 if not
```c
uint8_t rotaryb_button_push ( rotaryb_t *ctx );
```

## Example Description

> The demo application controls led on Click with rotary on board.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI driver, set initial states, set RST logic high and performs device configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryb_cfg_t rotaryb_cfg;  /**< Click config object. */

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

    rotaryb_cfg_setup( &rotaryb_cfg );
    ROTARYB_MAP_MIKROBUS( rotaryb_cfg, MIKROBUS_1 );
    err_t init_flag  = rotaryb_init( &rotaryb, &rotaryb_cfg );
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

> Show functionality of Rotary_R Click, rotating and turn on/off led's, using the SPI interface.

```c

void application_task ( void ) {
    rotaryb_turn_on_led_by_data( &rotaryb, led_data );

//     Push button
    if ( rotaryb_button_push( &rotaryb ) ) {
        new_state = 1;
        if ( new_state == 1 && old_state == 0 ) {
            old_state = 1;
            led_state = ( led_state + 1 ) % 5;
            if ( led_state == 4 ) {
                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryb_turn_on_led_by_data( &rotaryb, 0xAAAA );
                    Delay_ms ( 100 );
                    rotaryb_turn_on_led_by_data( &rotaryb, 0x5555 );
                    Delay_ms ( 100 );
                }

                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryb_turn_on_led_by_position( &rotaryb, old_state );
                    Delay_ms ( 100 );
                }

                led_state = 0;
                led_data = rotaryb_get_led_data( led_state );
            }
            else {
                led_data = rotaryb_get_led_data( led_state );
            }
        }
    }
    else {
        old_state = 0;
    }

//     Rotate Clockwise and CounterClockwise
    if ( rotaryb_get_eca_state( &rotaryb ) == rotaryb_get_ecb_state( &rotaryb ) ) {
        old__rot_state = 0;
        start_status = rotaryb_get_eca_state( &rotaryb ) && rotaryb_get_ecb_state( &rotaryb );
    }
    else {
        new_rotate_state = 1;
        if ( new_rotate_state != old__rot_state ) {
            old__rot_state = 1;
            if ( start_status != rotaryb_get_eca_state( &rotaryb ) ) {
                led_data = ( led_data << 1 ) | ( led_data >> 15 );
            }
            else {
                led_data = ( led_data >> 1 ) | ( led_data << 15 );
            }
        }
    }
}

```

## Note

> In orther to use all of the clicks functionality, pull down INT pin.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RotaryB

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
