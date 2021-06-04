#include "app.h"


/*===============================các hàm xử lý dữ liệu bên trong=======================*/

/**
* \remove_trailing -> bỏ dấu cách của các string
*
* \s: string cần bỏ dấu cách
*/
void remove_trailing(char *s) {
  int len = strlen(s);
  while (len > 0 && isspace(s[len - 1])) {
    s[len - 1] = '\0';
    --len;
  }
}

/**
* \set_img_by_sex -> Nếu dữ liệu đầu vào không có file ảnh sẽ lấy ảnh dựa vào giới tính 
*
* \node: địa chỉ node chứa dữ liệu
*/
void set_img_by_sex(contact_infor_t * node)
{
    if(strcmp(node->sex,"man") == 0)
    {
        strcpy(node->img, "../image/man.jpg");
    }
    if(strcmp(node->sex,"woman") == 0)
    {
        strcpy(node->img, "../image/woman.jpg");
    }
}

/**
* \get_save_id -> Lưu các key và value thích hợp vào cây bn_tree s2i , vector i2s
* \hàm trả về giá trị id nếu lưu các dữ liệu thành công ngược lại trả về k_s2i_invalid
*
* \key: chuỗi làm key = trường name của thông tin
* \s2i: địa chỉ cây chứa dữ liệu
* \i2s: địa chỉ vector_t chứa dữ liệu
* \g_id: id tương ứng với key
*/
void get_save_id(char *key, JRB s2i,vector_t *i2s, int g_id) 
{
                      
    jrb_insert_str(s2i, key, (Jval){.i = g_id});      
    gtv_set_value_with_index(i2s, (gtype){.s = key}, g_id);
    gtv_setsize(*i2s,g_id + 1);
}


/**
* \s2i_value_id -> lấy id tưng ứng của chuỗi key bằng cách tìm trong cây JRB s2i
* \hàm trả về giá trị id tương ứng của chuỗi đưa vào
*
* \key: chuỗi làm key = trường name của thông tin
*/
int s2i_value_id(JRB root, char *key)
{
    JRB node = jrb_find_str(root, key);
    if( node == NULL)
    {
        return -1;
    }
    return node->val.i;
}


/**
* \read_data -> đọc dữ liệu từ file đầu vào và luưu vào các cấu trúc dữ liệu
*
* \list_contact: địa chỉ danh sánh mảng dữ liệu
* \s2i: địa chỉ cây chứa dữ liệu
* \i2s: địa chỉ vector_t chứa dữ liệu
* \size: biến đếm để chỉ số phần tử danh sách
*/
void read_data(contact_infor_t * list_contact, JRB s2i,vector_t *i2s, int *size)
{
    FILE * inp = fopen("../input.txt", "r");

    if(inp == NULL)
        printf("Cannot open file!\n");

    while(!feof(inp)) {
        fscanf(inp, " %[^+\n]", (list_contact + *size )->name);
        get_save_id((list_contact + *size)->name,s2i,i2s,*size);
        //printf("%s\n",list_contact[size].name);
        fscanf(inp, "%*[+]");   

        fscanf(inp, " %[^+\n]", (list_contact + *size )->contact);
        //printf("%s\n",list_contact[size].contact);
        fscanf(inp, "%*[+]");

        fscanf(inp, " %[^+\n]", (list_contact + *size )->sex);
        //printf("%s\n",list_contact[size].sex);
        fscanf(inp, "%*[+]");

        fscanf(inp, " %[^+\n]", (list_contact + *size )->age);
        //printf("%s\n",list_contact[size].age);
        fscanf(inp, "%*[+]");

        fscanf(inp, " %[^+\n]", (list_contact + *size )->address);
        //printf("%s\n",list_contact[size].address);
        fscanf(inp, "%*[+]");

        fscanf(inp, " %[^+\n]", (list_contact + *size )->img);

        //printf("%s\n",list_contact[size].img);
        if(strcmp((list_contact + *size )->img,"none") == 0 )
        {
            set_img_by_sex(list_contact + *size) ;
        }
        fscanf(inp, "%*[+]");
        (*size) ++;
  }
    printf("%s\n","Đọc dữ liệu từ file text thành công!");
    fclose(inp);
}


