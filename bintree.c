#include <stdio.h>
#include <malloc.h>

//FOR_QUEUE
#define SeqQueueMaxSize 1000

//FOR_BINTREE
typedef char TreeNodeType;

typedef struct TreeNode{
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    TreeNodeType data;
} TreeNode;

typedef TreeNode*  SeqQueueType;

typedef struct SeqQueue{
    SeqQueueType data[SeqQueueMaxSize];
    size_t head;//队首元素的下标
    size_t tail;//队尾元素的下标
    size_t size;//顺序表的长度
} SeqQueue;


////////////////////////////////////////////////////////////////
//以下是队列的功能函数
///////////////////////////////////////////////////////////////

//初始化
void SeqQueueInit(SeqQueue* q)
{
    if(q==NULL)
    {
        return;
    }
    q->size=0;
    q->head=0;
    q->tail=0;
    return;
}

//销毁
void SeqQueueDestroy(SeqQueue* q)
{
    if(q==NULL)
    {
        return;
    }
    q->size=0;
    q->head=0;
    q->tail=0;
    return;
}

//入队列(尾插)
void SeqQueuePush(SeqQueue* q,SeqQueueType value)
{
    if(q==NULL)
    {
        return;
    }
    if(q->size>=SeqQueueMaxSize)
    {//满了
        return;
    }
    q->data[q->tail++]=value;
    //加完元素之后，需要再次判断顺序表的长度是否满了
    if(q->tail>=SeqQueueMaxSize)
    {
        q->tail=0;
    }
    //此时入栈一个元素后，需要更新size
    ++q->size;
    return;
}

//出队列（头删）
void SeqQueuePop(SeqQueue* q)
{
    if(q==NULL)
    {
        return;
    }
    if(q->size==0)
    {
        return;
    }
    //出队列：删队首元素，头删
    ++q->head;
    if(q->head>=SeqQueueMaxSize)
    {
        q->head=0;
    }
    --q->size;
    return;
}

//取队首元素
int SeqQueueFront(SeqQueue* q,SeqQueueType* value)
{
    if(q==NULL||value==NULL)
    {
        return 0;
    }
    if(q->size==0)
    {
        return 0;
    }
    *value=q->data[q->head];
    return 1;
}


/////////////////////////////////////////////////////////////////
//以下是二叉树的操作
////////////////////////////////////////////////////////////////

void TreeInit(TreeNode** proot)
{
    if(proot==NULL)
    {
        //非法输入
        return;
    }
    *proot=NULL;//空树
    return;
}

//先序遍历
void TreePreOrder(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        printf("#");
        return;
    }
    //先访问根节点
    printf("%c",root->data);
    //再遍历左子树
    TreePreOrder(root->lchild);
    //最后遍历右子树
    TreePreOrder(root->rchild);
    return;
}

//中序遍历
void TreeInOrder(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return;
    }
    //先左子树
    TreeInOrder(root->lchild);
    //再打印根节点
    printf("%c ",root->data);
    //最后右子树
    TreeInOrder(root->rchild);
    return;
}

//后序遍历
void TreePostOrder(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return;
    }
    //先左子树
    TreePostOrder(root->lchild);
    //最后右子树
    TreePostOrder(root->rchild);
    //再打印根节点
    printf("%c ",root->data);
    return;
}

//层序遍历
void TreeLevelOrder(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return;
    }
    SeqQueue q;
    SeqQueueInit(&q);
    //循环取队首元素、打印、出队列、再把左、右子节点依次入队列
    //根节点入队列
    SeqQueuePush(&q,root);
    while(1)
    {
        SeqQueueType front;
        int ret=SeqQueueFront(&q,&front);
        if(ret==0)
        {
            break;
        }
        //打印队首元素
        printf("%c ",front->data);
        //出队列
        SeqQueuePop(&q);
        if(front->lchild!=NULL)
        {
            //左子树入队列
             SeqQueuePush(&q,front->lchild);
        }
        if(front->rchild!=NULL)
        {
            //右子树入队列
             SeqQueuePush(&q,front->rchild);
        }
    }
    printf("\n");
    return;
}

