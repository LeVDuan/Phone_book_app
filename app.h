#ifndef APP_H_
#define APP_H_

#include <gtk/gtk.h>
#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"
#include "libfdr/jrb.h"


#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum{
    COLUMN_NAME,
    NUM_COLUMNS
};


typedef struct 
{
    char name[100];
    char contact[13];
    char sex[10];
    char age[5];
    char address[1000];
    char img[1000];
}contact_infor_t;


typedef struct 
{
    // about dialog pointer
    GtkWidget *w_dlg_about;
    GtkWidget *w_dlg_new_contact;
    GtkWidget *w_dlg_choose_img;
    GtkWidget *w_dlg_help;
    
    // mess and warning pointer
    GtkWidget *w_mess_err_find;     //thông báo lỗi khi tìm không thấy
    GtkWidget *w_wrn_delete;        //Cảnh báo xác nhận xóa
    GtkWidget *w_err_add_contact;   //Dialog để nhập thông tin các trường
    GtkWidget *w_err_delete;        //thông báo lỗi khi hiện không có thông tin hiển thị để xóa
    GtkWidget *w_mess_susscess;     //thông báo thao tác thành công

    // button pointer 
    // các button chức năng chính của app
    GtkWidget *btn_clear_current;
    GtkWidget *btn_new;
    GtkWidget *btn_edit;
    GtkWidget *btn_delete;
    GtkWidget *btn_help;
    GtkWidget *btn_about;


    //các button xác nhận xóa thông tin trong dialog wrn_delete 
    GtkWidget *btn_yes; 
    GtkWidget *btn_no;

    //buttuon đóng thông báo thành công mess_susscess
    GtkWidget *btn_ok;

    //button thêm thông tin của dialog dlg_new_contact
    GtkWidget *btn_add;

    //button thêm ảnh của dialog dlg_new_contact, để hiện cửa sổ chọn ảnh
    GtkWidget *btn_choose_img;
 
    // label pointer 
    // các label hiện thị thông tin cụ thể đang làm việc lên màn hình 
    GtkWidget *lbl_name;
    GtkWidget *lbl_contact;
    GtkWidget *lbl_sex;
    GtkWidget *lbl_age;
    GtkWidget *lbl_address;
    GtkWidget *lbl_title;

    //label để thay dổi nội dung thông báo cùa mess_susscess
    GtkWidget *lbl_mess_susscess;

    //entry pointer
    // các trường nhập dữ liệu của dialog new_contact
    GtkWidget *entry_new_name;
    GtkWidget *entry_new_tel;
    GtkWidget *entry_new_sex;
    GtkWidget *entry_new_age;
    GtkWidget *entry_new_address;
    GtkWidget *entry_avatar_file;
    GtkWidget *w_img_new; //ảnh hiển thị khi người dùng chọn ảnh cho liên hệ mới
    
    // search entry 
    GtkWidget *entry_search;


    //image pointer
    GtkWidget *w_img_avartar;


    // tree view pointer
    GtkWidget *w_tree_view;
    

}app_widgets;



/*===============================các hàm xử lý dữ liệu bên trong=======================*/
void remove_trailing(char *s);
void set_img_by_sex(contact_infor_t *node);
void get_save_id(char *key, JRB s2i,vector_t *i2s, int g_id);
int s2i_value_id(JRB root, char *key);
void read_data(contact_infor_t * list_contact, JRB s2i,vector_t *i2s, int *size);
void assign_value_list(contact_infor_t *node_1, contact_infor_t *node_2);
void delete_contact(int position,
                   contact_infor_t *list_contact, 
                   JRB s2i, 
                   vector_t *i2s, 
                   int *size);
void add_contact(contact_infor_t *new_node_tmp, 
                 JRB s2i, vector_t *i2s, 
                 contact_infor_t *list_contact, 
                 int *size);
void edit_contact(contact_infor_t *new_node_tmp,
                 JRB s2i, vector_t *i2s, 
                 contact_infor_t *list_contact, 
                 int position);
int check_mail(contact_infor_t *node);
void rewrite_input(contact_infor_t *list_contact,int size);




/*=======các hàm lấy dữ liệu từ nguời dùng, đưa các dữ liệu đã xử lý ra màn hìn============*/


contact_infor_t *assign_value_by_entry(contact_infor_t *node_tmp, app_widgets* app_wdgts);
int check_entry(contact_infor_t *node_tmp);
char *text_buffer_get_label(GtkLabel *label);
char *text_buffer_get_entry(GtkEntry *entry);
void add_columns(GtkTreeView *treeview);
GtkTreeModel *create_model(contact_infor_t *list_contact,JRB s2i);
GtkTreeModel *create_completion_model (JRB s2i);
void entry_completion(app_widgets *app_wdgts,JRB s2i);
void show_infor_window(int i, app_widgets *app_wdgts, contact_infor_t * list_contact);
void show_infor_window_default(app_widgets *app_wdgts);
void clean_buff_entry(app_widgets *app_wdgts);
void on_btn_clear_current_clicked(GtkButton *button, app_widgets *app_wdgts);
void on_btn_new_clicked(GtkButton *button, app_widgets *app_wdgts);
void on_btn_delete_clicked(GtkButton *button, app_widgets *app_wdgts);
void on_btn_help_clicked(GtkButton *button, app_widgets* app_wdgts );
void on_btn_about_clicked(GtkButton *button, app_widgets* app_wdgts );
void on_bnt_no_clicked(GtkButton *button, app_widgets *app_wdgts);
void on_btn_ok_clicked(GtkButton *button,app_widgets *app_wdgts);
void on_btn_choose_img_clicked(GtkButton *button,app_widgets *app_wdgts);


#endif // APP_H