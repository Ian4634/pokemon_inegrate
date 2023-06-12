#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <my_headers/main.h> // sdl functions
#include <my_headers/variables.h> // definitions of windows, etc. 


#define PASSWORD_SIZE 50
#define FILENAME "login_data.txt"

static void showOptions();

static void register_user(const char *username, const char *password) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Fail to read the data\n");
        exit(1);
    }
    
    fprintf(file, "%s %s 100 0 0\n", username, password);
    fclose(file);
}

static int login(const char *username, const char *password) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Fail to read the data\n");
        exit(1);
    }

    char stored_username[USERNAME_SIZE];
    char stored_password[PASSWORD_SIZE];
    char buffer[300];
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
        fgets(buffer, 300, file);
        if (strcmp(username, stored_username) == 0 &&
            strcmp(password, stored_password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}


char *login_main() {
    
    char password[PASSWORD_SIZE];
    int cmd=299;
    printf("login started\n");
    //showOptions();
    while(cmd != 0 ){
		printf("CMD Mode... <-<< Status:Reading >>-> :");
        scanf("%d",&cmd);
       //scanf("%d",&switchline);
        printf("cmd[%d]\n",cmd);
        if(cmd==1){
	  	  printf("Registration:\nUsername:");
    	  scanf("%s", username);
          printf("Password:");
          scanf("%s", password);
          register_user(username, password);
          printf("Registration complete\n");
		}else if(cmd==2){
    	  printf("Login:\nUsername:");
          scanf("%s", username);
          printf("Password:");
          scanf("%s", password);
          if (login(username, password)) {
          	printf("Sign in suceesfully!\n");
            return username;
    	  } else {
        	printf("Failed to log in!\nPlease check the Username&Password again.\n");
    	  }
		}else{
	  		printf("wrong cmd!!\n");
		}
	}
	return NULL;
}

/* Ian's code */

static void showOptions(){
    printf("inside showOption\n");
    static SDL_Rect textRect1 = {.x = 100, .y = SCREEN_HEIGHT/2-50, .w = 25, .h = 35}; 
    static SDL_Rect textRect2 = {.x = 100, .y = SCREEN_HEIGHT/2-100, .w = 400, .h = 30};
    static SDL_Rect textRect3 = {.x = 100, .y = SCREEN_HEIGHT/2, .w = 400, .h = 30};

    SDL_Color color = {255, 0, 255};
    SDL_Texture *text1 = SDL_CreateTextureFromSurface(getRenderer(), TTF_RenderText_Solid(getFont(), "A",color));
    SDL_Texture *text2 = SDL_CreateTextureFromSurface(getRenderer(), TTF_RenderText_Solid(getFont(), "2 for login",color));
    SDL_Texture *text3 = SDL_CreateTextureFromSurface(getRenderer(), TTF_RenderText_Solid(getFont(), "0 end the register&login system",color));

    SDL_RenderClear(getRenderer());
    SDL_RenderCopy(getRenderer(), text1, NULL, &textRect1);
    SDL_RenderCopy(getRenderer(), text2, NULL, &textRect2);
    SDL_RenderCopy(getRenderer(), text3, NULL, &textRect3);
    SDL_RenderPresent(getRenderer());
    if(getFont() == NULL) printf("font not load\n");
    if(getRenderer() == NULL) printf("renderer not get\n");
    if(&textRect1 == NULL) printf("textRect is null\n");

    SDL_Delay(5000);
}
