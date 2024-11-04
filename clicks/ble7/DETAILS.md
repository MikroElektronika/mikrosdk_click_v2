\mainpage Main Page
 
---
# BLE 7 Click

The BLE 7 Click is a Click board™ witch provide BT/BLE connectivity for any embedded application. BLE 7 Click based on the BGX13S22GA-V31, a SiP module from Silicon Labs with a buit-in antenna. Click board™ an ultra-small, high-performing, Bluetooth low energy module for easy integration of Bluetooth low energy connectivity (BLE) into various electronic devices. Given its features, this Click can be used for health, sports, and wellness devices as well as Industrial, home, and building automation; and smart phone, tablet, and PC accessories.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ble-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Ble7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ble7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ble7_cfg_setup ( ble7_cfg_t *cfg ); 
 
- Initialization function.
> BLE7_RETVAL ble7_init ( ble7_t *ctx, ble7_cfg_t *cfg );


#### Example key functions :

- This function allows user to reset BGX module.
> void ble7_reset ( ble7_t *ctx );

- This function allows user to transmit data to the BGX module.
> void ble7_send_command ( ble7_t *ctx, char *command );

## Examples Description

> This example reads and processes data from BLE 7 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble7_cfg_t cfg;

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

    ble7_cfg_setup( &cfg );
    BLE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble7_init( &ble7, &cfg );
    Delay_1sec( );
    
    log_printf( &logger, "Configuring the module...\r\n" );
    Delay_1sec( );
    config_mode = 1;
    
    do 
    {
        ble7_reset( &ble7 );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_CLEAR_BONDING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_ECHO );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_PAIRING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_BONDING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_DEVICE_NAME );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_ADVERTISING_ON );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_ADVERTISING_HIGH_DURATION );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SAVE_CONFIGURATION );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SWITCH_TO_STREAM_MODE );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    config_mode = 0;
    log_printf( &logger, "The module has been configured.\r\n" );
    Delay_1sec( );
}
  
```

### Application Task

> Checks for the received data, reads it and replies with a certain message.

```c

void application_task ( void )
{
    ble7_process(  );
}  

```

## Note

> We have used the BLE Scanner smartphone application for the test. 
> A smartphone and the Click board must be paired in order to exchange messages with each other.
> For more information about the BGX module commands, please refer to the following link:
> https://docs.silabs.com/gecko-os/1/bgx/latest/commands

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble7

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
