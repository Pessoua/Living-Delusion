#ifndef LD_SAVE_PATH_H
#define LD_SAVE_PATH_H

bool ExistDiret(const char * path);
void GetCurPath(path newPath);
void ChangeCurPath(const char * changeToThis);
bool GetNeededPaths(void);

#endif /* LD_SAVE_PATH_*/
