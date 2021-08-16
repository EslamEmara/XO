#include <stdio.h>
#include <Windows.h>
#include <ctype.h>

#define P1 1          //player 1 plays with x
#define P2 2          //player 2 plays with o

char matrix[3][3] = {{'\0','\0','\0'},{'\0','\0','\0'},{'\0','\0','\0'}};     //global matrix defines all positions
COORD coord= {0,0};     //cursor cordinates


/*
function to set the poition of the console cursor by line
  */
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
/*
function checks for draw condition in the matrix

return: 1   in draw condition , 0 otherwise
*/
int check_for_draw()
{
  for (int i =0;i<3;i++)
  {
      for (int j=0 ; j<3 ; j++)
      {
          if (matrix[i][j] == '\0')           // if there are empty elements return 0
              return 0;
      }
  }
  return 1;     // return 1 if all elements are occupied
}

/*
function to check for win conditions

return: 'x' or 'o' in win conditions and 'n' otherwise
*/
char check_for_win()
{
  for (int i=0;i<3;i++)
  {
      if (matrix[i][0] == matrix[i][1]&&matrix[i][0] == matrix[i][2]&&matrix[i][0] != '\0') //row
          return matrix[i][0];
      if (matrix[0][i] == matrix[1][i]&&matrix[0][i] == matrix[2][i]&&matrix[0][i]!='\0') //column
          return matrix[0][i];
  }
      if (matrix[0][0]==matrix[1][1]&&matrix[0][0]==matrix[2][2]&&matrix[0][0]!='\0') //main diagonal
          return matrix[0][0];
      if (matrix[0][2]==matrix[1][1]&&matrix[0][2]==matrix[2][0]&&matrix[0][2]!='\0') //other diagonal
          return matrix[1][1];
 return 'n';
}

/*
function to draw the matrix
*/
void draw_layout_matrix()
{
  gotoxy(0,8);        // go to line 8
  for(int i=0; i<3; i++) {
       for(int j=0;j<3;j++) {
             if (j ==2){              //dont draw vertical line in the last element
                printf("%c", matrix[i][j]);
             }
             else
                printf("%c\t|\t", matrix[i][j]);
             }
      printf("\n----------------------------------\n");
       }
}

/*
gets the position from the user and checks if it's valid

return: integer represents valid input from user
*/
int getValueUsr()
{
  int play_pos = 0;
  while (1)
  {
    printf("Enter position from 1-9: ");
    fflush(stdin);
    scanf("%d",&play_pos);
    if (play_pos > 9 || play_pos < 1){
        printf("Enter a valid value!\n");
        gotoxy(25,0);
        printf("                             ");  // clear last input from screen
        gotoxy(0,0);
        continue;
    }
    else{
      gotoxy(25,0);
      printf("                             ");
      gotoxy(0,1);
      printf("                             ");  //clear warning msgs in case of validity
      gotoxy(0,1);
        play_pos-=1;                // match it with array index
        break;
    }
  }
  return play_pos;
}

/*
function to put the desired value position mapped in the matrix
return : return 0 if the position is taken , 1 otherwise
*/
int putPosInMatrix(char chr,int play_pos)
{
  if (play_pos / 3 == 0){               //position in first row
      if (matrix[0][play_pos] == '\0')    // check for repetancy
          matrix[0][play_pos] = chr;
      else{
        return 0;
    }
  }
  else if (play_pos / 3 == 1)         //second row
  {
      if (matrix[1][play_pos-3] == '\0')
          matrix[1][play_pos-3] = chr;
      else{
        return 0;
      }

  }
  else if (play_pos / 3 == 2)       //third row
  {
      if (matrix[2][play_pos-6] == '\0')
          matrix[2][play_pos-6] = chr;
      else{
        return 0;
    }
 }
 return 1;
}


int main()
{
    int play_pos = 0;
    int player_turn = P1;
    int playAgain = 0;
  while (1)
  {
    draw_layout_matrix();
      while (1)
      {
        gotoxy(0,0);
        play_pos = getValueUsr();
        if (player_turn == P1)
        {
            if (!putPosInMatrix('x',play_pos))
            {
              printf("Already Chosen!\n");
              continue;
            }

            player_turn = P2;
        }
        else if (player_turn == P2)
        {
            if (!putPosInMatrix('o',play_pos))
            {
              printf("Already Chosen!\n");
              continue;
            }
            player_turn = P1;
        }

       draw_layout_matrix();

       if(check_for_win() == 'x')
       {
         printf("\t\nP1 winss!\n") ;
         break;
       }
       else if(check_for_win() == 'o')
       {
         printf("\t\nP2 winss!\n") ;
         break;
       }
       if(check_for_draw())
       {
         printf("\t\nDraw!\n");
        break;
       }
      }

    printf ("Play Again (Y/N) ? ");
    fflush(stdin);
    scanf("%c",&playAgain);

    if (toupper(playAgain) == 'Y')
    {
      player_turn = P1;           //begin with player 1
      for(int i=0; i<3; i++) {    // reset position matrix to nulls
           for(int j=0;j<3;j++) {
             matrix[i][j]='\0';
            }
         }
         gotoxy(0,15);
         printf("              \n                          ");  //clear win msgs
    }
    else
      break;
  }

    return 0;
}