/**
* \assign_value_list -> gán dữ liệu từ node_2 vào node_1
*
* \node_1: địa chỉ của node cần lấy dữ liệu
* \node_2: địa chỉ của node chứa dữ liệu cần lấy
*/
void assign_value_list(contact_infor_t *node_1, contact_infor_t *node_2) 
{
    remove_trailing((*node_2).name);
    remove_trailing((*node_2).contact);
    remove_trailing((*node_2).sex);
    remove_trailing((*node_2).age);
    remove_trailing((*node_2).address);
    remove_trailing((*node_2).img);

    strcpy((*node_1).name,      (*node_2).name);
    strcpy((*node_1).contact,   (*node_2).contact);
    strcpy((*node_1).sex,       (*node_2).sex);
    strcpy((*node_1).age,       (*node_2).age);
    strcpy((*node_1).address,   (*node_2).address);
    strcpy((*node_1).img,       (*node_2).img);
}


/**
* \delete_contact -> xóa liên hệ
*
* \position: id hay chỉ số của liên hệ trong danh sách dữ liệu list_contact
* \list_contact: địa chỉ danh sánh mảng dữ liệu
* \s2i: địa chỉ cây chứa dữ liệu
* \i2s: địa chỉ vector_t chứa dữ liệu
* \size: biến đếm để chỉ số phần tử danh sách
*/
void delete_contact(int position,
				   contact_infor_t *list_contact, 
				   JRB s2i, 
				   vector_t *i2s, 
				   int *size)
{
	JRB find = jrb_find_str(s2i, (list_contact + position)->name);
    jrb_delete_node(find);
    for(int i = position ; i < *size - 1; i++)
    {

        JRB node = jrb_find_str(s2i, (list_contact + i+1)->name);
        node->val.i = i;
        node->key.s = strdup((list_contact + i+1)->name);

        assign_value_list(list_contact + i, list_contact + i + 1);
        gtv_set_value_with_index(i2s, (gtype){.s = (*i2s+i+1)->s},i);
    }
    (*size) --;
    gtv_setsize(*i2s,*size);

}


/**
* \delete_contact -> thêm liên hệ
*
* \new_node_tmp: node chứa thông tin liên hệ mới
* \list_contact: địa chỉ danh sánh mảng dữ liệu
* \s2i: địa chỉ cây chứa dữ liệu
* \i2s: địa chỉ vector_t chứa dữ liệu
* \size: biến đếm để chỉ số phần tử danh sách
*/
void add_contact(contact_infor_t *new_node_tmp, 
                  JRB s2i, 
                  vector_t *i2s, 
                  contact_infor_t *list_contact, 
                  int *size)
{
    jrb_insert_str(s2i, new_node_tmp->name, (Jval){.i = *size});
    gtv_set_value_with_index(i2s,(gtype){.s = new_node_tmp->name},*size);
    assign_value_list(list_contact + *size, new_node_tmp);
    (*size) ++;
    gtv_setsize(*i2s,*size);
}

/**
* \edit_contact -> chỉnh sửa lên hệ
*
* \new_node_tmp: node chứa thông tin cập nhật
* \list_contact: địa chỉ danh sánh mảng dữ liệu
* \s2i: địa chỉ cây chứa dữ liệu
* \i2s: địa chỉ vector_t chứa dữ liệu
* \position: id hay chỉ số của liên hệ cần chỉnh sủa
*/
void edit_contact(contact_infor_t *new_node_tmp,
                 JRB s2i, vector_t *i2s, 
                 contact_infor_t *list_contact, 
                 int position)
{
    JRB node = jrb_find_str(s2i,(list_contact+position)->name);
    jrb_delete_node(node);
    jrb_insert_str(s2i, new_node_tmp->name, (Jval){.i = position});
    gtv_set_value_with_index(i2s,(gtype){.s = new_node_tmp->name},position);
    assign_value_list(list_contact + position, new_node_tmp);
}

/**
* \check_mail -> kiểm tra định dạng mail
*
* \node: liên hệ cần kiểm tra
*/
int check_mail(contact_infor_t *node)
{
    char *gmail = strstr(node->address, "@gmail.com");
    char *hust = strstr(node->address, "@sis.hust.edu.vn");
    if( gmail == NULL && hust == NULL)
    {
        return 0;
    }
    else {
        return 1;
    }
}


