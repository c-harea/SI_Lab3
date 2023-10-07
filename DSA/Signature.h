#ifndef SIGNATURE
#define SIGNATURE

#include "RsaUtil.h"
#include "Sha256.h"
#include <stdio.h>
#include <stdlib.h>

extern char keyGenus(int* pubKey, int* prvKey);
extern int* signText(char* a, int prvKey);
extern char verifySignature(char* fileName, int* signature, int pubKey);
extern void tamperFile(char* fileName);

#endif // !SIGNATURE
