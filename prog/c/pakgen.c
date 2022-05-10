/*
  pakgen.c by VAXbusters International

  version 1.1 fixed 64 bit issues, July 2018

  purdy code is:
  (C) Copyright 1991-1994 The Trustees of Indiana University
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

struct s {
    int32_t l[5][2];
} ctable[] = {
    {
        {
            {-587, -1},
            {-29,  -1},
            {-139, -1},
            {-947, -1},
            {-257, -1},
        }
    },
    {
        {
            {-821, -1},
            {-487, -1},
            {-107, -1},
            {-71,  -1},
            {-643, -1},
        }
    },
    {
        {
            {-521, -1},
            {-229, -1},
            {-379, -1},
            {-53,  -1},
            {-907, -1},
        }
    },
    {
        {
            {-43,  -1},
            {-467, -1},
            {-613, -1},
            {-761, -1},
            {-967, -1},
        }
    },
    {
        {
            {-53,  -1},
            {-127, -1},
            {-257, -1},
            {-337, -1},
            {-419, -1},
        }
    },
    {
        {
            {-13,  -1},
            {-839, -1},
            {-431, -1},
            {-563, -1},
            {-181, -1},
        }
    },
    {
        {
            {-83,  -1},
            {-283, -1},
            {-863, -1},
            {-349, -1},
            {-127, -1},
        }
    },
    {   {
            {-739, -1},
            {-313, -1},
            {-97,  -1},
            {-683, -1},
            {-157, -1},
        }
    },
    {   {
            {-61,  -1},
            {-199, -1},
            {-787, -1},
            {-401, -1},
            {-653, -1},
        }
    },
    {
        {
            {-991, -1},
            {-601, -1},
            {-19,  -1},
            {-449, -1},
            {-743, -1},
        }
    },
};

#define PRODUCT_NAME_TYPE  2
#define ISSUER_TYPE        4
#define AUTHORIZATION_TYPE 6
#define PRODUCER_TYPE      1
#define UNITS_TYPE         7
#define AVAILABILITY_TYPE  8
#define ACTIVITY_TYPE      9
#define KEY_OPTIONS_TYPE   17

uint32_t crctable[16] = {
    0x00000000,
    0x1DB71064,
    0x3B6E20C8,
    0x26D930AC,
    0x76DC4190,
    0x6B6B51F4,
    0x4DB26158,
    0x5005713C,
    0xEDB88320,
    0xF00F9344,
    0xD6D6A3E8,
    0xCB61B38C,
    0x9B64C2B0,
    0x86D3D2D4,
    0xA00AE278,
    0xBDBDF21C,
};

uint32_t lib_crc(int len,
                 uint8_t *array,
                 uint32_t initcrc,
                 uint32_t *crctbl) {
    uint32_t res = initcrc;

    while (len--) {
        uint32_t c = *(array++);
        res = res ^ c;
        res = (res >> 4u) ^ crctbl[res & 15u];
        res = (res >> 4u) ^ crctbl[res & 15u];
    }
    return res;
}

typedef uint32_t ULong;

static void pqexp(int32_t num[], int32_t power);
static void pqmod(int32_t nump[]);
static void pqmul(int32_t mulr[], int32_t muld[], int32_t prod[]);
static void emulq(int32_t mulr, int32_t muld, int32_t prod[]);
static void pqlsh(int32_t num[]);
static void pqadd(int32_t add[], int32_t sum[]);

void lib_emul(int32_t *mulr, int32_t *muld, int32_t *addend, int32_t prod[]) {
    int64_t res = (int64_t)*mulr * (int64_t)*muld + (int64_t)*addend;
    prod[0] = (int32_t)(res & 0xFFFFFFFF);
    prod[1] = (int32_t)((res >> 32ll) & 0xFFFFFFFFll);
}

void lib_addx(uint32_t *a1, uint32_t *a2, uint32_t *dst) {
    uint64_t a1_0 = a1[0],
        a1_1 = a1[1],
        a2_0 = a2[0],
        a2_1 = a2[1];

    uint64_t ll1 = a1_0 + (a1_1 << 32u);
    uint64_t ll2 = a2_0 + (a2_1 << 32u);
    uint64_t res = ll1 + ll2;

    dst[0] = (res & 0xFFFFFFFF);
    dst[1] = (res >> 32) & 0xFFFFFFFF;
}

#define CRC_DISPATCH(num, array) \
  { (num)[0] = ((array)[1] << 24) | ((array)[0] << 8);        \
    (num)[1] = (array)[2] | ((array)[3] << 16); }

#define COPY_32BIT_TO_ARRAY(val, array) \
  { (array)[0] = (val) & 0xFF; \
    (array)[1] = ((val) >> 8) & 0xFF; \
    (array)[2] = ((val) >> 16) & 0xFF; \
    (array)[3] = ((val) >> 24) & 0xFF; }

#define COPY_STRING_TO_BUFFER(str, type, buf) \
  { len = strlen((str)); \
    memcpy(buf, (str), len); \
    (buf)[len++] = (type); \
    (buf)[len++] = 0; }

void calc_checksum(char *product_name,
                   char *issuer,
                   char *authorization,
                   char *producer,
                   char *units,
                   char *availability,
                   char *activity,
                   unsigned char *key_options,
                   int salt,
                   uint32_t *cksum) {
    unsigned char tmp[256];
    int len;
    uint32_t crcnum[2];
    uint32_t crcval;
    uint32_t inicrc = -1;
    unsigned char crc_array[4];

    cksum[0] = 0;
    cksum[1] = 0;

    if (product_name != NULL) {
        /* PRODUCT NAME */
        COPY_STRING_TO_BUFFER(product_name, PRODUCT_NAME_TYPE, tmp);
        crcval = lib_crc(len, tmp, inicrc, crctable);
        COPY_32BIT_TO_ARRAY(crcval, crc_array);
        CRC_DISPATCH(crcnum, crc_array);
        lib_addx(crcnum, cksum, cksum);
    }

    if ((key_options[0] != 0) ||
        (key_options[1] != 0)) {
        /* OPTIONS */
        memcpy(tmp, key_options, 8);
        tmp[8] = KEY_OPTIONS_TYPE;
        tmp[9] = 0;
        crcval = lib_crc(10, tmp, inicrc, crctable);
        COPY_32BIT_TO_ARRAY(crcval, crc_array);
        CRC_DISPATCH(crcnum, crc_array);
        lib_addx(crcnum, cksum, cksum);
    }

    if (issuer != NULL) {
        /* ISSUER */
        COPY_STRING_TO_BUFFER(issuer, ISSUER_TYPE, tmp);
        crcval = lib_crc(len, tmp, inicrc, crctable);
        COPY_32BIT_TO_ARRAY(crcval, crc_array);
        CRC_DISPATCH(crcnum, crc_array);
        lib_addx(crcnum, cksum, cksum);
    }

    if (authorization != NULL) {
        /* AUTHORIZATION */
        COPY_STRING_TO_BUFFER(authorization, AUTHORIZATION_TYPE, tmp);
        crcval = lib_crc(len, tmp, inicrc, crctable);
        COPY_32BIT_TO_ARRAY(crcval, crc_array);
        CRC_DISPATCH(crcnum, crc_array);
        lib_addx(crcnum, cksum, cksum);
    }

    if (units != NULL) {
        /* UNITS */
        COPY_STRING_TO_BUFFER(units, UNITS_TYPE, tmp);
        crcval = lib_crc(len, tmp, inicrc, crctable);
        COPY_32BIT_TO_ARRAY(crcval, crc_array);
        CRC_DISPATCH(crcnum, crc_array);
        lib_addx(crcnum, cksum, cksum);
    }

    if (producer != NULL) {
        /* UNITS */
        COPY_STRING_TO_BUFFER(producer, PRODUCER_TYPE, tmp);
        crcval = lib_crc(len, tmp, inicrc, crctable);
        COPY_32BIT_TO_ARRAY(crcval, crc_array);
        CRC_DISPATCH(crcnum, crc_array);
        lib_addx(crcnum, cksum, cksum);
    }

    if (availability != NULL) {
        /* AVAILABILITY */
        COPY_STRING_TO_BUFFER(availability, AVAILABILITY_TYPE, tmp);
        crcval = lib_crc(len, tmp, inicrc, crctable);
        COPY_32BIT_TO_ARRAY(crcval, crc_array);
        CRC_DISPATCH(crcnum, crc_array);
        lib_addx(crcnum, cksum, cksum);
    }

    if (activity != NULL) {
        /* ACTIVITY */
        COPY_STRING_TO_BUFFER(activity, ACTIVITY_TYPE, tmp);
        crcval = lib_crc(len, tmp, inicrc, crctable);
        COPY_32BIT_TO_ARRAY(crcval, crc_array);
        CRC_DISPATCH(crcnum, crc_array);
        lib_addx(crcnum, cksum, cksum);
    }
}