/**
* \rewrite_input -> ghi lại thông tin cập nhật danh sách liên hệ ra file input.txt
*
* \list_contact: địa chỉ danh sánh mảng dữ liệu
* \size: số phần tử danh sách
*/
void rewrite_input(contact_infor_t *list_contact,int size)
{
    FILE *input = fopen("../input.txt","w");
    if(input == NULL)
        printf("Cannot open file!\n");
    for (int i = 0; i < size ; ++i)
    {
        if( i == size -1)
        {
            fprintf(input,"%s+%s+%s+%s+%s+%s",(list_contact +i)->name,
                                                (list_contact +i)->contact,
                                                (list_contact +i)->sex,
                                                (list_contact +i)->age,
                                                (list_contact +i)->address,
                                                (list_contact +i)->img);
        }
        else
        {
            fprintf(input,"%s+%s+%s+%s+%s+%s\n",(list_contact +i)->name,
                                                (list_contact +i)->contact,
                                                (list_contact +i)->sex,
                                                (list_contact +i)->age,
                                                (list_contact +i)->address,
                                                (list_contact +i)->img);
        }
    }
    fclose(input);
}



/*=======các hàm lấy dữ liệu từ nguời dùng, đưa các dữ liệu đã xử lý ra màn hìn============*/

/**
* \assign_value_by_entry -> lấy dữ liệu từ các trường entry và lưu vào 1 node
* \trả về node_tmp lưu các giá trị
*
* \node_tmp: node 
* \app_wdgts: con trỏ đồ họa gtk
*/
contact_infor_t *assign_value_by_entry(contact_infor_t *node_tmp, app_widgets* app_wdgts)
{
    strcpy(node_tmp->name,text_buffer_get_entry(GTK_ENTRY(app_wdgts->entry_new_name))); 
    strcpy(node_tmp->contact, text_buffer_get_entry(GTK_ENTRY(app_wdgts->entry_new_tel))); 
    strcpy(node_tmp->sex, text_buffer_get_entry(GTK_ENTRY(app_wdgts->entry_new_sex))); 
    strcpy(node_tmp->age, text_buffer_get_entry(GTK_ENTRY(app_wdgts->entry_new_age))); 
    strcpy(node_tmp->address, text_buffer_get_entry(GTK_ENTRY(app_wdgts->entry_new_address))); 
    
    return node_tmp;
}

/**
* \check_entry -> check các trường được nhập đủ hay chưa
* \trả về 1 nếu nhập đủ các trường ngược lại trả về 1
*
* \node_tmp: node chứa các dữ liệu đọc được từ các entry các trường
*/
int check_entry(contact_infor_t *node_tmp)
{
    return  node_tmp->name[0]       == '\0' || 
            node_tmp->contact[0]    == '\0' ||
            node_tmp->sex[0]        == '\0' ||
            node_tmp->age[0]        == '\0' ||
            node_tmp->address[0]    == '\0' ;
        
}

/**
* \text_buffer_get_label -> lấy dữ liệu text từ lablel
* \trả về con trỏ mảng kí tự
*
*label: label đang chứa dữ liệu cần lấy
*/
char *text_buffer_get_label(GtkLabel *label)
{
    char *name_find = strdup(gtk_label_get_text(label));
    return name_find;
}


/**
* \text_buffer_get_entry -> lấy dữ liệu text từ entry
* \trả về con trỏ mảng kí tự
*
* \entry: entry chứa dữ liệu nhập vào
*/
char *text_buffer_get_entry(GtkEntry *entry)
{
    char *name_find = strdup(gtk_entry_get_text (entry));
    return name_find;
}


/**
* \add_columns -> tạo các cột trong treeveiw để in thông tin 
*
* \treeview: đối tượng w_tree_view trong app, thông tin sẽ hiển thị tại đối tượng này
*/

void add_columns(GtkTreeView *treeview)
{
    GtkTreeViewColumn *column1;
    GtkCellRenderer *renderer;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    renderer = gtk_cell_renderer_text_new();
    column1 = gtk_tree_view_column_new_with_attributes("名前/Name", renderer, "text", COLUMN_NAME, NULL);
    gtk_tree_view_column_set_min_width (column1, 150);
    gtk_tree_view_append_column(treeview, column1);
}



