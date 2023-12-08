
---
# H-Bridge 14 click

> H-Bridge 14 Click is a compact add-on board with an H-Bridge gate driver, also known as a full-bridge pre-driver. This board features the DRV8873, an automotive H-Bridge motor driver from Texas Instruments. The DRV8873 is an N-channel H-Bridge motor driver that can drive one bidirectional brushed DC motor, two unidirectional brushed DC motors, solenoids, or other resistive inductive loads.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-14-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the H-Bridge 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for H-Bridge 14 Click driver.

#### Standard key functions :

- `hbridge14_cfg_setup` Config Object Initialization function.
```c
void hbridge14_cfg_setup ( hbridge14_cfg_t *cfg );
```

- `hbridge14_init` Initialization function.
```c
err_t hbridge14_init ( hbridge14_t *ctx, hbridge14_cfg_t *cfg );
```

- `hbridge14_default_cfg` Click Default Configuration function.
```c
err_t hbridge14_default_cfg ( hbridge14_t *ctx );
```

#### Example key functions :

- `hbridge14_set_pins` H-Bridge 14 set pins function.
```c
err_t hbridge14_set_pins ( hbridge14_t *ctx, uint8_t set_mask, uint8_t clr_mask );
```

- `hbridge14_sleep_state` H-Bridge 14 control sleep function.
```c
err_t hbridge14_sleep_state ( hbridge14_t *ctx, uint8_t sleep_state );
```

- `hbridge14_drive_motor` H-Bridge 14 drive motor function.
```c
err_t hbridge14_drive_motor ( hbridge14_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of the H-Bridge 14 board by driving the 
  motor in both directions with braking and coasting in between.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge14_cfg_t hbridge14_cfg;  /**< Click config object. */

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
    hbridge14_cfg_setup( &hbridge14_cfg );
    HBRIDGE14_MAP_MIKROBUS( hbridge14_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge14_init( &hbridge14, &hbridge14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE14_ERROR == hbridge14_default_cfg ( &hbridge14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor in both directions with coasting and braking in between, every sate is lasting 5 seconds.

```c
void application_task ( void )
{
    uint8_t fault_status = 0;

    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_CW );
    log_printf( &logger, " Driving motor Clockwise \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms( 5000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_BRAKE );
    log_printf( &logger, " Brake is on \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms( 5000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_CCW );
    log_printf( &logger, " Driving motor counter-clockwise \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms( 5000 );
    
    hbridge14_drive_motor( &hbridge14, HBRIDGE14_DRIVE_MOTOR_COASTING );
    log_printf( &logger, " Driving motor Coasting \r\n" );
    hbridge14_register_read( &hbridge14, HBRIDGE14_REG_FAULT_STATUS, &fault_status );
    log_printf( &logger, " Fault status : 0x%.2X \r\n", ( uint16_t ) fault_status );
    Delay_ms( 5000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
