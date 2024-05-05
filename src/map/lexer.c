


#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../lineutils.h"
#include <kelib.h>


//reads map file 
// tokenises and gives us some data structure that contains the map itself
//
// map is stored in a plaintext file
// formatted like such
//
//
// points:
// n,n
// n,n
// n,n
// n,n;
// lines:
// p,p
// p,p
// p,p
// p,p;

// if third point that means it is bezier curve, where the third is the thing they curve around
//
// n in points is the cords of the point in world space




//clean this file


struct FileData{
    Vector2* points;
    u32 point_count;
    Vector2* lines;
    u32 line_count;
};


typedef struct MapData{
    Line* lines;
    u8 line_count;
}MapData;


struct FileData lex_file(FILE* file);





//loads map and returns mapdata struct.
//mapdata is stored on the heap.
MapData* load_map(const char* filepath){

    // if can open file
    // open file
    FILE* f=fopen(filepath,"r");

    if(!f){
        panic("cannot open file\n", 1);
    }

    struct FileData file_data=lex_file(f);


    Line *lines =malloc(sizeof(struct Line)*file_data.line_count);

    //make lines from lines and point data
    
    //loop linecount
    for (u32 line_index=0;line_index<file_data.line_count;line_index++){
        //get first point index
        u8 point_index_x=file_data.lines[line_index].x;
        u8 point_index_y=file_data.lines[line_index].y;
        
        lines[line_index].a=file_data.points[point_index_x];
        lines[line_index].b=file_data.points[point_index_y];

    }


    MapData* map = malloc(sizeof(struct MapData));
    map->lines=lines;
    map->line_count=file_data.line_count;

    //free used mem
    free(file_data.lines);
    free(file_data.points);


    return map;
}


u32 char_b_to_num(const char buffer[10],const u8 buffer_size){
    u32 num=0;

    u32 current_mul=1;

    for (int i=buffer_size; i>=0; i--) {
            if (buffer[i]>='0' && buffer[i]<='9'){
                num += (buffer[i]-0x30)*current_mul;
                current_mul*=10;
            }
        }


    return num;
}


//returns a 64 size array of vec2
//takes in the file and the start point that we start reading the file from
//vector is on the heap 
Vector2* get_touple_from_file(FILE* file,u32 start, u32* v_size){
    printf("start read touple\n");
    //needs debugging since no workka
    Vector2* retvec= malloc(sizeof(struct Vector2)*64);
    u32 vector_index=0;

    //char current_character=fgetc(file);
    // this should be \n

    //loop
    

    char num_buffer[10]={0};
    u8 numbuffer_size=0;

    u8 is_x=1;

    for(;;){
        // TODO this loop needs to be rewritten

        char current_character=fgetc(file);
        printf("c:%c\n",current_character);
        //number or bad char

        //clean this ifelse mess


        if(current_character<='9' && current_character>='0'){
            // place num into buffer 
            num_buffer[numbuffer_size++]=current_character;

        //read into buffer untill we hit ,
        }else if(current_character==',' || current_character=='\n'){
            //get number from the numbuffer

            u32 number =char_b_to_num(num_buffer,numbuffer_size);
            if(is_x){
                retvec[vector_index].x=number;
                is_x=0;
            }else{
                retvec[vector_index++].y=number;
                //fgetc(file);//should be \n
                is_x=1;
            }

            numbuffer_size=0;

        } else{
            if(current_character=='\n'){
                vector_index++;
                current_character=fgetc(file); //read another char
                continue;
            }
            //is not a number meaning we need to break from function
            //could be l or eof
            break;
        }



    }
    
    *v_size=vector_index;

    return retvec;
}



//rename function it is not lexer it is parser aswell
struct FileData lex_file(FILE* file){

    //read file
    //parse them into some data
    //array vec2 points array vec2 lines

    //currenttly only 64 points 


    //position in file
    u32 pos=0;

    char strbuffer[32]={0};
    u8 strsize=0;// size of current string in buffer



    char character=fgetc(file);
    pos++;

    //first should be "points:"
    //should be written differently
    while(character>'a' && character<'z'){
        strbuffer[strsize++]=character;
        character=fgetc(file);
        pos++;
    }
    strsize=0;

    //ends when we hit ':'
    character=fgetc(file);
    pos++;
    u32 poinsize=0;
    Vector2 *points=get_touple_from_file(file, pos,&poinsize);

    character=fgetc(file);
    //seek untill we find :
    //should be written differently
    while(character>'a' && character<'z'){
        strbuffer[strsize++]=character;
        character=fgetc(file);
        pos++;
    }
    strsize=0;

    character=fgetc(file);
    pos++;
    u32 linesize=0;
    Vector2 *lines=get_touple_from_file(file, pos,&linesize);
    //read point to pointliset

    //read line into line list

    struct FileData ret={
        .points=points,
        .point_count=poinsize,
        .lines=lines,
        .line_count=linesize,
    };

    return ret;
}









