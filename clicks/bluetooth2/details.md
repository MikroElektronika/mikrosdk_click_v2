
---
# Bluetooth 2 click

Bluetooth 2 Click features WT41u, a long range class 1, Bluetooth® 2.1 + EDR module from Silicon Labs. WT41u is a highly integrated and sophisticated Bluetooth® module, containing all the necessary elements from Bluetooth® radio and a fully implemented protocol stack. Therefore WT41u provides an ideal solution for developers who want to integrate Bluetooth® wireless technology into their design with limited knowledge of Bluetooth® and RF technologies. WT41u optimized for long range applications is available with an integrated chip antenna. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bluetooth2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bluetooth-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Bluetooth2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Bluetooth2 Click driver.

#### Standard key functions :

- `bluetooth2_cfg_setup` Config Object Initialization function.
```c
void bluetooth2_cfg_setup ( bluetooth2_cfg_t *cfg );
```

- `bluetooth2_init` Initialization function.
```c
err_t bluetooth2_init ( bluetooth2_t *ctx, bluetooth2_cfg_t *cfg );
```

- `bluetooth2_default_cfg` Click Default Configuration function.
```c
void bluetooth2_default_cfg ( bluetooth2_t *ctx );
```

#### Example key functions :

- `bluetooth2_factory_reset` This function factory resets the device.
```c
err_t bluetooth2_factory_reset ( bluetooth2_t *ctx );
```

- `bluetooth2_set_device_name` This function sets the local device name.
```c
err_t bluetooth2_set_device_name ( bluetooth2_t *ctx, char *dev_name );
```

- `bluetooth2_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t bluetooth2_generic_write ( bluetooth2_t *ctx, char *data_buf, uint16_t len );
```

## Example Description

> This example reads and processes data from Bluetooth 2 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, then performs a factory reset, removes all pairings, and sets the local device name.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    bluetooth2_cfg_t bluetooth2_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    bluetooth2_cfg_setup( &bluetooth2_cfg );
    BLUETOOTH2_MAP_MIKROBUS( bluetooth2_cfg, MIKROBUS_1 );
    err_t init_flag  = bluetooth2_init( &bluetooth2, &bluetooth2_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    bluetooth2_default_cfg ( &bluetooth2 );
    bluetooth2_process( );
    bluetooth2_clear_app_buf( );
    
    log_printf( &logger, " - Factory Reset -\r\n" );
    bluetooth2_factory_reset ( &bluetooth2 );
    bluetooth2_display_rsp ( 2000 ); 
    
    log_printf( &logger, " - Enable OK response -\r\n" );
    bluetooth2_enable_ok_response ( &bluetooth2 );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Remove Pairings -\r\n" );
    bluetooth2_remove_pairings ( &bluetooth2 );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    bluetooth2_set_device_name ( &bluetooth2, DEVICE_NAME );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Logs all the received messages/responses on the USB UART, and if there's any device
> connected to the click board the module sends a desired message every 5 seconds back to it.

```c

void application_task ( void )
{
    bluetooth2_process();
    if ( app_buf_len > 0 ) 
    {
        Delay_ms( 200 );
        bluetooth2_process();
        
        if ( strstr( app_buf, RSP_RING ) )
        {
            connection_flag = 1;
            send_cnt = 0;
        }
        if ( strstr( app_buf, RSP_NO_CARRIER ) )
        {
            connection_flag = 0;
            send_cnt = 0;
        }
        log_printf( &logger, "%s", app_buf );
        bluetooth2_clear_app_buf(  );
    }
    
    if ( connection_flag == 1 && send_cnt++ > SENDING_FREQ )
    {
        bluetooth2_generic_write( &bluetooth2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
        send_cnt = 0;
    }
    
    Delay_ms( 1 );
}

```

## Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
> A smartphone and the click board must be paired in order to exchange messages with each other.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Bluetooth2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
