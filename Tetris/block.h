#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
// 这个block类用工厂模式
class AbstractBlock
{
public:
    //左上角坐标
    int x;
    int y;
    int bk[4][4];
    // 这里储存了方块状态
    AbstractBlock()
    {
        int i, j;
        x = 0;
        y = 0;
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++) {
                bk[i][j] = 0;
            } 
        }    
    }
    int move(int dir);
    virtual void rotate();
    // 这个函数是给方块赋形状
    virtual void shape() {}
    void setLocate(int a, int b)
    {
        x = a;
        y = b;
    }
    void getLocate(int *a, int *b)
    {
        *a = x;
        *b = y;
    }
    void showblock();
    // 获取数组首地址
    void *getArray() { return (void *)bk; }
};

//邓锴
class LongBlock : public AbstractBlock
{
public:
    void shape()
    {
        // 0, 0, 0, 0,
        // 1, 1, 1, 1,
        // 0, 0, 0, 0,
        // 0, 0, 0, 0
        bk[1][0] = 1;
        bk[1][1] = 1;
        bk[1][2] = 1;
        bk[1][3] = 1;
    }

    void rotate() {
        if (bk[1][0] == 1) {

            bk[1][0] = 0;
            bk[1][1] = 0;
            bk[1][2] = 0;
            bk[1][3] = 0;

            bk[0][1] = 1;
            bk[1][1] = 1;
            bk[2][1] = 1;
            bk[3][1] = 1;
        }
        else {
            bk[0][1] = 0;
            bk[1][1] = 0;
            bk[2][1] = 0;
            bk[3][1] = 0;

            bk[1][0] = 1;
            bk[1][1] = 1;
            bk[1][2] = 1;
            bk[1][3] = 1;
        }
    }
};

//段先林
class SquareBlock : public AbstractBlock
{
public:
    void shape()
    {
        // 0, 0, 0, 0,
        // 0, 1, 1, 0,
        // 0, 1, 1, 0,
        // 0, 0, 0, 0
        bk[1][1] = 1;
        bk[1][2] = 1;
        bk[2][1] = 1;
        bk[2][2] = 1;
    }
};

//李金岷
class ZBlock : public AbstractBlock
{
public:
    void shape()
    {
        //1,1,0,0
        //0,1,1,0
        //0,0,0,0
        //0,0,0,0
        bk[0][0] = 1;
        bk[0][1] = 1;
        bk[1][1] = 1;
        bk[1][2] = 1;

    }
};

//孟玲
class SBlock : public AbstractBlock
{
public:
    void shape()
    {
        //0,1,1,0
        //1,1,0,0
        //0,0,0,0
        //0,0,0,0
        bk[0][1] = 1;
        bk[0][2] = 1;
        bk[1][0] = 1;
        bk[1][1] = 1;
    }
};

//魏斐洋
class LBlock : public AbstractBlock
{
public:
    void shape()
    {
        //0,0,1,0
        //1,1,1,0
        //0,0,0,0
        //0,0,0,0
        bk[0][2] = 1;
        bk[1][0] = 1;
        bk[1][1] = 1;
        bk[1][2] = 1;
    }
};

//许宏林
class JBlock : public AbstractBlock
{
public:
    void shape()
    {
        //1,0,0,0
        //1,1,1,0
        //0,0,0,0
        //0,0,0,0
        bk[0][0] = 1;
        bk[1][0] = 1;
        bk[1][1] = 1;
        bk[1][2] = 1;

    }
};

//曾葚
class TBlock : public AbstractBlock
{
public:
    void shape()
    {
        //0,1,0,0
        //1,1,1,0
        //0,0,0,0
        //0,0,0,0
        bk[0][1] = 1;
        bk[1][0] = 1;
        bk[1][1] = 1;
        bk[1][2] = 1;
    }
};

// 方块工厂
class BlockFactory
{
public:
    AbstractBlock *block;
    BlockFactory() {
        block=new AbstractBlock;
    }
    BlockFactory(BlockFactory &copyblock) {
        block = new AbstractBlock;
        memcpy(block->bk, copyblock.block->bk, 16 * sizeof(int));
    }
    BlockFactory(std::string blocks)
    {
        if ("LongBlock" == blocks)
        {
            block = new LongBlock;
        }
        else if ("SquareBlock" == blocks)
        {
            block = new SquareBlock;
        }
        else if ("ZBlock" == blocks)
        {
            block = new ZBlock;
        }
        else if ("SBlock" == blocks)
        {
            block = new SBlock;
        }
        else if ("LBlock" == blocks)
        {
            block = new LBlock;
        }
        else if ("JBlock" == blocks)
        {
            block = new JBlock;
        }
        else if ("TBlock" == blocks)
        {
            block = new TBlock;
        }
        else
        {
            block = NULL;
        }
    }
    ~BlockFactory()
    {
        delete block;
    }
    int move(int dir) { return block->move(dir); }
    void rotate() { block->rotate(); }
    void shape() { block->shape(); }
    void setLocate(int a, int b) { block->setLocate(a, b); }
    void getLocate(int *a, int *b) { block->getLocate(a, b); }
    //void getArray() {  block->getArray(); }
    void showblock() { block->showblock(); }
};

#endif

// void test01()
// {
//     BlockFactory *factory = new BlockFactory;
//     AbstractBlock *block = factory->CreateBlock("TBlock");
//     block->shape();
//     delete block;
//     bloc;
//     block = factory->CreateBlock("TBlock");
//     block->shape();
//     delete block;
//     bloc;
//     delete factory;
//     factory = NULL;
// }

// int main()
// {
//     test01();
//     block= 0;
// }这是测试代码
