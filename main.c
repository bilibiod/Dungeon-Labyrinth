#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "objetos.h"



// CONSTANTES E OUTRAS DEFINCICOES====================================================================================================
    const int   largura         = 1920;
    const int   altura          = 1080;
    const float FPS             = 60.0;
    const float FPSanim         = 11.0;
    int         qtd_derrot      = 0;
    int         cronAnimVitoria = 0;
    int         cronAnimDerrota = 0;
    int         haloFrame       = 0;
    int         localvidas      = 100;
    int         tomoudano       = 0;
    int         tempototal      = 0;

    enum ESTADOS{MENU, INTRO, LABIRINTO, ORCLUTA, SLIMELUTA, WEREWOLFLUTA, DERROTA, VITORIA};

    bool teclas[7] = {false, false, false, false, false, false, false};
    enum TECLAS{UP, DOWN, LEFT, RIGHT, SPACE, ESCAPE, E};



// DECLARAR ========================================================================================================================
void colisao();

void movWerewolf();
void movSlime();
void movOrc();

void cobretela ();

void reset();


// MAIN ==============================================================================================================================-

int main (void)
{

    bool acabou = false;
    int estados = MENU;


    ALLEGRO_DISPLAY     *display    = NULL;
    ALLEGRO_EVENT_QUEUE *fila       = NULL;
    ALLEGRO_TIMER       *timer      = NULL;
    ALLEGRO_TIMER       *timeranim  = NULL;

    ALLEGRO_BITMAP *introd      = NULL;
    ALLEGRO_BITMAP *segs80      = NULL;
    ALLEGRO_BITMAP *menuini     = NULL;
    ALLEGRO_BITMAP *perderorc   = NULL;
    ALLEGRO_BITMAP *perderslime = NULL;
    ALLEGRO_BITMAP *perderwere  = NULL;
    ALLEGRO_BITMAP *quase       = NULL;
    ALLEGRO_BITMAP *festeje     = NULL;
    ALLEGRO_BITMAP *semdano     = NULL;

    ALLEGRO_BITMAP *fundo                   = NULL;
    ALLEGRO_BITMAP *werewolfimg             = NULL;
    ALLEGRO_BITMAP *slimeimg                = NULL;
    ALLEGRO_BITMAP *orcimg                  = NULL;
    ALLEGRO_BITMAP *halo                    = NULL;
    ALLEGRO_BITMAP *knightsprite            = NULL;
    ALLEGRO_BITMAP *espadavert              = NULL;
    ALLEGRO_BITMAP *espadatk                = NULL;
    ALLEGRO_BITMAP *porta                   = NULL;
    ALLEGRO_BITMAP *portalarga              = NULL;
    ALLEGRO_BITMAP *portawere               = NULL;
    ALLEGRO_BITMAP *vidasimg                = NULL;
    ALLEGRO_BITMAP *orcderrot               = NULL;
    ALLEGRO_BITMAP *slimederrot             = NULL;
    ALLEGRO_BITMAP *werederrot              = NULL;
    ALLEGRO_BITMAP *knightderrot            = NULL;


    ALLEGRO_SAMPLE *swing               = NULL;
    ALLEGRO_SAMPLE *orcdor              = NULL;
    ALLEGRO_SAMPLE *slimedor            = NULL;
    ALLEGRO_SAMPLE *weredor             = NULL;
    ALLEGRO_SAMPLE *knightdor           = NULL;

    ALLEGRO_SAMPLE *mus                     = NULL;
    ALLEGRO_SAMPLE_INSTANCE *musCon         = NULL;

    ALLEGRO_SAMPLE *lutamus                     = NULL;
    ALLEGRO_SAMPLE_INSTANCE *lutamusCon         = NULL;


    if(!al_init())
    {fprintf(stderr, "falhou ao inicializar o Allegro!\n");return -1;}


    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(largura,altura);
    al_set_window_position(display,0,0);

    if(!display)
    {fprintf(stderr, "falhou ao criar o display!\n");return -1;}


    //INICIAR ADDONS ================================================================================================-

    al_init_primitives_addon();
    al_install_keyboard();

    al_init_image_addon();

    al_init_font_addon();
    al_init_ttf_addon();

    al_install_audio();
    al_init_acodec_addon();

// INICIAR OUTRAS COISAS==============================================================================================-
    fila = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    timeranim = al_create_timer(1.0 / FPSanim);

// INICIAR IMAGENS E FONTES==============================================================================================-
    segs80      = al_load_bitmap("img/menus/segs80.jpg");
    menuini     = al_load_bitmap("img/menus/menuini.jpg");
    perderorc   = al_load_bitmap("img/menus/perderorc.jpg");
    perderslime = al_load_bitmap("img/menus/perderslime.jpg");
    perderwere  = al_load_bitmap("img/menus/perderwere.jpg");
    quase       = al_load_bitmap("img/menus/quase.jpg");
    festeje     = al_load_bitmap("img/menus/festeje.jpg");
    semdano     = al_load_bitmap("img/menus/semdano.jpg");
    introd      = al_load_bitmap("img/menus/INTRO.png");



    fundo           = al_load_bitmap("img/mapa.png");
    knightsprite    = al_load_bitmap("img/knightsprite.png");
    werewolfimg     = al_load_bitmap("img/werewolf.png");
    slimeimg        = al_load_bitmap("img/slimesprites.png");
    orcimg          = al_load_bitmap("img/orcsprites.png");
    halo            = al_load_bitmap("img/halo.png");
    espadavert      = al_load_bitmap("img/espada.png");
    espadatk        = al_load_bitmap("img/espadatk.png");
    porta           = al_load_bitmap("img/porta.png");
    portalarga      = al_load_bitmap("img/portalarga.png");
    portawere       = al_load_bitmap("img/portawere.png");
    vidasimg        = al_load_bitmap("img/coracao.png");
    orcderrot       = al_load_bitmap("img/orcderrot.png");
    slimederrot     = al_load_bitmap("img/slimederrot.png");
    werederrot      = al_load_bitmap("img/werederrot.png");
    knightderrot    = al_load_bitmap("img/knightderrot.png");


    ALLEGRO_FONT *fonte = al_load_font("arial.ttf", 36, 0);
    ALLEGRO_FONT *fonte2 = al_load_font("INVASION2000.ttf", 90, 0);

     al_reserve_samples(15);

    swing       = al_load_sample("aud/atk.wav");
    orcdor      = al_load_sample("aud/orcdor.ogg");
    slimedor    = al_load_sample("aud/slimedor.ogg");
    weredor     = al_load_sample("aud/weredor.ogg");
    knightdor   = al_load_sample("aud/knightdor.ogg");

    mus         = al_load_sample("aud/musfundo.ogg");
    musCon      = al_create_sample_instance(mus);

    lutamus     = al_load_sample("aud/lutamus.ogg");
    lutamusCon  = al_create_sample_instance(lutamus);


    al_set_sample_instance_playmode(musCon, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musCon, al_get_default_mixer());

    al_set_sample_instance_playmode(lutamusCon, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(lutamusCon, al_get_default_mixer());



    // REGISTRA OS EVENTOS  ================================================================================
    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_display_event_source(display));

    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_register_event_source(fila, al_get_timer_event_source(timeranim));

//COMECA OS DOIS TIMERS ================================================================================
    al_start_timer(timer);
    al_start_timer(timeranim);

//LOOP "WHILE"================================================================================
    while(!acabou)
    {

        ALLEGRO_EVENT ev;
        al_wait_for_event(fila, &ev);

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                teclas[ESCAPE] = true;
                break;

                case ALLEGRO_KEY_UP:
                teclas[UP] = true;
                break;

                case ALLEGRO_KEY_DOWN:
                teclas[DOWN] = true;
                break;

                case ALLEGRO_KEY_RIGHT:
                teclas[RIGHT] = true;
                knight.dir = 0;
                espada.dir = 0;
                espadadano.dir = 0;
                break;

                case ALLEGRO_KEY_LEFT:
                teclas[LEFT] = true;
                knight.dir = 1;
                espada.dir = 1;
                espadadano.dir = 1;
                break;

                if(knight.vidas>0)
                {
                    case ALLEGRO_KEY_SPACE:
                    teclas[SPACE] = true;
                    if(teclas[SPACE]&&espadadano.usou>=espadadano.cooldown)
                    {espadadano.existe = 1;
                    espadadano.usou=0;
                    al_play_sample(swing,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);}

                    if(espadadano.existe==1&&espadadano.usou<=espadadano.cooldown){espadadano.usou+=1;}
                    if(espadadano.existe==1&&espadadano.usou==espadadano.dura){espadadano.existe=0;}
                    break;
                }

                case ALLEGRO_KEY_E:
                teclas[E] = true;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                teclas[ESCAPE] = false;
                break;
                case ALLEGRO_KEY_UP:
                teclas[UP] = false;
                break;
                case ALLEGRO_KEY_DOWN:
                teclas[DOWN] = false;
                break;
                case ALLEGRO_KEY_RIGHT:
                teclas[RIGHT] = false;
                break;
                case ALLEGRO_KEY_LEFT:
                teclas[LEFT] = false;
                break;
                case ALLEGRO_KEY_SPACE:
                teclas[SPACE] = false;
                break;
                }
        }

