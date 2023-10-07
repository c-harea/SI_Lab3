#include "Signature.h"

static int n, fileLen;

char keyGenus(int* pubKey, int* prvKey) {

	unsigned int p, q, lambda;

    printf("Enter the first prime number: ");
    scanf("%u", &p);

    if (!prime(p)) {
        printf("\nWrong Input, you must enter a prime number\n");
        getchar();
        return 0;
    }

    printf("\nEnter the second prime number: ");
    scanf("%u", &q);

    if (!prime(q)) {
        printf("\nWrong Input, you must enter a prime number\n");
        getchar();
        return 0;
    }

    n = p * q;
    printf("\nThe compute of n is: %u\n", n);

    lambda = lcm(p - 1, q - 1);
    printf("The lambda value is: %u\n", lambda);

    printf("Choose a coprime number(e - private key) < %u: ", lambda);
    scanf("%u", &*(prvKey));

    if (*(prvKey) > lambda) {
        printf("\nWrong Input, you must choose a prime number < %u\n", lambda);
        getchar();
        return 0;
    }

    if (!prime(*(prvKey))) {
        printf("\nWRONG INPUT\n");
        getchar();
        return 0;
    }

    *(pubKey) = modInverse(*(prvKey), lambda);
    printf("The compute of d(public key) is: %u\n", *(pubKey));
}

int* signText(char* fileName, int b) {

    FILE* file = fopen(fileName, "rb");

    fseek(file, 0, SEEK_END);
    fileLen = ftell(file) + 1;
    rewind(file);

    char* fileBuff = (char*)malloc(fileLen);
    fileBuff[fileLen - 1] = '\0';

    fread(fileBuff, 1, fileLen - 1, file);

    fclose(file);

    char* sha256 = SHA256_Main(fileBuff);
    printf("File hash value: \n");
    printf("%s\n", sha256);

	int* signature = (int*)malloc(65 * sizeof(int));

	for (int i = 0; i < 65; i++)
	{
		signature[i] = (int)sha256[i];
	}

	for (int i = 0; i < 65; i++)
	{
		signature[i] = moduloPow(signature[i], b, n);
	}

    free(fileBuff);

	return signature;
}

char verifySignature(char* fileName, int* signature, int b) {

	char* hash = malloc(66);

	for (int i = 0; i < 65; i++)
	{
		signature[i] = moduloPow(signature[i], b, n);
	}

	for (int i = 0; i < 65; i++)
	{
		hash[i] = (char)signature[i];
	}

	hash[65] = '\0';

    printf("\n\nDecrypted hash value: \n");
    printf("%s\n", hash);

    FILE* file = fopen(fileName, "rb");

    char* fileBuff = (char*)malloc(fileLen);
    fileBuff[fileLen - 1] = '\0';
    fread(fileBuff, 1, fileLen - 1, file);
    fclose(file);

    char* sha256 = SHA256_Main(fileBuff);

    printf("\n\Computed file hash value: \n");
    printf("%s\n", sha256);

    for (int i = 0; i < 65; i++)
    {
        if (sha256[i] != hash[i])
        {
            return 0;
        }
    }

    free(hash);
    free(fileBuff);

	return 1;
}

void tamperFile(char* fileName) {

    FILE* file = fopen(fileName, "ab");

    fileLen++;
    fputc('o', file);
    fclose(file);

}