void format_pwd(uint32_t pwd[], int salt) {
    char chars[17] = "ABCDEFGHIJKLMNOP";
    int i, j, k;

    printf("%d-", salt);
    for (k = 0; k < 2; k++) {
        int32_t tmp = pwd[k];
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 4; i++) {
                printf("%c", chars[(tmp >> 28) & 0xF]);
                tmp <<= 4;
            }
            if (j != 1) {
                printf("-");
            }
        }
        if (k != 1) {
            printf("-");
        }
    }
    printf("\n");
}

#define quadasgn(d, l, h) (d[0] = l,d[1] = h)
#define quadcopy(s, d)   (d[0] = s[0],d[1] = s[1])

static int32_t a = 59, n0 = (1 << 24) - 3, n1 = (1 << 24) - 63;

static void purdy(uint32_t epwd[], struct s *sc) {
    int i = 0;
    int32_t power, rs1[2], rs2[2], rs3[2];
    int32_t c[5][2];

    memcpy(c, sc->l, sizeof(c));

    // XXX don't understand this cast fully
    pqmod((int32_t *)epwd);

    /*
     *  Get x^n1.
     */

    quadcopy(epwd, rs2);
    power = n1;
    pqexp(rs2, power);

    /*
     *  Get x^(n0 - n1) + c1. Obtain x^n0 + x^n1 * c1 by multiplying the
     *  first two number.
     */

    quadcopy(epwd, rs1);
    power = n0 - n1;
    pqexp(rs1, power);
    pqadd(c[i], rs1);
    pqmul(rs2, rs1, rs1);
    i++;

    /*
     *  Get x * c2 + c3. Obtaining x^2 * c2 + x * c3 by multiplying x to
     *  the result.
     */

    quadcopy(epwd, rs2);
    pqmul(c[i], rs2, rs2);
    i++;
    pqadd(c[i], rs2);
    i++;
    quadcopy(epwd, rs3);
    pqmul(rs3, rs2, rs2);

    /*
     *  Get x^2 * c2 + x * c3 + c4. Obtaining x^3 * c2 + x^2 * c3 + x * c4
     *  by multiply x to the last result.
     */

    pqadd(c[i], rs2);
    i++;
    quadcopy(epwd, rs3);
    pqmul(rs3, rs2, rs2);

    /*
     *  Add c5 and the first number to produce the result.
     */

    pqadd(c[i], rs2);
    pqadd(rs2, rs1);
    quadcopy(rs1, epwd);
}

