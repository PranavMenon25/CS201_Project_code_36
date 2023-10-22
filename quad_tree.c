#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct quad_tree q_t;
typedef struct point pt;
struct point{
    float x;
    float y;
};

struct quad_tree{
    struct point val;
    struct quad_tree * n_e;
    struct quad_tree * n_w;
    struct quad_tree * s_e;
    struct quad_tree * s_w;
};

q_t * make_node(float x_c, float y_c){
    q_t * new;
    new = (q_t * ) malloc (sizeof(q_t));
    new->val.x = x_c;
    new->val.y = y_c;
    new->n_e = NULL;
    new->n_w = NULL;
    new->s_e = NULL;
    new->s_w = NULL;
    return new;
}

q_t * insert(q_t * root, float key_x, float key_y){
    if(root == NULL){
       // printf("%f %f", key_x, key_y);
        return (make_node(key_x,key_y));
    }

    else{
        if(root->val.x >= key_x && root->val.y >= key_y){
            root->s_w = insert(root->s_w, key_x, key_y);
        }

        else if(root->val.x <= key_x && root->val.y <= key_y){
            root->n_e = insert(root->n_e, key_x, key_y);
        }

        else if(root->val.x <= key_x && root->val.y >= key_y){
            root->s_e = insert(root->s_e, key_x, key_y);
        }

        else if(root->val.x >= key_x && root->val.y <= key_y){
            root->n_w = insert(root->n_w, key_x, key_y);
        }
    }
}

void search(q_t * root, float key_x, float key_y){
    if(root == NULL){
        printf("Element not found \n");
        return;
    }

    if(root->val.x == key_x && root->val.y == key_y){
        printf("Element has been found \n");
        return;
    }

    else{
        if(root->val.x >= key_x && root->val.y >= key_y){
            search(root->s_w, key_x, key_y);
        }

        else if(root->val.x <= key_x && root->val.y <= key_y){
            search(root->n_e, key_x, key_y);
        }

        else if(root->val.x <= key_x && root->val.y >= key_y){
            search(root->s_e, key_x, key_y);
        }

        else if(root->val.x >= key_x && root->val.y <= key_y){
            search(root->n_w, key_x, key_y);
        }
    }
}

void display(q_t * root){
    if(root == NULL){
        return;
    }

    printf("(%f, %f), ", root->val.x, root->val.y);

    display(root->n_w);
    display(root->s_e);
    display(root->n_e);
    display(root->s_w);
}

bool in_range(pt p1, pt p2, pt p3, pt p4, float key_x, float key_y){
    if(p1.x <= key_x && p1.y >= key_y && p2.x >= key_x && p2.y >= key_y && p3.x >= key_x && p3.y <= key_y && p4.x <= key_x && p4.y <= key_y){
        return true;
    }

    else return false;
}

void display_range(struct point p1, struct point p2, struct point p3, struct point p4, q_t * root){
    if(root == NULL){
        return;
    }

    if(in_range(p1, p2, p3, p4, root->val.x, root->val.y)){
        printf("(%f, %f), ", root->val.x, root->val.y);
    }

    

    display_range(p1, p2, p3, p4,root->n_w);
    display_range(p1, p2, p3, p4, root->s_e);
    display_range(p1, p2, p3, p4, root->n_e);
    display_range(p1, p2, p3, p4, root->s_w);
}

int main(){
    q_t * root = NULL;

    while(1){
        int choice;

        int quit = 0;

        printf("Please enter the operation \n 1. Insert \n 2. Search \n 3. Display \n 4. To display points in a region\n 5. Quit ");

        scanf("%d", &choice);

        switch(choice){
            case 1 : {
                float key_x, key_y;
                printf("Please enter the element you want to insert : \nx_coordinate : ");
                scanf("%f", &key_x);
                printf("y_coordinate : ");
                scanf("%f", &key_y);
                //printf("%f, %f \n", key_x, key_y);
                root = insert(root, key_x, key_y);
                //printf("The x value is : %f %f \n", root->val.x, root->val.y);
                break;
            }

            case 2 : {
                float key_x, key_y;
                printf("Please enter the element you want to search : \nx_coordinate : ");
                scanf("%f", &key_x);
                printf("y_coordinate : ");
                scanf("%f", &key_y);
                search(root, key_x, key_y);
                break;
            }

            case 3 : {
                display(root);
                break;
            }

            case 4 : {
                struct point p1, p2, p3, p4;
                printf("Please enter the points (rectangle) in clockwise order \n");
                printf("Enter the top-left most point \n ");
                printf("x_coordinate : ");
                scanf("%f", &p1.x);
                printf("y_coordinate : ");
                scanf("%f", &p1.y);
                printf("Enter the top-right most point \n");
                printf("x_coordinate : ");
                scanf("%f", &p2.x);
                printf("y_coordinate : ");
                scanf("%f", &p2.y);
                printf("Enter the bottom-right most point \n");
                printf("x_coordinate : ");
                scanf("%f", &p3.x);
                printf("y_coordinate : ");
                scanf("%f", &p3.y);
                printf("Enter the botoom-left most point \n");
                printf("x_coordinate : ");
                scanf("%f", &p4.x);
                printf("y_coordinate : ");
                scanf("%f", &p4.y);

                display_range(p1, p2, p3, p4, root);
                printf("\n");
                break;
            }

            case 5 : {
                quit = 1;
            }
        }

        if(quit == 1){
            break;
        }
    }
}
