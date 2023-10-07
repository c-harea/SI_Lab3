#include "RsaUtil.h"
#include "Sha256.h"
#include "Signature.h"

int main()
{
    int pub, prv;
    char tamper = 'n';

    printf("Key Generation:\n\n");

    if (!keyGenus(&pub, &prv))
    {
        return 0;
    }

    int* fileSignature = signText("dummy.txt", prv);

    printf("\nFile Signature: \n");

    for (int i = 0; i < 65; i++)
    {
        printf("%d", fileSignature[i]);
    }

    if (tamper == 'y')
    {
        tamperFile("dummy.txt");
    }

    if (verifySignature("dummy.txt", fileSignature, pub))
    {
        printf("\nSignature was checked successfuly!");
    }
    else
    {
        printf("\nSignature didn't pass!");
    }

    return 0;
}