TreeNode* CreateNode(TreeNodeType  value);
//创建一个树的递归辅助函数
TreeNode* _TreeCreate(TreeNodeType data[],size_t size,size_t* index,char null_node)
{
    if(index==NULL)
    {
        //非法输入
        return NULL;
    }
    if(*index>=size)
    {
        //数组遍历完成
        return NULL;
    }
    if(data[*index]==null_node)
    {
        //遇到空节点了
        return NULL;
    }
    TreeNode* new_node=CreateNode(data[*index]);
    ++(*index);//取下一个节点
    new_node->lchild=_TreeCreate(data,size,index,null_node);
    ++(*index);
    new_node->rchild=_TreeCreate(data,size,index,null_node);
    return new_node;
}

//创建一棵树
TreeNode* TreeCreate(TreeNodeType data[],size_t size,char null_node)
{
    //index表示当前取数组的哪个元素
    size_t index=0;
    return _TreeCreate(data,size,&index,null_node);
}

//树的拷贝
TreeNode* TreeClone(TreeNode* root)
{
    if(root==NULL)
    {
        return NULL;
    }
    //按照先序来拷贝
    TreeNode* new_node=CreateNode(root->data);
    new_node->lchild=TreeClone(root->lchild);
    new_node->rchild=TreeClone(root->rchild);
    return new_node;
}
void DestroyNode(TreeNode* root);
//销毁树
void DestroyTree(TreeNode* root)
{
    if(root==NULL)
    {
        return ;
    }
    //按照后序遍历来销毁 左右根
    DestroyTree(root->lchild);
    DestroyTree(root->rchild);
    DestroyNode(root);
    return;
}

//二叉树中节点个数
//方法一

void _TreeSize(TreeNode* root,size_t* size)
{
    if(root==NULL)
    {
        return ;
    }
    ++(*size);
    _TreeSize(root->lchild,size);
    _TreeSize(root->rchild,size);
}

int TreeSize(TreeNode* root)
{
    size_t size=0;
    _TreeSize(root,&size);
    return size;
}

//方法二
size_t TreeSize2(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    return 1+TreeSize2(root->lchild)+TreeSize2(root->rchild);
}

//求二叉树中叶子节点的个数
//方法一

void _TreeLeafSize(TreeNode* root,size_t* size)
{
    if(root==NULL)
    {
        return ;
    }
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        ++(*size);
    }
    _TreeLeafSize(root->lchild,size);
    _TreeLeafSize(root->rchild,size);
}
size_t TreeLeafSize(TreeNode* root)
{
    size_t size=0;
    _TreeLeafSize(root,&size);
    return size;

}

//方法二
size_t TreeLeafSize2(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        return 1;
    }
    return TreeLeafSize2(root->lchild)+TreeLeafSize2(root->rchild);
}

//求出二叉树第K层节点的个数
size_t TreeKLevelSize(TreeNode* root,int k)
{
    if(root==NULL)
    {
        return 0;
    }
    if(k==1)
    {
        return 1;
    }
    return TreeKLevelSize(root->lchild,k-1)+TreeKLevelSize(root->rchild,k-1);
}

//求出二叉树的高度，也就是深度
size_t TreeHeight(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        return 1;
    }

    size_t lheight=TreeHeight(root->lchild);
    size_t rheight=TreeHeight(root->rchild);
    return 1+(lheight>rheight?lheight:rheight);
}

//给定值，在二叉树中找到相应的节点
TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find)
{
    //遍历
    //访问操作：比较
    if(root==NULL)
    {
        return NULL;
    }
    if(root->data==to_find)
    {
        return root;
    }
    TreeNode* lresult=TreeFind(root->lchild,to_find);
    TreeNode* rresult=TreeFind(root->rchild,to_find);
    return lresult !=NULL ? lresult:rresult;
}

//求出child 节点的父节点
TreeNode* Parent(TreeNode* root,TreeNode* child)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->lchild==child||root->rchild==child)
    {
        return root;
    }
    TreeNode* lresult=Parent(root->lchild,child);
    TreeNode* rresult=Parent(root->rchild,child);
    return lresult !=NULL ? lresult:rresult;
}

//求出当前节点的左子树和右子树
TreeNode* LChild(TreeNode* root)
{
    if(root==NULL)
    {
        return NULL;
    }
    return root->lchild;
}
TreeNode* RChild(TreeNode* root)
{
    if(root==NULL)
    {
        return NULL;
    }
    return root->rchild;
}

