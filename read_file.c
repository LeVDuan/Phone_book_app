#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"
#include <glib.h>
#include "libfdr/jrb.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

JRB s2i = NULL; //cay chua string -> int
vector_t i2s = NULL;  // vector cac string theo chi so int
int size = 0;
int g_id = 0;
typedef struct 
{
	char name[100];
	char contact[13];
	char sex[10];
	char age[10];
	char address[1000];
    char img[100];
} contact_infor_t;
contact_infor_t list_contact[100];

void get_save_id(char *key) {
	printf("bug\n");					
	jrb_insert_str(s2i, key, (Jval){.i = g_id});
    gtv_setsize(i2s,g_id +1 );	  
	gtv_set_value_with_index(&i2s, (gtype){.s = key}, g_id);
	++g_id;
}
void set_img_by_sex(contact_infor_t *node)
{
    if(strcmp(node->sex,"man") == 0)
    {
        strcpy(node->img, "../man.jpg");
    }
    if(strcmp(node->sex,"woman") == 0)
    {
        strcpy(node->img, "../woman.jpg");
    }
}
void read_data(contact_infor_t * list_contact)
{
    FILE * inp = fopen("../input.txt", "r");

    if(inp == NULL)
        printf("Cannot open file!\n");

    while(!feof(inp)) {
        fscanf(inp, " %[^+\n]", list_contact[(int)size].name);
        get_save_id(list_contact[(int)size].name);
        //printf("%s\n",list_contact[size].name);
        fscanf(inp, "%*[+]");   

        fscanf(inp, " %[^+\n]", list_contact[(int)size].contact);
        //printf("%s\n",list_contact[size].contact);
        fscanf(inp, "%*[+]");

        fscanf(inp, " %[^+\n]", list_contact[(int)size].sex);
        //printf("%s\n",list_contact[size].sex);
        fscanf(inp, "%*[+]");

        fscanf(inp, " %[^+\n]", list_contact[(int)size].age);
        //printf("%s\n",list_contact[(int)size].age);
        fscanf(inp, "%*[+]");

        fscanf(inp, " %[^+\n]", list_contact[(int)size].address);
        //printf("%s\n",list_contact[(int)size].address);
        fscanf(inp, "%*[+]");

        fscanf(inp, " %[^+\n]", list_contact[(int)size].img);

        printf("%s\n",list_contact[(int)size].img);
        if(strcmp(list_contact[(int)size].img,"") == 0 )
        {
            set_img_by_sex(&list_contact[(int)size]);
        }
        fscanf(inp, "%*[+]");

        size ++;
  }
    fclose(inp);
}

void assign_value_list(contact_infor_t *node_1, contact_infor_t *node_2) 
{
    strcpy((*node_1).name, (*node_2).name);
    strcpy((*node_1).contact, (*node_2).contact);
    strcpy((*node_1).sex, (*node_2).sex);
    strcpy((*node_1).age, (*node_2).age);
    strcpy((*node_1).address, (*node_2).address);
    strcpy((*node_1).img, (*node_2).img);
}
void rewrite_input()
{
    FILE *input = fopen("../input.txt","w");
    if(input == NULL)
        printf("Cannot open file!\n");
    for (int i = 0; i < size; ++i)
    {
        fprintf(input, "%s+%s+%s+%s+%s+%s\n",list_contact[i].name,
                                            list_contact[i].name,
                                            list_contact[i].name,
                                            list_contact[i].name,
                                            list_contact[i].name,
                                            list_contact[i].name );
    }
    fclose(input);
}
void delete_contact(int position)
{

    gtv_setsize(i2s, g_id);
    JRB find = jrb_find_str(s2i, list_contact[position].name);
    jrb_delete_node(find);
    for(int i = position ; i < size - 1; i++)
    {
        JRB node = jrb_find_str(s2i, list_contact[i+1].name);
        node->val.i = i;
        assign_value_list(&list_contact[i], &list_contact[i+1]);
        gtv_set_value_with_index(&i2s, i2s[i+1],i);
    }
    g_id --;
    size --;
}

int main() {
  	s2i = make_jrb();
	i2s = gtv_create();

    read_data(list_contact);
    printf("%d\n",size );
    delete_contact(size-1);
    JRB cur1;
    jrb_traverse(cur1, s2i){
        printf("%s %d\n", cur1->key.s, cur1->val.i);
    }
    delete_contact(size -1  );
    JRB cur;
    jrb_traverse(cur, s2i){
        printf("%s %d\n", cur->key.s, cur->val.i);
    }
    //printf("\n%d\n",(int)size );

    //rewrite_input();
	return 0;
}