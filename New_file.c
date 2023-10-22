#include<stdio.h>
#include<stdlib.h>

typedef struct quad_tree q_t;

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

int main(){
    q_t * root = NULL;

    while(1){
        int choice;

        int quit = 0;

        printf("Please enter the operation \n 1. Insert \n 2. Search \n 3. Display \n 4. Quit ");

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
                quit = 1;
            }
        }

        if(quit == 1){
            break;
        }
    }
}