//FECHA O JOGO ====================================================================================================-
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){acabou = true;}

// TIMERS ==============================================================================================================
        else if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            //TIMER NORMAL==================================================================================================================
            if(ev.timer.source==timer)
            {
                if(knight.vidas>0){
                knight.y -= teclas[UP]    * knight.vy;
                knight.y += teclas[DOWN]  * knight.vy;

                knight.x -= teclas[LEFT]  * knight.vx;
                knight.x += teclas[RIGHT] * knight.vx;}


                if(!(teclas[RIGHT])&&!(teclas[LEFT])&&!(teclas[UP])&&!(teclas[DOWN])) {knight.curFrame=0;}

                if (knight.y<27)                    {knight.y = 27;}
                if (knight.y>altura-54-knight.tam_y){knight.y = altura-54-knight.tam_y;}
                if (knight.x>largura-21-knight.tam_x) {knight.x = largura-21-knight.tam_x;}
                if (knight.x<20)                    {knight.x = 20;}

                espadadano.x = knight.x+(knight.tam_x/2)+(-80*espada.dir);
                espadadano.y = knight.y+35;
                if(espadadano.existe==1&&espadadano.usou==espadadano.dura){espadadano.existe=0;}

                    //CONTAGENS==========================================================================================================
                    if(estados!=VITORIA){tempototal +=1;}
                    espadadano.usou+=1;
                    werewolf.tdano+=1;
                    slime.tdano+=1;
                    orc.tdano+=1;
                    knight.tdano+=1;

                    if(qtd_derrot==3){cronAnimVitoria+=1;}
                    if(knight.vidas==0){cronAnimDerrota+=1;}

// LOGICA DOS ESTADOS================================================================================================-
            if (estados == MENU)
            {
                    if(teclas[SPACE]){estados = INTRO;}
                    if(teclas[ESCAPE]){acabou = true;}
            }

            if (estados == INTRO)
            {
                    if(teclas[E]){estados = LABIRINTO;}
                    if(teclas[ESCAPE]){acabou = true;}
            }

            else if (estados == LABIRINTO)
            {
                if(teclas[ESCAPE]){acabou = true;}

                al_play_sample_instance(musCon);

                if ((knight.x>=gaiolaOrc.x)&&(knight.x<(gaiolaOrc.x+gaiolaOrc.tam_x))&&((knight.y>gaiolaOrc.y)&&(knight.y+knight.tam_y<gaiolaOrc.y+gaiolaOrc.tam_y))&&((orc.vidas>0)&&(knight.vidas>0)))
                    {
                        estados=ORCLUTA;
                    }

                if ((knight.x>gaiolaSlime.x)&&(knight.x<(gaiolaSlime.x+gaiolaSlime.tam_x))&&(knight.y>gaiolaSlime.y+50)&&((knight.y+knight.tam_y)<(gaiolaSlime.y+gaiolaSlime.tam_y)&&(slime.vidas>0)&&(knight.vidas>0)))
                    {
                    estados=SLIMELUTA;
                    slime.x = 1000;
                    slime.y = 600;
                    }

                if ((knight.x>gaiolaWerewolf.x)&&(knight.x<(gaiolaWerewolf.x+gaiolaWerewolf.tam_x))&&((knight.y)>(gaiolaWerewolf.y))&&(knight.y<gaiolaWerewolf.y+gaiolaWerewolf.tam_y)&&(werewolf.vidas>0)&&(knight.vidas>0))
                    {
                        estados = WEREWOLFLUTA;
                        werewolf.x = 1500;
                        werewolf.y = 800;
                    }

                    colisao(knight.x, knight.y, parede2.x, parede2.y, parede2.tam_x, parede2.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede3.x, parede3.y, parede3.tam_x, parede3.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede4.x, parede4.y, parede4.tam_x, parede4.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede5.x, parede5.y, parede5.tam_x, parede5.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede6.x, parede6.y, parede6.tam_x, parede6.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede7.x, parede7.y, parede7.tam_x, parede7.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede8.x, parede8.y, parede8.tam_x, parede8.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede9.x, parede9.y, parede9.tam_x, parede9.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede10.x, parede10.y, parede10.tam_x, parede10.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede11.x, parede11.y, parede11.tam_x, parede11.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede12.x, parede12.y, parede12.tam_x, parede12.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede13.x, parede13.y, parede13.tam_x, parede13.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede14.x, parede14.y, parede14.tam_x, parede14.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede15.x, parede15.y, parede15.tam_x, parede15.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede16.x, parede16.y, parede16.tam_x, parede16.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede17.x, parede17.y, parede17.tam_x, parede17.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede18.x, parede18.y, parede18.tam_x, parede18.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede19.x, parede19.y, parede19.tam_x, parede19.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede20.x, parede20.y, parede20.tam_x, parede20.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede21.x, parede21.y, parede21.tam_x, parede21.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede22.x, parede22.y, parede22.tam_x, parede22.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede23.x, parede23.y, parede23.tam_x, parede23.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede24.x, parede24.y, parede24.tam_x, parede24.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede25.x, parede25.y, parede25.tam_x, parede25.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede26.x, parede26.y, parede26.tam_x, parede26.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede27.x, parede27.y, parede27.tam_x, parede27.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede28.x, parede28.y, parede28.tam_x, parede28.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede29.x, parede29.y, parede29.tam_x, parede29.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede30.x, parede30.y, parede30.tam_x, parede30.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede31.x, parede31.y, parede31.tam_x, parede31.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede32.x, parede32.y, parede32.tam_x, parede32.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede33.x, parede33.y, parede33.tam_x, parede33.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede34.x, parede34.y, parede34.tam_x, parede34.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede35.x, parede35.y, parede35.tam_x, parede35.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede36.x, parede36.y, parede36.tam_x, parede36.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede37.x, parede37.y, parede37.tam_x, parede37.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede38.x, parede38.y, parede38.tam_x, parede38.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede39.x, parede39.y, parede39.tam_x, parede39.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede40.x, parede40.y, parede40.tam_x, parede40.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede41.x, parede41.y, parede41.tam_x, parede41.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede42.x, parede42.y, parede42.tam_x, parede42.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede43.x, parede43.y, parede43.tam_x, parede43.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede44.x, parede44.y, parede44.tam_x, parede44.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede45.x, parede45.y, parede45.tam_x, parede45.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede46.x, parede46.y, parede46.tam_x, parede46.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede47.x, parede47.y, parede47.tam_x, parede47.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede48.x, parede48.y, parede48.tam_x, parede48.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);
                    colisao(knight.x, knight.y, parede49.x, parede49.y, parede49.tam_x, parede49.tam_y-50, knight.tam_y, knight.tam_x, knight.vx, 0, 0);

            }

//ORC LUTA ==========================================================================================================================================
            else if (estados == ORCLUTA)
            {
                if (orc.vidas>0&&(knight.vidas>0))
                {
                    if (knight.y<gaiolaOrc.y-50)            {knight.y = gaiolaOrc.y-50;}
                    if (knight.y+knight.tam_y>gaiolaOrc.y+gaiolaOrc.tam_y){knight.y = gaiolaOrc.y+gaiolaOrc.tam_y-knight.tam_y;}
                    if (knight.x>gaiolaOrc.x+gaiolaOrc.tam_x-knight.tam_x) {knight.x = gaiolaOrc.x+gaiolaOrc.tam_x-knight.tam_x;}
                    if (knight.x<gaiolaOrc.x)                    {knight.x = gaiolaOrc.x;}
                    movOrc();
                    colisao(knight.x, knight.y, orc.x, orc.y, orc.tam_x, orc.tam_y, knight.tam_y, knight.tam_x, knight.vx, orc.vx, orc.dano);
                        {
                            if( (espadadano.existe==1)                                                                                  &&

                                (((espadadano.x>=orc.x&&espadadano.x<=orc.x+orc.tam_x)                                   ||
                                (espadadano.x+espadadano.tam_x>=orc.x&&espadadano.x+espadadano.tam_x<=orc.x+orc.tam_x))  &&
                                ((espadadano.y>=orc.y&&espadadano.y<=orc.y+orc.tam_y)                                    ||
                                (espadadano.y+espadadano.tam_y>=orc.y&&espadadano.y+espadadano.tam_y<=orc.y+orc.tam_y))) &&

                                (orc.tdano>=orc.invul) )

                                    {
                                    al_play_sample(orcdor,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                                    orc.tdano=0;orc.vidas-=1;
                                    }

                        }
                }
                if (!(orc.vidas>0)){qtd_derrot=1;estados=LABIRINTO;}
            }



            else if (estados == SLIMELUTA)
            {

                    if (knight.y<gaiolaSlime.y-50)            {knight.y = gaiolaSlime.y-50;}
                    if (knight.y+knight.tam_y>gaiolaSlime.y+gaiolaSlime.tam_y){knight.y = gaiolaSlime.y+gaiolaSlime.tam_y-knight.tam_y;}
                    if (knight.x+knight.tam_x>gaiolaSlime.x+gaiolaSlime.tam_x) {knight.x = gaiolaSlime.x+gaiolaSlime.tam_x-knight.tam_x;}
                    if (knight.x<gaiolaSlime.x)                    {knight.x = gaiolaSlime.x;}

                if((slime.vidas>0)&&(knight.vidas>0))
                    {
                        movSlime();

                        colisao(knight.x, knight.y, slime.x, slime.y, slime.tam_x, slime.tam_y, knight.tam_y, knight.tam_x, knight.vx, slime.vx, slime.dano);

                        if( (espadadano.existe==1)                                                                                  &&

                        (((espadadano.x>=slime.x&&espadadano.x<=slime.x+slime.tam_x)                                   ||
                        (espadadano.x+espadadano.tam_x>=slime.x&&espadadano.x+espadadano.tam_x<=slime.x+slime.tam_x))  &&
                        ((espadadano.y>=slime.y&&espadadano.y<=slime.y+slime.tam_y)                                    ||
                        (espadadano.y+espadadano.tam_y>=slime.y&&espadadano.y+espadadano.tam_y<=slime.y+slime.tam_y))) &&

                        (slime.tdano>=slime.invul) )
                            {
                            al_play_sample(slimedor,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                            slime.tdano=0;slime.vidas-=1;
                            }
                    }
                if (!(slime.vidas>0)){qtd_derrot=2;estados=LABIRINTO;}

            }



            else if (estados == WEREWOLFLUTA)
            {
                if (knight.y<gaiolaWerewolf.y-50)            {knight.y = gaiolaWerewolf.y-50;}
                if (knight.y+knight.tam_y>gaiolaWerewolf.y+gaiolaWerewolf.tam_y){knight.y = gaiolaWerewolf.y+gaiolaWerewolf.tam_y-knight.tam_y;}
                if (knight.x>gaiolaWerewolf.x+gaiolaWerewolf.tam_x-knight.tam_x) {knight.x = gaiolaWerewolf.x+gaiolaWerewolf.tam_x-knight.tam_x;}
                if (knight.x<gaiolaWerewolf.x)                    {knight.x = gaiolaWerewolf.x;}

                if(werewolf.vidas>0&&(knight.vidas>0))
                {

                    movWerewolf();
                    if (werewolf.vidas>0){colisao(knight.x, knight.y, werewolf.x, werewolf.y, werewolf.tam_x, werewolf.tam_y, knight.tam_y, knight.tam_x, knight.vx, werewolf.vx, werewolf.dano);}

                    if( (espadadano.existe==1)                                                                                  &&

                        (((espadadano.x>=werewolf.x&&espadadano.x<=werewolf.x+werewolf.tam_x)                                   ||
                        (espadadano.x+espadadano.tam_x>=werewolf.x&&espadadano.x+espadadano.tam_x<=werewolf.x+werewolf.tam_x))  &&
                        ((espadadano.y>=werewolf.y&&espadadano.y<=werewolf.y+werewolf.tam_y)                                    ||
                        (espadadano.y+espadadano.tam_y>=werewolf.y&&espadadano.y+espadadano.tam_y<=werewolf.y+werewolf.tam_y))) &&

                        (werewolf.tdano>=werewolf.invul)  )

                        {
                            al_play_sample(weredor,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                            werewolf.tdano=0;werewolf.vidas-=1;
                        }

                }

                if(werewolf.vidas==0){qtd_derrot = 3;}
                if(cronAnimVitoria==90){estados=VITORIA;}
            }



            else if (estados == DERROTA)
            {
                if(teclas[SPACE]){ reset();estados = LABIRINTO;}
                if(teclas[ESCAPE]){acabou = true;}
            }



            else if (estados == VITORIA)
            {

                if(teclas[SPACE]){reset();estados = LABIRINTO;}
                if(teclas[ESCAPE]){acabou = true;}
            }

            if((estados == ORCLUTA)||(estados == SLIMELUTA)||(estados == WEREWOLFLUTA))
            {
                al_play_sample_instance(lutamusCon);
            }


            if(tomoudano==1){al_play_sample(knightdor,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);tomoudano=0;}
            if(estados != LABIRINTO){al_stop_sample_instance(musCon);}
            if(estados == LABIRINTO){al_stop_sample_instance(lutamusCon);}
            if(knight.vidas <=0){knight.vidas=0;}
            if(cronAnimDerrota >= 90){estados = DERROTA;}

            }
//TIMER DAS ANIMACOES==============================================================================================-
            else if(ev.timer.source==timeranim)
            {
                knight.curFrame+= teclas[DOWN];
                knight.curFrame+= teclas[UP];
                knight.curFrame+= teclas[LEFT];
                knight.curFrame+= teclas[RIGHT];

                if(knight.curFrame>=8){knight.curFrame=0;}

                slime.curFrame+=1;
                if(slime.curFrame>=11){slime.curFrame=0;}

                orc.curFrame+=1;
                if(orc.curFrame>=8){orc.curFrame=0;}

                werewolf.curFrame+=1;
                if(werewolf.curFrame>=8){werewolf.curFrame=0;}

                haloFrame+=1;
                if(haloFrame>=10){haloFrame=0;}
            }






//AQUI FECHA O WHILE LOOP================================================================
    }


//DESENHOS PRA CADA ESTADO
                if (estados == MENU)
                {
                    al_draw_bitmap(menuini,0,0,0);
                }
                if (estados == INTRO)
                {
                    al_draw_bitmap(introd,0,0,0);
                }

                else if (estados == LABIRINTO)
                {
                    al_draw_bitmap (fundo, 0, 0, 0);

                    if (orc.vidas==0)       {al_draw_bitmap(orcderrot,orc.x, orc.y,0);}
                    if (slime.vidas==0)     {al_draw_bitmap(slimederrot,slime.x, slime.y,0);}
                    if (werewolf.vidas==0)  {al_draw_bitmap(werederrot,werewolf.x, werewolf.y,0);}


                    //COBRIR A TELA==========================================================================================================================-
                    cobretela();
                    al_draw_bitmap_region(halo, haloFrame*400, 0, 400, 400, -200+knight.x+(knight.tam_x/2), knight.y+knight.tam_y-200, 0);
                }


                else if (estados == ORCLUTA)
                {
                    al_draw_bitmap_region   (fundo, 373,127,324,324, 373, 127,0);
                    if (orc.vidas>0){al_draw_bitmap_region   (orcimg, 66*orc.curFrame,84*orc.dir,66,84, orc.x, orc.y,0);}
                    al_draw_bitmap(porta,530,132,0);
                    al_draw_bitmap(portalarga,550,403,0);
                }


                else if (estados == SLIMELUTA)
                {
                    al_draw_bitmap_region   (fundo, 672,496,508,339, 672, 496,0);
                    if(slime.vidas>0){al_draw_bitmap_region   (slimeimg, 78*slime.curFrame,76*slime.dir,78,76, slime.x, slime.y,0);}
                    al_draw_bitmap(porta,916,778,0);
                    al_draw_bitmap(porta,1019,778,0);
                }


                else if (estados == WEREWOLFLUTA)
                {
                    al_draw_bitmap_region   (fundo, 1458,351,370,630, 1458, 351,0);
                    al_draw_bitmap(portawere,1643,355,0);

                    if(werewolf.vidas>0){al_draw_bitmap_region   (werewolfimg, 116*werewolf.curFrame,90*werewolf.dir,116,90, werewolf.x, werewolf.y,0);}
                    else{al_draw_bitmap(werederrot,werewolf.x,werewolf.y,0);}
                }

                else if (estados == DERROTA)
                {
                    if(qtd_derrot==0){al_draw_bitmap(perderorc,0,0,0);}
                    if(qtd_derrot==1){al_draw_bitmap(perderslime,0,0,0);}
                    if(werewolf.vidas==1){al_draw_bitmap(quase,0,0,0);}
                    else if(qtd_derrot==2){al_draw_bitmap(perderwere,0,0,0);}
                }


                else if (estados == VITORIA)
                {
                    if(knight.vidas==12){al_draw_bitmap(semdano,0,0,0);}
                    else if(tempototal<=60*60){al_draw_bitmap(segs80,0,0,0);al_draw_textf(fonte2, al_map_rgb(166,166,166), 430, 209, 0, "%i", tempototal/60);
}
                    else {al_draw_bitmap(festeje,0,0,0);}
                }



                if((estados != MENU)&&(estados != INTRO)&&(estados != DERROTA)&&(estados != VITORIA))
                {
                    if(knight.x+(knight.tam_x/2)>680){localvidas = 50;} else{localvidas = largura-50-894;}

                    al_draw_bitmap_region(vidasimg, 0,0,75*knight.vidas, 90,localvidas, 50, 0);

                    //KNIGHT E ESPADAS==========================================================================================================================-
                    if(knight.vidas>0){
                    if(espadadano.existe==0){al_draw_bitmap_region(espadavert,0,70*(espada.dir),14,70,(10+knight.x+knight.tam_x/2 - 40*espada.dir),knight.y-20+knight.curFrame,0);}// espada do fundo
                    al_draw_bitmap_region(knightsprite,54*knight.curFrame,63*knight.dir,54,63,knight.x,knight.y,0);
                    if(espadadano.existe==0){al_draw_bitmap_region(espadavert,0,70*(espada.dir)+50,  14, 20, (10+knight.x+knight.tam_x/2 - 40*espada.dir),  knight.y+30+knight.curFrame,0);} // cabo da espada
                    if(espadadano.existe==1){al_draw_bitmap_region(espadatk, 70*espada.dir, 0, 70, 14, espadadano.x, espadadano.y+knight.curFrame, 0);}}
                    else{al_draw_bitmap(knightderrot,knight.x,knight.y,0);}
                }


    //TEXTOS PRA TESTE==========================================================================================================================
    /*al_draw_textf(fonte, al_map_rgb(255,255,0), 100, 500, 0, "estado: %i", estados);
    al_draw_textf(fonte, al_map_rgb(255,255,0), 100, 550, 0, "cron vitoria: %i", cronAnimVitoria);
    al_draw_textf(fonte, al_map_rgb(255,255,0), 100, 600, 0, "cron derrota: %i", cronAnimDerrota);
    al_draw_textf(fonte, al_map_rgb(255,255,0), 100, 650, 0, "tempo total: %i", tempototal/60);
    al_draw_textf(fonte, al_map_rgb(255,255,0), 100, 700, 0, "tempo total: %i", qtd_derrot);*/


    //FINALIZACAO==========================================================================================================================-
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));
    }

    //DESTROI TUDO QUANDO FECHAR==========================================================================================================


    al_destroy_sample_instance  (lutamusCon);
    al_destroy_sample_instance  (musCon);

    al_destroy_sample           (swing);
    al_destroy_sample           (mus);
    al_destroy_sample           (lutamus);
    al_destroy_sample           (orcdor);
    al_destroy_sample           (slimedor);
    al_destroy_sample           (weredor);
    al_destroy_sample           (knightdor);

    al_destroy_bitmap(introd);
    al_destroy_bitmap(segs80);
    al_destroy_bitmap(menuini);
    al_destroy_bitmap(perderorc);
    al_destroy_bitmap(perderslime);
    al_destroy_bitmap(perderwere);
    al_destroy_bitmap(quase);
    al_destroy_bitmap(festeje);
    al_destroy_bitmap(semdano);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(werewolfimg);
    al_destroy_bitmap(slimeimg);
    al_destroy_bitmap(orcimg);
    al_destroy_bitmap(halo);
    al_destroy_bitmap(knightsprite);
    al_destroy_bitmap(espadavert);
    al_destroy_bitmap(espadatk);
    al_destroy_bitmap(porta);
    al_destroy_bitmap(portalarga);
    al_destroy_bitmap(portawere);
    al_destroy_bitmap(vidasimg);
    al_destroy_bitmap(orcderrot);
    al_destroy_bitmap(slimederrot);
    al_destroy_bitmap(werederrot);
    al_destroy_bitmap(knightderrot);

    al_destroy_display          (display);
    al_destroy_event_queue      (fila);
    al_destroy_timer            (timer);
    al_destroy_timer            (timeranim);

    return 0;
}

