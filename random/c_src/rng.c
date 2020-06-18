#include <stdlib.h>
#include <stdint.h>

#if defined(USE_GETRANDOM)
#include <sys/random.h>
#elif defined(USE_ARC4RANDOM)
#elif defined(USE_SECRANDOMCOPYBYTES)
#include <Security/SecRandom.h>
#elif defined(USE_CRYPTGENRANDOM)
#include <windows.h>
#include <Wincrypt.h>
#elif defined(USE_DEV_URANDOM)
#include <stdio.h>
#endif

uint8_t os_random_secrandom(uint8_t *buf, size_t len)
{
#if defined(USE_GETRANDOM)
    return getrandom(buf, len, 0) == -1 ? 1 : 0;
#elif defined(USE_ARC4RANDOM)
    arc4random_buf(buf, len);
    return 0;
#elif defined(USE_SECRANDOMCOPYBYTES)
    return SecRandomCopyBytes(kSecRandomDefault, len, buf) == errSecSuccess ? 0 : 1;
#elif defined(USE_CRYPTGENRANDOM)
    HCRYPTPROV rng;
    if (CryptAcquireContext(&rng, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT) == 0)
        return 1;

    uint8_t ret_val = CryptGenRandom(rng, (DWORD)len, (BYTE *)buf) == 0 ? 1 : 0;
    CryptReleaseContext(rng, 0);
    return ret_val;
#elif defined(USE_DEV_URANDOM)
    FILE *urandom = fopen("/dev/urandom", "r");
    if (urandom == NULL)
        return 1;

    while (len)
    {
        size_t bytes_read = fread(buf, 1, len, urandom);
        if (bytes_read == 0)
        {
            fclose(urandom);
            return 1;
        }

        buf += bytes_read;
        len -= bytes_read;
    }

    fclose(urandom);
    return 0;
#else
#error "No secure random number generator selected"
#endif
}