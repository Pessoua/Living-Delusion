#ifndef LD_SYS_H
#define LD_SYS_H

//"Encrypt"
char * EncryptedWordsV1(u8 * numOfSpaces);
char * EncryptedWordsV2(const char * exampleLine);

//Input Managers
void StrInp(void);
i64 IntInp(void);

//Setting up terminal and calling other functions to start the setup
bool RunThisAtStart(void);

#endif /* LD_SYS_H */
