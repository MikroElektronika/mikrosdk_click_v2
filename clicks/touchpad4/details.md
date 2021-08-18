
---
# Touchpad 4 click

> Touchpad 4 Click is a compact add-on board that easily integrates projected capacitive touch into user's applications. This board features the IQS7211A, a tiny capacitive touch controller from Azoteq.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchpad_4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/touchpad-4-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Touchpad4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Touchpad4 Click driver.

#### Standard key functions :

- `touchpad4_cfg_setup` Config Object Initialization function.
```c
void touchpad4_cfg_setup ( touchpad4_cfg_t *cfg );
```

- `touchpad4_init` Initialization function.
```c
TOUCHPAD4_RETVAL touchpad4_init ( touchpad4_t *ctx, touchpad4_cfg_t *cfg );
```

- `touchpad4_default_cfg` Click Default Configuration function.
```c
void touchpad4_default_cfg ( touchpad4_t *ctx );
```

#### Example key functions :

- `touchpad4_reset` Reset function.
```c
void touchpad4_reset ( touchpad4_t *ctx );
```

- `touchpad4_get_touch` Read touch informations.
```c
err_t touchpad4_get_touch ( touchpad4_t *ctx, touchpad4_info_t *touch_info );
```

- `touchpad_get_channels` Read channel information.
```c
err_t touchpad_get_channels ( touchpad4_t *ctx, uint32_t *channels );
```

## Example Description

> This example showcases ability of the device to read touch coordinates, 
active/inactive channels, and gesture informations.

**The demo application is composed of two sections :**

### Application Init

> Initialize host communication modules(UART and I2C)  and additional pins,
for device control. Then resets device and set default configuration where
Channels and pins are mapped and configured, and set communication with device
only on touch/event. In the end one of 3 examples is set;

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    touchpad4_cfg_t touchpad4_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    touchpad4_cfg_setup( &touchpad4_cfg );
    TOUCHPAD4_MAP_MIKROBUS( touchpad4_cfg, MIKROBUS_1 );
    err_t init_flag = touchpad4_init( &touchpad4, &touchpad4_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    touchpad4_reset( &touchpad4 );

    init_flag = touchpad4_default_cfg ( &touchpad4 );
    if ( TOUCHPAD4_ERROR == init_flag ) 
    {
        log_error( &logger, " Configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    example_selector = TOUCHPAD4_EXAMPLE_TOUCH;
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> There are 3 examples that shocaes ability of the device: 
 - Reading touch coorinates and addinal informations of touch strength, 
   and touch area and logging them,
 - Reading channel statuses and show them by logging them,
 - Reading gesture events and logging them;

```c

void application_task ( void ) 
{
    if ( !touchpad4_get_ready( &touchpad4 ) )
    {
        switch ( example_selector )
        {
            case TOUCHPAD4_EXAMPLE_TOUCH:
            {
                touchpad4_touch_reading( );
                break;
            }
            case TOUCHPAD4_EXAMPLE_CHANNEL:
            {
                touchpad4_channel_reading( );
                break;
            }
            case TOUCHPAD4_EXAMPLE_GESTURE:
            {
                touchpad4_gesture_reading( );
                break;
            }
            default:
            {
                log_error( &logger, " Select Example" );
                break;
            }
        } 
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Touchpad4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
