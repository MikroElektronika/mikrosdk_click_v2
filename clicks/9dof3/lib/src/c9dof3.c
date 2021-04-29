/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "c9dof3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C9DOF3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c9dof3_i2c_write ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c9dof3_i2c_read ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c9dof3_spi_write ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c9dof3_spi_read ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void dev_soft_reset_delay ( void );

static void dev_mag_wake_up_delay ( void );

static void dev_set_slave_addr ( c9dof3_t *ctx );

static void dev_start_chip_select ( c9dof3_t *ctx );

static void dev_stop_chip_select ( c9dof3_t *ctx, uint8_t sel_mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c9dof3_cfg_setup ( c9dof3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs1 = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->cs2 = HAL_PIN_NC;
    cfg->cs3 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_STANDARD_SPEED; 
    cfg->i2c_address = C9DOF3_ACC_I2C_SLAVE_ADDRESS;
    cfg->spi_speed = SPI_MEDIUM; 
    cfg->spi_mode = SPI_MODE_0;
    cfg->sel = C9DOF3_MASTER_I2C;
}

C9DOF3_RETVAL c9dof3_init ( c9dof3_t *ctx, c9dof3_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C9DOF3_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.pins.scl = cfg->scl;
        i2c_cfg.pins.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) != I2C_SUCCESS )
        {
            return C9DOF3_INIT_ERROR;
        }

        ctx->read_f = c9dof3_i2c_read;
        ctx->write_f = c9dof3_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode        = cfg->spi_mode;
        spi_cfg.speed       = cfg->spi_speed;
        spi_cfg.pins.sck    = cfg->sck;
        spi_cfg.pins.miso   = cfg->miso;
        spi_cfg.pins.mosi   = cfg->mosi;
        spi_cfg.chip_select = cfg->cs1;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_SUCCESS )
        {
            return  C9DOF3_INIT_ERROR;
        }

         spi_master_set_dummy_data( &ctx->spi, C9DOF3_DUMMY );
        
        ctx->read_f = c9dof3_spi_read;
        ctx->write_f = c9dof3_spi_write;
    }
    
    // Output pins 

    digital_out_init( &ctx->cs2, cfg->cs2 );
    digital_out_init( &ctx->cs3, cfg->cs3 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    spi_master_stop( &ctx->spi ); 
    digital_out_high( &ctx->cs2 );
    digital_out_high( &ctx->cs3 );


    return C9DOF3_OK;
}

