#ifndef LD_SYS_H
#define LD_SYS_H

//"Encrypt"
char * EncryptedWordsV1(u8 numOfSpaces);
char * EncryptedWordsV2(const char * exampleLine);

//Input Managers
void StrInp(void);
i64 IntInp(void);

//Setting up terminal and calling other functions to start the setup
bool RunThisAtStart(void);

//Exit manager
void ExitEarly(u16 errCode, char * errMsg);

//Better free + mallocs (i only use the malloc to exit with the error message for me)
void SaferFree(void ** pointer);
int * IntMalloc(size_t size);
char * CharMalloc(size_t size);

#endif /* LD_SYS_H */
