
#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "src/lineutils.h"
#include <kelib.h>
#include "src/map/lexer.c"


int VIEW_DISTANCE=100;

i32 SCREEN_HEIGTH=800;
i32 SCREEN_WIDTH=800;





//also do world to screen for the minimap so we can have it as hud element maybe
//or other hud elements

//collision




//angle is in radians
typedef struct Player{
    double x;
    double y;
    float angle;
}Player;





//
void movePlayerForward(Player* player,float amount){
    //W and S keys
    player->x= player->x+cosf(player->angle*DEG2RAD)*amount;
    player->y= player->y+sinf(player->angle*DEG2RAD)*amount;

}



//
void movePlayerSideways(Player* player,float amount){
    //A and D keys
    player->x= player->x+cosf((player->angle+90)*DEG2RAD)*amount;
    player->y= player->y+sinf((player->angle+90)*DEG2RAD)*amount;
}




//render topdown
//curretly does not render whole map
int renderMinimap(Player player,MapData *map){
    DrawCircle(player.x, player.y, 9.0f, RED);
    for (u32 line_i=0; line_i < map->line_count; line_i++) {
        Line l = map->lines[line_i];
        DrawLine(l.a.x, l.a.y, l.b.x, l.b.y, BLACK);
    }
    return 0;
}



void draw_vert_line(int x,int len){
    i32 screen_heigth=800;
    i32 screen_width=800;
    DrawLine( 
            x,
            - len / 2+screen_heigth/2,
            x,
             len / 2+screen_heigth/2,
            RED
    );
}



//another try at the same thing
void draw_fp(Player player, MapData* map){
    //unit  vector direction
    float nx= cosf(player.angle*DEG2RAD);
    float ny= sinf(player.angle*DEG2RAD);

    //plane aka 90deg offset from playerangle
    //needed to get raydir
    float px= cosf((player.angle+90)*DEG2RAD);
    float py= sinf((player.angle+90)*DEG2RAD);

    //all pixels in screen w
    for (int x=0; x<GetScreenWidth();x++){
        float normalized= 2*x/(float)800 -1;

        float raydirx= nx+px*normalized;
        float raydiry= ny+py*normalized;

        float raylen=VIEW_DISTANCE*10;

        float endrayx=raydirx*raylen;
        float endrayy=raydiry*raylen;


        //DrawLine(player.x, player.y, player.x+endrayx, player.y+endrayy, GREEN);

        Line pline={
            .a={
                .x=player.x,
                .y=player.y
            },
            .b={
                .x=player.x+endrayx,
                .y=player.y+endrayy
            }
        };

        //float smallest_len

        //loop all lines
        for (u32 line_i=0; line_i<map->line_count; line_i++) {
        
            Vector2 *collopoint= lineSegmentIntersection(pline, map->lines[line_i]);
            if(collopoint){
                //DrawCircle(collopoint->x, collopoint->y, 9.0f, GREEN);
                float hypotenuse = distanceBetweenPoints(pline.a, *collopoint);

                //remove fish eye
                //cosine of delta rayangle, playerange
                float rayangle=atan2f(raydiry,raydirx);
                float ca=(player.angle*DEG2RAD)-rayangle;
                hypotenuse=hypotenuse*cosf(ca);

                //TODO draw smallest len line only
                draw_vert_line(x, SCREEN_HEIGTH/hypotenuse);
                free(collopoint);
            }
        }
    }
}







int main(){

    Line testline;
    Vector2 a ={100,130};
    Vector2 b ={500,530};
    testline.a= a;
    testline.b= b;

    MapData* tmap=load_map("./maps/testmap");


    

    //this is placeholder for the entire map 


    int WindowWidth=800;
    int WindowHeight=800;

    InitWindow(WindowWidth, WindowHeight, "raycast");

    Player player;
    player.angle=0.0f;
    player.y=WindowHeight/2.f;
    player.x=WindowWidth/2.f;
    


    while(!WindowShouldClose()){
        //input input can use somewhat same method as the input in rpg if i know how to use some map in C
        //
        float frametime=GetFrameTime();

        float movement_s=50.f*frametime;
        float rotate_s=100.f*frametime;

        int key=GetKeyPressed();

        //do propper input handle

        if (IsKeyDown(KEY_A)) {
            movePlayerSideways(&player, -movement_s);
        }

        if (IsKeyDown(KEY_D)) {
            movePlayerSideways(&player, movement_s);
        }

        if (IsKeyDown(KEY_W)) {
            movePlayerForward(&player, movement_s);
        }

        if (IsKeyDown(KEY_S)) {
            movePlayerForward(&player, -movement_s);
        }

        if (IsKeyDown(KEY_J)) {
            player.angle-=rotate_s;
        }

        if (IsKeyDown(KEY_K)) {
            player.angle+=rotate_s;
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_fp(player,tmap);
        renderMinimap(player, tmap);


        EndDrawing();
    }


    CloseWindow();
    return 0;
}





