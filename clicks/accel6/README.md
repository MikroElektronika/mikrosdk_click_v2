\mainpage Main Page
 
 

---
# Accel 6 Click

Accel 6 Click is a three-axis acceleration sensor with many features. It uses the BMA280, a 14bit triaxial acceleration sensor with intelligent on-chip motion triggered interrupt controller, from Bosch Sensortec.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accel-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel6_cfg_setup ( accel6_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL6_RETVAL accel6_init ( accel6_t *ctx, accel6_cfg_t *cfg );

- Click Default Configuration function.
> void accel6_default_cfg ( accel6_t *ctx, uint8_t range_data, uint8_t bw_data, uint8_t lpw_data );

#### Example key functions :

- Functions for set offset
> void accel6_data_offset ( accel6_t *ctx, uint8_t set_offset, float *offset_data );
 
- Functions for read orient
> void accel6_get_orient ( accel6_t *ctx, uint8_t *z_orient, uint8_t *xy_orient );

- Functions for read axis data
> float accel6_get_axis ( accel6_t *ctx, uint8_t axis );

## Examples Description

> This application allows acceleration measurement in three perpendicular axes.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init and settings accelerometer data range, 
> bandwidth, mode and sleep timer which are necessary for the init chip.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel6_cfg_t cfg;

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

    accel6_cfg_setup( &cfg );
    ACCEL6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel6_init( &accel6, &cfg );

    accel6_soft_reset( &accel6 );
    Delay_1sec();
    log_info( &logger, "---- Device reset done ----" );
    
    accel6_default_cfg( &accel6, ACCEL6_PMU_RANGE_4g, 
                                          ACCEL6_PMU_BW_125Hz, 
                                          ACCEL6_PMU_LPW_NORMAL_MODE | 
                                          ACCEL6_PMU_LPW_SLEEP_10ms );
    
    log_info( &logger, "---- Device configuration done ----" );
    
    Delay_1sec();
}
  
```

### Application Task

> Reads the accel X / Y / Z axis data in mg, 
> Temperature data in C, detects the orientation of the X,Y and Z axis
> and checking on which axis the tap is detected.
> All data logs on usb uart for every 500 ms.

```c

void application_task ( )
{
    uint8_t tap_detect;
    uint8_t orient;
    uint8_t z_orient;
    uint8_t xy_orient;
    float f_axis = 0.0;
    float temp = 0.0;
    
    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_X );
    log_printf( &logger, " X axis: %f mg \r\n ", f_axis );


    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_Y );
    log_printf( &logger, " Y axis: %f mg \r\n ", f_axis );

    f_axis = accel6_get_axis ( &accel6, ACCEL6_AXIS_Z );
    log_printf( &logger, " Z axis: %f mg \r\n ", f_axis );

    temp = accel6_get_temperature( &accel6 );
    log_printf( &logger, " Temperature: %.2f C \r\n ", temp );

    accel6_get_orient( &accel6, &z_orient, &xy_orient );
    
    switch ( z_orient )
    {
        case 1:
        {
            log_printf( &logger, " Z orient : UPWARD looking \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Z orient : DOWNWARD looking \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }

    switch ( xy_orient )
    {
        case 1:
        {
            log_printf( &logger, " XY orient : UPSIDE DOWN \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " XY orient : LANDSCAPE LEFT \r\n " );
            break;
        }
        case 3:
        {
            log_printf( &logger, " XY orient : LANDSCAPE RIGHT \r\n " );
            break;
        }
        case 4:
        {
            log_printf( &logger, " XY orient : UPRIGHT \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }
	
	tap_detect = accel6_get_tap_status( &accel6 );
    switch ( tap_detect )
    {
        case 1:
        {
            log_printf( &logger, " Tap status : X negative \r\n " );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Tap status : Y negative \r\n " );
            break;
        }
        case 3:
        {
            log_printf( &logger, " Tap status : Z negative \r\n " );
            break;
        }
        case 4:
        {
            log_printf( &logger, " Tap status : X positive \r\n " );
            break;
        }
        case 5:
        {
            log_printf( &logger, " Tap status : Y positive \r\n " );
            break;
        }
        case 6:
        {
            log_printf( &logger, " Tap status : Z positive \r\n " );
            break;
        }
        default:
        {
            break;
        }
    }
	
    log_printf( &logger, "   \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel6

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
