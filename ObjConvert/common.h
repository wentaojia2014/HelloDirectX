#pragma once
#include <cstring>
#include <cstdlib>
const int LINEMAX = 512;
void parseLine(const char *line, float *nums, int numsSize, int &numsCount) {
    numsCount = 0;
    int len = strlen(line);
    char copy[LINEMAX] = {0};
    strcpy(copy, line);
    char *p = strtok(copy, " ");
    while (p)
    {
        nums[numsCount] = atof(p);
        numsCount++;
        if (numsCount == numsSize)
        {
            break;
        }
        p = strtok(nullptr, " ");
    }
}
void parseLine2 (const char *line, float datas[], int dataSize = 9)
{
    int len = strlen(line);
    char copy[LINEMAX] = { 0 };
    char copy2[LINEMAX] = { 0 };
    char buf1[LINEMAX];
    char buf2[LINEMAX];
    memcpy(copy, line, len);
    char *p = strtok_s(copy, " ", (char **)&buf1);
    int index = 0;
    while (p)
    {
        memcpy(copy2, p, strlen(p));
        char *p2 = strtok_s(copy2, "/", (char **)&buf2);
        while (p2)
        {
            datas[index++] = atoi(p2);
            p2 = strtok_s(nullptr, "/", (char **)&buf2);
        }
        p = strtok_s(nullptr, " ", (char **)&buf1);
    }
}