void c9dof3_default_cfg ( c9dof3_t *ctx )
{
    uint8_t write_data;

    // Accel Soft Reset
    ctx->sel_mode = COMMUNICATION_MODE_ACCEL;
    write_data = C9DOF3_INITIATED_SOFT_RESET;
    c9dof3_generic_write ( ctx, C9DOF3_REG_ACC_BGW_SOFTRESET, &write_data, 1 );
    dev_soft_reset_delay( );
  
    // Gyro Soft Reset
    ctx->sel_mode = COMMUNICATION_MODE_GYRO;
    c9dof3_generic_write( ctx, C9DOF3_REG_GYRO_BGW_SOFTRESET, &write_data, 1 );
    dev_soft_reset_delay( );
  
    // Mag Soft Reset
    ctx->sel_mode = COMMUNICATION_MODE_MAG;
    write_data = C9DOF3_MAG_POW_CTL_SOFT_RESET;
    c9dof3_generic_write( ctx, C9DOF3_REG_MAG_PWR_CNTL1, &write_data, 1 );
    dev_soft_reset_delay( );

    // Accel Default Configuration
    // Select Accel PMU Range( +-2 )
    ctx->sel_mode = COMMUNICATION_MODE_ACCEL;
    write_data = C9DOF3_ACC_RANGE_2;
    c9dof3_generic_write( ctx, C9DOF3_REG_ACC_PMU_RANGE, &write_data, 1 );
    
    // Select Accel PMU_BW   ( 7.81Hz )
    write_data = C9DOF3_ACC_PMU_BW_7_81;
    c9dof3_generic_write( ctx, C9DOF3_REG_ACC_PMU_BW, &write_data, 1 );
  
    // Select Accel PMU_LPW  ( NomalMode, SleepDuration 0.5ms )
    write_data =  C9DOF3_ACC_PMU_LPW_MODE_NOMAL | C9DOF3_ACC_PMU_LPW_SLEEP_DUR_0_5MS;
    c9dof3_generic_write( ctx, C9DOF3_REG_ACC_PMU_LPW, &write_data, 1 );

    // Gyro Default Configuration
    // Select Gyro Range( 262.4 LSB/�/s )
    ctx->sel_mode = COMMUNICATION_MODE_GYRO;
    write_data = C9DOF3_GYRO_RANGE_262_4;
    c9dof3_generic_write( ctx, C9DOF3_REG_GYRO_RANGE, &write_data, 1 );
    
    // Select Gyro BW   ( 32Hz )
    write_data = C9DOF3_GYRO_BW_32;
    c9dof3_generic_write( ctx, C9DOF3_REG_GYRO_BW, &write_data, 1 );
    
    // Select Gyro LPM1 ( NomalMode, SleepDuration 2ms )
    write_data = C9DOF3_GYRO_LPM1_MODE_NOMAL | C9DOF3_GYRO_LPM1_SLEEP_DUR_2MS;
    c9dof3_generic_write( ctx, C9DOF3_REG_GYRO_LPM1, &write_data, 1 );

    // Mag Default Configuration
    // Set sleep mode
    ctx->sel_mode = COMMUNICATION_MODE_MAG;
    write_data = C9DOF3_MAG_POW_CTL_SLEEP_MODE;
    c9dof3_generic_write( ctx, C9DOF3_REG_MAG_PWR_CNTL1, &write_data, 1 );
    dev_mag_wake_up_delay( );
  
    // Adv. st., DataRate, OperationMode, SelfTest ( NomalMode, ODR 10Hz )
    write_data = C9DOF3_MAG_DATA_RATE_10;
    c9dof3_generic_write( ctx, C9DOF3_REG_MAG_PWR_CNTL2, &write_data, 1 );
    
    // Repetitions for X-Y Axis: 0x04 -> ( 1 + 2 ( 2 ^ 2 ) ) = 9
    write_data = C9DOF3_MAG_XY_REPET_9;
    c9dof3_generic_write( ctx, C9DOF3_REG_MAG_REP_XY, &write_data, 1 );
    
    // Repetition for Z-Axis: 0x0F -> ( 1 +( 2 ^ 0 + 2 ^ 1 + 2 ^ 2 + 2 ^ 3) = 15
    write_data = C9DOF3_MAG_Z_REPET_15;
    c9dof3_generic_write( ctx, C9DOF3_REG_MAG_REP_Z, &write_data, 1 );
}

void c9dof3_generic_write ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c9dof3_generic_read ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t c9dof3_check_communication ( c9dof3_t *ctx )
{
    uint8_t accel_id;
    uint8_t gyro_id;
    uint8_t mag_id;
    uint8_t comm_status;
    
    comm_status = 0;

    ctx->sel_mode = COMMUNICATION_MODE_ACCEL;
    c9dof3_generic_read( ctx, C9DOF3_REG_ACC_WHO_AM_I, &accel_id, 1 );

    if ( accel_id == C9DOF3_ACC_DEVICE )
    {
        accel_id = C9DOF3_ID_CHECK_SUCCESS;
    }
    else
    {
        accel_id = C9DOF3_ID_CHECK_ERROR;
    }

    ctx->sel_mode = COMMUNICATION_MODE_GYRO;
    c9dof3_generic_read( ctx, C9DOF3_REG_GYRO_WHO_AM_I, &gyro_id, 1 );

    if ( gyro_id == C9DOF3_GYRO_DEVICE )
    {
        gyro_id = C9DOF3_ID_CHECK_SUCCESS;
    }
    else
    {
        gyro_id = C9DOF3_ID_CHECK_ERROR;
    }
    
    ctx->sel_mode = COMMUNICATION_MODE_MAG;
    c9dof3_generic_read( ctx, C9DOF3_REG_MAG_WHO_AM_I, &mag_id, 1 );

    if ( mag_id == C9DOF3_MAG_DEVICE )
    {
        mag_id = C9DOF3_ID_CHECK_SUCCESS;
    }
    else
    {
        mag_id = C9DOF3_ID_CHECK_ERROR;
    }
    
    comm_status = accel_id;
    comm_status <<= 1;
    comm_status |= gyro_id;
    comm_status <<= 1;
    comm_status |= mag_id;
    
    return comm_status;
}