//FUNCOES AUXILIARES==========================================================================================================================
void cobretela ()
{
    al_draw_circle          (knight.x+(knight.tam_x/2), knight.y+(knight.tam_y), 750, al_map_rgb(0,0,0), 1150);
    al_draw_filled_rectangle(knight.x+ 600, knight.y -1080, knight.x + 1920, knight.y + 1080, al_map_rgb(0,0,0));
    al_draw_filled_rectangle(knight.x- 1920, knight.y -1080, knight.x - 600, knight.y + 1080, al_map_rgb(0,0,0));
}


//COLISOES DO PERSONAGEM COM OS INIMIGOS E AS PAREDES==================================================================================

void colisao(int playerX, int playerY, int enemyX, int enemyY, int enemyTamX, int enemyTamY, int playerTamY, int playerTamX, int playerV, int enemyV, int enemyDmg)
{
    /*da esquerda*/ if ((((playerY<enemyY+enemyTamY)&&(playerY>enemyY))||((playerY+playerTamY> enemyY)&&(playerY+playerTamY<enemyY+enemyTamY)))&&(playerX+playerTamX>enemyX)&&(playerX+playerTamX<enemyX+10*playerV))
                {
                    knight.x = -10*enemyDmg+ enemyX-playerTamX;
                    if(knight.tdano>=knight.invul){knight.vidas -= enemyDmg;if(enemyDmg>0){tomoudano=1;}}
                    werewolf.x += +5*enemyDmg;
                    slime.x += +5*enemyDmg;
                    orc.x += +5*enemyDmg;
                    if(knight.tdano>=knight.invul){knight.tdano = 0;}

                }

    /*de cima*/     if ((((playerX<enemyX+enemyTamX)&&(playerX>enemyX))||((playerX+playerTamX>enemyX)&&(playerX+playerTamX<enemyX+enemyTamX)))&&(playerY+playerTamY>enemyY)&&(playerY+playerTamY<enemyY+10*playerV))
                {
                    knight.y = -10*enemyDmg+enemyY-playerTamY;
                    if(knight.tdano>=knight.invul){knight.vidas -= enemyDmg;if(enemyDmg>0){tomoudano=1;}}
                    werewolf.y += +5*enemyDmg;
                    slime.y += +5*enemyDmg;
                    orc.y += +5*enemyDmg;
                    if(knight.tdano>=knight.invul){knight.tdano = 0;}

                }
    /*de baixo*/    if ((((playerX<enemyX+enemyTamX)&&(playerX>enemyX))||((playerX+playerTamX>enemyX)&&(playerX+playerTamX<enemyX+enemyTamX)))&&(playerY<enemyY+enemyTamY)&&(playerY>enemyY+enemyTamY-10*playerV))
                {
                    knight.y = +10*enemyDmg + enemyY+enemyTamY;
                    if(knight.tdano>=knight.invul){knight.vidas -= enemyDmg;if(enemyDmg>0){tomoudano=1;}}
                    werewolf.x -= +5*enemyDmg;
                    slime.x -= +5*enemyDmg;
                    orc.x -= +5*enemyDmg;
                    if(knight.tdano>=knight.invul){knight.tdano = 0;}
                }
    /*da direita*/  if ((((playerY<enemyY+enemyTamY)&&(playerY>enemyY))||((playerY+playerTamY>enemyY)&&(playerY+playerTamY<enemyY+enemyTamY)))&&(playerX<enemyX+enemyTamX)&&(playerX>enemyX+enemyTamX-10*playerV))
                {
                    knight.x = +10*enemyDmg+enemyX+enemyTamX;
                    if(knight.tdano>=knight.invul){knight.vidas -= enemyDmg;if(enemyDmg>0){tomoudano=1;}}
                    werewolf.x -= +5*enemyDmg;
                    slime.x -= +5*enemyDmg;
                    orc.x -= +5*enemyDmg;
                    if(knight.tdano>=knight.invul){knight.tdano = 0;}
                }
}