/**
* \create_model -> Tạo kiểu in thông tin theo hàng duới dạng gtk_list_store
* \trả về model để in các dữ liệu từng hàng
*
* \list_contact: địa chỉ danh sách thông tin
* \size : sô lượng hàng(để in) hay thông tin liên hệ hiện có
*/
GtkTreeModel *create_model(contact_infor_t *list_contact,JRB s2i)
{
    GtkListStore *store;

    GtkTreeIter iter;
    store = gtk_list_store_new(NUM_COLUMNS, 
                               G_TYPE_STRING);
    JRB cur;
    jrb_traverse(cur, s2i)
    {
        gtk_list_store_append(store, &iter);
        int i = s2i_value_id(s2i,cur->key.s);
        gtk_list_store_set(store, &iter, COLUMN_NAME, (list_contact +i)->name, -1);

    }
    return GTK_TREE_MODEL(store);
}

/**
* \create_completion_model -> Tạo kiểu in thông tin có thể được tìm kiếm khi đang nhập vào entry search
* \trả về model để in các dữ liệu từng hàng
*
* \s2i: địa chỉ cây chứa dữ liệu
*/
GtkTreeModel *create_completion_model (JRB s2i)
{
  GtkListStore *store;
  GtkTreeIter iter;

  store = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_STRING);

  JRB cur;
  jrb_traverse(cur, s2i)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, cur->key.s, -1);

    }

  return GTK_TREE_MODEL (store);
}

/**
* \entry_completion -> Tạo hộp tự động điền với thông tin trong cây s2i
*
* \s2i: địa chỉ cây chứa dữ liệu
* \app_wdgts: con trỏ đến các đối tượng đồ họa
*/
void entry_completion(app_widgets *app_wdgts,JRB s2i)
{
    GtkEntryCompletion *completion;
    GtkTreeModel *completion_model;
    completion = gtk_entry_completion_new ();

      /* Assign the completion to the entry */
      gtk_entry_set_completion (GTK_ENTRY(app_wdgts->entry_search), completion);
      g_object_unref (completion);

      /* Create a tree model and use it as the completion model */
      completion_model = create_completion_model (s2i);
      gtk_entry_completion_set_model (completion, completion_model);
      g_object_unref (completion_model);

      /* Use model column 0 as the text column */
      gtk_entry_completion_set_text_column (completion, 0);
}

/**
* \show_infor_window -> in thông tin ra màn hình để thao tác
*
* \app_wdgts: con trỏ đồ họa gtk
* \list_contact: địa chỉ danh sách thông tin
*/
void show_infor_window(int i, app_widgets *app_wdgts, contact_infor_t *list_contact)
{

    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_avartar),(list_contact +i)->img);
    gtk_widget_set_sensitive(app_wdgts->w_img_avartar, TRUE);
    
    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_name), (list_contact +i)->name);
    gtk_widget_set_sensitive(app_wdgts->lbl_name, TRUE);
    
    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_contact), (list_contact +i)->contact);
    gtk_widget_set_sensitive(app_wdgts->lbl_contact, TRUE);

    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_sex), (list_contact +i)->sex);
    gtk_widget_set_sensitive(app_wdgts->lbl_sex, TRUE);

    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_age), (list_contact +i)->age);
    gtk_widget_set_sensitive(app_wdgts->lbl_age, TRUE);

    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_address), (list_contact +i)->address);
    gtk_widget_set_sensitive(app_wdgts->lbl_address, TRUE);

}


/**
* \show_infor_window_default -> xóa thông tin hiện tại trên màn hình
*
* \app_wdgts: con trỏ đồ họa gtk
*/
void show_infor_window_default(app_widgets *app_wdgts)
{
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_avartar),"../image/default.png");
    gtk_widget_set_sensitive(app_wdgts->w_img_avartar, FALSE);
    
    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_name), "名前");
    gtk_widget_set_sensitive(app_wdgts->lbl_name, FALSE);
    
    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_contact), "012345678910");
    gtk_widget_set_sensitive(app_wdgts->lbl_contact, FALSE);

    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_sex), "男性/女性");
    gtk_widget_set_sensitive(app_wdgts->lbl_sex, FALSE);

    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_age), "xy");
    gtk_widget_set_sensitive(app_wdgts->lbl_age, FALSE);

    gtk_label_set_text (GTK_LABEL(app_wdgts->lbl_address), "duanlv@gmail.com");
    gtk_widget_set_sensitive(app_wdgts->lbl_address, FALSE);
}