//////////////////////////////////////////////////////////////
//测试函数
/////////////////////////////////////////////////////////////

TreeNode* CreateNode(TreeNodeType value)
{
    TreeNode* new_node=(TreeNode* )malloc(sizeof(TreeNode));
    new_node->data=value;
    new_node->lchild=NULL;
    new_node->rchild=NULL;
    return new_node;
    return new_node;
}

//销毁节点
void DestroyNode(TreeNode* root)
{
    root=NULL;
    free(root);
}

void TestInit()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    printf("root理论值为NULL，实际为 %p\n",root);
}

void TestPreOrder()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a=CreateNode('a');
    TreeNode* b=CreateNode('b');
    TreeNode* c=CreateNode('c');
    TreeNode* d=CreateNode('d');
    TreeNode* e=CreateNode('e');
    TreeNode* f=CreateNode('f');
    TreeNode* g=CreateNode('g');
    root=a;
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    c->rchild=f;
    e->lchild=g;

    TreePreOrder(root);
    printf("\n");
}

void TestInOrder()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a=CreateNode('a');
    TreeNode* b=CreateNode('b');
    TreeNode* c=CreateNode('c');
    TreeNode* d=CreateNode('d');
    TreeNode* e=CreateNode('e');
    TreeNode* f=CreateNode('f');
    TreeNode* g=CreateNode('g');
    root=a;
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    c->rchild=f;
    e->lchild=g;

    TreeInOrder(root);
    printf("\n");
}

void TestPostOrder()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a=CreateNode('a');
    TreeNode* b=CreateNode('b');
    TreeNode* c=CreateNode('c');
    TreeNode* d=CreateNode('d');
    TreeNode* e=CreateNode('e');
    TreeNode* f=CreateNode('f');
    TreeNode* g=CreateNode('g');
    root=a;
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    c->rchild=f;
    e->lchild=g;

    TreePostOrder(root);
    printf("\n");
}

void TestLevelOrder()
{
    printf("================= %s ==============\n",__FUNCTION__);
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a=CreateNode('a');
    TreeNode* b=CreateNode('b');
    TreeNode* c=CreateNode('c');
    TreeNode* d=CreateNode('d');
    TreeNode* e=CreateNode('e');
    TreeNode* f=CreateNode('f');
    TreeNode* g=CreateNode('g');
    root=a;
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    c->rchild=f;
    e->lchild=g;

    TreeLevelOrder(a);
}

void TestCreateTree()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
}

void TestClone()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    TreeNode* new_root=TreeClone(node);
    TreePreOrder(new_root);
    printf("\n");
}

void TestSize()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    size_t len1=TreeSize(node);
    size_t len2=TreeSize2(node);
    printf("len1= %lu,len2=%lu \n",len1,len2);
}
void TestLeafSize()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    size_t leaf1=TreeLeafSize(node);
    size_t leaf2=TreeLeafSize2(node);
    printf("leaf1= %lu,leaf2=%lu \n",leaf1,leaf2);
}

void TestKLevel()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    size_t klen=TreeKLevelSize(node,2);
    printf("klen = %lu \n",klen);
}

void TestHeight()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    size_t kh=TreeHeight(node);
    printf("kh = %lu \n",kh);
}

void TestFind()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    TreeNodeType to_find='a';
    TreeNode* find=TreeFind(node,to_find);
    printf("find = %p\n",find);
    printf("find.data = %c\n",find->data);
}

void TestParent()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    TreeNode* parent=Parent(node,node->lchild->rchild);
    printf("parent= %c\n",parent->data);

}

void LRChild()
{
    printf("============ %s ==============\n",__FUNCTION__);
    TreeNodeType data[]="abd##eg###c#f##"; 
    char null_node='#';
    size_t size=sizeof(data)/sizeof(data[0])-1;
    TreeNode* node=TreeCreate(data,size,null_node);
    TreePreOrder(node);
    printf("\n");
    TreeNode* lc=LChild(node->lchild);
    TreeNode* rc=RChild(node->rchild);
    printf("lc=%p ,rc=%p\n",lc,rc);

}

int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    TestCreateTree();
    TestClone();
    TestSize();
    TestLeafSize();
    TestKLevel();
    TestHeight();
    TestHeight();
    TestFind();
    TestParent();
    LRChild();
}