//MOVIMENTAR O LOBISOMEM==========================================================================================================================
void movWerewolf()
{
    if( (((knight.y<=gaiolaWerewolf.y+gaiolaWerewolf.tam_y)&&(knight.y>=gaiolaWerewolf.y))||((knight.y+knight.tam_y>= gaiolaWerewolf.y)&&(knight.y+knight.tam_y<=gaiolaWerewolf.y+gaiolaWerewolf.tam_y)))
        &&
        (((knight.x<=gaiolaWerewolf.x+gaiolaWerewolf.tam_x)&&(knight.x>=gaiolaWerewolf.x))||((knight.x+knight.tam_x>= gaiolaWerewolf.x)&&(knight.x+knight.tam_x<=gaiolaWerewolf.x+gaiolaWerewolf.tam_x))) &&(werewolf.vidas>0) )
    {
        if(knight.x>werewolf.x+werewolf.tam_x/2){werewolf.dir=0;}
        if(knight.x<werewolf.x+werewolf.tam_x/2){werewolf.dir=1;}

        if (knight.x+(knight.tam_x/2.0)<werewolf.x+(werewolf.tam_x/2)){werewolf.x-=werewolf.vx; werewolf.dir=0;}
        if (knight.x+(knight.tam_x/2.0)>werewolf.x+(werewolf.tam_x/2)){werewolf.x+=werewolf.vx; werewolf.dir=1;}
        if (knight.y+(knight.tam_y/3.0)<werewolf.y+(werewolf.tam_y/2)){werewolf.y-=werewolf.vy;}
        if (knight.y+(knight.tam_y/3.0)>werewolf.y+(werewolf.tam_y/2)){werewolf.y+=werewolf.vy;}
    }
}

