
---
# RN4678 Click

RN4678 Click carries the RN4678 Bluetooth® 4.2 dual mode module from Microchip. The Click is designed to run on a 3.3V power supply. It communicates with the target microcontroller over I2C and UART interface, with additional functionality provided by the following pins on the mikroBUS™ line: AN, RST, CS, PWM, INT.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rn4678_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rn4678-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Rn4678 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rn4678 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rn4678_cfg_setup ( rn4678_cfg_t *cfg ); 
 
- Initialization function.
> RN4678_RETVAL rn4678_init ( rn4678_t *ctx, rn4678_cfg_t *cfg );

- Enable device function
> void rn4678_enable ( rn4678_t *ctx );


#### Example key functions :

- Enter the command mode function
> void rn4678_enter_command_mode ( rn4678_t *ctx );
 
- Exit the command mode function
> void rn4678_exit_command_mode ( rn4678_t *ctx );

- Set the device name function
> void rn4678_set_device_name ( rn4678_t *ctx, uint8_t *name );

## Examples Description

> This example reads and processes data from RN4678 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4678_cfg_t cfg;

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

    rn4678_cfg_setup( &cfg );
    RN4678_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4678_init( &rn4678, &cfg );

    rn4678_enable ( &rn4678 );
    Delay_ms ( 1000 );
    rn4678_hw_reset ( &rn4678 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Configuring the module...\n" );
    
    do
    {    
        log_printf( &logger, " --- Command mode --- \r\n" );
        rn4678_enter_command_mode( &rn4678 );
    }
    while( rn4678_process( "CMD" ) != 1 );
    
    do
    {
        log_printf( &logger, " --- Device name --- \r\n" );
        rn4678_set_device_name( &rn4678, &DEVICE_NAME_DATA[ 0 ] );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Status string --- \r\n" );
        rn4678_set_extended_status_string( &rn4678, &EXTENDED_STRING_DATA[ 0 ] );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Operating mode --- \r\n" );
        rn4678_set_operating_mode( &rn4678, 0 );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Authentication --- \r\n" );
        rn4678_set_authentication( &rn4678, 1 );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Pin code --- \r\n" );
        rn4678_set_security_pin_code( &rn4678, &PIN_CODE_DATA[ 0 ] );
    }
    while( rn4678_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Exit command mode --- \r\n" );
        rn4678_exit_command_mode( &rn4678 );
    }
    while( rn4678_process( "END" ) != 1 );
    
    log_printf( &logger, "The module has been configured.\n" );
    
    rn4678_set_cts_pin( &rn4678, 0 );
}
  
```

### Application Task

> Checks for the received data, reads it and replies with a certain message.

```c

void application_task ( void )
{
    rn4678_process( PROCESS_LOG_RSP );
}

```

## Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
> A smartphone and the Click board must be paired in order to exchange messages with each other.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rn4678

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
