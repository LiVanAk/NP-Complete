#include"npc.h"
#include"graph.h"

int main(){
    int index;
    printHint();
    while(scanf("%d",&index)!=EOF){
        switch (index)
        {
        case 0:
            printf("Exit...\n");
            exit(0);
            break;
        case 1:
            npc1();
            break;
        case 3:
            npc3();
            break;
        case 4:
            npc4();
            break;
        case 5:
            npc5();
            break;
        case 9:
            npc9();
            break;
        case 10:
            npc10();
            break;
        case 12:
            npc12();
            break;
        case 13:
            npc13();
            break;
        case 18:
            npc18();
            break;
        default:
            printHint();
            break;
        }
    }
    return 0;
}
