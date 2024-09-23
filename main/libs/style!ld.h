#ifndef LD_STYLE_H
#define LD_STYLE_H

//mowore arguments
typedef struct {
    char * msg;
    bool newLine;
    i32 repeatTimes, displaceX, displaceY;
    u8 modeId;
} Format;

//Advanced w optional args
u8 FormatText(Format * extraArgs);

//Stand alone (no struct dependency needed)
void CenterText(const char * line);
void RightText(const char * line);
void MidScreenText(const char * line);
void RandText(const char * line);

//Helper function for all of them (we dont need to format text with the \x1b strlen included)
u16 GetStrlenOfANSI(const char * line);

#endif /* LD_STYLE_H */
