#include <gtk/gtk.h>
#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"
#include "app.h"
#include "libfdr/jrb.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000 // giới hạn lưu trữ của danh sách

JRB s2i = NULL; // cây rb với mỗi node có key là tên, value là id tương ứng
vector_t i2s = NULL;  // vector chứa các tên định dạng string và chỉ số vector là id tương ứng
contact_infor_t list_contact[MAX_LEN]; // Danh sách lưu dữ liệu đọc từ file
int size = 0; // biến đếm chiều dài danh sách thông tin

contact_infor_t *get_and_check_data_entry(GtkButton *button, 
                                          app_widgets *app_wdgts, 
                                          char *name_current);
void on_btn_add_clicked(GtkButton *button, app_widgets *app_wdgts);
void on_btn_edit_clicked(GtkButton *button, app_widgets *app_wdgts);
void on_entry_search_activate(GtkEntry *entry_search, app_widgets *app_wdgts);
void on_btn_yes_clicked(GtkButton *button,app_widgets *app_wdgts );
void on_tree_view_row_activated(GtkTreeView *tree_view,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column, 
                                app_widgets *app_wdgts);



int main(int argc, char *argv[])
{
    s2i = make_jrb();
    i2s = gtv_create();

    read_data(list_contact,s2i,&i2s, &size);
    
    GtkBuilder      *builder;
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../window_main.glade", NULL);


    /*====xây dựng đồ họa cho chương trình====*/
    //cửa sổ chính của chương trình
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    //hiển thị dữ liệu bằng tree view
    widgets->w_tree_view = GTK_WIDGET(gtk_builder_get_object(builder, "tree_view"));
    gtk_tree_view_set_model(GTK_TREE_VIEW(widgets->w_tree_view), 
                            GTK_TREE_MODEL(create_model(list_contact,s2i)));
    add_columns(GTK_TREE_VIEW(widgets->w_tree_view));

    //các dialog con
    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_about"));
    widgets->w_dlg_new_contact = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_new_contact"));
    
    widgets->w_mess_err_find = GTK_WIDGET(gtk_builder_get_object(builder, "mess_err_find"));
    widgets->w_wrn_delete= GTK_WIDGET(gtk_builder_get_object(builder, "wrn_delete"));
    widgets->w_err_add_contact= GTK_WIDGET(gtk_builder_get_object(builder, "err_add_contact"));
    widgets->w_err_delete= GTK_WIDGET(gtk_builder_get_object(builder, "err_delete"));
    widgets->w_mess_susscess= GTK_WIDGET(gtk_builder_get_object(builder, "mess_susscess"));
    widgets->w_dlg_choose_img= GTK_WIDGET(gtk_builder_get_object(builder, "dlg_choose_img"));
    widgets->w_dlg_help = GTK_WIDGET(gtk_builder_get_object(builder,"dlg_help"));

    // các nút chức năng chính của chương trình
    widgets->btn_clear_current = GTK_WIDGET(gtk_builder_get_object(builder, "btn_clear_current"));
    widgets->btn_new = GTK_WIDGET(gtk_builder_get_object(builder, "btn_new"));
    widgets->btn_edit = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit"));
    widgets->btn_delete = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete"));
    widgets->entry_search = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search"));
    widgets->btn_help = GTK_WIDGET(gtk_builder_get_object(builder,"btn_help"));
    widgets->btn_about = GTK_WIDGET(gtk_builder_get_object(builder, "btn_about"));

    // nút xác nhận của dialog wrn_delete
    widgets->btn_yes = GTK_WIDGET(gtk_builder_get_object(builder, "btn_yes"));
    widgets->btn_no = GTK_WIDGET(gtk_builder_get_object(builder, "btn_no"));

    //nút xác nhận xóa của dialog mess_susscess
    widgets->btn_ok = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ok"));


    //các nút thao tác và các entry của dialog newcontact
    widgets->lbl_title = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_title")); //title của dialog
    widgets->btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));
    widgets->btn_choose_img = GTK_WIDGET(gtk_builder_get_object(builder, "btn_choose_img"));  
    widgets->w_img_new = GTK_WIDGET(gtk_builder_get_object(builder, "img_new"));

    widgets->entry_new_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_name"));
    widgets->entry_new_tel = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_tel"));
    widgets->entry_new_sex = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_sex"));
    widgets->entry_new_age = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_age"));
    widgets->entry_new_address = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_address"));
    widgets->entry_avatar_file = GTK_WIDGET(gtk_builder_get_object(builder, "entry_avatar_file"));

    //các label hiển thị thông tin của 1 liên hệ 
    widgets->lbl_name = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_name"));
    widgets->lbl_contact = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_Contact"));
    widgets->lbl_sex = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_sex"));
    widgets->lbl_age = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_age"));
    widgets->lbl_address = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_address"));
    widgets->lbl_mess_susscess = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_mess_susscess"));
    widgets->w_img_avartar = GTK_WIDGET(gtk_builder_get_object(builder, "img_avartar"));
    

    //kết nối các tín hiệu đến các hàm tín hiệu
    gtk_builder_connect_signals(builder, widgets);
    entry_completion(widgets,s2i);
    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();
    
    
    //free 
    jrb_free_tree(s2i);
    gtv_free(&i2s);
    return 0;
}


