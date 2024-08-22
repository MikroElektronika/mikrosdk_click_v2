\mainpage Main Page

---
# Joystick 4 click

> Joystick 4 Click is a compact add-on board that provides precise and reliable input control for various interactive projects. This board features the 2434804-1, a 5-position tactile switch from the ALCOSWITCH series by TE Connectivity. The switch features an extended top actuator for precise input detection, a stainless steel contact base, and silver contact plating, ensuring durability and corrosion resistance with a lifespan of 100,000 cycles. With a low-profile design, it handles a contact current rating of 50mA.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/joystick4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/joystick-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Joystick 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Joystick 4 Click driver.

#### Standard key functions :

- `joystick4_cfg_setup` Config Object Initialization function.
```c
void joystick4_cfg_setup ( joystick4_cfg_t *cfg );
```

- `joystick4_init` Initialization function.
```c
err_t joystick4_init ( joystick4_t *ctx, joystick4_cfg_t *cfg );
```

- `joystick4_default_cfg` Click Default Configuration function.
```c
err_t joystick4_default_cfg ( joystick4_t *ctx );
```

#### Example key functions :

- `joystick4_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t joystick4_get_int_pin ( joystick4_t *ctx );
```

- `joystick4_get_pins` This function reads all input pins logic state.
```c
err_t joystick4_get_pins ( joystick4_t *ctx, uint8_t *pin_mask );
```

- `joystick4_get_position` This function returns the joystick position flag extracted from the input pins state mask.
```c
uint8_t joystick4_get_position ( uint8_t pin_mask );
```

## Example Description

> This example demonstrates the use of the Joystick 4 click board by reading and displaying the joystick position.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    joystick4_cfg_t joystick4_cfg;  /**< Click config object. */

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
    joystick4_cfg_setup( &joystick4_cfg );
    JOYSTICK4_MAP_MIKROBUS( joystick4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == joystick4_init( &joystick4, &joystick4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( JOYSTICK4_ERROR == joystick4_default_cfg ( &joystick4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    if ( JOYSTICK4_PIN_STATE_HIGH == joystick4_get_int_pin ( &joystick4 ) )
    {
        log_printf ( &logger, " Joystick position: IDLE\r\n\n" );
    }
}

```

### Application Task

> Waits for the input change interrupt, reads the input pins mask, extracts the joystick position from those readings, and displays it on the USB UART.

```c
void application_task ( void )
{
    uint8_t pin_mask = 0;
    if ( JOYSTICK4_PIN_STATE_LOW == joystick4_get_int_pin ( &joystick4 ) )
    {
        if ( JOYSTICK4_OK == joystick4_get_pins ( &joystick4, &pin_mask ) )
        {
            log_printf ( &logger, " Joystick position: " );
            switch ( joystick4_get_position ( pin_mask ) )
            {
                case JOYSTICK4_POSITION_IDLE:
                {
                    log_printf ( &logger, "IDLE" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER:
                {
                    log_printf ( &logger, "CENTER" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_UP:
                {
                    log_printf ( &logger, "CENTER-UP" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_RIGHT:
                {
                    log_printf ( &logger, "CENTER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_DOWN:
                {
                    log_printf ( &logger, "CENTER-DOWN" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_LEFT:
                {
                    log_printf ( &logger, "CENTER-LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_UP:
                {
                    log_printf ( &logger, "UP" );
                    break;
                }
                case JOYSTICK4_POSITION_UPPER_RIGHT:
                {
                    log_printf ( &logger, "UPPER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_RIGHT:
                {
                    log_printf ( &logger, "RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_LOWER_RIGHT:
                {
                    log_printf ( &logger, "LOWER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_DOWN:
                {
                    log_printf ( &logger, "DOWN" );
                    break;
                }
                case JOYSTICK4_POSITION_LOWER_LEFT:
                {
                    log_printf ( &logger, "LOWER-LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_LEFT:
                {
                    log_printf ( &logger, "LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_UPPER_LEFT:
                {
                    log_printf ( &logger, "UPPER-LEFT" );
                    break;
                }
                default:
                {
                    log_printf ( &logger, "UNKNOWN" );
                    break;
                }
            }
            log_printf ( &logger, "\r\n\n" );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Joystick4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
