\mainpage Main Page

---
# Brushless 21 click

> Brushless 21 Click is a compact add-on board suitable for controlling brushless DC (BLDC) motors with any MCU. This board features the AMT49400, an advanced 3-phase, sensorless BLDC motor driver with integrated power MOSFETs from Allegro Microsystems. The AMT49400 is rated for an operating voltage range from 4V to 16V. Motor rotation speed is controlled by applying a duty cycle command to the PWM input, while a simple I2C interface is provided for setting motor-rated voltage, rated current, rated speed, resistance, and startup profiles.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless21_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : PWM/I2C type


# Software Support

We provide a library for the Brushless 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 21 Click driver.

#### Standard key functions :

- `brushless21_cfg_setup` Config Object Initialization function.
```c
void brushless21_cfg_setup ( brushless21_cfg_t *cfg );
```

- `brushless21_init` Initialization function.
```c
err_t brushless21_init ( brushless21_t *ctx, brushless21_cfg_t *cfg );
```

- `brushless21_default_cfg` Click Default Configuration function.
```c
err_t brushless21_default_cfg ( brushless21_t *ctx );
```

#### Example key functions :

- `brushless21_set_duty_cycle` This function sets the duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless21_set_duty_cycle ( brushless21_t *ctx, float duty_cycle );
```

- `brushless21_get_motor_speed` This function reads the motor speed in Hz.
```c
err_t brushless21_get_motor_speed ( brushless21_t *ctx, float *motor_speed_hz );
```

- `brushless21_switch_direction` This function switches the motor direction by toggling the DIR bit.
```c
err_t brushless21_switch_direction ( brushless21_t *ctx );
```

## Example Description

> This example demonstrates the use of the Brushless 21 click board by driving the motor at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the GPIO as a default communication and enables the PWM.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless21_cfg_t brushless21_cfg;  /**< Click config object. */

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
    brushless21_cfg_setup( &brushless21_cfg );
    BRUSHLESS21_MAP_MIKROBUS( brushless21_cfg, MIKROBUS_1 );
    err_t init_flag = brushless21_init( &brushless21, &brushless21_cfg );
    if ( ( PWM_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS21_ERROR == brushless21_default_cfg ( &brushless21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle once per second. The duty cycle ranges from 0% to 100%. 
When the click board is configured in I2C mode the motor switches the direction at a minimal speed.
Also, the chip internal temperature, VBB voltage and the motor speed readings are supported in I2C mode.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    if ( BRUSHLESS21_OK == brushless21_set_duty_cycle ( &brushless21, duty ) )
    {
        log_printf( &logger, "\r\n Duty Cycle : %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    }
    
    if ( BRUSHLESS21_DRV_SEL_I2C == brushless21.drv_sel ) 
    {
        int8_t temperature = 0;
        float motor_speed = 0;
        float vbb_voltage = 0;
        if ( BRUSHLESS21_OK == brushless21_get_temperature ( &brushless21, &temperature ) )
        {
            log_printf( &logger, " Temperature: %d C\r\n", ( int16_t ) temperature );
        }
        if ( BRUSHLESS21_OK == brushless21_get_motor_speed ( &brushless21, &motor_speed ) )
        {
            log_printf( &logger, " Motor Speed: %.2f Hz\r\n", motor_speed );
        }
        if ( BRUSHLESS21_OK == brushless21_get_vbb_voltage ( &brushless21, &vbb_voltage ) )
        {
            log_printf( &logger, " VBB Voltage: %.2f V\r\n", vbb_voltage );
        }
        if ( 0 == duty_cnt ) 
        {
            duty_inc = 1;
            if ( BRUSHLESS21_OK == brushless21_switch_direction ( &brushless21 ) )
            {
                log_printf( &logger, " Switch direction\r\n" );
            }
        }
    }
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
