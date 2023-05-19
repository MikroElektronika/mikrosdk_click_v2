
---
# Brushless 25 click

> Brushless 25 Click is a compact add-on board that controls brushless DC (three-phase BLDC) motors with any MCU. This board features the MCT8316A, a high-speed sensorless trapezoidal control integrated FET BLDC driver from Texas Instruments. It provides three individually controllable drivers intended to drive a three-phase BLDC motor, solenoids, or other loads.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless25_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-25-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Brushless 25 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 25 Click driver.

#### Standard key functions :

- `brushless25_cfg_setup` Config Object Initialization function.
```c
void brushless25_cfg_setup ( brushless25_cfg_t *cfg );
```

- `brushless25_init` Initialization function.
```c
err_t brushless25_init ( brushless25_t *ctx, brushless25_cfg_t *cfg );
```

- `brushless25_default_cfg` Click Default Configuration function.
```c
err_t brushless25_default_cfg ( brushless25_t *ctx );
```

#### Example key functions :

- `brushless25_register_write` Brushless 25 data writing function.
```c
err_t brushless25_register_write ( brushless25_t *ctx, uint16_t reg, uint32_t data_in );
```

- `brushless25_register_read` Brushless 25 data reading function.
```c
err_t brushless25_register_read ( brushless25_t *ctx, uint16_t reg, uint32_t *data_out );
```

- `brushless25_set_speed_value` Brushless 25 set speed function.
```c
err_t brushless25_set_speed_value ( brushless25_t *ctx, float spd_val );
```

## Example Description

> Application example shows the device's capability of controlling 
 the brushless motor speed and state of the driver.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, sets the device into slow start mode 
 and sets the speed of the motor to 30%.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless25_cfg_t brushless25_cfg;  /**< Click config object. */
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
    brushless25_cfg_setup( &brushless25_cfg );
    BRUSHLESS25_MAP_MIKROBUS( brushless25_cfg, MIKROBUS_1 );
    err_t init_flag = brushless25_init( &brushless25, &brushless25_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS25_ERROR == brushless25_default_cfg ( &brushless25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    brushless25_set_speed_value( &brushless25, ( speed_val * 10 ) );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example is taking track of the state of the driver and motor, as well as its 
 voltage and speed which is changing from 30% to 100%, and logging it onto the USB UART terminal

```c
void application_task ( void )
{
    uint32_t tmp_data = 0;
    uint16_t spd_data = 0;
    uint16_t voltage_data = 0;
    

    brushless25_register_read( &brushless25, BRUSHLESS25_SYS_STATUS2_REG, &tmp_data );
    tmp_data &= BRUSHLESS25_STATE_MASK; 
    
    switch ( tmp_data )
    {
        case BRUSHLESS25_STATE_SYSTEM_IDLE:
        {
            log_info( &logger, " System is idle " );
            break;
        }
        case BRUSHLESS25_STATE_MOTOR_START:
        {
            log_info( &logger, " Motor is starting " );
            break;
        }
        case BRUSHLESS25_STATE_MOTOR_RUN:
        {
            log_info( &logger, " Motor is running" );
            if ( ( speed_val < 10 ) && ( sw_data == 0 ) )
            {
                speed_val++;
                if ( speed_val == 10 )
                {
                    sw_data = 1;
                }
            }
            else if ( ( speed_val > 3 ) && ( sw_data == 1 ) )
            {
                speed_val--;
                if ( speed_val == 3 )
                {
                    sw_data = 0;
                }
            }
            
            break;
        }
        case BRUSHLESS25_STATE_MOTOR_ALIGN:
        {
            log_info( &logger, " Motor is aligning " );
            break;
        }
        case BRUSHLESS25_STATE_MOTOR_IDLE:
        {
            log_info( &logger, " Motor is in idle mode " );
            break;
        }
        case BRUSHLESS25_STATE_MOTOR_STOP:
        {
            log_info( &logger, " Motor is stoped " );
            brushless25_set_brake_state( &brushless25, BRUSHLESS25_BRAKE_ON );
            break;
        }
        case BRUSHLESS25_STATE_FAULT:
        {
            log_error( &logger, " Fault accured " );
            brushless25_set_brake_state( &brushless25, BRUSHLESS25_BRAKE_ON );
            for ( ; ; );
        }
        case BRUSHLESS25_STATE_MOTOR_BRAKE:
        {
            log_info( &logger, " Motor brake is on " );
            brushless25_set_brake_state( &brushless25, BRUSHLESS25_BRAKE_OFF );
            break;
        }
        default:
        {
            break;
        }
    }

    brushless25_set_speed_value( &brushless25, ( speed_val * 10 ) );
    Delay_ms ( 1000 );
    brushless25_register_read( &brushless25, BRUSHLESS25_SYS_STATUS2_REG, &tmp_data );
    spd_data = ( uint16_t ) tmp_data / 10;
    brushless25_register_read( &brushless25, BRUSHLESS25_SYS_STATUS1_REG, &tmp_data );
    voltage_data = ( ( uint16_t ) ( tmp_data >> 16 ) / 10 );

    log_printf( &logger, " Motor speed: %d Hz \r\n", spd_data );
    log_printf( &logger, " Motor voltage: %d V \r\n", voltage_data );
    log_printf( &logger, " --------------------- \r\n" );
    Delay_ms ( 1000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless25

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