void c9dof3_read_accel_data ( c9dof3_t *ctx, c9dof3_accel_t *accel_data )
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    int16_t sign_res;

    ctx->sel_mode = COMMUNICATION_MODE_ACCEL;
    c9dof3_generic_read( ctx, C9DOF3_REG_ACC_DATA_START, rx_buf, 6 );

    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= ( rx_buf[ 0 ] << 4 );
    sign_res = ( int16_t ) tmp;
    sign_res >>= 4;
    accel_data->x = sign_res;

    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= ( rx_buf[ 2 ] << 4 );
    sign_res = ( int16_t ) tmp;
    sign_res >>= 4;
    accel_data->y = sign_res;

    tmp = rx_buf[ 5 ];
    tmp <<= 8;
    tmp |= ( rx_buf[ 4 ] << 4 );
    sign_res = ( int16_t ) tmp;
    sign_res >>= 4;
    accel_data->z = sign_res;
}

void c9dof3_read_gyro_data ( c9dof3_t *ctx, c9dof3_gyro_t *gyro_data )
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    int16_t sign_res;

    ctx->sel_mode = COMMUNICATION_MODE_GYRO;
    c9dof3_generic_read( ctx, C9DOF3_REG_GYRO_DATA_START, rx_buf, 6 );

    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];
    sign_res = ( int16_t ) tmp;
    gyro_data->x = sign_res;

    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    sign_res = ( int16_t ) tmp;
    gyro_data->y = sign_res;

    tmp = rx_buf[ 5 ];
    tmp <<= 8;
    tmp |= rx_buf[ 4 ];
    sign_res = ( int16_t ) tmp;
    gyro_data->z = sign_res;
}

void c9dof3_read_mag_data ( c9dof3_t *ctx, c9dof3_mag_t *mag_data )
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    int16_t sign_res;

    ctx->sel_mode = COMMUNICATION_MODE_MAG;
    c9dof3_generic_read( ctx, C9DOF3_REG_MAG_DATA_START, rx_buf, 6 );

    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= ( rx_buf[ 0 ] << 3 );
    sign_res = ( int16_t ) tmp;
    sign_res >>= 3;
    mag_data->x = sign_res;

    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= ( rx_buf[ 2 ] << 3 );
    sign_res = ( int16_t ) tmp;
    sign_res >>= 3;
    mag_data->y = sign_res;

    tmp = rx_buf[ 5 ];
    tmp <<= 8;
    tmp |= ( rx_buf[ 4 ] << 3 );
    sign_res = ( int16_t ) tmp;
    sign_res >>= 3;
    mag_data->z = sign_res;
}

void c9dof3_get_data ( c9dof3_t *ctx, c9dof3_accel_t *accel_data, c9dof3_gyro_t *gyro_data, c9dof3_mag_t *mag_data )
{
    c9dof3_read_accel_data( ctx, accel_data );
    
    c9dof3_read_gyro_data( ctx, gyro_data );

    c9dof3_read_mag_data( ctx, mag_data );
}

uint8_t c9dof3_check_interrupt ( c9dof3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c9dof3_i2c_write ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_transfer_t i2c_transfer;
    uint8_t tx_buf[ 256 ];
    uint16_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    dev_set_slave_addr( ctx );

    i2c_transfer.slave_address = ctx->slave_address;
    i2c_transfer.buffer   = tx_buf;
    i2c_transfer.count    = len + 1;
    i2c_transfer.end_mode = I2C_STOP_MODE;

    i2c_master_start( &ctx->i2c );
    i2c_master_write( &ctx->i2c, &i2c_transfer );    
}

