\mainpage Main Page
 
 

---
# Light Ranger 4 click

Light Ranger 4 click is an accurate distance measurement Click board based on a ToF (Time of Flight) measurement principle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-4-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LightRanger4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lightranger4_cfg_setup ( lightranger4_cfg_t *cfg ); 
 
- Initialization function.
> LIGHTRANGER4_RETVAL lightranger4_init ( lightranger4_t *ctx, lightranger4_cfg_t *cfg );

- Click Default Configuration function.
> void lightranger4_default_cfg ( lightranger4_t *ctx );


#### Example key functions :

- Function that checks whether the new data is ready for reading
> uint8_t lightranger4_new_data_ready ( lightranger4_t *ctx );
 
- Function reads distance of the object in front of the sensor
> uint16_t lightranger4_get_distance ( lightranger4_t *ctx );

- Function for starts power ON procedure
> void lightranger4_power_on ( lightranger4_t *ctx );


## Examples Description

>  Demo application is used to shows basic controls LightRanger 4 click

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration,
> adjusts the LONG mode (distance measurement up to 4 meters),
> sets the time budget and start measurement with the adjustment of inter measurements period.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger4_cfg_t cfg;

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

    lightranger4_cfg_setup( &cfg );
    LIGHTRANGER4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger4_init( &lightranger4, &cfg );

    lightranger4_power_on( &lightranger4 );
    log_info( &logger, "--- Wait until the configuration of the chip is completed ---" );

    lightranger4_default_cfg( &lightranger4 );
    lightranger4_set_distance_mode( &lightranger4, LR4_DISTANCE_MODE_LONG );
    lightranger4_set_measurement_timing_budget( &lightranger4, 1000 );
    lightranger4_start_measurement( &lightranger4, 20 );

    log_info( &logger, "--- Sensor start measurement ---" );
    Delay_100ms( );
}
```

### Application Task

> Reads the distance of the object in front of the sensor and logs 
> distance to USBUART every 500 ms.

```c
void application_task ( void )
{
    uint16_t distance;
    uint8_t m_status;

    //  Task implementation.

    while ( lightranger4_new_data_ready( &lightranger4 ) != 0 )
    {
        Delay_1ms();
    }

    distance = lightranger4_get_distance( &lightranger4 );
    log_printf( &logger, "** Distance: %d mm \r\n", distance );

    m_status = lightranger4_get_range_status( &lightranger4 );
    switch ( m_status )
    {
        case LR4_MRESP_SIGNAL_FAIL:
        {
            log_info( &logger, "Signal fail." );
            break;
        }
        case LR4_MRESP_PHASE_OUT_OF_VALID_LIMITS:
        {
            log_info( &logger, "Phase out of valid limits" );
            break;
        }
        case LR4_MRESP_SIGMA_FAIL:
        {
            log_info( &logger, "Sigma Fail. " );
            break;
        }
        case LR4_MRESP_WRAP_TARGET_FAIL:
        {
            log_info( &logger, "Wrap target fail." );
            break;
        }
        case LR4_MRESP_MINIMUM_DETECTION_THRESHOLD:
        {
            log_info( &logger, "Target is below minimum detection threshold. " );
            break;
        }
    }
    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger4

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
