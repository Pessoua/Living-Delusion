#ifndef LD_ART_ASCII_H
#define LD_ART_ASCII_H

/*
 * Notes for Art:
 *
 * We do have a struct for extra optional arguments
 * pallet is to define a new pallet, the standart pallet is just 0 - 16 ANSI values (uchar color)
 * displacementX and displacementY should be self-explanatory
 * filter is just hardcoded pallets like "grayscale" and stuff
 */

typedef struct {
    u8 pallet [17];
    u32 displacementX, displacementY;
    char filter [15];
} ArtOptions;

u32 Art(const char * callerTopic, u8 typeWanted, ArtOptions * ArtModifiers);

#endif /* LD_ART_ASCII_H */
