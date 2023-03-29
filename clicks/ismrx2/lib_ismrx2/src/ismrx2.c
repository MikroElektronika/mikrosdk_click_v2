/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file ismrx2.c
 * @brief ISM RX 2 Click Driver.
 */

#include "ismrx2.h"

/**
 * @brief ISM RX 2 Click data buffers.
 * @details Data proccesing buffers of the ISM RX 2 Click board.
 */
uint8_t sample_buf[ 1024 ];
uint8_t man_buf[ 512 ];
uint8_t bit_buf[ 256 ];

/**
 * @brief ISM RX 2 Click data counters and flags.
 * @details Data proccesing counters and flags of the ISM RX 2 Click board.
 */
uint16_t sample_cnt = 0;
uint16_t man_cnt = 0;
uint16_t bit_cnt = 0;
uint16_t data_cnt = 0;
uint16_t max_1 = 0;
uint16_t cnt_1 = 0;
uint8_t change_val_1 = 0;
uint16_t max_0 = 0;
uint16_t max_00 = 0;
uint16_t cnt_0 = 0;
uint8_t change_val_0 = 0;
uint16_t same_sample_cnt = 0;
uint8_t valid_data = 0;

/**
 * @brief Sample collecting function.
 * @details This function is used to collect data samples of ISM RX 2 Click.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[out] sample_buf : Collected data.
 * @return Nothing.
 * @note None.
 */
static void dev_sample_collecter ( ismrx2_t *ctx );

/**
 * @brief Check minimum and maximum value function.
 * @details This function is used to get minimum and maximum data of 
 * manchester encoded data of ISM RX 2 Click.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[out] check_b : checked data.
 * @return Nothing.
 * @note None.
 */
static void dev_min_max_check ( uint8_t check_b );

/**
 * @brief Filtering collected data function.
 * @details This function is used to filter collected data samples of ISM RX 2 Click.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[in] sample_buf : Data to be filtred.
 * @return Nothing.
 * @note None.
 */
static void dev_filter_sample ( void );

/**
 * @brief Resets flags and counters to default values function.
 * @details This function is used to reset flags and counters of ISM RX 2 Click.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void dev_reset_to_default ( void );

/**
 * @brief Function for extracting data from sample buffer.
 * @details This function is used to extract data from sample baffer of ISM RX 2 Click.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[in] sample_buf : Sampled data buffer.
 * @return Nothing.
 * @note None.
 */
static void dev_man_sort ( void );

/**
 * @brief Function that sets data to manchester buffer.
 * @details This function is used to set data into manchester baffer of ISM RX 2 Click.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[in] smp_cnt : Number of samples.
 * @param[in] man_data : Manchester encoded data.
 * @return Nothing.
 * @note None.
 */
static void dev_man_set_data ( uint16_t smp_cnt, uint8_t man_data );

/**
 * @brief Extracting bit data from manchester buffer.
 * @details This function is used to extract bit of data from manchester baffer of ISM RX 2 Click.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void dev_bit_sort ( void );

/**
 * @brief Extracting data from bit buffer.
 * @details This function is used to extract data from baffer of ISM RX 2 Click.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void dev_data_sort ( uint8_t *data_buf );

/**
 * @brief Delay between reading two preable bits.
 * @details This function is used to generate delay between reading two 
 * preable bits of ISM RX 2 Click.
 * @return Nothing.
 * @note None.
 */
static void dev_preable_delay ( void );

/**
 * @brief Delay between reading two data bits.
 * @details This function is used to generate delay between reading two 
 * data bits of ISM RX 2 Click.
 * @return Nothing.
 * @note None.
 */
static void dev_read_delay ( void );

void ismrx2_cfg_setup ( ismrx2_cfg_t *cfg ) 
{
    cfg->rst = HAL_PIN_NC;
    cfg->stb = HAL_PIN_NC;
    cfg->mst = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
}

err_t ismrx2_init ( ismrx2_t *ctx, ismrx2_cfg_t *cfg ) 
{
    err_t error_flag = ISMRX2_OK;

    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->stb, cfg->stb );

    error_flag |= digital_in_init( &ctx->mst, cfg->mst );
    error_flag |= digital_in_init( &ctx->rx_pin, cfg->rx_pin );
    
    return error_flag;
}

