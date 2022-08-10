#include <stdio.h>
#include <stdint.h>

#include "varints.h"


int main(void)
{
    uint8_t buf[VARINTS_MAX_ENCODED_LEN];
    int size = 0;
    int val = -2232334;

    if (0 != varint_encode_i64(val, buf, &size))
    {
        printf("varint_encode_i64 failed\n");
        return -1;
    }

    int64_t decoded = 0u;
    int decoded_size = 0;
    if (0 != varint_decode_i64(buf, &decoded, &decoded_size))
    {
        printf("varint_encode_i64 failed\n");
        return -1;
    }

    int decoded_int = (int) decoded;
    printf("input=%d, encode_size=%d, decoded=%d, decode_size=%d\n",
           val, size, decoded_int, decoded_size);

    return 0;
}
