// Implementation of quad tree
#include <stdio.h>
#include <stdlib.h>

// decalaring the struct for a point which has two coordinates
typedef struct Point 
{
    int x;
    int y;
} Point;

typedef struct Node 
{
    Point pos;
    int data;
} Node;

typedef struct Quad 
{
    Point topLeft;
    Point botRight;
    Node* n;
    struct Quad* topLeftTree;
    struct Quad* topRightTree;
    struct Quad* botLeftTree;
    struct Quad* botRightTree;
} Quad;

// function to allocate memory for the new code
Quad* newQuad(Point topLeft, Point botRight) 
{
    Quad* quad = (Quad*)malloc(sizeof(Quad));
    quad->topLeft = topLeft;
    quad->botRight = botRight;
    quad->n = NULL;
    quad->topLeftTree = NULL;
    quad->topRightTree = NULL;
    quad->botLeftTree = NULL;
    quad->botRightTree = NULL;

    return quad;
}

// function to check the boundary point

int inBoundary(Point topLeft, Point botRight, Point p) 
{
    return (p.x >= topLeft.x && 
            p.x <= botRight.x && 
            p.y >= topLeft.y && 
            p.y <= botRight.y);
}

// function to insert in quad tree
void insert(Quad* root, Node* node) 
{
    if (node == NULL)
        return;

    if (!inBoundary(root->topLeft, root->botRight, node->pos))
        return;

    if (abs(root->topLeft.x - root->botRight.x) <= 1 &&
        abs(root->topLeft.y - root->botRight.y) <= 1) 
    {
        if (root->n == NULL)
            root->n = node;
        return;
    }
    int xMid = (root->topLeft.x + root->botRight.x) / 2;
    int yMid = (root->topLeft.y + root->botRight.y) / 2;
    if (node->pos.x <= xMid) 
    {
        if (node->pos.y <= yMid) 
        {
            if (root->topLeftTree == NULL)
                root->topLeftTree = newQuad(root->topLeft, (Point){xMid, yMid});
            insert(root->topLeftTree, node);
        } 
        else 
        {
            if (root->botLeftTree == NULL)
                root->botLeftTree = newQuad((Point){root->topLeft.x, yMid}, (Point){xMid, root->botRight.y});
            insert(root->botLeftTree, node);
        }
    } 
    else 
    {
        if (node->pos.y <= yMid) 
        {
            if (root->topRightTree == NULL)
                root->topRightTree = newQuad((Point){xMid, root->topLeft.y}, (Point){root->botRight.x, yMid});
            insert(root->topRightTree, node);
        }
        else 
        {
            if (root->botRightTree == NULL)
                root->botRightTree = newQuad((Point){xMid, yMid}, root->botRight);
            insert(root->botRightTree, node);
        }
    }
}

// function to Search in quad tree
void search(Quad* root, Point p, char* path) {


    if (root == NULL)
        {   
            printf("Not found.\n");
            return;
        }

    if (root->n != NULL && root->n->pos.x == p.x && root->n->pos.y == p.y) {
        printf("Found node in square with (%d,%d) as topLeft and (%d,%d) as botRight", root->topLeft.x,root->topLeft.y,root->botRight.x,root->botRight.y);
        return;
    }

    int xMid = (root->topLeft.x + root->botRight.x) / 2;
    int yMid = (root->topLeft.y + root->botRight.y) / 2;

    if (p.x <= xMid) 
    {
        if (p.y <= yMid)
            {
               
                printf("Searching in square with (%d,%d) as topleft and (%d,%d) as botright\n",root->topLeft.x,root->topLeft.y,root->botRight.x,root->botRight.y);
                printf("Topleft of (%d,%d):\n",xMid,yMid);
                printf("-------------------------------------------------------------------------------------------------\n");
                search(root->topLeftTree, p, "top left");
            }
        else
        {
            
            printf("Searching in square with (%d,%d) as topleft and (%d,%d) as botright\n",root->topLeft.x,root->topLeft.y,root->botRight.x,root->botRight.y);
            printf("BottomLeft of(%d,%d):\n",xMid,yMid);
            printf("-------------------------------------------------------------------------------------------------\n");
            search(root->botLeftTree, p, "bottom left");
        }
    } 
    else {
        if (p.y <= yMid)
        {
            
             printf("Searching in square with (%d,%d) as topleft and (%d,%d) as botright\n",root->topLeft.x,root->topLeft.y,root->botRight.x,root->botRight.y);
             printf("TopRight of (%d,%d):\n",xMid,yMid);
             printf("-------------------------------------------------------------------------------------------------\n");
             search(root->topRightTree, p, "top right");
        }
        else
            {
                
                 printf("Searching in square with (%d,%d) as topleft and (%d,%d) as botright\n",root->topLeft.x,root->topLeft.y,root->botRight.x,root->botRight.y);
                 printf("BotRight of (%d,%d):\n",xMid,yMid);
                 printf("-------------------------------------------------------------------------------------------------\n");
                 search(root->botRightTree, p, "bottom right");
            }
    }
}

int main()
{
    Point topLeft={0,0};
    Point botRight={16,16};      // Specifying the limit of the quad
    Quad* quad = newQuad(topLeft,botRight);

    int n=1;
    printf("Enter the number of points you want to add:-\n");
    scanf("%d",&n);
    printf("Enter the points you want to add\n");
    while(n--)
    {
        int l,r;
        scanf("%d %d",&l,&r);
        Point pos={l,r};
        Node* node= (Node*)malloc(sizeof(Node));
        node->pos=pos;
        node->data=1;
        insert(quad,node);
    }
    int a,b;
    printf("Enter the point you want to search\n");
    scanf("%d %d",&a,&b);
    Point yo={a,b};
    search(quad,yo,"root");
}