static void c9dof3_i2c_read ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_transfer_t i2c_transfer;
    uint8_t tx_buf[ 3 ];

    tx_buf [ 0 ] = reg;

    dev_set_slave_addr( ctx );
    
    i2c_transfer.slave_address = ctx->slave_address;
    i2c_transfer.buffer   = tx_buf;
    i2c_transfer.count    = 1;
    i2c_transfer.end_mode = I2C_RESTART_MODE;

    i2c_master_start( &ctx->i2c );
    i2c_master_write( &ctx->i2c, &i2c_transfer );
    
    i2c_transfer.buffer   = data_buf;
    i2c_transfer.count    = len;
    i2c_transfer.end_mode = I2C_STOP_MODE;

    i2c_master_read( &ctx->i2c, &i2c_transfer );
}

static void c9dof3_spi_write ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    spi_master_transfer_data_t block;

    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg & C9DOF3_BIT_MASK_SPI_CMD_WRITE;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    block.tx_buffer = tx_buf;
    block.rx_buffer = 0;
    block.tx_length = len + 1;
    block.rx_length = 0;

    dev_start_chip_select( ctx );
    spi_master_transfer( &ctx->spi, &block );
    dev_start_chip_select( ctx );    
}

static void c9dof3_spi_read ( c9dof3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    spi_master_transfer_data_t block;

    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | C9DOF3_BIT_MASK_SPI_CMD_READ;
    
    block.tx_buffer = tx_buf;
    block.rx_buffer = rx_buf;
    block.tx_length = 1;
    block.rx_length = len + 1;
    
    dev_start_chip_select( ctx );
    spi_master_transfer( &ctx->spi, &block );
    dev_start_chip_select( ctx );  

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt + 1];
    }
}

static void dev_soft_reset_delay ( void )
{
    Delay_1ms( );
    Delay_1ms( );
}

static void dev_mag_wake_up_delay ( void )
{
    Delay_100ms();
}

static void dev_set_slave_addr ( c9dof3_t *ctx )
{
    switch ( ctx->sel_mode )
    {
        case COMMUNICATION_MODE_ACCEL:
        {
            ctx->slave_address = C9DOF3_ACC_I2C_SLAVE_ADDRESS;
            break;
        }
        case COMMUNICATION_MODE_GYRO:
        {
            ctx->slave_address = C9DOF3_GYRO_I2C_SLAVE_ADDRESS;
            break;
        }
        case COMMUNICATION_MODE_MAG:
        {
            ctx->slave_address = C9DOF3_MAG_I2C_SLAVE_ADDRESS;
            break;
        }
        default:
        {
            ctx->slave_address = C9DOF3_ACC_I2C_SLAVE_ADDRESS;
            break;
        }
    }
}

static void dev_start_chip_select ( c9dof3_t *ctx )
{
    switch ( ctx->sel_mode )
    {
        case COMMUNICATION_MODE_ACCEL:
        {
            spi_master_start( &ctx->spi ); 
            break;
        }
        case COMMUNICATION_MODE_GYRO:
        {
            digital_out_low( &ctx->cs2 );
            break;
        }
        case COMMUNICATION_MODE_MAG:
        {
            digital_out_low( &ctx->cs3 );
            break;
        }
        default:
        {
            spi_master_start( &ctx->spi ); 
            break;
        }
    }
}

static void dev_stop_chip_select ( c9dof3_t *ctx, uint8_t sel_mode )
{
    switch ( sel_mode )
    {
        case COMMUNICATION_MODE_ACCEL:
        {
            spi_master_stop( &ctx->spi ); 
            break;
        }
        case COMMUNICATION_MODE_GYRO:
        {
            digital_out_high( &ctx->cs2 );
            break;
        }
        case COMMUNICATION_MODE_MAG:
        {
            digital_out_high( &ctx->cs3 );
            break;
        }
        default:
        {
            spi_master_stop( &ctx->spi ); 
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