/*
 *      pqexp() replaces the quadword num with num^p where p is of the
 *          form p = 2^64 - a.
 *          Parameters:
 *              1) long num[2] Quadword to be raised to the given power
 *              2) long power  Raised to this power
 *          Return values:
 *              None
 */

static void pqexp(int32_t num[], int32_t power) {
    int32_t multi[2], save_num[2];


    if (power <= 0) {
        return;
    }
    quadasgn(multi, 1, 0);
    quadcopy(num, save_num);
    for (;;) {
        if (power & 0x00000001) {
            pqmul(num, multi, num);
            quadcopy(num, multi);
            if ((power & 0xfffffffe) == 0) {
                break;
            }
        }
        pqmul(save_num, save_num, num);
        quadcopy(num, save_num);
        power >>= 1;
    }

}

/*
 *      pqmod() replaces the quadword num with num mod p where p is of the
 *          form p = 2^64 - a.
 *          Parameters:
 *              1) long num[2] Quadword to be mod by p
 *          Return values:
 *              None
 */

static void pqmod(int32_t num[]) {
    if ((ULong)num[0] < (ULong)-a) {
        return;
    }
    if ((ULong)num[1] < (ULong)-1) {
        return;
    }
    num[0] += a;
    num[1] += 1;
}

/*
 *      pqmul() computes the product mulr * muld mod p where p is of the
 *          form p = 2^64 - a.
 *          The product may be form as the sum of four longword multiplications
 *          which are scaled by powers of  2^32 by evaluating:
 *          2^64 * v * z + 2^32 * (v * y + u * z) + u * y
 *          where u = muld[0]
 *                v = muld[1]
 *                y = mulr[0]
 *                z = mulr[1]
 *          Parameters:
 *              1) long mulr[2] Quadword multiplier
 *              2) long muld[2] Quadword multiplicand
 *              3) long prod[2] Quadword product
 *          Return values:
 *              None
 */

