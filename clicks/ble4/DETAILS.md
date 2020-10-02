 
---
# BLE 4  click

BLE 4 Click is fully embedded stand-alone Bluetooth 5.0 low energy connectivity module, equipped with the NINA-B312, an ultra-small, high-performing, standalone Bluetooth low energy module for easy integration of Bluetooth low energy connectivity (BLE) into various electronic devices. This module combines a high-performance Arm® Cortex®-M4 CPU microprocessor with FPU, and state-of-the-art power performance.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ble4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ble-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the BLE4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BLE4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ble4_cfg_setup ( ble4_cfg_t *cfg ); 
 
- Initialization function.
> BLE4_RETVAL ble4_init ( ble4_t *ctx, ble4_cfg_t *cfg );

- Click Default Configuration function.
> void ble4_default_cfg ( ble4_t *ctx );


#### Example key functions :

- This is the generic write function for the UART communication protocol.
> void ble4_generic_write ( ble4_t *ctx, char *data_buf, uint16_t len );
 
- This is the generic read function for the UART communication protocol.
> uint16_t ble4_generic_read ( ble4_t *ctx, char *data_buf, uint16_t max_len );

- This function performs a hardware reset of the device.
> void ble4_hardware_reset ( ble4_t *ctx );

## Examples Description

> This example reads and processes data from BLE 4 clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble4_cfg_setup( &cfg );
    BLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble4_init( &ble4, &cfg );

    //  Module configuration.

    ble4_hardware_reset( &ble4 );
    Delay_1sec( );
    ble4_factory_reset( &ble4 );
    Delay_1sec( );
    ble4_set_device_name( &ble4, dev_name );
    Delay_1sec( );
    ble4_set_data_mode( &ble4, BLE4_DATA_MODE );
    Delay_1sec( );
#ifdef TX_MODE
    log_printf( &logger, " * Device mode: TX *\r\n" );
#endif
#ifdef RX_MODE
    log_printf( &logger, " * Device mode: RX *\r\n" );
#endif
    log_printf( &logger, "----Initialized----\r\n" );
    Delay_1sec( );

    process_cnt = 0;
}
  
```

### Application Task

> Reads the received data and parses it. 

```c

void application_task ( void )
{
#ifdef TX_MODE
    uint8_t cnt;

    for( cnt = 0; cnt < 9; cnt++ ) 
    {
        ble4_generic_write( &ble4, &message[ cnt ], 1 );
        Delay_1sec( );
    }
#endif 
#ifdef RX_MODE

    ble4_process( );
#endif 
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}  

```



The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE4

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
