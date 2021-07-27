\mainpage Main Page

---
# TouchPad 2 click

Touchpad 2 Click is a compact add-on board that easily integrates projected capacitive touch into their applications. This board features the IQS525, a projected capacitive touch and proximity trackpad/touchscreen controller from Azoteq. It features best in class sensitivity, signal-to-noise ratio, and automatic tuning of electrodes, in addition to the multi-touch and multi-hover feature. This Click board™ is characterized by embedded gesture engine recognition for simple gestures (tap, swipes, hold), as well as built-in noise detection and filtering.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchpad2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/touchpad-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the TouchPad2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TouchPad2 Click driver.

#### Standard key functions :

- `touchpad2_cfg_setup` Config Object Initialization function.
```c
void touchpad2_cfg_setup ( touchpad2_cfg_t *cfg );
```

- `touchpad2_init` Initialization function.
```c
TOUCHPAD2_RETVAL touchpad2_init ( touchpad2_t *ctx, touchpad2_cfg_t *cfg );
```

- `touchpad2_default_cfg` Click Default Configuration function.
```c
void touchpad2_default_cfg ( touchpad2_t *ctx );
```

#### Example key functions :

- `touchpad2_check_version` TouchPad 2 check version function.
```c
err_t touchpad2_check_version ( touchpad2_t *ctx, touchpad2_ver_info_t *ver_info );
```

- `touchpad2_get_touch` TouchPad 2 get touch function.
```c
err_t touchpad2_get_touch ( touchpad2_t *ctx, touchpad2_touch_t *touch_data );
```

## Example Description

> This library contains API for the TouchPad 2 Click driver.
> The library contains drivers to get touch details,
> the number of touches, X and Y coordinates and touch strength.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C driver, check communication and reads device version information.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    touchpad2_cfg_t touchpad2_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    touchpad2_cfg_setup( &touchpad2_cfg );
    TOUCHPAD2_MAP_MIKROBUS( touchpad2_cfg, MIKROBUS_1 );
    err_t init_flag = touchpad2_init( &touchpad2, &touchpad2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    touchpad2_default_cfg ( &touchpad2 );
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );
    
    touchpad2_check_version( &touchpad2, &ver_info );
    Delay_ms( 100 );
    
    if ( ver_info.product_num != TOUCHPAD2_IQS525_PRODUCT_NUMBER ) {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, " Product number : %u \r\n", ver_info.product_num );
    log_printf( &logger, " Project number : %u \r\n", ver_info.projec_num );
    log_printf( &logger, " Version        : %.1f \r\n", ver_info.version );
    log_printf( &logger, " HW ID          : %u \r\n", ver_info.hw_id );
    log_printf( &logger, " HW Revision    : %u \r\n", ver_info.hw_revision );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, " Waiting for a new touch\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the TouchPad 2 Click board. 
> Read XY data consisting of a status byte, the number of touches,
> X and Y coordinates and touch strength data. 
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
   
    touchpad2_wait_ready( &touchpad2 );
    
    touchpad2_get_touch ( &touchpad2, &touch_data );
    Delay_ms( 100 );
    
    if ( ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_1 ) || 
         ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_2 ) ||
         ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_3 ) ||
         ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_4 ) ||
         ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_5 ) ) {
        log_printf( &logger, "  Number of touches : %d \r\n", ( uint16_t ) touch_data.no_of_fingers );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, "  Coordinate X = %d \r\n", touch_data.x_pos );
        log_printf( &logger, "  Coordinate Y = %d \r\n", touch_data.y_pos );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, "  Touch Strength   : %u  \r\n", ( uint16_t ) touch_data.touch_str );
        log_printf( &logger, "------------------------ \r\n" );
        Delay_ms( 500 );    
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchPad2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
