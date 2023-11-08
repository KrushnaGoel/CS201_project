// code for the problem we addressed
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

// decalaring the struct for a point which has two coordinates 
typedef struct Point 
{
    int x;
    int y;
} Point;

typedef struct Node 
{
    Point pos;
    char city[50];         // each node has a city associated to it 
} Node;

typedef struct Quad 
{
    Point NorthWest;
    Point SouthEast;
    Node* n;
    int number;
    char* city;
    struct Quad* NorthWestTree;
    struct Quad* NorthEastTree;
    struct Quad* SouthWestTree;
    struct Quad* SouthEastTree;
} Quad;

// function to allocate memory for the new quad using malloc function
Quad* newQuad(Point NorthWest, Point SouthEast) 
{
    Quad* quad = (Quad*)malloc(sizeof(Quad));
    quad->NorthWest = NorthWest;
    quad->SouthEast = SouthEast;
    quad->n = NULL;
    quad->NorthWestTree = NULL;
    quad->NorthEastTree = NULL;           
    quad->SouthWestTree = NULL;
    quad->SouthEastTree = NULL;
    quad->number=0;
    return quad;
}

// for checking the Boundary point
int inBoundary(Point NorthWest, Point SouthEast, Point p) 
{
    return (p.x >= NorthWest.x && 
            p.x <= SouthEast.x && 
            p.y >= NorthWest.y && 
            p.y <= SouthEast.y);
}

// Insertion in Quad tree 
void insert(Quad* root, Node* node, char* city) 
{
    int xMid = (root->NorthWest.x + root->SouthEast.x) / 2; // calculating mid point 
    int yMid = (root->NorthWest.y + root->SouthEast.y) / 2;

    if (root->NorthWestTree == NULL)
                root->NorthWestTree = newQuad(root->NorthWest, (Point){xMid, yMid});

    if (root->SouthWestTree == NULL)
                root->SouthWestTree = newQuad((Point){root->NorthWest.x, yMid}, (Point){xMid, root->SouthEast.y});

    if (root->NorthEastTree == NULL)
                root->NorthEastTree = newQuad((Point){xMid, root->NorthWest.y}, (Point){root->SouthEast.x, yMid});

    if (node == NULL)
    return;
    if (root->SouthEastTree == NULL)
                root->SouthEastTree = newQuad((Point){xMid, yMid}, root->SouthEast);
    if (!inBoundary(root->NorthWest, root->SouthEast, node->pos))
        return;

    if (abs(root->NorthWest.x - root->SouthEast.x) <= 1 &&
        abs(root->NorthWest.y - root->SouthEast.y) <= 1) 
    {
        if (root->n == NULL)
            root->n = node;
        return;
    }
    root->number++;              // increasing the number of city added 
    root->city=city;             // Storing the city name
    if (node->pos.x <= xMid) 
    {
        if (node->pos.y <= yMid) 
        {
            insert(root->NorthWestTree, node,city);
        } 
        else 
        {
            
            insert(root->SouthWestTree, node,city);
        }
    } 
    else 
    {
        if (node->pos.y <= yMid) 
        {
            
            insert(root->NorthEastTree, node,city);
        }
        else 
        {
    
            insert(root->SouthEastTree, node,city);
        }
    }
}

// Search function
void search(Quad* root, Point p, char* path) 
{
   
   if(root->number==1)                  // if the number of city in that quad is one simply output that
   printf("%s",root->city);             // otherwise go further

   else
   {
    
    int xMid = (root->NorthWest.x + root->SouthEast.x) / 2;
    int yMid = (root->NorthWest.y + root->SouthEast.y) / 2;

    if (p.x <= xMid) 
    {
        if (p.y <= yMid)
            {
               
                
                 if(root->NorthWestTree->number==0)
                 printf("%s",root->city);
                 else
                 search(root->NorthWestTree, p, "top left");
            }
        else
        {
            
           
            if(root->SouthWestTree->number==0)
            printf("%s",root->city);
            else
            search(root->SouthWestTree, p, "bottom left");
        }
    } 
    else {
        if (p.y <= yMid)
        {
            
            
             if(root->NorthEastTree->number==0)
            printf("%s",root->city);
             else
                 search(root->NorthEastTree, p, "top right");
        }
        else
            {
                
                
                 if(root->SouthEastTree->number==0)
                 printf("%s",root->city);
                 else
                 search(root->SouthEastTree, p, "bottom right");
            }
    }
   }
}

// Main function+
int main()

{
    Point NorthWest={0,0};     // Specifying the limit of the quad
    Point SouthEast={128,128};      
    Quad* quad = newQuad(NorthWest,SouthEast);
    int n=1;

    printf("Enter the number of points you want to add:- ");
    scanf("%d",&n);
    while(n--)
    {
        int l,r;
        scanf("%d %d",&l,&r);
        char* name;
        Point pos={l,r};
        Node* node= (Node*)malloc(sizeof(Node));
        node->pos=pos;
    
        scanf("%s",node->city);
        insert(quad,node,node->city);
    }
    
    while(1){
        printf("Enter 1 for Search\n");
        printf("Enter 0 for Exit\n");
        int f;
        scanf("%d",&f);
        if(f==1){
              int a,b;
              printf("Enter the co ordinates you want the nearest city to : ");
              scanf("%d %d", &a,&b);
              Point p = {a,b};
              search(quad,p,"root");

              printf("\n");
        }
        else
        break;
    }
    
}