/**
* \clean_buff_entry -> xóa các text được nhập lần trước đó 
*
* \app_wdgts: con trỏ đồ họa gtk
*/
 void clean_buff_entry(app_widgets *app_wdgts)
{
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->entry_new_name), "");
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->entry_new_tel), "");
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->entry_new_sex), "");
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->entry_new_age), "");
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->entry_new_address), "");
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->entry_avatar_file), "");
}

/**
* \on_btn_clear_current_clicked -> xóa thông tin hiện tại đang hiển thị
*
* \button: btn_clear_current trong màn hình chính
* \app_wdgts: con trỏ đồ họa gtk
*/
void on_btn_clear_current_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    show_infor_window_default(app_wdgts);
}


/**
* \on_btn_new_clicked -> hiện dialog để nhập thông tin
*
* \button: new Button trong cửa sổ chính
* \app_wdgts: con trỏ đồ họa gtk
*/
void on_btn_new_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    clean_buff_entry(app_wdgts);
    gtk_widget_show(app_wdgts->w_dlg_new_contact);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_new),"../image/default.png");
    gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_title), "   新しい連絡先情報\nNew Contact Information");
    gtk_button_set_label (GTK_BUTTON(app_wdgts->btn_add) ,"Add");
    gtk_label_set_text(GTK_LABEL(app_wdgts->lbl_mess_susscess),"連絡先を正常に追加!\nAdd contact successfully !");

    gtk_widget_show(app_wdgts->w_dlg_new_contact);

}

/**
* \on_btn_about_clicked -> hiện các cửa sổ xác nhận xóa  và kiểm tra có thông tin nào đang hiển thị hay không
*
* \button: btn_delete trong của sổ chính
* \app_wdgts: con trỏ đồ họa gtk
*/
void on_btn_delete_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    char *name_current = text_buffer_get_label(GTK_LABEL(app_wdgts->lbl_name) );
    if( strcmp(name_current,"名前") == 0)
    {
        gtk_widget_show(app_wdgts->w_err_delete);
    }
    else {
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(app_wdgts->w_wrn_delete),"%s",name_current);
        gtk_widget_show(app_wdgts->w_wrn_delete);
    }
    free(name_current);
}

/**
* \on_btn_help_clicked -> hiện dialog_help mô tả cách sử dụng
*
* \button: Help button trong của sổ chính
* \app_wdgts: con trỏ đến các đối tượng đồ họa trong chương trình
*/
void on_btn_help_clicked(GtkButton *button, app_widgets* app_wdgts )
{
    gtk_widget_show(app_wdgts->w_dlg_help);
}

/**
* \on_btn_about_clicked -> hiện dialog_about thông tin về app
*
* \button: About button trong của sổ chính
* \app_wdgts: con trỏ đồ họa gtk
*/
void on_btn_about_clicked(GtkButton *button, app_widgets* app_wdgts )
{
    gtk_widget_show(app_wdgts->w_dlg_about);
}


/**
* \on_bnt_no_clicked -> hủy thao tác xóa và đóng dialog cảnh báo
*
* \button: No button của dialog wrn_delete
* \app_wdgts: con trỏ đồ họa gtk
*/
void on_bnt_no_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    gtk_widget_hide(app_wdgts->w_wrn_delete);
}


/**
* \on_btn_ok_clicked -> xác nhận thông báo mess_susscess và đóng dialog 
*
* \button: ok button của dialog mess_susscess
* \app_wdgts: con trỏ đồ họa gtk
*/
void on_btn_ok_clicked(GtkButton *button,app_widgets *app_wdgts)
{
    gtk_widget_hide(app_wdgts->w_dlg_new_contact);
}

/**
* \on_btn_choose_img_clicked -> tín hiệu khi nhấp vào btn_choose_img để hiển thị của sổ để chọn file ảnh 
* và hiển thị địa chỉ của ảnh vào entry_avatar_file
*
* \button: btn_choose_img trong dialog dlg_new_contact 
* \app_wdgts: con trỏ đồ họa gtk
*/

void on_btn_choose_img_clicked(GtkButton *button,app_widgets *app_wdgts)
{
    gchar *file_name = NULL;
    gtk_widget_show(app_wdgts->w_dlg_choose_img);
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_choose_img)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_choose_img));
        if (file_name != NULL) {
            gtk_entry_set_text( GTK_ENTRY(app_wdgts->entry_avatar_file),file_name);
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_new),file_name);
        }
        g_free(file_name);
    }
    
}