#ifndef VARINTS_H
#define VARINTS_H


/**
 * @brief Maximum size of an encoded 64-bit VLQ/varint value
 */
#define VARINTS_MAX_ENCODED_LEN (9u)


/**
 * Encode an unsigned 64-bit integer into a VLQ/varint byte stream.
 *
 * @param input            Input value to encode.
 * @param output           Pointer to location to store encoded output bytes.
 *                         At least #VARINTS_MAX_ENCODED_LEN bytes are expected to
 *                         be available.
 * @param bytes_generated  Pointer to location to store number of output bytes
 *                         generated, may be NULL.
 *
 * @return 0 if successful, and -1 if a NULL pointer was provided for 'output'.
 */
int varint_encode_u64(uint64_t input, uint8_t *output, int *bytes_generated);


/**
 * Decode a VLQ/varint byte stream into an unsigned 64-bit integer.
 *
 * @param input            Pointer to VLQ/varint byte stream to decode.
 * @param output           Pointer to location to store decoded integer value.
 * @param bytes_consumed   Pointer to location to store number of input bytes
 *                         consumed before the end of the VLQ/varint value
 *                         was found, may be NULL.
 *
 * @return 0 if successful, 1 if the end of the VLQ/varint byte stream was not
 *         found after #VARINTS_MAX_ENCODED_LEN bytes, and -1 if a NULL pointer was
 *         provided for 'input' or 'output'.
 */
int varint_decode_u64(uint8_t *input, uint64_t *output, int *bytes_consumed);


/**
 * Encode a signed 64-bit integer into a VLQ/varint byte stream.
 *
 * @param input            Input value to encode.
 * @param output           Pointer to location to store encoded output bytes.
 *                         At least #VARINTS_MAX_ENCODED_LEN bytes are expected to
 *                         be available.
 * @param bytes_generated  Pointer to location to store number of output bytes
 *                         generated, may be NULL.
 *
 * @return 0 if successful, and -1 if a NULL pointer was provided for 'output'.
 */
int varint_encode_i64(int64_t input, uint8_t *output, int *bytes_generated);


/**
 * Decode a VLQ/varint byte stream into a signed 64-bit integer.
 *
 * @param input            Pointer to VLQ/varint byte stream to decode.
 * @param output           Pointer to location to store decoded integer value.
 * @param bytes_consumed   Pointer to location to store number of input bytes
 *                         consumed before the end of the VLQ/varint value
 *                         was found, may be NULL.
 *
 * @return 0 if successful, 1 if the end of the VLQ/varint byte stream was not
 *         found after #VARINTS_MAX_ENCODED_LEN bytes, and -1 if a NULL pointer was
 *         provided for 'input' or 'output'.
 */
int varint_decode_i64(uint8_t *input, int64_t *output, int *bytes_consumed);

#endif // VARINTS_H
