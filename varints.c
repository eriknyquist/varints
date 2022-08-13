#include <stdint.h>
#include <stddef.h>

#include "varints.h"


#define BYTE_DATA_MASK (0x7fu)
#define BYTE_CONT_BIT  (0x80u)


/**
 * Encodes an unsigned 64-bit value to a VLQ/varint byte stream.
 */
static void _u64_to_varint(uint64_t input, uint8_t *output, int *bytes_generated)
{
    /* Handle 7 bits at a time, shifting down until we reach the most significant 7
     * non-zero bits, to generate all encoded bytes except the last one */
    int byte_count = 0;
    while (input > BYTE_DATA_MASK)
    {
        *output = (input & BYTE_DATA_MASK) | BYTE_CONT_BIT; // Set continuation bit
        output++;
        byte_count++;
        input >>= 7u;
    }

    // Populate the last byte, no continuation bit this time
    *output = input;
    byte_count++;

    if (NULL != bytes_generated)
    {
        *bytes_generated = byte_count;
    }
}


/**
 * Decodes a VLQ/varint byte stream to an unsigned 64-bit integer.
 */
static int _varint_to_u64(uint8_t *input, uint64_t *output, int *bytes_consumed)
{
    *output = 0u;
    uint64_t bit_pos = 0u;
    unsigned int i = 0u;

    for (i = 0u; i < VARINTS_MAX_ENCODED_LEN; i++)
    {
        *output |= ((uint64_t) (input[i] & BYTE_DATA_MASK)) << bit_pos;
        bit_pos += 7u;

        if ((input[i] & BYTE_CONT_BIT) == 0u)
        {
            // Continutation bit is cleared, break out
            break;
        }
    }

    if (i >= VARINTS_MAX_ENCODED_LEN)
    {
        // Consumed VARINTS_MAX_ENCODED_LEN bytes without seeing the cont. bit get cleared
        return 1;
    } else if (NULL != bytes_consumed)
    {
        *bytes_consumed = i + 1u;
    }

    return 0;
}


/**
 * @see varints_api.h
 */
int varint_encode_u64(uint64_t input, uint8_t *output, int *bytes_generated)
{
    if (NULL == output)
    {
        return -1;
    }

    _u64_to_varint(input, output, bytes_generated);

    return 0;
}


/**
 * @see varints_api.h
 */
int varint_decode_u64(uint8_t *input, uint64_t *output, int *bytes_consumed)
{
    if ((NULL == input) || (NULL == output))
    {
        return -1;
    }

    return _varint_to_u64(input, output, bytes_consumed);
}


/**
 * @see varints_api.h
 */
int varint_encode_i64(int64_t input, uint8_t *output, int *bytes_generated)
{
    if (NULL == output)
    {
        return -1;
    }

    uint64_t uintin = (uint64_t) ((input << 1) ^ (input >> 63));
    _u64_to_varint(uintin, output, bytes_generated);

    return 0;
}


/**
 * @see varints_api.h
 */
int varint_decode_i64(uint8_t *input, int64_t *output, int *bytes_consumed)
{
    if ((NULL == input) || (NULL == output))
    {
        return -1;
    }

    uint64_t uintout = 0u;
    int ret = _varint_to_u64(input, &uintout, bytes_consumed);
    if (ret != 0)
    {
        return ret;
    }

    *output = (uintout & 1u) ? (uintout >> 1u) ^ -1 : (uintout >> 1u);
    return 0;
}
