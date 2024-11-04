
---
# Oximeter 3 Click

Oximeter 3 Click is a compact add-on board perfectly suited for measuring the blood oxygen saturation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/oximeter3_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/oximeter-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Oximeter3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Oximeter3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void oximeter3_cfg_setup ( oximeter3_cfg_t *cfg ); 
 
- Initialization function.
> OXIMETER3_RETVAL oximeter3_init ( oximeter3_t *ctx, oximeter3_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> uint8_t oximeter3_generic_read ( oximeter3_t *ctx, uint8_t reg );
 
- Gets state of the int pin
> uint8_t oximeter3_get_int_status ( oximeter3_t *ctx );

- Generic function for reading als and proximity values
> uint16_t oximeter3_read_value ( oximeter3_t *ctx, uint8_t type_macro );

## Examples Description

> This example demonstrates the use of Oximeter 3 Click board. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, checks the device ID then configures the device for the selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter3_cfg_t cfg;

    uint8_t dev_status;

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

    oximeter3_cfg_setup( &cfg );
    OXIMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter3_init( &oximeter3, &cfg );

    dev_status = oximeter3_generic_read( &oximeter3, OXIMETER3_REG_PRODUCT_ID );
    
    if ( dev_status != OXIMETER3_ID_VAL )
    {
        log_printf( &logger, " *****  ERROR!  ***** \r\n" );
        for ( ; ; );
    }

    dev_mode = OXIMETER3_HEART_RATE;
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                                         OXIMETER3_CMD_MEASUREMENT_DISABLE );
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_CTRL,
                                         OXIMETER3_INT_STATUS_PROX );
    
    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT, 
                                             OXIMETER3_LED_CURR_MID );
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_MODULATOR_TIMING,
                                             OXIMETER3_PROX_TIMING_FREQ_390p625_KHZ );
    }
    else
    {
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT, 
                                             OXIMETER3_LED_CURR_MIN );
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_MODULATOR_TIMING,
                                             OXIMETER3_PROX_TIMING_FREQ_3p125_MHZ );
    }
    
    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_RATE,
                                         OXIMETER3_PROX_RATE_250_MPS );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                                         OXIMETER3_CMD_MEASUREMENT_ENABLE |
                                         OXIMETER3_CMD_PROX_PERIODIC_MEASUREMENT_ENABLE |
                                         OXIMETER3_CMD_ALS_PERIODIC_MEASUREMENT_ENABLE );

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
}
  
```

### Application Task

> Depending on the selected mode it reads heart rate data (OXIMETER3_HEART_RATE mode) or
> values of proximity and ambient light sensor (OXIMETER3_PROX or OXIMETER3_ALS modes).
> All data is being logged on USB UART where you can track their changes.

```c

void application_task ( void )
{
    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        if( !oximeter3_get_int_status( &oximeter3 ) )
        {
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
            oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_STATUS, 
                                                 OXIMETER3_INT_STATUS_PROX );
            
            counter++;
            if ( rd_val > 10000 )
            {
                log_printf( &logger, "%u\r\n", rd_val );
                counter = 2500;
            }
            else if ( counter > 2500 )
            {
                log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
                counter = 0;
            }
        }
    }
    else if ( OXIMETER3_PROX == dev_mode || OXIMETER3_ALS == dev_mode )
    {
        if( !oximeter3_get_int_status( &oximeter3 ) )
        {
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
            oximeter3_generic_write( &oximeter3, OXIMETER3_REG_INTERRUPT_STATUS, 
                                                 OXIMETER3_INT_STATUS_PROX );
            
            log_printf( &logger, " * Proximity: %u \r\n", rd_val );
        
            rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_ALS );
            log_printf( &logger, " * ALS: %u \r\n", rd_val );
            
            log_printf( &logger, "******************** \r\n" );
            
            Delay_ms ( 500 );
        }
    }
} 

```

## Note

> In the case of heart rate, please use a Serial Plot application for data plotting.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Oximeter3

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
