\mainpage Main Page
 
---
# Pedometer 3 Click

> Pedometer 3 Click is a three-axis acceleration sensing Click board
which utilizes the KX126-1063. An advanced tri-axis acceleration sensor, KX126-1063 includes the pedometer algorithm support.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pedometer3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pedometer-3-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pedometer3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pedometer3 Click driver.

#### Standard key functions :

- `pedometer3_cfg_setup` Config Object Initialization function.
```c
void pedometer3_cfg_setup ( pedometer3_cfg_t *cfg ); 
```

- `pedometer3_init` Initialization function.
```c
err_t pedometer3_init ( pedometer3_t *ctx, pedometer3_cfg_t *cfg );
```

- `pedometer3_default_cfg` Click Default Configuration function.
```c
void pedometer3_default_cfg ( pedometer3_t *ctx );
```

#### Example key functions :

- `pedometer3_get_hp_accel_axis` High Pass Accel axis data
```c
void pedometer3_get_hp_accel_axis ( pedometer3_t *ctx, pedometer3_axis_t *axis );
```

- `pedometer3_get_accel_axis` Accel axis data
```c
void pedometer3_get_accel_axis ( pedometer3_t *ctx, pedometer3_axis_t *axis );
```

- `pedometer3_get_step_counter` Pedometer step counter
```c
uint16_t pedometer3_get_step_counter ( pedometer3_t *ctx );
```

## Examples Description

> The demo application displays measuring 2 accelerometers (normal accel and high pass accel),
> counting steps and displaying tilt positions.
> The sensor includes additional feature and setups that you can look up in the library.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pedometer3_cfg_t cfg;
    uint8_t tmp;

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
    pedometer3_cfg_setup( &cfg );
    PEDOMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pedometer3_init( &pedometer3, &cfg );

    // Default Click configurations
    pedometer3_default_cfg( &pedometer3 );

    tmp = PEDOMETER3_CNTL1_MODE_LOW_POWER | PEDOMETER3_CNTL1_MODE_LOW_POWER |
          PEDOMETER3_CNTL1_RES_MODE_LOWER_NOISE | PEDOMETER3_CNTL1_DATA_READY_DISABLE |
          PEDOMETER3_CNTL1_G_RANGE_2g | PEDOMETER3_CNTL1_TAP_ENABLE |
          PEDOMETER3_CNTL1_PEDOMETER_ENABLE | PEDOMETER3_CNTL1_TILT_ENABLE;

    pedometer3_generic_write( &pedometer3, PEDOMETER3_REG_CONTROL_1, &tmp, 1 );
}
```

### Application Task

> Reads Accel and High Pass Accel X/Y/Z axis and detect Tilt Position.
> All data logs on the USBUART every 400 ms.

```c
void application_task ( void )
{
    static uint16_t ped_step = 0;
    pedometer3_axis_t accel_axis;
    pedometer3_axis_t highpass_axis;
    pedometer3_tilt_position_t tilt;

    pedometer3_get_accel_axis( &pedometer3, &accel_axis );
    pedometer3_get_hp_accel_axis( &pedometer3, &highpass_axis );
    ped_step += pedometer3_get_step_counter( &pedometer3 );

    log_printf( &logger, "___________ Pedometer 3 Click _____________\r\n");

    log_printf( &logger, "--  Accel : [ X ]: %d / [ Y ]: %d / [ Z ]: %d \r\n", 
                accel_axis.x, accel_axis.y, accel_axis.z );
    log_printf( &logger, "--  HP Accel : [ X ]: %d / [ Y ]: %d / [ Z ]: %d \r\n", 
                highpass_axis.x, highpass_axis.y, highpass_axis.z );

    log_printf( &logger, "--  Step counter : [ STEP ]: %d \r\n", ped_step );

    pedometer3_get_tilt_position( &pedometer3, &tilt);

    switch ( tilt.current_pos )
    {
        case PEDOMETER3_TILT_POSITION_LEFT:
        {
            log_printf( &logger, "--  Current Tilt Position: [ LEFT ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_RIGHT:
        {
            log_printf( &logger, "--  Current Tilt Position: [ RIGHT ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_DOWN:
        {
            log_printf( &logger, "--  Current Tilt Position: [ DOWN ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_UP:
        {
            log_printf( &logger, "--  Current Tilt Position: [ UP ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_FACE_DOWN:
        {
            log_printf( &logger, "--  Current Tilt Position: [ FACE DOWN ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_FACE_UP:
        {
            log_printf( &logger, "--  Current Tilt Position: [ FACE UP ] \r\n" );
            break;
        }
    }

    Delay_ms ( 400 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pedometer3

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