err_t ismrx2_default_cfg ( ismrx2_t *ctx ) 
{
    err_t error_flag = ISMRX2_OK;
    
    ismrx2_set_rst_pin_state( ctx, ISMRX2_PIN_STATE_HIGH );
    Delay_1ms( );
    ismrx2_set_rst_pin_state( ctx, ISMRX2_PIN_STATE_LOW );
    Delay_10ms( );

    ismrx2_set_stb_pin_state( ctx, ISMRX2_PIN_STATE_LOW );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    ismrx2_set_stb_pin_state( ctx, ISMRX2_PIN_STATE_HIGH );
    Delay_10ms( );
    ismrx2_set_stb_pin_state( ctx, ISMRX2_PIN_STATE_LOW );
    Delay_1ms( );
    ismrx2_set_stb_pin_state( ctx, ISMRX2_PIN_STATE_HIGH );

    ismrx2_set_rst_pin_state( ctx, ISMRX2_PIN_STATE_HIGH );
    Delay_1ms( );
    ismrx2_set_rst_pin_state( ctx, ISMRX2_PIN_STATE_LOW );
    Delay_10ms( );

    return error_flag;
}

void ismrx2_set_rst_pin_state ( ismrx2_t *ctx, uint8_t state )
{
    if ( state == ISMRX2_PIN_STATE_HIGH )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void ismrx2_set_stb_pin_state ( ismrx2_t *ctx, uint8_t state )
{
    if ( state == ISMRX2_PIN_STATE_HIGH )
    {
        digital_out_high( &ctx->stb );
    }
    else
    {
        digital_out_low( &ctx->stb );
    }
}

uint8_t ismrx2_get_mst_pin_state ( ismrx2_t *ctx )
{
    return digital_in_read( &ctx->mst );
}

uint8_t ismrx2_get_data_pin_state ( ismrx2_t *ctx )
{
    return digital_in_read( &ctx->rx_pin );
}

err_t ismrx2_read_manchester_data ( ismrx2_t *ctx, uint8_t *data_out )
{
    err_t error_flag = ISMRX2_OK;
    
    dev_sample_collecter( ctx );
    dev_filter_sample( );
    
    if ( valid_data == ISMRX2_OK )
    {
        dev_man_sort( );
        dev_bit_sort( );
        dev_data_sort( data_out );
        
        if ( valid_data == ISMRX2_OK )
        {
            error_flag |= ISMRX2_OK;
        }
        else
        {
            error_flag |= ISMRX2_ERROR;
        }
    }
    else
    {
        error_flag |= ISMRX2_ERROR;
    }
    dev_reset_to_default( );
    
    return error_flag;
}

err_t ismrx2_read_rf_data ( ismrx2_t *ctx, uint8_t *data_out )
{
    uint8_t cnt_byte;
    // collecting data for sync data
    for ( cnt_byte = 0; cnt_byte < 16; cnt_byte++ )
    {
        dev_preable_delay( );
        if ( ( ( ISMRX2_DEFAULT_SYNC_BYTE >> ( 15 - cnt_byte ) ) &  1 ) != digital_in_read( &ctx->rx_pin ) )
        {
            return ISMRX2_ERROR;
        }
    }
    // Reading data till 0 timeout byte
    for ( ; ; )
    {
        for ( cnt_byte = 0; cnt_byte < 8; cnt_byte++ )
        {
            dev_read_delay( );
            *data_out = ( *data_out << 1 ) | digital_in_read( &ctx->rx_pin );
        }
        if ( 0x00 == *data_out )
            return ISMRX2_OK;
        data_out++;
    }
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_sample_collecter ( ismrx2_t *ctx )
{
    uint8_t sample;

    for ( ; ; )
    {
        sample = digital_in_read( &ctx->rx_pin ); 

        sample_buf[ sample_cnt ] = sample; //collect sample

        if ( ( sample == sample_buf[ sample_cnt - 1 ] ) && ( sample_cnt > 0 ) )
        {
            same_sample_cnt++;
            if ( same_sample_cnt > 50 )
            {
                return;
            }
        }
        else
        {
            same_sample_cnt = 0;
        }

        if ( sample_cnt > 1000 )
        {
            return;
        }

        sample_cnt++; 
        Delay_50us( );
    }
}

static void dev_min_max_check ( uint8_t check_b )
{   
    if ( 1 == check_b )
    {   //check maximum 1 data value in a row
        if ( cnt_1 > max_1 )
        {
            max_1 = cnt_1;
        }
    }
    else
    {   //check maximum 0 data value in a row
        if ( cnt_0 > max_0 )
        {
            max_0 = cnt_0;
        }
    }
}

static void dev_filter_sample ( void )
{  
    uint8_t last_sample = 1;

    for ( uint16_t cnt = 0; cnt < sample_cnt; cnt++ )
    {
        if ( sample_buf[ cnt ] )
        {
            cnt_0 = 0;
            max_00 = max_0;
            if ( last_sample == sample_buf[ cnt ] )
            {
                cnt_1++;
            }
            else
            {
                cnt_1 = 1;
            }
        }
        else
        {
            cnt_1 = 0;
            if ( last_sample == sample_buf[ cnt ] )
            {
                cnt_0++;
            }
            else
            {
                cnt_0 = 1;
            }
        }
        dev_min_max_check( sample_buf[ cnt ] );
        last_sample = sample_buf[ cnt ];
    }
    // checks if timeout occured on low data
    if ( max_0 == same_sample_cnt )
    {
        valid_data = ISMRX2_OK;
    }
    else
    {
        valid_data = ISMRX2_ERROR;
    }
}

static void dev_reset_to_default ( void )
{   
    max_1 = 0;
    cnt_1 = 0;
    max_0 = 0;
    max_00 = 0;
    cnt_0 = 0;
    sample_cnt = 0;
    valid_data = 0;
    man_cnt = 0;
    bit_cnt = 0;
    data_cnt = 0;
}

static void dev_man_sort ( void )
{   //sorting sample data into manchester data
    uint8_t last_sample = 1;
    uint16_t same_smpl_cnt = 0;

    change_val_0 = max_00 / 2 + 1;
    change_val_1 = max_1 / 2 + 1;

    last_sample = sample_buf[ 0 ];
    for ( uint16_t cnt = 1; cnt < sample_cnt; cnt++ )
    {
        if ( ( last_sample == sample_buf[ cnt ] ) )
        {
            same_smpl_cnt++;
            last_sample = sample_buf[ cnt ];
        }
        else
        {
            dev_man_set_data( same_smpl_cnt, last_sample );
            same_smpl_cnt = 1;
            last_sample = sample_buf[ cnt ];
        }
    }
}

static void dev_man_set_data ( uint16_t smp_cnt, uint8_t man_data )
{   
    if ( man_data )
    {
        if ( smp_cnt > change_val_1 )
        {
            man_buf[ man_cnt ] = 1;
            man_buf[ man_cnt + 1 ] = 1;
            man_cnt += 2;
        }
        else
        {
            man_buf[ man_cnt ] = 1;
            man_cnt++;
        }
    }
    else
    {
        if ( smp_cnt > change_val_0 )
        {
            man_buf[ man_cnt ] = 0;
            man_buf[ man_cnt + 1 ] = 0;
            man_cnt += 2;
        }
        else
        {
            man_buf[ man_cnt ] = 0;
            man_cnt++;
        }
    }
}

static void dev_bit_sort ( void )
{
    for ( uint16_t cnt = 0; cnt < man_cnt; cnt+=2 )
    {   //first man_buf data is 0 so next will be 1, bit 1 value ( rising edge )
        if ( man_buf[cnt] == 0 )
        {
            bit_buf[ bit_cnt ] = 1;
        }
        //first man_buf data is 1 so newt will be 0, bit 0 value ( falling edge )
        if (  man_buf[cnt] == 1 )
        {
            bit_buf[ bit_cnt ] = 0;
        }
        bit_cnt++;
    }
}

static void dev_data_sort ( uint8_t *data_buf )
{
    uint8_t step_flag = 7;
    uint16_t temp_data = 0;
    //converting bit data to bytes
    for ( uint16_t cnt = 0; cnt < bit_cnt; cnt++ )
    {
        if ( cnt  > step_flag )
        {
            data_cnt++;
            step_flag += 8;
            temp_data = 0;
        }

        temp_data <<= 1;
        temp_data |= bit_buf[ cnt ];
        data_buf[ data_cnt ] = temp_data;
    }
    data_cnt++;
    //checks if sync_byte is received
    if ( data_buf[ 0 ] == ISMRX2_FSK_DEFAULT_SYNC_BYTE )
    {
        valid_data = ISMRX2_OK;
    }
    else
    {
        valid_data = ISMRX2_ERROR;
    }
}

static void dev_preable_delay ( void )
{
    #if defined(__MIKROC_AI_FOR_PIC__)
        Delay_480us();
        Delay_10us();
    #elif defined(__MIKROC_AI_FOR_PIC32__)
        Delay_500us( ); 
    #else
        Delay_500us( ); 
    #endif
}

static void dev_read_delay ( void )
{
    #if defined(__MIKROC_AI_FOR_PIC__)
        Delay_480us();
        Delay_10us();
    #elif defined(__MIKROC_AI_FOR_PIC32__)
        Delay_480us();
        Delay_10us();
    #else
        Delay_500us( ); 
    #endif
}

// ------------------------------------------------------------------------- END