static void pqmul(int32_t mulr[], int32_t muld[], int32_t prod[]) {
    int32_t tmp[2], rs1[2], rs2[2];

    /*
     *  Get 2^32 * v * z.
     */

    emulq(mulr[1], muld[1], tmp);
    pqmod(tmp);
    pqlsh(tmp);
    quadcopy(tmp, rs2);

    /*
     *  Get v * y and add in the above sum.
     */

    emulq(mulr[0], muld[1], tmp);
    pqmod(tmp);
    quadcopy(tmp, rs1);

    /*
     *  Get u * z and add in the above sum. Obtain the first two
     *  items by pqlsh() the sum.
     */

    emulq(mulr[1], muld[0], tmp);
    pqmod(tmp);
    pqadd(tmp, rs1);
    pqadd(rs2, rs1);
    pqlsh(rs1);

    /*
     *  Get u * y and add in the above sum.
     */

    emulq(mulr[0], muld[0], tmp);
    pqmod(tmp);
    pqadd(tmp, rs1);
    quadcopy(rs1, prod);
}

/*
 *      emulq() knows how to multiply two unsigned longwords, producing an
 *          unsigned quadword product.
 *          Parameters:
 *              1) long mulr    Longword multiplier
 *              2) long muld    Longword multiplicand
 *              3) long prod[2] Quadword product
 *          Return values:
 *              None
 */

static void emulq(int32_t mulr, int32_t muld, int32_t prod[]) {
    int32_t compensate = 0;
    int32_t null = 0;

    lib_emul(&mulr, &muld, &null, prod);
    if (mulr < 0) {
        compensate += muld;
    }
    if (muld < 0) {
        compensate += mulr;
    }
    prod[1] += compensate;
}

/*
 *      pqlsh() computes the product 2^32 * u mod p where p is of the
 *          form p = 2^64 - a.
 *          Parameters:
 *              1) long num[2] Quadword to be mod by p
 *          Return values:
 *              None
 */

#define ASH             32

