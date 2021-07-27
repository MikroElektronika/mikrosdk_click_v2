

---
# TMR Angle click

TMR Angle Click is a Click board� perfectly suited for developing applications 
that range from steering angle applications with the highest functional safety
requirements to motors for wipers, pumps and actuators and electric motors in
general.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tmrangle_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/tmr-angle-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the TMRAngle Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TMRAngle Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void tmrangle_cfg_setup ( tmrangle_cfg_t *cfg ); 
 
- Initialization function.
> TMRANGLE_RETVAL tmrangle_init ( tmrangle_t *ctx, tmrangle_cfg_t *cfg );

- Click Default Configuration function.
> void tmrangle_default_cfg ( tmrangle_t *ctx );


#### Example key functions :

- Function read and stores negative and positive, sine and cosine parameters data.
> void tmrangle_init_sensor_data ( tmrangle_t* ctx );
 
- This function will extract the maximum, minimum voltage levels, amplitude, offset, and orthogonality.
> void tmrangle_calibration_find_param ( tmrangle_t* ctx,
                                         tmrangle_calib_data_t* calib_param );

- Function calculates the calibrated angle in degrees and this structure holds the current sensor calibration parameters.
  > float tmrangle_get_calib_angle ( tmrangle_calib_data_t* calib_param );

## Examples Description

> This example reads and value in deegres, and then logs the result. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, and also write log.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    tmrangle_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    tmrangle_cfg_setup( &cfg );
    TMRANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tmrangle_init( &tmrangle, &cfg );

}
  
```

### Application Task

> Reads angle value in degrees and logs the results.

```c

void application_task ( void )
{
    float angle;
    trigonometry_t trig_set;
    tmrangle_calib_data_t calibration_store_params;
    tmrangle_init_sensor_data( &tmrangle );

    trig_set.max_diff_sin = TMRANGLE_MAX_DIFF_SIN;
    trig_set.max_diff_cos = TMRANGLE_MAX_DIFF_COS;
    trig_set.min_diff_sin = TMRANGLE_MIN_DIFF_SIN;
    trig_set.min_diff_cos = TMRANGLE_MIN_DIFF_COS;
    trig_set.sin_45 = TMRANGLE_SIN_45;
    trig_set.cos_45 = TMRANGLE_COS_45;
    trig_set.sin_135 = TMRANGLE_SIN_135;
    trig_set.cos_135 = TMRANGLE_COS_135;

    tmrangle_init_calib_data( &tmrangle, &calibration_store_params, &trig_set );
    tmrangle_calibration_find_param( &tmrangle, &calibration_store_params );

    angle = tmrangle_get_calib_angle( &tmrangle, &calibration_store_params );

    log_printf( &logger, "Angle is %f deg\r\n", angle );

    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TMRAngle

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
