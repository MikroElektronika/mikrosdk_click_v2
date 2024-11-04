
---
# Accel3 Click

Accel 3 Click represent 3-axis linear accelerometer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accel3-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel3_cfg_setup ( accel3_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL3_RETVAL accel3_init ( accel3_t *ctx, accel3_cfg_t *cfg );

- Click Default Configuration function.
> void accel3_default_cfg ( accel3_t *ctx );


#### Example key functions :

- This function select communication mode and executes start initialization.
> void accel3_default_cfg ( accel3_t *ctx, accel3_cfg_t *cfg );
 
- This function reads Accel data ( X, Y and Z axis ) from the desired Accel registers of the H3LIS331DL module.
> void accel3_read_data ( accel3_t *ctx, accel3_data_t *accel3_data );

## Examples Description

> 
> This is an example which demonstrates the usage of Accel 3 Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel3_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    accel3_cfg_setup( &cfg );
    ACCEL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel3_init( &accel3, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " -----  Accel 3 Click  -----\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    accel3_default_cfg ( &accel3, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, " -- Initialization  done. --\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> Measured coordinates (X,Y,Z) are being sent to the UART where you can 
> track their changes. All data logs on USB UART for every 1 sec.
> 

```c

void application_task ( void )
{
    accel3_read_data( &accel3, &accel3_data );
    Delay_ms ( 100 );
    
    log_printf( &logger, "        Accelerometer       \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "        X = %d \r\n", accel3_data.x );
    log_printf( &logger, "        Y = %d \r\n", accel3_data.y );
    log_printf( &logger, "        Z = %d \r\n", accel3_data.z );
    log_printf( &logger, "----------------------------\r\n" );
    
    Delay_ms ( 1000 );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel3

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
