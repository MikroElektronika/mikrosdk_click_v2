\mainpage Main Page

---
# ROTARY R Click

Rotary Click carries a 15-pulse incremental rotary encoder with detents, surrounded by a ring of 16 red LEDs. It’s a perfect solution for adding a precision input knob to your design. The encoder outputs A and B signals (out of phase to each other); the knob also acts as a push-button which sends an interrupt to the target board MCU. The LED ring is controlled through SPI lines (CS, SCK, MISO, MOSI). Rotary Click can be used with either a 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rotaryr_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rotary-r-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the RotaryR Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RotaryR Click driver.

#### Standard key functions :

- `rotaryr_cfg_setup` Config Object Initialization function.
```c
void rotaryr_cfg_setup ( rotaryr_cfg_t *cfg );
```

- `rotaryr_init` Initialization function.
```c
ROTARYR_RETVAL rotaryr_init ( rotaryr_t *ctx, rotaryr_cfg_t *cfg );
```

#### Example key functions :

- `rotaryr_generic_transfer` ROTARY R data transfer function.
```c
void rotaryr_generic_transfer ( rotaryr_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );
```

- `rotaryr_turn_on_led_by_position` Function turn on led by position
```c
void rotaryr_turn_on_led_by_position ( rotaryr_t *ctx, uint8_t led_position );
```

- `rotaryr_button_push` Function return 1 if button is pushed and return 0 if not
```c
uint8_t rotaryr_button_push ( rotaryr_t *ctx );
```

## Example Description

> The demo application controls led on Click with rotary on board.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI driver, set initial states, set RST logic high and performs device configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryr_cfg_t rotaryr_cfg;  /**< Click config object. */

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

    rotaryr_cfg_setup( &rotaryr_cfg );
    ROTARYR_MAP_MIKROBUS( rotaryr_cfg, MIKROBUS_1 );
    err_t init_flag  = rotaryr_init( &rotaryr, &rotaryr_cfg );
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

> Show functionality of Rotary R Click, rotating and turn on/off led's, using the SPI interface.

```c

void application_task ( void ) {
    rotaryr_turn_on_led_by_data( &rotaryr, led_data );

//     Push button
    if ( rotaryr_button_push( &rotaryr ) ) {
        new_state = 1;
        if ( new_state == 1 && old_state == 0 ) {
            old_state = 1;
            led_state = ( led_state + 1 ) % 5;
            if ( led_state == 4 ) {
                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryr_turn_on_led_by_data( &rotaryr, 0xAAAA );
                    Delay_ms ( 100 );
                    rotaryr_turn_on_led_by_data( &rotaryr, 0x5555 );
                    Delay_ms ( 100 );
                }

                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryr_turn_on_led_by_position( &rotaryr, old_state );
                    Delay_ms ( 100 );
                }

                led_state = 0;
                led_data = rotaryr_get_led_data( led_state );
            }
            else {
                led_data = rotaryr_get_led_data( led_state );
            }
        }
    }
    else {
        old_state = 0;
    }

//     Rotate Clockwise and CounterClockwise
    if ( rotaryr_get_eca_state( &rotaryr ) == rotaryr_get_ecb_state( &rotaryr ) ) {
        old__rot_state = 0;
        start_status = rotaryr_get_eca_state( &rotaryr ) && rotaryr_get_ecb_state( &rotaryr );
    }
    else {
        new_rotate_state = 1;
        if ( new_rotate_state != old__rot_state ) {
            old__rot_state = 1;
            if ( start_status != rotaryr_get_eca_state( &rotaryr ) ) {
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
- Click.RotaryR

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
