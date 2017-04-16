//вар 1, 1. реализовать класс время, есть часы минуты секунды, конструкторы с проверкой корректности, реализовать исключения (напр., 70 секунд - ошибка)
//Сделать пустой, от трех значений, для времени от секунд, которые надо бует переводить
//Операторы сложения и вычитания, метод возвращающий число секунд, часть методов следать методами класса, часть фрэндами(аналогично число часов и минут)
//2. Класс фигура - абстрактный(координаты х у, методы - вывод координат, перемещение фигуры, умножение значения координат на мастабные коэфф, подсчет площади) 
//, прямоугольник, треугольник и круг(дополнительно: проверка, что точка внутри круга, проверка, что другой круг внутри этого круга)
//3. Шаблон класса комплексного числа, в качестве а и б может быть вектор, вещественное число, дробь и т.д. Реализовать сложение, вычитание, умножение, умножение на
// число, модуль

#include <stdlib.h>
#include <glut.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <time.h>
 
typedef struct Snake Snake;
typedef struct SnakeEat SnakeEat;
typedef struct Game Game;
 
#define SCALE 20				//������� ����
#define TIME  200				//����� ���������� �������� ������ - �������� ��������
/*
	������ ����� ������ ������������ �� ���� ���������: ������ ���� ����������, ��������� �� ������, � ��������� �� �������� ��� ����� ������
*/
struct Snake
{
    int posx, posy;
    Snake *next, *prev;
    GdkPixbuf *pSnakeTexture;
};
/*
    ���������, ���������� ���������� � ��� ������: ���������� ������������ � ��������� �� ������
*/
struct SnakeEat
{
    int posx, posy;
    GdkPixbuf *pEatTexture;
};
/*
    �������� ���������, �������� ��� ���������� ��� ����
*/
struct Game
{
    GtkWidget *window;                                              //����, ��� ������
    GdkPixbuf *BackGroundTexture;                                   //������ ��������� ����
    GdkFont *ScoreFont;                                             //����� ��� ����������� �����
    Snake *SnakeHead;                                               //��������� �� ������ ������
    Snake *SnakeTail;                                               //�� ��������� ����� ������
    SnakeEat *SnakeEat;                                             //�� ��� ������
    unsigned int Score;                                             //���������� ��� �����
    char StateHor, StateVer;                                        //����������, ���������� �� ����������� �������� ������
    char ScoreString[10];                                           //������, ��� ������ ����� �� �����
    gboolean KeyState;                                              //����������, ����������� ������������ ��������� ����������� �������� ������ �� ���� ��������, ����� �������� ������ ��� �������� ������
};
 
//--- ������ ������������� ����: ��������� ����������� �����������, ������������� ��������� ������ ---//
void Init_Game(GtkWidget *wid, Game *game)
{
    game->window = wid;
    game->BackGroundTexture = gdk_pixbuf_new_from_file("img/BackGround.png", NULL);
    game->StateHor  = 0;
    game->StateVer = -SCALE;
    game->Score = 0;
    game->SnakeEat = (SnakeEat *) malloc(sizeof(SnakeEat));
    game->SnakeEat->pEatTexture = gdk_pixbuf_new_from_file("img/eat.png", NULL);
 
    Snake *hSnake = (Snake *) malloc(sizeof(Snake));
    hSnake->pSnakeTexture = gdk_pixbuf_new_from_file("img/head.png", NULL);
    hSnake->prev = NULL;
    hSnake->posx = 260;
    hSnake->posy = 260;
    game->SnakeHead = game->SnakeTail = hSnake;
    AddNewPartToSnake( game );
    AddNewPartToSnake( game );
    SetSnakeEatPos( game );
}
 
 
//--- �������, ��������� ��� ������ ������ ---//
void DestroySnake(Game *cgame)
{
    if( cgame->SnakeHead ) {
        Snake *cur, *temp;
        cur = cgame->SnakeHead;
        while( cur ) {
            temp = cur->next;
            free( cur );
            cur = temp;
        }
    }
}
//--- �������, ��������� ��� ������ ���� ---//
void DestroyGame(Game *cgame)
{
    if( cgame ) {
        DestroySnake   ( cgame );
        DestroySnakeEat( cgame );
        free( cgame );
    }
}
//--- �������, ��������� ������ ���--//
void DestroySnakeEat(Game *cgame)
{
    if( cgame->SnakeEat ) {
        free( cgame->SnakeEat );
    }
}
 
 
//--- ������, ����������� ����� ����� � ������ ---//
void AddNewPartToSnake(Game *cgame)
{
    Snake *NewPart = (Snake *) malloc(sizeof(Snake));
    NewPart->pSnakeTexture = gdk_pixbuf_new_from_file("img/part.png", NULL);
    NewPart->prev = cgame->SnakeTail;
    NewPart->posx = NewPart->prev->posx;
    NewPart->posy = NewPart->prev->posy;
    NewPart->next = NULL;
    cgame->SnakeTail->next = NewPart;
    cgame->SnakeTail = NewPart;
}
 
