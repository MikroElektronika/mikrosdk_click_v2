
---
# ATA6571 Click

ATA6571 Click is a compact add-on board that contains a transceiver designed for high-speed CAN applications. This board features the ATA6571, a standalone high-speed CAN FD transceiver that interfaces a CAN protocol controller and the physical two-wire CAN bus from Microchip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ata6571_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ata6571-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the ATA6571 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ATA6571 Click driver.

#### Standard key functions :

- `ata6571_cfg_setup` Config Object Initialization function.
```c
void ata6571_cfg_setup ( ata6571_cfg_t *cfg );
```

- `ata6571_init` Initialization function.
```c
err_t ata6571_init ( ata6571_t *ctx, ata6571_cfg_t *cfg );
```

#### Example key functions :

- `ata6571_set_operating_mode` This function sets the device operating mode by controlling the EN and NSTB pins.
```c
void ata6571_set_operating_mode ( ata6571_t *ctx, uint8_t op_mode );
```

- `ata6571_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t ata6571_generic_write ( ata6571_t *ctx, char *data_buf, uint16_t len );
```

- `ata6571_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t ata6571_generic_read ( ata6571_t *ctx, char *data_buf, uint16_t max_len );
```

## Example Description

> This example reads and processes data from ATA6571 Clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the device operating mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    ata6571_cfg_t ata6571_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ata6571_cfg_setup( &ata6571_cfg );
    ATA6571_MAP_MIKROBUS( ata6571_cfg, MIKROBUS_1 );
    err_t init_flag = ata6571_init( &ata6571, &ata6571_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_RECEIVER
    log_printf( &logger, "---- RECEIVER MODE ----\r\n" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "---- TRANSMITTER MODE ----\r\n" );
#endif 
    
    ata6571_set_operating_mode ( &ata6571, ATA6571_OPERATING_MODE_NORMAL );
    app_buf_len = 0;
    app_buf_cnt = 0;

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> Depending on the selected demo application mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    ata6571_process();

    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 100 );
        ata6571_process();
        
        log_printf( &logger, "%s", app_buf );
        log_printf( &logger, "-------------------------------------\r\n" );
        ata6571_clear_app_buf(  );
    }
#endif  

#ifdef DEMO_APP_TRANSMITTER 
    ata6571_generic_write( &ata6571, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, "---- The message has been sent ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ATA6571

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