//MOVIMENTAR O SLIME==========================================================================================================================
void movSlime()
{
     if( (((knight.y<=gaiolaSlime.y+gaiolaSlime.tam_y)&&(knight.y>=gaiolaSlime.y))||((knight.y+knight.tam_y>= gaiolaSlime.y)&&(knight.y+knight.tam_y<=gaiolaSlime.y+gaiolaSlime.tam_y)))
        &&
        (((knight.x<=gaiolaSlime.x+gaiolaSlime.tam_x)&&(knight.x>=gaiolaSlime.x))||((knight.x+knight.tam_x>= gaiolaSlime.x)&&(knight.x+knight.tam_x<=gaiolaSlime.x+gaiolaSlime.tam_x))) &&(slime.vidas>0) )
    {
        if(knight.x>slime.x+slime.tam_x/2){slime.dir=0;}
        if(knight.x<slime.x+slime.tam_x/2){slime.dir=1;}

        if (knight.x+(knight.tam_x/2.0)<slime.x+(slime.tam_x/2)){slime.x-=slime.vx; slime.dir=1;}
        if (knight.x+(knight.tam_x/2.0)>slime.x+(slime.tam_x/2)){slime.x+=slime.vx; slime.dir=0;}
        if (knight.y+(knight.tam_y/3.0)<slime.y+(slime.tam_y/2)){slime.y-=slime.vy;}
        if (knight.y+(knight.tam_y/3.0)>slime.y+(slime.tam_y/2)){slime.y+=slime.vy;}
    }
}


