#include "common.h"

#include <fstream>
#include <iostream>
using namespace std;
struct Vector3
{
    float x, y, z;
};
union Vertex {
    Vector3 v;
    float data[3];
};
union Face {
    int vIndex1, vIndex2, vIndex3, tIndex1, tIndex2, tIndex3, nIndex1, nIndex2, nIndex3;
    int data[9];
};

bool ReadFileCounts(const char *inputFileName, int &vertexCount, int &textureCount, int &normalCount, int &faceCount);
bool Convert(const char *inputFileName, const char *outputFileName, int vertexCount, int textureCount, int normalCount, int faceCount);
void usage(char *exeName)
{
    cout << "Usage: " << endl;
    cout << exeName << " inputFileName outputFileName" << endl;
}
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        usage(argv[0]);
        return -1;
    }

    bool result;
    char inputFileName[LINEMAX];
    char outputFileName[LINEMAX];
    int vertexCount;
    int textureCount;
    int normalCount;
    int faceCount;
    char garbage;
    strcpy(inputFileName, argv[1]);
    strcpy(outputFileName, argv[2]);

    result = ReadFileCounts(inputFileName, vertexCount, textureCount, normalCount, faceCount);
    if (!result)
    {
        return -1;
    }
    cout << endl;
    cout << "Vertex:" << vertexCount << endl;
    cout << "Texture:" << textureCount << endl;
    cout << "Normal:" << normalCount << endl;
    cout << "Face:" << faceCount << endl;
    result = Convert(inputFileName, outputFileName, vertexCount, textureCount, normalCount, faceCount);
    if (!result)
    {
        return -1;
    }
    cout << "File has been converted" << endl;
    return 0;
}

bool ReadFileCounts(const char *inputFileName, int &vertexCount, int &textureCount, int &normalCount, int &faceCount)
{
    ifstream fin;
    char line[LINEMAX];

    vertexCount = 0;
    textureCount = 0;
    normalCount = 0;
    faceCount = 0;
    fin.open(inputFileName);
    if (fin.fail())
    {
        cout << "open file failed " << inputFileName << endl;
        return false;
    }

    while (!fin.eof())
    {
        fin.getline(line, LINEMAX);
        if (0 == memcmp(line, "v ", 2))
        {
            vertexCount++;
        }
        else if (0 == memcmp(line, "vt", 2))
        {
            textureCount++;
        }
        else if (0 == memcmp(line, "vn", 2))
        {
            normalCount++;
        }
        else if (0 == memcmp(line, "f ", 2))
        {
            faceCount++;
        }
    }
    fin.close();
    return true;
}
bool Convert(const char *inputFileName, const char *outputFileName, int vertexCount, int textureCount, int normalCount, int faceCount)
{
    Vertex *vertex = new Vertex[vertexCount];
    Vertex *texture = new Vertex[textureCount];
    Vertex *normal = new Vertex[normalCount];
    Face *face = new Face[faceCount];
    int vIndex = 0;
    int tIndex = 0;
    int nIndex = 0;
    int fIndex = 0;
    char line[LINEMAX];
    const int numSize = 3;
    float nums[numSize];
    const int indexSize = 9;
    float indexs[indexSize];
    int numCount;
    ifstream fin;

    fin.open(inputFileName);

    if (fin.fail())
    {
        cout << "open file failed " << inputFileName << endl;
        return false;
    }
    while (!fin.eof())
    {
        fin.getline(line, LINEMAX);
        if (0 == memcmp(line, "v ", 2))
        {
            parseLine(line + 2, nums, numSize, numCount);
            if (numCount == 3)
            {
                for (int i = 0; i < numCount; ++i)
                {
                    vertex[vIndex].data[i] = nums[i];
                }
                vertex[vIndex].v.z *= -1.0f;
                vIndex++;
            }
            else
            {
                cout << "error " << __FUNCTION__ << " " << __LINE__ << endl;
            }
        }
        else if (0 == memcmp(line, "vt ", 3))
        {
            parseLine(line + 3, nums, numSize, numCount);
            if (numCount == 2)
            {
                for (int i = 0; i < numCount; ++i)
                {
                    texture[tIndex].data[i] = nums[i];
                }
                texture[tIndex].v.y = 1.0f - texture[tIndex].v.y;
                tIndex++;
            }
            else
            {
                cout << "error " << __FUNCTION__ << " " << __LINE__ << endl;
            }
        }
        else if (0 == memcmp(line, "vn ", 3))
        {
            parseLine(line + 3, nums, numSize, numCount);
            if (numCount == 3)
            {
                for (int i = 0; i < numCount; ++i)
                {
                    normal[nIndex].data[i] = nums[i];
                }
                normal[nIndex].v.z *= -1.0f;
                nIndex++;
            }
            else
            {
                cout << "error " << __FUNCTION__ << " " << __LINE__ << endl;
            }
        }
        else if (0 == memcmp(line, "f ", 2))
        {
            parseLine2(line + 2, indexs);
            int reverse[] = { 2, 0, -2 };
            int reverseIndex = 0;
            for (int i = 0; i < indexSize; ++i)
            {
                face[fIndex].data[i] = indexs[i + reverse[reverseIndex]];
                reverseIndex = (reverseIndex + 1) % 3;
            }
            fIndex++;
        }
    }
    ofstream fout;
    fout.open(outputFileName);
    if (fout.fail())
    {
        cout << "open file failed " << outputFileName << endl;
        return false;
    }
    fout << "Vertex Count:" << (faceCount * 3) << endl;
    fout << endl;
    fout << "Data:" << endl;
    fout << endl;
    for (int i = 0; i < fIndex; ++i)
    {
        vIndex = face[i].vIndex1 - 1;
        tIndex = face[i].tIndex1 - 1;
        nIndex = face[i].nIndex1 - 1;
        fout << vertex[vIndex].v.x << ' ' << vertex[vIndex].v.y << ' ' << vertex[vIndex].v.z << ' ' << texture[tIndex].v.x << ' ' << texture[tIndex].v.y << ' '
             << normal[nIndex].v.x << ' ' << normal[nIndex].v.y << ' ' << normal[nIndex].v.z << ' ' << endl;

        vIndex = face[i].vIndex2 - 1;
        tIndex = face[i].tIndex2 - 1;
        nIndex = face[i].nIndex2 - 1;
        fout << vertex[vIndex].v.x << ' ' << vertex[vIndex].v.y << ' ' << vertex[vIndex].v.z << ' ' << texture[tIndex].v.x << ' ' << texture[tIndex].v.y << ' '
             << normal[nIndex].v.x << ' ' << normal[nIndex].v.y << ' ' << normal[nIndex].v.z << ' ' << endl;

        vIndex = face[i].vIndex3 - 1;
        tIndex = face[i].tIndex3 - 1;
        nIndex = face[i].nIndex3 - 1;
        fout << vertex[vIndex].v.x << ' ' << vertex[vIndex].v.y << ' ' << vertex[vIndex].v.z << ' ' << texture[tIndex].v.x << ' ' << texture[tIndex].v.y << ' '
             << normal[nIndex].v.x << ' ' << normal[nIndex].v.y << ' ' << normal[nIndex].v.z << ' ' << endl;
    }
    fout.close();
    delete[] vertex;
    delete[] texture;
    delete[] normal;
    delete[] face;
    return true;
}
