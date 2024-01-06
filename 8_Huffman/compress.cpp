#include <iostream>
#include <queue>
#include <stdio.h>
#include "Huffman.hpp"

using namespace std;

struct BitOutputBuffer
{
    char c;
    int cnt;
    FILE *fp;
    BitOutputBuffer(FILE *fp)
    {
        c = 0;
        cnt = 0;
        this->fp = fp;
    }
    void put(bool b)
    {
        c = c | (b << cnt);
        cnt++;
        if (cnt == 8)
        {
            fputc(c, fp);
            c = 0;
            cnt = 0;
        }
    }
    void finalPut()
    {
        fputc(c, fp);
    }
};

class HuffmanCompresser:HuffmanTree
{
public:
    HuffmanCompresser() {}
    void read(FILE *fp)
    {
        int ch;
        while ((ch = fgetc(fp)) != EOF)
        {
            ++this->node[ch].val;
        }
    }
    void compress(FILE *fin, FILE *fout)
    {
        read(fin);
        TreeNode *root = build();
        fseek(fin, 0, SEEK_SET);
        for(int i = 0; i < 256; ++i){
            fwrite(&this->node[i].val, sizeof(int), 1, fout);
        }
        BitOutputBuffer outputBuffer(fout);
        int ch;
        while ((ch = fgetc(fin)) != EOF)
        {
            vector<int> code;
            TreeNode *p = &this->node[ch];
            while (p != root)
            {
                if (p == p->parent->left)
                {
                    code.push_back(0);
                }
                else
                {
                    code.push_back(1);
                }
                p = p->parent;
            }
            for (int i = code.size() - 1; i >= 0; i--)
            {
                outputBuffer.put(code[i]);
            }
            // for(int i = code.size()-1; i >= 0; i--){
            //     cout << code[i];
            // }
            // cout << endl;
        }
        outputBuffer.finalPut();
    }
};

int main(int argc, char* argv[])
{
    if(argc != 3){
        cout << "usage: ./main input output" << endl;
        exit(EXIT_FAILURE);
    }
    HuffmanCompresser h;
    FILE *fin = fopen(argv[1], "rb");
    if (!fin)
    {
        cout << "open in failure" << endl;
        exit(EXIT_FAILURE);
    }
    FILE *fout = fopen(argv[2], "wb");
    if (!fout)
    {
        cout << "open out failure" << endl;
        fclose(fin);
        exit(EXIT_FAILURE);
    }
    h.compress(fin, fout);
    fclose(fin);
    fclose(fout);
}