//--- ��������� ����� ������� ��� ������
void SetSnakeEatPos(Game *cgame)
{
    cgame->SnakeEat->posx = rand() % 25 * SCALE;                                                //�������� ���������� ����������
    cgame->SnakeEat->posy = rand() % 25 * SCALE;
    //--- ���� ������ ���������, ����� ��� �� ��������� ���, ��� ������ ��������� ������, � ������ ���� ��������� - �������� ������� ����� ---//
    Snake *cSnake = cgame->SnakeHead;
    while( cSnake ) {
        if( ( cgame->SnakeEat->posx == cSnake->posx && cgame->SnakeEat->posy == cSnake->posy )
                            || cgame->SnakeEat->posy < 20 ) {
            SetSnakeEatPos( cgame );
            break;
        }
        cSnake = cSnake->next;
    }
}
 
//--- ������� ��������, ��������� �� ������������� ������ �� ������ ������� ���� ---//
//--- ���������� TRUE - ���� ���������, FALSE - ���� ���
gboolean Collision(Game *cgame)
{
    Snake *CurSnake = cgame->SnakeHead->next;
    while( CurSnake ) {
        if( CurSnake->posx == cgame->SnakeHead->posx
                    && CurSnake->posy == cgame->SnakeHead->posy )
            return TRUE;
        CurSnake = CurSnake->next;
    }
    return FALSE;
}
 
//--- ������� ���������� ������, � ������ ������ �����, �� ����������� ����������� x, y ---//
void DrawScoreText(Game *game, int x, int y)
{
    GdkColor Color;                                                                             //���������, �������� � ���� �������� ����� (RGBA)
    /*
        ���� ������ ��������� �� ������� ����� ������� � ����� ��� �������������� ��� ������ ����� �� �����
    */
    GdkGC *GC = game->window->style->fg_gc[ GTK_WIDGET_STATE (game->window) ];
    gdk_color_parse("#FF6600", &Color);                                                         //���������� RGB-���� � ��������� Color
    gdk_gc_set_rgb_fg_color(GC, &Color);														//������������� ����� ���� � ��� �����
 
    sprintf(game->ScoreString, "SCORE: %d", game->Score );                                      //��������� � ������ ����� � ������ ������
    gdk_draw_string(game->window->window, game->ScoreFont, GC, x, y, game->ScoreString);        //������� �� ����� � ���. ����������� � ���� ���������� ������ ������ � ������
}
 
//--- �������, � ������� ��� ���������� ���� ����������� ����� ����
gboolean Draw_Field(GtkWidget *win, GdkEventExpose *event, gpointer data)
{
    Game *game = (Game *) data;
    Snake *cSnake = game->SnakeTail;
    gdk_draw_pixbuf(win->window,                                                                 //������ ��� ������
                    win->style->black_gc,
                    game->BackGroundTexture,
                    0, 0,
                    0, 0,
                    500, 500,
                    GDK_RGB_DITHER_NONE,
                    0, 0);
 
    gdk_draw_pixbuf(win->window,                                                                //���
                    win->style->black_gc,
                    game->SnakeEat->pEatTexture,
                    0, 0,
                    game->SnakeEat->posx, game->SnakeEat->posy,
                    20, 20,
                    GDK_RGB_DITHER_NONE,
                    0, 0);
 
 
    while( cSnake ) {                                                                           //��� ����� ������
        gdk_draw_pixbuf(win->window,
                        win->style->black_gc,
                        cSnake->pSnakeTexture,
                        0, 0,
                        cSnake->posx, cSnake->posy,
                        20, 20,
                        GDK_RGB_DITHER_NONE,
                        0, 0);
        cSnake = cSnake->prev;
    }
    DrawScoreText(game, 10, 16);                                                                //����� �����
    gtk_widget_queue_draw(game->window);														//������� ��, ��� �������� ���� ��� ����������
    return TRUE;																				//TRUE - ���������� ������������ ������� ���������� ������� FALSE - ���������
}
//---   ---//
 
