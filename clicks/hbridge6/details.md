
---
# H-Bridge 6 click

> H-Bridge 6 Click is a compact add-on board that contains a DC motor driver for automotive applications. This board features the VNHD7008AY, an H-bridge motor driver for automotive DC motor driving from STMicroelectronics. The VNHD7008AY, features an undervoltage shutdown, load current limitation, overload active power limitation, overtemperature shutdown, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-6-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the HBridge6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HBridge6 Click driver.

#### Standard key functions :

- `hbridge6_cfg_setup` Config Object Initialization function.
```c
void hbridge6_cfg_setup ( hbridge6_cfg_t *cfg );
```

- `hbridge6_init` Initialization function.
```c
err_t hbridge6_init ( hbridge6_t *ctx, hbridge6_cfg_t *cfg );
```

- `hbridge6_default_cfg` Click Default Configuration function.
```c
err_t hbridge6_default_cfg ( hbridge6_t *ctx );
```

#### Example key functions :

- `hbridge6_reset` HW reset function.
```c
void hbridge6_reset ( hbridge6_t *ctx );
```

- `hbridge6_enable_diagnostic` Enable the diagnostic function.
```c
void hbridge6_enable_diagnostic ( hbridge6_t *ctx, uint8_t en_state );
```

- `hbridge6_set_direction` Adjust the direction function.
```c
void hbridge6_set_direction ( hbridge6_t *ctx, uint8_t direction );
```

## Example Description

> This is an example that demonstrates the use of H-Bridge 6 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C, reset the device and set default configuration, initialization and configure the PWM, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge6_cfg_t hbridge6_cfg;  /**< Click config object. */

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
    hbridge6_cfg_setup( &hbridge6_cfg );
    HBRIDGE6_MAP_MIKROBUS( hbridge6_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge6_init( &hbridge6, &hbridge6_cfg );
    if ( I2C_MASTER_ERROR == init_flag || PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Set default config.  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_default_cfg( &hbridge6 );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> It shows moving in the clockwise direction of rotation and moving in the counterclockwise direction of rotation from slow to fast speed. All data logs write on USB uart changes.

```c

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = 0;
    
    log_printf( &logger, "       Clockwise       \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_CLOCKWISE );
    
    while ( duty_cnt < 10 ) {
        duty = duty_cnt / 10.0;
        hbridge6_set_duty_cycle ( &hbridge6, duty );
        Delay_ms( 500 );
        duty_cnt += duty_inc;
    }
    
    log_printf( &logger, "         Brake         \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_BRAKE );
    duty_cnt = 1;
    Delay_ms( 1000 );
    
    log_printf( &logger, "    Counterclockwise   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_COUNTERCLOCKWISE );
    
    while ( duty_cnt < 10 ) {
        duty = duty_cnt / 10.0;
        hbridge6_set_duty_cycle ( &hbridge6, duty );
        Delay_ms( 500 );
        duty_cnt += duty_inc;
    }
    
    log_printf( &logger, "         Brake         \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_BRAKE );
    duty_cnt = 1;
    
    Delay_ms( 3000 );
    hbridge6_pwm_stop( &hbridge6 );
    Delay_ms( 2000 );
    hbridge6_pwm_start( &hbridge6 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