/**
* \get_and_check_data_entry -> kiểm tra các trường được nhập có thỏa mãn hay không
* \trả về node_tmp lưu các giá trị thỏa mãn ngược lại trả về NULL;
*
* \button: button Add hoặc Apply khi được nhấp vào
* \app_wdgts: con trỏ đồ họa của app
* \name_current: liên hệ hiện tại đang thao tác, nếu tạo mới thì giá trị là NULL
*/

contact_infor_t *get_and_check_data_entry(GtkButton *button, app_widgets *app_wdgts, char *name_current)
{
    contact_infor_t *node_tmp = (contact_infor_t *)malloc(sizeof(contact_infor_t));
    node_tmp = assign_value_by_entry(node_tmp, app_wdgts);
    int finded = s2i_value_id(s2i, node_tmp->name);
    char *avatar = text_buffer_get_entry(GTK_ENTRY(app_wdgts->entry_avatar_file) );

    //nếu không chọn ảnh thì ảnh sẽ được thêm theo giới tính
    if(strcmp(avatar,"") == 0) 
    {
        set_img_by_sex(node_tmp);
    }
    else {
        strcpy(node_tmp->img,avatar);
    }
    free(avatar);

    if(check_entry(node_tmp))  // Kiểm tra các trường cần thiết đã nhập đủ hay chưa
    {
        gtk_widget_show(app_wdgts->w_err_add_contact);
        gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (app_wdgts->w_err_add_contact),"データがない一部のデータフィールド\nsome data fields you have not data!");
        return NULL;    
    }
    if(finded != -1) // Tìm thấy trong CSDL
    {
        if(name_current == NULL)
        {
            gtk_widget_show(app_wdgts->w_err_add_contact);
            gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (app_wdgts->w_err_add_contact),"%s is exist!",node_tmp->name);
            return NULL;
        } 
    }
    // check sdt phai co 10 so va la so
    if( strlen(node_tmp->contact) != 10 || strcmp(node_tmp->contact,"0000000000") < 0 || strcmp(node_tmp->contact,"9999999999") > 0 )
    {
        gtk_widget_show(app_wdgts->w_err_add_contact);
        gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (app_wdgts->w_err_add_contact),
                                                    "電話番号が間違っています!\nIncorrect telephone number!");
        return NULL;
    }
    // gioi tinh khong hop le
    if(!(strcmp(node_tmp->sex,"man") == 0 || strcmp(node_tmp->sex, "woman") == 0)) 
    {
        gtk_widget_show(app_wdgts->w_err_add_contact);
        gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (app_wdgts->w_err_add_contact),"入力性別フィールドは「男性」または「女性」である必要があります\nInput Sex field must be 'man' or 'woman'!");
        return NULL;    
    }
    // check tuoi (0;130)
    if(atol(node_tmp->age) < 1 || atol(node_tmp->age) >130) {
        gtk_widget_show(app_wdgts->w_err_add_contact);
        gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (app_wdgts->w_err_add_contact),"入力した Age が正しくありません\nThe age you entered is not correct!");
        return NULL;
    }
    // check dinh dang mail
    if( check_mail(node_tmp) == 0)
    {
        gtk_widget_show(app_wdgts->w_err_add_contact);
        gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (app_wdgts->w_err_add_contact),
                                                    "入力された電子メールは無効です!\nThe email entered is not valid!");
        return NULL;
    }

    return node_tmp;

}

/**
* \on_btn_add_clicked -> Hàm tín hiệu khi nhấp vào btn_add
*
* \button: button Add hoặc Apply khi được nhấp vào
* \app_wdgts: con trỏ đồ họa của app
*/
void on_btn_add_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    //chức năng thêm liên hệ 
    if(strcmp(gtk_button_get_label(GTK_BUTTON(app_wdgts->btn_add)),"Add" ) == 0)
    {
        contact_infor_t * new_node_add = get_and_check_data_entry(button,app_wdgts,NULL);
        if(new_node_add != NULL)
        {
            add_contact(new_node_add,s2i,&i2s,list_contact,&size);
            gtk_widget_show(app_wdgts->w_mess_susscess);
            show_infor_window(s2i_value_id(s2i,new_node_add->name), app_wdgts,list_contact);
            printf(" %s thêm thành công!\n",new_node_add->name );
        }
    }
    //chức năng chỉnh sửa liên hệ 
    else {
        char *name_current = text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_name));
        int position = s2i_value_id(s2i, name_current);
        contact_infor_t * new_node = get_and_check_data_entry(button,app_wdgts,name_current);
        if(new_node != NULL)
        {
            edit_contact(new_node,s2i,&i2s,list_contact,position);
            gtk_widget_show(app_wdgts->w_mess_susscess);
            show_infor_window(s2i_value_id(s2i,new_node->name), app_wdgts,list_contact);
            printf(" %s sửa thành công!\n",new_node->name );
        }
        free(name_current);    
    }
    //ghi lại ra file tất cả thay đổi dữ liệu
    rewrite_input(list_contact,size);
    //cập nhật hiển thị ra màn hình
    entry_completion(app_wdgts,s2i);
    gtk_tree_view_set_model(GTK_TREE_VIEW(app_wdgts->w_tree_view), GTK_TREE_MODEL(create_model(list_contact,s2i)));  
}