//MOVIMENTAR O ORC==========================================================================================================================
void movOrc()
{
    if( (((knight.y<=gaiolaOrc.y+gaiolaOrc.tam_y)&&(knight.y>=gaiolaOrc.y))||((knight.y+knight.tam_y>= gaiolaOrc.y)&&(knight.y+knight.tam_y<=gaiolaOrc.y+gaiolaOrc.tam_y)))
        &&
        (((knight.x<=gaiolaOrc.x+gaiolaOrc.tam_x)&&(knight.x>=gaiolaOrc.x))||((knight.x+knight.tam_x>= gaiolaOrc.x)&&(knight.x+knight.tam_x<=gaiolaOrc.x+gaiolaOrc.tam_x))) &&(orc.vidas>0)  )
    {
        if(knight.x>orc.x+orc.tam_x/2){orc.dir=0;}
        if(knight.x<orc.x+orc.tam_x/2){orc.dir=1;}

        if (knight.x+(knight.tam_x/2.0)<orc.x+(orc.tam_x/2)){orc.x-=orc.vx; orc.dir=1;}
        if (knight.x+(knight.tam_x/2.0)>orc.x+(orc.tam_x/2)){orc.x+=orc.vx; orc.dir=0;}
        if (knight.y+(knight.tam_y/3.0)<orc.y+(orc.tam_y/2)){orc.y-=orc.vy;}
        if (knight.y+(knight.tam_y/3.0)>orc.y+(orc.tam_y/2)){orc.y+=orc.vy;}

    }
}

void reset()
{
    knight.vidas    = 12;
    knight.x        = 100;
    knight.y        = 900;
    werewolf.x      = 1687;
    werewolf.y      = 828;
    werewolf.vidas  = 4;
    slime.x         = 1082;
    slime.y         = 563;
    slime.vidas     = 3;
    orc.x           = 402;
    orc.y           = 316;
    orc.vidas       = 4;
    qtd_derrot      = 0;
    cronAnimDerrota = 0;
    cronAnimVitoria = 0;
    tempototal      = 0;
}
