
---
# RFID 2 Click

> RFID 2 Click is a compact add-on board that contains a stand-alone RFID reader with a built-in antenna easy-to-use for embedded applications. This board features the ID-12LA-SA, an advanced low-cost RFID reader module usable with 38 different tags from ID Innovations.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rfid2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rfid-2-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Aug 2021.
- **Type**          : UART type


# Software Support

We provide a library for the RFID2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RFID2 Click driver.

#### Standard key functions :

- `rfid2_cfg_setup` Config Object Initialization function.
```c
void rfid2_cfg_setup ( rfid2_cfg_t *cfg );
```

- `rfid2_init` Initialization function.
```c
err_t rfid2_init ( rfid2_t *ctx, rfid2_cfg_t *cfg );
```

#### Example key functions :

- `rfid2_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t rfid2_generic_write ( rfid2_t *ctx, char *data_buf, uint16_t len );
```

- `rfid2_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rfid2_generic_read ( rfid2_t *ctx, char *data_buf, uint16_t max_len );
```

- `rfid2_reset` This function resets the chip.
```c
void rfid2_reset( rfid2_t *ctx );
```

## Example Description

> This example reads and processes data from RFID 2 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART module and sets RST pin as OUTPUT and INT pin as INPUT. Also, initializes Driver init and reset chip.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;      /**< Logger config object. */
    rfid2_cfg_t rfid2_cfg;  /**< Click config object. */

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
    rfid2_cfg_setup( &rfid2_cfg );
    RFID2_MAP_MIKROBUS( rfid2_cfg, MIKROBUS_1 );
    err_t init_flag  = rfid2_init( &rfid2, &rfid2_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    rfid2_reset( &rfid2 );
    Delay_ms ( 100 );

    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    log_printf( &logger, "*** Please, put your ID card.***\r\n" );
    log_printf( &logger, "*** ID card :\r\n" );
}

```

### Application Task

> Reads the ID card (HEX) and logs data on the USBUART-a.

```c

void application_task ( void ) {
    app_buf_len = rfid2_generic_read( &rfid2, app_buf, PROCESS_BUFFER_SIZE );
    
    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        memset( app_buf, 0, PROCESS_BUFFER_SIZE );    
    }
}

```
The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RFID2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
