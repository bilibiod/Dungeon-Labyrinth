// OBJETOS ////////////////////////////////
struct PLAYER{int   x,
                    y,
                    vidas,
                    vx,
                    vy,
                    tam_x,
                    tam_y,

                    dir,
                    curFrame,
                    invul,
                    tdano;};
struct PLAYER knight = {100, 900, 12, 3,4, 48, 62, 0, 45, 90};



struct ENEMY          {int    x,       y,       vidas, vx,vy,  tam_x, tam_y,   dano,  dir, curFrame, invul, tdano;};

struct ENEMY werewolf   = {1500,     800,     4,     1,2,  110,    80,      2,      1,  0, 60, 60};
struct ENEMY slime      = {1000,    600,     3,     2,2,  65,     70,      1,      1,  0, 60, 60};
struct ENEMY orc        = {410,    300,     4,     1,1,  60,     80,      3,      1,  0, 60, 60};



struct PAREDES              {int x,y,tam_x,tam_y;};

struct PAREDES parede2  = {0,0,1920,67 }; // todo o topo da tela
struct PAREDES parede3  = {0,0,51,836};
struct PAREDES parede4  = {0,688,150,148};
struct PAREDES parede5  = {123,520,34,316};
struct PAREDES parede6  = {138,187,164,126};
struct PAREDES parede7  = {128,187,46,278};
struct PAREDES parede8  = {224,0,78,313};
struct PAREDES parede9  = {229,520,69,316};
struct PAREDES parede10 = {0,1012,280,68};
struct PAREDES parede11 = {239,700,220,73};
struct PAREDES parede12 = {269,520,29,600};
struct PAREDES parede13 = {229,820,315,67};
struct PAREDES parede14 = {363,519,100,73};
struct PAREDES parede15 = {434,519,29,253};
struct PAREDES parede16 = {273,349,119,123};
struct PAREDES parede17 = {263,399,281,73};
struct PAREDES parede18 = {379,99,155,96};
struct PAREDES parede19 = {369,99,33,373};
struct PAREDES parede20 = {597,0,33,181};
struct PAREDES parede21 = {607,127,94,68};
struct PAREDES parede22 = {668,118,33,328};
struct PAREDES parede23 = {678,346,506,105};
struct PAREDES parede24 = {794,241,194,68};
struct PAREDES parede25 = {784,0,33,309};
struct PAREDES parede26 = {898,112,286,88};
struct PAREDES parede27 = {1155,112,33,717};
struct PAREDES parede28 = {668,496,499,67};
struct PAREDES parede29 = {668,496,33,300};
struct PAREDES parede30 = {529,399,24,488};
struct PAREDES parede31 = {371,920,132,64};
struct PAREDES parede32 = {616,890,33,190};
struct PAREDES parede33 = {616,885,394,99};
struct PAREDES parede34 = {987,767,33,217};
struct PAREDES parede35 = {668,767,249,73};
struct PAREDES parede36 = {1089,777,33,128};
struct PAREDES parede37 = {1089,767,95,72};
struct PAREDES parede38 = {1161,561,138,72};
struct PAREDES parede39 = {1253,670,130,72};
struct PAREDES parede40 = {1155,440,228,72};
struct PAREDES parede41 = {1364,357,29,385};
struct PAREDES parede42 = {1364,347,279,72};
struct PAREDES parede43 = {1458,347,29,630};
struct PAREDES parede44 = {1258,803,229,72};
struct PAREDES parede45 = {1208,918,624,67};
struct PAREDES parede46 = {1803,127,29,858};
struct PAREDES parede47 = {1735,346,97,73};
struct PAREDES parede48 = {1267,117,565,170};
struct PAREDES parede49 = {1267,127,33,238};



struct GAIOLAS                    {int x,    y,   tam_x, tam_y;};

struct GAIOLAS gaiolaWerewolf       = {1487,  419, 316,   499};
struct GAIOLAS gaiolaSlime          = {701,  563, 450,   204};
struct GAIOLAS gaiolaOrc            = {390, 195, 280,   204};



struct ATK{int              x,     y,    tam_x,  tam_y,  dura,   cooldown,   usou,   existe, dir;};

struct ATK espada =         {160,   900,     14,     70,    0};
struct ATK espadadano =     {160,   900,     70,     14,    30,     45,        180,    0,   0};
