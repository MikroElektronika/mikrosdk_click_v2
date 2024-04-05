

---
# Accel 8 click

Accel 8 Click is an advanced 6-axis motion tracking Click board™, which utilizes the MPU6050, a very popular motion sensor IC, equipped with a 3-axis gyroscope and 3-axis accelerometer. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Accel8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel8_cfg_setup ( accel8_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL8_RETVAL accel8_init ( accel8_t *ctx, accel8_cfg_t *cfg );

- Click Default Configuration function.
> void accel8_default_cfg ( accel8_t *ctx );


#### Example key functions :

- This function reads Accel axis data.
> void accel8_get_accel_axis ( accel8_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );
 
- This function reads Gyro axis data.
> void accel8_get_gyro_axis ( accel8_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );

- This function returns Interupt state.
> uint8_t accel8_get_interrupt ( accel8_t *ctx );

## Examples Description

> This application measures accelermeter and gyroscopic data and temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init, reset chip and start configuration chip for measurement.
 
```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel8_cfg_t cfg;

    uint8_t temp_write;

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

    accel8_cfg_setup( &cfg );
    ACCEL8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel8_init( &accel8, &cfg );

    log_printf( &logger, " *-* Device Reset *-* \r\n");
    temp_write = ACCEL8_PM1_DEVICE_RESET;
    accel8_generic_write( &accel8, ACCEL8_REG_PWR_MGMT_1, &temp_write, 1 );
    temp_write = ACCEL8_GYRO_RESET | ACCEL8_ACCEL_RESET | ACCEL8_TEMP_RESET;
    accel8_generic_write( &accel8, ACCEL8_REG_SIGNAL_PATH_RESET, &temp_write, 1 );

    log_printf( &logger, " *-* Device Configuration *-* \r\n" );
    accel8_default_cfg ( &accel8, ACCEL8_INTE_DATA_RDY_ENABLE, ACCEL8_GYRO_CFG_FULL_SCALE_RANGE_250dbs, &range);

    Delay_ms ( 1000 );
    log_printf( &logger, " --- Start Measurement --- \r\n" );
}
  
```

### Application Task

> Reads Accel X/Y/Z axis, Gyro X/Y/Z axis and device Temperature. 
> All data logs on the USBUART every 2 sec.

```c

void application_task ( void )
{   
    float temperature;
    int16_t x_gyro_axis;
    int16_t y_gyro_axis;
    int16_t z_gyro_axis;
    int16_t x_accel_axis;
    int16_t y_accel_axis;
    int16_t z_accel_axis;

    //  Task implementation.

    accel8_get_accel_axis( &accel8,&x_accel_axis, &y_accel_axis, &z_accel_axis );
    accel8_get_gyro_axis( &accel8, &x_gyro_axis, &y_gyro_axis, &z_gyro_axis );
    temperature = accel8_get_temperature( &accel8 );
    
    // LOGS DATA

    log_printf( &logger, "________________ Accel 8 click _________________\r\n" );
    log_printf( &logger, "|  Data   | X axis | Y axis | Z axis |  Range  |\r\n" );
    log_printf( &logger, "|_________|________|________|________|_________|\r\n" );
    log_printf( &logger, "|  Accel  | %d  | %d  | %d  | %dg |\r\n", x_accel_axis, y_accel_axis, z_accel_axis, accel_range );
    log_printf( &logger, "|_________|________|________|________|_________|\r\n" );
    log_printf( &logger, "|  Gyro   | %d  | %d  | %d  | %ddps|\r\n", x_gyro_axis, y_gyro_axis, z_gyro_axis, gyro_range );
    log_printf( &logger, "|_________|________|________|________|_________|\r\n" );
    log_printf( &logger, "|  Temp   | %.2f  C         |\r\n" , temperature);
    log_printf( &logger, "|_________|_________________|\r\n" );

    log_printf( &logger, " \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel8

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
