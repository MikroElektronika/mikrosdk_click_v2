
---
# Barometer 3 click

Barometer 3 Click is a compact add-on board for applications which require digital barometric air pressure measurement. This board features the DPS368, a digital barometric air pressure sensor from Infineon.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/barometer-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Barometer3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Barometer3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void barometer3_cfg_setup ( barometer3_cfg_t *cfg ); 
 
- Initialization function.
> BAROMETER3_RETVAL barometer3_init ( barometer3_t *ctx, barometer3_cfg_t *cfg );

- Click Default Configuration function.
> void barometer3_def_cfg ( barometer3_t *ctx );


#### Example key functions :

- Temperature Measurement Configuration function.
> void barometer3_cfg_temp ( barometer3_t *ctx, uint8_t temp_mr, uint8_t temp_osr );
 
- Get Temperature Measurement Once function.
> uint8_t barometer3_meas_temp_once ( barometer3_t *ctx, float *result, uint8_t temp_osr );

- Get Pressure Measurement Once function.
> uint8_t barometer3_meas_prs_once ( barometer3_t *ctx, float *result, uint8_t prs_osr );

## Examples Description

> This example demonstrates the use of Barometer 3 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, sets the click board default configuration and check the communication by reading the device ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    barometer3_cfg_t cfg;
    uint8_t status_val;

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

    barometer3_cfg_setup( &cfg );
    BAROMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer3_init( &barometer3, &cfg );

    barometer3_def_cfg( &barometer3 );
    Delay_ms( 100 );
    
    barometer3_generic_read( &barometer3, BAROMETER3_PROD_ID, &status_val, 1 );
    
    if ( status_val != BAROMETER3_PRODUCT_ID )
    {
        
        log_printf( &logger, " ERROR - wrong ID\r\n" );
        log_printf( &logger, " Please restart your system.\r\n" );
        for ( ; ; );
    }
    log_info( &logger, "---- Application Task ----" );
}
  
```

### Application Task

> Reads the temperature [ Celsius ] and pressure [ mBar ] and displays the results on the USB UART.

```c

void application_task ( void )
{
    barometer3_cfg_temp( &barometer3, BAROMETER3_TMP_RATE_1, BAROMETER3_TMP_PRC_128 );
    barometer3_standby( &barometer3 );
    while ( BAROMETER3_SUCCESS != barometer3_meas_temp_once( &barometer3, &temperature, BAROMETER3_TMP_PRC_128 ) );
    log_printf( &logger, " Temperature: %.2f Celsius \r\n", temperature );
    
    barometer3_cfg_pres( &barometer3, BAROMETER3_PM_RATE_1, BAROMETER3_PM_PRC_128 );
    barometer3_standby( &barometer3 );
    while ( BAROMETER3_SUCCESS != barometer3_meas_prs_once( &barometer3, &pressure, BAROMETER3_PM_PRC_128 ) );
    log_printf( &logger, " Pressure: %.2f mBar \r\n", pressure );
    log_printf( &logger, "----------------------- \r\n" );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer3

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
