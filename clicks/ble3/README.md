\mainpage Main Page
 
---
# BLE 3 Click

BLE 3 Click is a quick and simple solution if you want to add Bluetooth Low Energy to your project. It features the NINA-B1 Bluetooth 4.2 module, from u-blox. This Click also comes with an integrated antenna mounted on the PCB.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ble-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Ble3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ble3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ble3_cfg_setup ( ble3_cfg_t *cfg ); 
 
- Initialization function.
> BLE3_RETVAL ble3_init ( ble3_t *ctx, ble3_cfg_t *cfg );


#### Example key functions :

- Generic read function.
> int32_t ble3_generic_read ( ble3_t *ctx, char *data_buf, uint16_t max_len );

- Generic write function.
> void ble3_generic_write ( ble3_t *ctx, char *data_buf, uint16_t len ); 

## Examples Description

> This example reads and processes data from BLE 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble3_cfg_t cfg;
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
    //  Click initialization.

    ble3_cfg_setup( &cfg );
    BLE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble3_init( &ble3, &cfg );
    
    log_printf( &logger, "Configuring the module...\n" );
    Delay_1sec( );
    
    do {
        ble3_generic_write( &ble3, AT, (uint16_t) strlen( AT ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, ATE1, (uint16_t) strlen( ATE1 ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTLN, (uint16_t) strlen( AT_UBTLN ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTDM, (uint16_t) strlen( AT_UBTDM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTCM, (uint16_t) strlen( AT_UBTCM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTPM, (uint16_t) strlen( AT_UBTPM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, ATO1, (uint16_t) strlen( ATO1 ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    data_mode = 1;
    log_printf( &logger, "The module has been configured.\n" );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    ble3_process(  );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