/**
* \on_btn_edit_clicked -> Hàm tín hiệu khi nhấp vào btn_edit 
* vì sử dụng chung với chức năng thêm nên hàm này đặt lại các thông tin hiển thị phù hợp với chức năng 
*
* \button: button edit 
* \app_wdgts: con trỏ đồ họa của app
*/
void on_btn_edit_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    char *name_current = text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_name));
    if( strcmp(name_current,"名前") == 0)
    {
        gtk_widget_show(app_wdgts->w_err_delete);
    }
    else{
        gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_title), "  連絡先情報を編集する\nEdit contact information");
        gtk_button_set_label (GTK_BUTTON(app_wdgts->btn_add) ,"Apply");
        gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_mess_susscess),"   連絡先の更新に成功!\nContact update successful!");

        gtk_entry_set_text( GTK_ENTRY(app_wdgts->entry_new_name),text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_name)) );
        gtk_entry_set_text( GTK_ENTRY(app_wdgts->entry_new_tel), text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_contact)) );
        gtk_entry_set_text( GTK_ENTRY(app_wdgts->entry_new_sex), text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_sex)) );
        gtk_entry_set_text( GTK_ENTRY(app_wdgts->entry_new_age), text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_age)) );
        gtk_entry_set_text( GTK_ENTRY(app_wdgts->entry_new_address), text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_address)) );
        gtk_entry_set_text( GTK_ENTRY(app_wdgts->entry_avatar_file), list_contact[s2i_value_id(s2i,name_current)].img );
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_new),list_contact[s2i_value_id(s2i,name_current)].img);
        gtk_widget_show(app_wdgts->w_dlg_new_contact);
    }
    free(name_current);
    
}

/**
* \on_entry_search_activate -> Hàm tín hiệu khi nhấn enter tại entry_search_activate 
*
* \entry_search: thanh tìm kiếm
* \app_wdgts: con trỏ đồ họa của app
*/
void on_entry_search_activate(GtkEntry *entry_search, app_widgets *app_wdgts)
{
    char *name_find = text_buffer_get_entry(GTK_ENTRY(app_wdgts->entry_search));
    remove_trailing(name_find);
    int finded = s2i_value_id(s2i, name_find);
    if(finded == -1)
    {
        gtk_widget_show(app_wdgts->w_mess_err_find);
        show_infor_window_default(app_wdgts);
        printf("Không tìm thấy %s,finded id = %d \n", name_find,finded);
    }
    else{
        show_infor_window(finded, app_wdgts,list_contact);
        printf("Tìm thấy %s,finded = %d \n", name_find,finded);
    }
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->entry_search), "");
    free(name_find);
}


/**
* \on_btn_yes_clicked -> Hàm tín hiệu khi nhấn xác nhận xóa liên hệ
*
* \button: btn_yes của dialog wrn_delete
* \app_wdgts: con trỏ đồ họa của app
*/
void on_btn_yes_clicked(GtkButton *button,app_widgets *app_wdgts )
{

    char *name_current = text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_name) );

    show_infor_window_default(app_wdgts);

    int position = s2i_value_id(s2i, name_current);
    delete_contact(position,
                   list_contact, 
                   s2i, 
                   &i2s, 
                   &size);
    gtk_widget_hide(app_wdgts->w_wrn_delete);
    printf("Xóa %s thành công!\n", name_current);
    free(name_current);
    //ghi lại ra file tất cả thay đổi dữ liệu
    rewrite_input(list_contact,size);
    entry_completion(app_wdgts,s2i);
    gtk_tree_view_set_model(GTK_TREE_VIEW(app_wdgts->w_tree_view), GTK_TREE_MODEL(create_model(list_contact,s2i)));
}



/**
* \on_tree_view_row_activated -> Hàm tín hiệu nhấp đúp vào hàng thông tin hiển thị tại treeview
*  thông tin hàng được chọn sẽ hiển thị ra vùng hiển thị thông tin bên trái màn hình
*
* \tree_view: vùng hiển thị thông tin treeview 
* \path: đường dẫn
* \column: cột mà bạn nhấp
*/
void on_tree_view_row_activated(GtkTreeView *tree_view,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column, 
                                app_widgets *app_wdgts)
{
   gchar *name;

   GtkTreeIter iter;
   GtkTreeModel *model = gtk_tree_view_get_model(tree_view);

   if (gtk_tree_model_get_iter(model, &iter, path)) 
    {
        gtk_tree_model_get (model, &iter, COLUMN_NAME, &name, -1);
        show_infor_window(s2i_value_id(s2i,name),app_wdgts,list_contact);
    }
    g_free(name);
} 