//--- �������, �������������� ������� ������
gboolean KeyPress(GtkWidget *wid, GdkEventKey *event, gpointer data)
{
    Game *cgame = (Game *) data;
    if( cgame->KeyState )                                                                       //���� ������� ��� ������ �����������, �� ������ �������
        return TRUE;
    switch( event->keyval ) {                                                                   //��������� ��� �� ������� ���� ������
        case GDK_Right:                                                                         //������
            if( !cgame->StateHor ) {
                cgame->StateHor = SCALE;
                cgame->StateVer = 0;
            }
            break;
        case GDK_Left:                                                                          //�����
            if( !cgame->StateHor ) {
                cgame->StateHor = -SCALE;
                cgame->StateVer = 0;
            }
            break;
        case GDK_Up:                                                                            //�����
            if( !cgame->StateVer ) {
                cgame->StateVer = -SCALE;
                cgame->StateHor = 0;
            }
            break;
        case GDK_Down:                                                                          //����
            if( !cgame->StateVer ) {
                cgame->StateVer = SCALE;
                cgame->StateHor = 0;
            }
            break;
        case GDK_Return:                                                                        //� �����, ����� ������ ������ ������
            DestroyGame(cgame);																	//������� ���������� ����, ����� �� ���� ������ ������
            Init_Game(wid, cgame);																//������ �����
            break;
    }
    cgame->KeyState = TRUE;																		//������������� ����, ��� ������� ��� ��������
    return TRUE;
}
 
 
//--- ������� ������������ ��� �������� ������, ������������ ��������� ������� ���
gboolean Engine(gpointer data)
{
    Game *cgame = (Game *) data;
    Snake *CurSnake = cgame->SnakeTail;
    while( CurSnake != cgame->SnakeHead ) {                                                 //�������� ������� ������ ����� ������ ������� � ������, �� ����� �������� ������� ����� �������
        CurSnake->posx = CurSnake->prev->posx;
        CurSnake->posy = CurSnake->prev->posy;
        CurSnake = CurSnake->prev;
    }
    cgame->KeyState = FALSE;																//�������� ���� ������� �������
    //--- �������� ������� ������ ������, ������ �� ����������, ���������� ��� ������� ������� ---//
    CurSnake->posx += cgame->StateHor;
    CurSnake->posy += cgame->StateVer;
    //--- ����� �������� �� ������� ����, ����� ��� ������������ � ������ ����� �� ������ ---//
    if( CurSnake->posx < 0 )
        CurSnake->posx = 480;
    if( CurSnake->posx > 480 )
        CurSnake->posx = 0;
    if( CurSnake->posy > 480 )
        CurSnake->posy = 20;
    if( CurSnake->posy < 20 )
        CurSnake->posy = 480;
    //--- ��������� ���� ������ ��������� � ���� ����� - �������� ������ ���� ---//
    if( Collision( cgame ) ) {
		DestroyGame(cgame);
        Init_Game( cgame->window, cgame );
	}
    //--- ��������, ���� ������ ���� �� ��� �� �����������, ��� � ���, �� ������ ������� ��� � ���������� ������, ����������� ���� ---//
    if(CurSnake->posx == cgame->SnakeEat->posx &&
                    CurSnake->posy == cgame->SnakeEat->posy) {
        AddNewPartToSnake( cgame );
        SetSnakeEatPos( cgame );
        //!!
        cgame->Score++;
    }
    return TRUE;																			//TRUE - ���������� ������ ������� �� ������ ������� Engine(), FALSE - ������� ������
}
 
int main (int argc, char *argv[])
{
    srand( time( 0 ) );                                                                 //��������� ��������� ��������� �����
    GtkWidget *win = NULL;                                                              //������ ������, � ������� ����� �������� ���� ����
    Game *cgame = (Game *) malloc(sizeof( Game ));                                      //�������� ����������� gfvznm ��� ��������� ����
    gtk_init (&argc, &argv);                                                            //������������� GTK
 
    //--- �������� ���� ---//
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);                                         //������ ���� ������ ���� ���������� ����, �� ��� �������� ������ GTK_WINDOW_TOPLEVEL
    gtk_window_set_title (GTK_WINDOW (win), "Snake");                                   //���������� ������� ���� �� "Snake"
    gtk_widget_set_size_request (win, 500, 500);                                         //������������� ������������� ������� ����
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);                     //������������� ���� �� �������� �� ������, �����-���� ������ GTK_WIN_POS_CENTER �� ��� ��������
    //---   ������� ���������� �������� ����, ��� �������, ���� ����� ���� �����������, TRUE - ����� �����������, FALSE - ���  ---//
    gtk_window_set_resizable (GTK_WINDOW(win), FALSE);
	//--- � Linux � Windows ������ �������� �������� �������, � ����� ���� ����� ���������������� ��� ������ �� ����� �������� - ��������� ��������������� ������� ��� �������� �� ---//
#if defined _WIN32
    cgame->ScoreFont = gdk_font_load ("Arial");
#else
    cgame->ScoreFont = gdk_font_load ("-*-helvetica-bold-r-*-*-*-160-*-*-*-*-*-*");    
#endif                                                                              //����� ������� �������������
 
    Init_Game(win, cgame);                                                              //�������������� ����, ������� ��������� ����
	//--- �������� ������� ��������� ����, ����������� ����, ������� ������ ---//
    g_signal_connect_data (win, "destroy", gtk_main_quit, NULL, NULL, 0);
 
    g_signal_connect_data (win, "expose_event", Draw_Field, (gpointer)cgame, NULL, 0);
 
    g_signal_connect_data (win, "key_press_event", KeyPress, (gpointer)cgame, NULL, 0);
 
	//--- ������ ������ ��� ������ ������� ���������� ������� ������, ��� ---//
    g_timeout_add( TIME, Engine, (gpointer) cgame );
 
    gtk_widget_realize (win);                                                            //��� ���������� ������
    gtk_widget_show_all (win);                                                          //���������� ��� ������� �� �����
    //--- ��������� ����������� ���� GTK, ������� ����� ������������ ��� ��������� ���� �������, � ���������� ������ ���� � �� ��� � ��
    gtk_main ();
    //--- ����� ���������� ������������ �����, � ���������� ���������� ������� destroy, ������� ����������� ������ �� �������� ����
    DestroyGame ( cgame );
    //              ---         //
    return 0;
}
