\mainpage Main Page
 
 

---
# STSPIN233 click

STSPIN233 click is a complete solution for a 3-phase integrated motor driver, based on the STSPIN233, Low voltage 3-phase integrated motor driver.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stspin233_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stspin233-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Stspin233 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Stspin233 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void stspin233_cfg_setup ( stspin233_cfg_t *cfg ); 
 
- Initialization function.
> STSPIN233_RETVAL stspin233_init ( stspin233_t *ctx, stspin233_cfg_t *cfg );

#### Example key functions :

- Send single command
> void stspin233_send_single_cmd ( stspin233_t *ctx, uint8_t *tx_buf );
 
- Send double command
> void stspin233_send_double_cmd ( stspin233_t *ctx, uint8_t *cmd_buf, uint8_t *arg_buf );

- Get INT pin state
> uint8_t stspin233_get_int_state ( stspin233_t *ctx );

## Examples Description

> This application is motor driver.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and configures the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin233_cfg_t cfg;

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

    stspin233_cfg_setup( &cfg );
    STSPIN233_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin233_init( &stspin233, &cfg );

    stspin233_default_cfg( &stspin233 );
}
  
```

### Application Task

> This example demonstrates the use of STSPIN233 Click board, by running the motor clockwise and counter clockwise.
> All results will be displayed on USB UART.

```c

void application_task ( void )
{
    log_printf( &logger, ">>> START MOTOR\r\n" );
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_START_MOTOR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> Set clockwise direction\r\n" );
    stspin233_send_double_cmd( &stspin233, STSPIN233_CMD_DIR_MOTOR, STSPIN233_CW_DIR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> Set counter clockwise direction\r\n" );
    stspin233_send_double_cmd( &stspin233, STSPIN233_CMD_DIR_MOTOR, STSPIN233_CCW_DIR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> STOP MOTOR\r\n" );
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_STOP_MOTOR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_STATUS );
    stspin233_process( );
    log_printf( &logger, ">>> STATUS: %.5s\r\n", &current_parser_buf[ 9 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------------------\r\n" );
} 

```

## Note

> For all other commands that you can use to control your engine, 
> see the firmware documentation. We used an 8 pole motor for the test.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Stspin233

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
