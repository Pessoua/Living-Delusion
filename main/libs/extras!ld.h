#ifndef LD_EXTRAS_H
#define LD_EXTRAS_H

/*
 * This struct is used to "relay" the return values of the functions
 *
 * errorType is if theres any errors
 * returnType is to specify the return type so the caller does not need to go through everything
 * and we also have pretty much a data type for every return
 * struct extrasReturn * in case we call extras inside of extras lol
 */

//What a mess lol
typedef struct {
   u16 errorType, returnType;
   char * returnStr;                        //type 0
   i64 returnInt;                           //type 1
   bool returnBool;                         //type 2
   f18 returnDouble;                        //type 3
   path returnPath;                         //type 4
   clock_t returnClock;                     //type 5
   struct extrasReturn * returnPointer;     //type 6

} extrasReturn;

extrasReturn * extras(const char * watCommand);

//Functions that return a struct need their own functions to return the pointer

#endif /* LD_EXTRAS_H */
