\mainpage Main Page

---
# Air Motion click

> Air Motion Click is a compact add-on board that contains a 6-axis inertial measurement unit. This board features TDK InvenSense’s ICM-40627, a 6-axis MEMS MotionTracking™ device that combines a 3-axis user-selectable gyroscope accelerometer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/airmotion_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/air-motion-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Air Motion Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Air Motion Click driver.

#### Standard key functions :

- `airmotion_cfg_setup` Config Object Initialization function.
```c
void airmotion_cfg_setup ( airmotion_cfg_t *cfg );
```

- `airmotion_init` Initialization function.
```c
err_t airmotion_init ( airmotion_t *ctx, airmotion_cfg_t *cfg );
```

- `airmotion_default_cfg` Click Default Configuration function.
```c
err_t airmotion_default_cfg ( airmotion_t *ctx );
```

#### Example key functions :

- `airmotion_set_reg_bank` Air Motion set register bank function.
```c
err_t airmotion_set_reg_bank( airmotion_t *ctx, uint8_t bank );
```

- `airmotion_sw_reset` Air Motion software reset function.
```c
err_t airmotion_sw_reset( airmotion_t *ctx );
```

- `airmotion_get_data_from_register` Air Motion read data function.
```c
err_t airmotion_get_data_from_register ( airmotion_t *ctx, float *temperature_data, airmotion_data_t *accel_data, airmotion_data_t *gyro_data, uint32_t *tmst_data );
```

## Example Description

> This example demonstrates the use of Air Motion Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver after that resets the device and performs default configuration and reads the device id.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airmotion_cfg_t airmotion_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    airmotion_cfg_setup( &airmotion_cfg );
    AIRMOTION_MAP_MIKROBUS( airmotion_cfg, MIKROBUS_1 );
    err_t init_flag = airmotion_init( &airmotion, &airmotion_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRMOTION_OK != airmotion_default_cfg ( &airmotion ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
   
    log_info( &logger, " Application Task " );
    
    uint8_t id = 0;
    airmotion_reg_read( &airmotion, AIRMOTION_BANK0_SEL, AIRMOTION_WHO_AM_I, &id, 1);
    log_printf( &logger, " WHO AM I = 0X%.2X\r\n", (uint16_t)id );
    
#if defined TAP_DETECTION_MODE
    log_printf( &logger, " Tap Detection Mode \r\n" );
    airmotion_set_basic_tap_detection( &airmotion );
#endif
    
}

```

### Application Task

> When the device is in Tap Detection Mode, Air Motion Click board will read and display the direction, axis, and number of taps that it detected. If Tap Detection mode is disabled, the device will read accel, gyro, and temperature data.

```c
void application_task ( void )
{
    if ( airmotion_get_int1_state( &airmotion) )
    {       
#if defined TAP_DETECTION_MODE
        uint8_t tap_num;
        uint8_t tap_axis;
        uint8_t tap_dir;
        
        airmotion_get_tap_detection( &airmotion, &tap_num, &tap_axis, &tap_dir );
        if (  AIRMOTION_TAP_SINGLE == tap_num )
        {
            log_printf( &logger, " SINGLE TAP" );
        }
        else
        {
            log_printf( &logger, " DOUBLE TAP" );
        }
        
        if (  AIRMOTION_TAP_DIR_POSITIVE == tap_dir )
        {
            log_printf( &logger, " IN POSITIVE" );
        }
        else
        {
            log_printf( &logger, " IN NEGATIVE" );
        }
        
        if (  AIRMOTION_TAP_AXIS_X == tap_axis )
        {
            log_printf( &logger, " X AXIS DIRECTION \r\n" );
        }
        else if ( AIRMOTION_TAP_AXIS_Y == tap_axis )
        {
            log_printf( &logger, " Y AXIS DIRECTION  \r\n" );
        }
        else
        {
            log_printf( &logger, " Z AXIS DIRECTION  \r\n" );
        }
#else
        airmotion_data_t accel_data;
        airmotion_data_t gyro_data;
        float temp_data;
        uint32_t tmst_data;
        
        airmotion_get_data_from_register( &airmotion, &temp_data, &accel_data, &gyro_data, &tmst_data );
        log_printf( &logger, " TEMP: %.2f \r\n", temp_data );
        log_printf( &logger, " GYRO: x:%d y:%d z:%d \r\n", gyro_data.data_x,gyro_data.data_y,gyro_data.data_z );
        log_printf( &logger, " ACCEL: x:%d y:%d z:%d \r\n", accel_data.data_x,accel_data.data_y,accel_data.data_z );
        log_printf( &logger, "========================== \r\n" );
        Delay_ms ( 1000 );
#endif
    }    
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AirMotion

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