static void pqlsh(int32_t num[]) {
    int32_t tmp[2], mask = 0x80000000;

    emulq(num[1], a, tmp);
    /* num[1] <<= ASH; */
    num[1] = 0;
    num[1] |= (ULong)((mask >>= ASH - 1) & num[0]) >> (32 - ASH);
    /* num[0] <<= ASH; */
    num[0] = 0;
    pqadd(tmp, num);
}

/*
 *      pqadd() computes the sum add + sum mod p where p is of the
 *          form p = 2^64 - a.
 *          Parameters:
 *              1) long add[2] Quadword addend
 *              2) long sum[2] Quadword sum
 *          Return values:
 *              None
 */

static void pqadd(int32_t add[], int32_t sum[]) {
    int c0, c1;

    if ((ULong)sum[0] > (ULong)-1 - (ULong)add[0]) {
        c0 = 1;
    } else {
        c0 = 0;
    }
    sum[0] += add[0];
    if ((ULong)(sum[1] + c0) > (ULong)-1 - (ULong)add[1]) {
        c1 = 1;
    } else {
        c1 = 0;
    }
    sum[1] += add[1] + c0;
    if (!c1 && (ULong)sum[1] < (ULong)-1) {
        return;
    }
    if ((ULong)sum[0] > (ULong)-1 - (ULong)a) {
        c0 = 1;
    } else {
        c0 = 0;
    }
    sum[0] += a;
    sum[1] += c0;
}

