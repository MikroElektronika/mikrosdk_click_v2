\mainpage Main Page

---
# UT-M 7-SEG R click

UT-M 7-SEG R click carries two SMD ultra thin LED 7-SEG displays and the MAX6969 constant-current LED driver from Maxim Integrated. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over SPI interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/utm7segr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ut-m-7-seg-r-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the UT-M7-SEGR Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UT-M7-SEGR Click driver.

#### Standard key functions :

- `utm7segr_cfg_setup` Config Object Initialization function.
```c
void utm7segr_cfg_setup ( utm7segr_cfg_t *cfg );
```

- `utm7segr_init` Initialization function.
```c
UTM7SEGR_RETVAL utm7segr_init ( utm7segr_t *ctx, utm7segr_cfg_t *cfg );
```

- `utm7segr_default_cfg` Click Default Configuration function.
```c
void utm7segr_default_cfg ( utm7segr_t *ctx );
```

#### Example key functions :

- `utm7segr_generic_write` This function writes a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
err_t utm7segr_generic_write ( utm7segr_t *ctx, uint8_t *data_in );
```

- `utm7segr_display_state` This function turns display on and off.
```c
void utm7segr_display_state ( utm7segr_t *ctx, uint8_t state ) ;
```

- `utm7segr_display_number` This function is used to show the number on the display.
```c
err_t utm7segr_display_number ( utm7segr_t *ctx, uint8_t number, uint8_t dot_pos );
```

## Example Description

> The demo application shows basic usage of the UT-M 7-SEG display.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects. Settings the click in the default configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    utm7segr_cfg_t utm7segr_cfg;  /**< Click config object.  */

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

    // Click initialization.

    utm7segr_cfg_setup( &utm7segr_cfg );
    UTM7SEGR_MAP_MIKROBUS( utm7segr_cfg, MIKROBUS_1 );
    err_t init_flag  = utm7segr_init( &utm7segr, &utm7segr_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    utm7segr_default_cfg ( &utm7segr );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Draws numbers from 0 to 99 on the screen.

```c

void application_task ( void ) {  
    log_info( &logger, "---- Number counter ----" );

    for ( uint8_t cnt = 0; cnt < 100; cnt++ ) {
        utm7segr_display_number( &utm7segr, cnt, UTM7SEGR_DOT_LEFT );
        Delay_ms( 500 );
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UT-M7-SEGR

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
