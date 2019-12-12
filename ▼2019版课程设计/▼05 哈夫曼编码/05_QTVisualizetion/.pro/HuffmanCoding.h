#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<iomanip>
#include<QMessageBox>
#include<QString>
using std::string;

struct HufNode
{//树的结点
    unsigned char val;
    int fre;
    int parent, lchild, rchild;
};

struct HufCode
{//编码元素（叶节点）
    unsigned char val;
    int fre;
    unsigned char code[128];
};

class HuffmanCoding
{
private:
    int n;//编码元素（叶节点）个数
    HufNode* huftree_;//哈夫曼树
    HufCode* hufcode_;//编码元素集合
    string sourcefile_;//待编码文本名
    string targetfile_;
public:
    HuffmanCoding(string sourcefile, string targetfile_);
    ~HuffmanCoding();
    void ReadSource();//统计
    void CreateHufTree();//建树
    void Encoding();//字符编码
    void WriteCodeTxt();//字符编码文本
    void WriteSourceCodeTxt();//文档编码文本
    int  WriteSourceCodeDat();//文档编码二进制文本
    void DecodeTargetCodeTxt(int left);//解码后编码文本
    void DecodeTargetTxt();//解码后文本
};
#endif // HUFFMANCODING_H
