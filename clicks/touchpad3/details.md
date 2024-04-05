
---
# Touchpad 3 click

Touchpad 3 Click is a compact add-on board that allows users to easily integrate projected capacitive touch into their applications. This board features the MTCH6301, a turnkey capacitive touch controller that makes it easy for users to use popular multitouch and gesture interfaces from Microchip. This controller’s sophisticated combination of Self and Mutual capacitive scanning for XY touchscreens and touchpads enables several features, including single and dual-touch drawing, the reporting of 11 single-finger gestures, and the detection of up to 10 touches. This Click board™ is suitable for human-machine interfaces, keypad or scrolling functions, single-finger gesture-based interfaces, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchpad3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/touchpad-3-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Touchpad3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Touchpad3 Click driver.

#### Standard key functions :

- `touchpad3_cfg_setup` Config Object Initialization function.
```c
void touchpad3_cfg_setup ( touchpad3_cfg_t *cfg );
```

- `touchpad3_init` Initialization function.
```c
err_t touchpad3_init ( touchpad3_t *ctx, touchpad3_cfg_t *cfg );
```

- `touchpad3_default_cfg` Click Default Configuration function.
```c
void touchpad3_default_cfg ( touchpad3_t *ctx );
```

#### Example key functions :

- `touchpad3_general_configuration` The function performs the general configuration of the MTCH6301 Projected Capacitive Touch Controller on the TouchPad 3 click board.
```c
void touchpad3_general_configuration ( touchpad3_t *ctx );
```

- `touchpad3_decoding_configuration` The function performs the decoding configuration of the MTCH6301 Projected Capacitive Touch Controller on the TouchPad 3 click board.
```c
void touchpad3_decoding_configuration ( touchpad3_t *ctx );
```

- `touchpad3_sensor_mapping_configuration` The function configures the sensor mapping of the MTCH6301 Projected Capacitive Touch Controller on the TouchPad 3 click board.
```c
void touchpad3_sensor_mapping_configuration ( touchpad3_t *ctx );
```

## Example Description

> This example prints the coordinate points of the position we touch on a click. We use RST and INT pins. The whole project is done through i2c communication.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - Initializes I2C, set RST pin as an output, set INT pin as input and start to write log. I2C, perform a hardware reset, configuration (general, decoding, sensor mapping), get device ID and enable the touch, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                 /**< Logger config object. */
    touchpad3_cfg_t touchpad3_cfg;     /**< Click config object. */

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
    touchpad3_cfg_setup( &touchpad3_cfg );
    TOUCHPAD3_MAP_MIKROBUS( touchpad3_cfg, MIKROBUS_1 );
    err_t init_flag = touchpad3_init( &touchpad3, &touchpad3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) { 
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    touchpad3_default_cfg ( &touchpad3 );
    
    touch_id_state = 0;
    log_printf( &logger, "------------------------------\r\n" );
    device_id = touchpad3_get_device_id( &touchpad3 );
    Delay_ms ( 100 );
    log_printf( &logger, "     Get Device ID : %d \r\n      ", device_id );
    log_printf( &logger, "------------------------------\r\n" );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    status_data = touchpad3_config_touch( &touchpad3, TOUCHPAD3_TOUCH_GESTURE_ENABLE );
    
    log_printf( &logger, "     Touch Enable Status:     \r\n");
    display_status( );
    log_printf( &logger, "------------------------------\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the TouchPad 3 click board. TouchPad 3 click board uses USB UART log to display X and Y coordinates of the touch, depending on the selected Touch ID.

```c

void application_task ( void ) {
    if ( touchpad3_get_int( &touchpad3 ) == TOUCHPAD3_INT_STATUS_HIGH ) {
       
       touchpad3_get_touch( &touchpad3, &touch_data, &x_axis, &y_axis );
       Delay_ms ( 100 );

        if ( ( touch_data.tch_state == TOUCHPAD3_STATE_TCH ) && ( touch_data.touch_id == touch_id_state ) ) {   
            log_printf( &logger, "  X Coordinate : %d   \r\n" , x_axis );
            log_printf( &logger, "  Y Coordinate : %d   \r\n" , y_axis );
            log_printf( &logger, "------------------------------\r\n" );
            Delay_ms ( 100 );
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Touchpad3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