static void strtoupper(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

static void usage(void) {
    fprintf(stderr,
            "Usage: pakgen [-p producer] [-i issuer] [-a authorization]\n");
    fprintf(stderr,
            "\t[-u units] [-v availability] [-c activity]\n");
    fprintf(stderr,
            "\t[-A] [-M] [-R] [-N] [-t]\n\n");
    fprintf(stderr, "\t-A : key option ALPHA\n");
    fprintf(stderr, "\t-N : key option NO_SHARE\n");
    fprintf(stderr, "\t-R : key option RESERVE_UNITS\n");
    fprintf(stderr, "\t-M : key option MOD_UNITS\n");
    fprintf(stderr, "\t-t : output lmf file, pipe into lmf with \"lmf -\"\n");
}

int main(int argc, char *argv[]) {
    unsigned char options[8] = {
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    uint32_t epwd[2];
    int salt = 2;
    int c;

    char *product_name = NULL;
    char *issuer = NULL;
    char *authorization = NULL;
    char *producer = NULL;
    char *units = NULL;
    char *availability = NULL;
    char *activity = NULL;

    int tru64 = 0;

    while ((c = getopt(argc, argv, "hi:a:p:u:c:v:AMRNt")) >= 0) {
        switch (c) {
        case 'h':
            usage();
            exit(EXIT_SUCCESS);
            break;

        case 't':
            tru64 = 1;
            break;

        case 'A':
            options[1] |= 0x2;
            break;

        case 'M':
            options[0] |= 0x4;
            break;

        case 'R':
            options[0] |= 0x80;
            break;

        case 'N':
            options[0] |= 0x8;
            break;

        case 'i':
            if (issuer) {
                free(issuer);
            }
            issuer = strdup(optarg);
            strtoupper(issuer);
            break;

        case 'a':
            if (authorization) {
                free(authorization);
            }
            authorization = strdup(optarg);
            strtoupper(authorization);
            break;

        case 'p':
            if (producer) {
                free(producer);
            }
            producer = strdup(optarg);
            strtoupper(producer);
            break;

        case 'u':
            if (units) {
                free(units);
            }
            units = strdup(optarg);
            break;

        case 'v':
            if (availability) {
                free(availability);
            }
            availability = strdup(optarg);
            strtoupper(availability);
            break;

        case 'c':
            if (activity) {
                free(activity);
            }
            activity = strdup(optarg);
            strtoupper(activity);
            break;
        }
    }

    if (optind != (argc - 1)) {
        usage();
        exit(EXIT_FAILURE);
    }

    product_name = argv[optind];
    strtoupper(product_name);

    if (product_name == NULL) {
        usage();
        exit(EXIT_FAILURE);
    }

    /*
      product name,
      issuer,
      authorization,
      producer,
      units,
      availability,
      activity,
      key_options
    */
    calc_checksum(product_name,
                  issuer,
                  authorization,
                  producer,
                  units,
                  availability,
                  activity,
                  options,
                  salt, epwd);

    purdy(epwd, ctable + salt);

    if (!tru64) {
        printf("LICENSE REGISTER %s -\n", product_name);
        if (issuer != NULL) {
            printf("        /ISSUER=%s -\n", issuer);
        }
        if (authorization != NULL) {
            printf("        /AUTHORIZATION=%s -\n", authorization);
        }
        if (producer != NULL) {
            printf("        /PRODUCER=%s -\n", producer);
        }
        if (units != NULL) {
            printf("        /UNITS=%s -\n", units);
        }
        if (availability != NULL) {
            printf("        /AVAILABILITY=%s -\n", availability);
        }
        if (activity != NULL) {
            printf("        /ACTIVITY=%s -\n", activity);
        }
        if ((options[0] != 0) ||
            (options[1] != 0)) {
            int cnt = 0;
            printf("        /OPTIONS=(");
            if (options[0] & 0x4) {
                cnt = 1;
                printf("MOD_UNITS");
            }
            if (options[0] & 0x8) {
                if (cnt) {
                    printf(",");
                } else {
                    cnt = 1;
                }
                printf("NO_SHARE");
            }
            if (options[0] & 0x80) {
                if (cnt) {
                    printf(",");
                } else {
                    cnt = 1;
                }
                printf("RESERVE_UNITS");
            }
            if (options[1] & 0x2) {
                if (cnt) {
                    printf(",");
                } else {
                    cnt = 1;
                }
                printf("ALPHA");
            }

            printf(") -\n");
        }
        printf("        /CHECKSUM=");
        format_pwd(epwd, salt);
    } else {
        printf("%30s: %s\n", "Issuer", (issuer ? issuer : ""));
        printf("%30s: %s\n", "Authorization Number",
               (authorization ? authorization : ""));
        printf("\n");
        printf("%30s: %s\n", "Product Name",
               (product_name ? product_name : ""));
        printf("%30s: %s\n", "Producer", (producer ? producer : ""));
        printf("\n");
        printf("%30s: %s\n", "Number of units", (units ? units : ""));
        printf("%30s: \n", "Version");
        printf("%30s: \n", "Product Release Date");
        printf("\n");
        printf("%30s: \n", "Key Termination Date");
        printf("\n");
        printf("%30s: %s\n", "Availability Table Code",
               (availability ? availability : ""));
        printf("%30s: %s\n", "Activity Table Code",
               (activity ? activity : ""));
        printf("\n");
        printf("%30s: ", "Key Options");
        if ((options[0] != 0) ||
            (options[1] != 0)) {
            int cnt = 0;
            if (options[0] & 0x4) {
                cnt = 1;
                printf("MOD_UNITS");
            }
            if (options[0] & 0x8) {
                if (cnt) {
                    printf(",");
                } else {
                    cnt = 1;
                }
                printf("NO_SHARE");
            }
            if (options[0] & 0x80) {
                if (cnt) {
                    printf(",");
                } else {
                    cnt = 1;
                }
                printf("RESERVE_UNITS");
            }
            if (options[1] & 0x2) {
                if (cnt) {
                    printf(",");
                } else {
                    cnt = 1;
                }
                printf("ALPHA");
            }
        }
        printf("\n");
        printf("%30s: \n", "Product Token");
        printf("%30s: \n", "Hardware-Id");
        printf("%30s: ", "Checksum");
        format_pwd(epwd, salt);
    }

    return 0;
}
