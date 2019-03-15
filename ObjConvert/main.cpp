#include "common.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Vertex
{
    float x, y, z;
};
struct Face
{
    int vIndex1, vIndex2, vIndex3, tIndex1, tIndex2, tIndex3, nIndex1, nIndex2, nIndex3;
};

bool ReadFileCounts(const std::string &inputFileName, int &vertexCount, int &textureCount, int &normalCount, int &faceCount);
bool Convert(const std::string &inputFileName, const std::string &outputFileName, int vertexCount, int textureCount, int normalCount, int faceCount);
void usage(const std::string &exeName)
{
    cout << "Usage: " << endl;
    cout << exeName << " inputFileName outputFileName" << endl;
}
std::string getApplicationDir(const std::string &appDir)
{
    const auto pos = appDir.find_last_of('\\');
    return appDir.substr(0, pos + 1);
}
int main(int argc, char **argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    if (argc != 3)
    {
        usage(argv[0]);
        return -1;
    }
    std::string appDir = getApplicationDir(argv[0]);
    bool result;
    string inputFileName = appDir;
    string outputFileName = appDir;
    int vertexCount;
    int textureCount;
    int normalCount;
    int faceCount;
    inputFileName += argv[1];
    outputFileName += argv[2];

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

bool ReadFileCounts(const std::string &inputFileName, int &vertexCount, int &textureCount, int &normalCount, int &faceCount)
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
bool Convert(const std::string &inputFileName, const std::string &outputFileName, int vertexCount, int textureCount, int normalCount, int faceCount)
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
            stringstream ss(line + 2);
            ss >> vertex[vIndex].x >> vertex[vIndex].y >> vertex[vIndex].z;
            cout << "vertex " << vIndex << " : " << vertex[vIndex].x << " " << vertex[vIndex].y << " " << vertex[vIndex].z << endl;
            vertex[vIndex].z = -vertex[vIndex].z;
            vIndex++;
        }
        else if (0 == memcmp(line, "vt ", 3))
        {
            stringstream ss(line + 3);
            ss >> texture[tIndex].x >> texture[tIndex].y;
            cout << "texture " << tIndex << " : " << texture[tIndex].x << " " << texture[tIndex].y << endl;
            texture[tIndex].y = 1.0f - texture[tIndex].y;
            tIndex++;
        }
        else if (0 == memcmp(line, "vn ", 3))
        {
            stringstream ss(line + 3);
            ss >> normal[nIndex].x >> normal[nIndex].y >> normal[nIndex].z;
            cout << "normal " << nIndex << " : " << normal[nIndex].x << " " << normal[nIndex].y << " " << normal[nIndex].z << endl;
            normal[nIndex].z *= -1.0f;
            nIndex++;
        }
        else if (0 == memcmp(line, "f ", 2))
        {
            char ignore;
            stringstream ss(line + 2);
            ss >> face[fIndex].vIndex3 >> ignore >> face[fIndex].tIndex3 >> ignore >> face[fIndex].nIndex3 >> face[fIndex].vIndex2 >> ignore
                >> face[fIndex].tIndex2 >> ignore >> face[fIndex].nIndex2 >> face[fIndex].vIndex1 >> ignore >> face[fIndex].tIndex1 >> ignore
                >> face[fIndex].nIndex1;
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
        fout << vertex[vIndex].x << ' ' << vertex[vIndex].y << ' ' << vertex[vIndex].z << ' ' << texture[tIndex].x << ' ' << texture[tIndex].y << ' '
             << normal[nIndex].x << ' ' << normal[nIndex].y << ' ' << normal[nIndex].z << ' ' << endl;

        vIndex = face[i].vIndex2 - 1;
        tIndex = face[i].tIndex2 - 1;
        nIndex = face[i].nIndex2 - 1;
        fout << vertex[vIndex].x << ' ' << vertex[vIndex].y << ' ' << vertex[vIndex].z << ' ' << texture[tIndex].x << ' ' << texture[tIndex].y << ' '
             << normal[nIndex].x << ' ' << normal[nIndex].y << ' ' << normal[nIndex].z << ' ' << endl;

        vIndex = face[i].vIndex3 - 1;
        tIndex = face[i].tIndex3 - 1;
        nIndex = face[i].nIndex3 - 1;
        fout << vertex[vIndex].x << ' ' << vertex[vIndex].y << ' ' << vertex[vIndex].z << ' ' << texture[tIndex].x << ' ' << texture[tIndex].y << ' '
             << normal[nIndex].x << ' ' << normal[nIndex].y << ' ' << normal[nIndex].z << ' ' << endl;
    }
    fout.close();
    delete[] vertex;
    delete[] texture;
    delete[] normal;
    delete[] face;
    return true;
}
