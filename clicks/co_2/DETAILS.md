
---
# CO 2 click

CO 2 click is a very accurate, carbon-monoxide-gas-sensor Click board™, equipped with the SPEC amperometric,3SP CO 1000 gas sensor which electrochemically reacts with the carbon monoxide (CO).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/co2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/co-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the CO2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CO2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void co2_cfg_setup ( co2_cfg_t *cfg ); 
 
- Initialization function.
> CO2_RETVAL co2_init ( co2_t *ctx, co2_cfg_t *cfg );


#### Example key functions :

- Function reads the converted data (CO) from the 12-bit AD converter.
> void co2_read_adc( co2_t *ctx, uint16_t *data_out );
 
- Function puts the device to enabled or to disabled state.
> void co2_enable( co2_t *ctx, uint8_t state );

- Function reads the CO converted data and calculates this value to the ppm.
> co2_get_co2_ppm( co2_t *ctx, float *co2_data );

## Examples Description

> This application enables usage of very accurate CO sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and performs the device configuration for properly working.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    co2_cfg_t cfg;
    uint8_t temp_w;

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

    co2_cfg_setup( &cfg );
    CO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    co2_init( &co2, &cfg );

    Delay_ms( 500 );
    
    //co2_default_cfg( &co2 );

    temp_w = CO2_WRITE_MODE;
    co2_generic_write( &co2, CO2_LOCK_REG, &temp_w, 1 );
    temp_w = CO2_STANDBY_MODE;
    co2_generic_write( &co2, CO2_MODECN_REG, &temp_w, 1 );
    temp_w = CO2_3500_OHM_TIA_RES | CO2_100_OHM_LOAD_RES;
    co2_generic_write( &co2, CO2_TIACN_REG, &temp_w, 1 );
    temp_w = CO2_VREF_EXT | CO2_50_PERCENTS_INT_ZERO | CO2_BIAS_POL_NEGATIVE | CO2_0_PERCENTS_BIAS;
    co2_generic_write( &co2, CO2_REFCN_REG, &temp_w, 1 );
    
    log_printf( &logger, "CO 2 is initialized\r\n\r\n" );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Gets CO (Carbon Monoxide) data as ppm value every 300 miliseconds.
> Results will be logged on UART. The CO value range is from 0 to 1000 ppm.

```c

void application_task ( void )
{
    float co2_value;
   
    co2_wait_i2c_ready( &co2 );
    co2_get_co2_ppm( &co2, &co2_value );
    
    log_printf( &logger, "CO : %.2f ppm\r\n", co2_value );
    Delay_ms( 300 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CO2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
