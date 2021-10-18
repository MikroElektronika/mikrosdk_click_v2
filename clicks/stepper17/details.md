
---
# Stepper 17 click

Stepper 17 Click is a compact add-on board that contains a bipolar stepper motor driver. This board features the TB67S539FTG, a two-phase bipolar stepping motor driver using a PWM chopper from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper_17_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-17-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Mar 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper17 Click driver.

#### Standard key functions :

- `stepper17_cfg_setup` Config Object Initialization function.
```c
void stepper17_cfg_setup ( stepper17_cfg_t *cfg );
```

- `stepper17_init` Initialization function.
```c
STEPPER17_RETVAL stepper17_init ( stepper17_t *ctx, stepper17_cfg_t *cfg );
```

- `stepper17_default_cfg` Click Default Configuration function.
```c
void stepper17_default_cfg ( stepper17_t *ctx );
```

#### Example key functions :

- `stepper17_reset_electrical_angle` Reset electrical angle to initial state.
```c
void stepper17_reset_electrical_angle ( stepper17_t *ctx )
```

- `stepper17_step_resolution` Step resolution setting.
```c
err_t stepper17_step_resolution ( stepper17_t *ctx, uint8_t resolution )
```

- `stepper17_set_en_state` Enable stepping motor output.
```c
void stepper17_set_en_state ( stepper17_t *ctx, uint8_t state )
```

## Example Description

> This is an example application for showing Stepper 17 click
ability to control motor. First, it sets default configuration,
then runs motor on every turn it stops when makes a full circle
and it changes direction on every iteration and on every CW
movement changes step resolution.

**The demo application is composed of two sections :**

### Application Init

> Initialization of UART(for logging states and errors), I2C and PWM
modules and additional GPIO's. Sets default configuration for click
board and starts motor rotating in CW direction in 1/32 step resolution.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper17_cfg_t stepper17_cfg;  /**< Click config object. */

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

    stepper17_cfg_setup( &stepper17_cfg );
    STEPPER17_MAP_MIKROBUS( stepper17_cfg, MIKROBUS_1 );
    err_t init_flag = stepper17_init( &stepper17, &stepper17_cfg );
    
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( stepper17_default_cfg ( &stepper17 ) < 0 ) 
    {
        log_error( &logger, " Default Configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    
    stepper17_step_resolution( &stepper17, STEPPER17_STEP_HALF_A );
    stepper17_set_dir_state( &stepper17, 1 );
    stepper17_set_en_state( &stepper17, 1 );
    
    log_info( &logger, " Application Task " );
    log_info( &logger, " Move motor CW." );
}

```

### Application Task

> Runs motor one circle, stops and pauses for 2seconds, 
and runs motor in opposite direction. On every CW run it changes step 
resolution. It loops from 1/2 step resolution to 1/32 resolution.

```c

void application_task ( void ) 
{
    static uint32_t counter = 0;
    static uint8_t run = 1;
    static uint8_t dir = 1;
    static uint8_t turns = 1;
    static uint8_t step = 2;
    
    if ( ( 0 == stepper17_get_int_state( &stepper17 ) ) && run )
    {
        counter++;
        
        if ( counter == ( FULL_CIRCLE * turns ) )
        {
            //Stop motor
            stepper17_set_en_state( &stepper17, 0 );
            run = 0;
            log_info( &logger, " Stop motor." );

            Delay_ms( 2000 );
            
            //Change direction
            if ( dir )
            {
                log_info( &logger, " Move motor CCW." );
                dir = 0;
                stepper17_set_dir_state( &stepper17, dir );
            }
            else
            {
                log_info( &logger, " Move motor CW." );
                dir = 1;
                stepper17_set_dir_state( &stepper17, dir );
                
                if ( 32 == step )
                {
                    step = 2;
                }
                else
                {
                    step *= 2;
                }
                set_step_resolution( step );
            }
            
            //Move motor
            stepper17_set_en_state( &stepper17, 1 );
            counter = 0;
            run = 1;
        }
        else
        {
            while ( 0 == stepper17_get_int_state( &stepper17 ) );
        }
    }
    
}

```

## Note

> Click is tested with motor with 1 step = 1.8degree with PWM 
configured with 1500Hz. You may need to lower MCU frequency 
to reach 1500Hz PWM frequency.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
