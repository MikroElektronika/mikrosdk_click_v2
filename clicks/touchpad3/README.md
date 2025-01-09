
---
# Touchpad 3 Click

> [Touchpad 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4382) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4382&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example prints the coordinate points of the position we touch on a Click. We use RST and INT pins. The whole project is done through i2c communication.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Touchpad3

### Example Key Functions

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

- `touchpad3_general_configuration` The function performs the general configuration of the MTCH6301 Projected Capacitive Touch Controller on the TouchPad 3 Click board.
```c
void touchpad3_general_configuration ( touchpad3_t *ctx );
```

- `touchpad3_decoding_configuration` The function performs the decoding configuration of the MTCH6301 Projected Capacitive Touch Controller on the TouchPad 3 Click board.
```c
void touchpad3_decoding_configuration ( touchpad3_t *ctx );
```

- `touchpad3_sensor_mapping_configuration` The function configures the sensor mapping of the MTCH6301 Projected Capacitive Touch Controller on the TouchPad 3 Click board.
```c
void touchpad3_sensor_mapping_configuration ( touchpad3_t *ctx );
```

### Application Init

> Initialization driver enables - Initializes I2C, set RST pin as an output, set INT pin as input and start to write log. I2C, perform a hardware reset, configuration (general, decoding, sensor mapping), get device ID and enable the touch, also write log.

```c
void application_init ( void ) 
{
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

> This is an example that demonstrates the use of the TouchPad 3 Click board. TouchPad 3 Click board uses USB UART log to display X and Y coordinates of the touch, depending on the selected Touch ID.

```c
void application_task ( void ) 
{
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
