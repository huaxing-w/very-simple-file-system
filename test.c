#include <stdio.h>
#include <stdlib.h>
#include "fs.h"

int main()
{
    create_fs();
    sync_fs();

    // mount_fs();
    int fileNum=allocate_file("hello");
    set_file_size(fileNum, 5000);
    char s[] = "Yeah You are my fire The one desire Believe when I say I want it that way But we are two worlds apart Cant reach to your heart When you say That I want it that way Tell me why Aint nothin but a heartache Tell me why Aint nothin but a mistake Tell me why I never wanna hear you say I want it that way Am I your fire? Your one desire Yes, I know its too late But I want it that way Tell me why Aint nothin but a heartache Tell me why Aint nothin but a mistake Tell me why I never wanna hear you say I want it that way Now I can see that we've fallen apart From the way that it used to be, yeah No matter the distance, I want you to know That deep down inside of me You are my fire The one desire You are (you are, you are, you are) Dont wanna hear you say Aint nothin' but a heartache Aint nothin' but a mistake (don't wanna hear you say) I never wanna hear you say (oh, yeah) I want it that way Tell me why Aint nothin but a heartache Tell me why Aint nothin but a mistake Tell me why I never wanna hear you say (dont wanna hear you say) I want it that way Tell me why Aint nothin but a heartache Aint nothin but a mistake Tell me why I never wanna hear you say (dont wanna hear you say) I want it that way Cause I want it that way";
    write_data_to_file(fileNum,0,&s[0]);
    sync_fs();

    print_fs();
    read_file("hello");
    

    

    int fileNum2=allocate_file("myhear");
    
    set_file_size(fileNum2, 5000);
    char t[] = "Every night in my dreamsI see you, I feel youThat is how I know you go onFar across the distanceAnd spaces between usYou have come to show you go onNear, far, wherever you areI believe that the heart does go onOnce more, you open the doorAnd you're here in my heartAnd my heart will go on and onLove can touch us one timeAnd last for a lifetimeAnd never let go 'til we're goneLove was when I loved youOne true time I'd hold toIn my life, we'll always go onNear, far, wherever you areI believe that the heart does go on (why does the heart go on?)Once more, you open the doorAnd you're here in my heartAnd my heart will go on and onYou're here, there's nothing I fearAnd I know that my heart will go onWe'll stay forever this wayYou are safe in my heart andMy heart will go on and on";
    write_data_to_file(fileNum2,0,&t[0]);
    sync_fs();
    
    print_fs();
    read_file("myhear");
    read_file("hello");

    printf("done\n");

    return 0;
}