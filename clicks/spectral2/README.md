\mainpage Main Page
 
 

---
# Spectral 2 Click

Spectral 2 Click is a multispectral color sensing device, which uses the state-of-the-art sensor IC for a very accurate color sensing. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spectral2_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/spectral-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Spectral2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Spectral2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void spectral2_cfg_setup ( spectral2_cfg_t *cfg ); 
 
- Initialization function.
> SPECTRAL2_RETVAL spectral2_init ( spectral2_t *ctx, spectral2_cfg_t *cfg );

- Click Default Configuration function.
> void spectral2_default_cfg ( spectral2_t *ctx );


#### Example key functions :

- Function for calculating integration time.
> void spectral2_set_integration_time ( spectral2_t *ctx, uint8_t cur_time );
 
- Function for reading Data.
> int16_t spectral2_get_data ( spectral2_t *ctx, uint8_t data_reg );

- Function that reads calibrated data.
> float spectral2_get_calibrated_data ( spectral2_t *ctx, uint8_t data_reg );

## Examples Description

> This application enables usage of multispectral color sensor.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialize, reset module and configuration measurement

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral2_cfg_t cfg;
    uint8_t cfg_data;

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

    spectral2_cfg_setup( &cfg );
    SPECTRAL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral2_init( &spectral2, &cfg );

    spectral2_reset( &spectral2 );

    Delay_100ms( );
    log_printf( &logger, "--- System init ---\r\n" );

    cfg_data = ( SPECTRAL2_NORMAL_OPERATION | SPECTRAL2_INT_DISABLE |
                                   SPECTRAL2_GAIN_16X |
                                   SPECTRAL2_MODE_2 );

    spectral2_default_cfg( &spectral2, cfg_data );

    Delay_1sec( );
}
  
```

### Application Task

> Reads the brightness value with R, G, B, I, O and V filter, every 1 second, and logs on to USBUART.

```c

void application_task ( void )
{
    float f_data;

    //  Task implementation.

    log_printf( &logger, "-------------------\r\n" );

    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_R );
    log_printf( &logger, "-- R ( Red data ) : %.2f \r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_G );
    log_printf( &logger, "-- G ( Green data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_B );
    log_printf( &logger, "-- B ( Blue data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_Y );
    log_printf( &logger, "-- Y ( Yellow data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_O );
    log_printf( &logger, "-- O ( Orange data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_V );
    log_printf( &logger, "-- V ( Violet data ) : %.2f\r\n", f_data );
    
    Delay_1sec( );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Spectral2

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
