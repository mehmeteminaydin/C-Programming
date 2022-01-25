#include<stdio.h>
#define max_width 25
#define max_height 25

void fill(int arr[][max_width], int color, int row, int col, int original_color){
      /*color that point*/
      if (arr[row][col] == original_color){
         arr[row][col] = color;
      if (row !=0 && col != 0){
         if ((arr[row-1][col-1]) != color){
            fill(arr, color, row-1, col-1, original_color);
         }
      }
      if (row != 0){
         if (arr[row-1][col] != color){
            fill(arr, color, row-1, col, original_color);
         }
      }
      if (row != 0 && col<max_width-1){
         if (arr[row-1][col+1] != color){
            fill(arr, color, row-1, col+1, original_color);
         }
      }
      if (col<max_width-1){
         if (arr[row][col+1] != color){
            fill(arr, color, row, col+1, original_color);
         }
      }
      if (col<max_width-1 && row<max_height-1){
         if (arr[row+1][col+1] != color){
            fill(arr, color, row+1,col+1, original_color);
         }
      }
      if (row<max_height-1){
         if (arr[row+1][col] != color){
            fill(arr, color, row+1, col, original_color);
         }
      }
      if (col != 0 && row<max_height-1){
         if (arr[row+1][col-1] != color){
            fill(arr, color, row+1, col-1, original_color);
         }
      }
      if (col != 0){
         if (arr[row][col-1] != color){
            fill(arr, color, row, col-1, original_color);
         }
      }
   }
}

int main(){

   int disp[max_height][max_width];
   char operator, direction;
   int i, j, row , col, color, row1, col1, original_color;
   int row_c1, col_c1, row_c2, col_c2, row_p1, col_p1, row_p2, col_p2;
   int top_left_row_c, top_left_col_c, bottom_right_row_c, bottom_right_col_c;
   int top_left_row_p, top_left_col_p, bottom_right_row_p, bottom_right_col_p;
   int count = 0, degree;
   for(i=0; i<max_width; i++) {
      for(j=0;j<max_height;j++) {
         scanf("%d", &disp[i][j]);
      }
   }
   scanf(" %c", &operator);
   switch (operator)
   {
   case 'F':
      scanf(" %d %d",&row,&col);
      
      /*Defining the color*/

      if (row<0 && col<0){
         color = 0;
      }
      else if (col>=0 && col<=max_width-1 && row<0){
         color = 1;
      }
      else if (col>=max_width && row<0){
         color = 2;
      }
      else if (row>=0 && row<=max_height-1 && col>max_width-1){
         color = 3;
      }
      else if (row>max_height-1 && col>max_width-1){
         color = 4;
      }
      else if (col>=0 && col<=max_width-1 && row>max_height-1){
         color = 5;
      }
      else if (col<0 && row>max_height-1){
         color = 6;
      }
      else if (row>=0 && row<max_height && col<0){
         color = 7;
      }
      else{
         color = disp[row][col];
      }
      /*Determining the coordinate which is wanted to be colored*/

      scanf(" %d %d", &row1,&col1);
      original_color = disp[row1][col1];
      fill(disp, color, row1, col1, original_color);
      /*Printing the output*/
      for(i=0; i<max_width; i++) {
         for(j=0;j<max_height;j++) {
            printf("%d ", disp[i][j]);
            if(j==max_height-1){
               printf("\n");
            }
         }
      }
      break;
   case 'P':
      scanf(" %d %d %d %d %d %d %d %d",&row_c1,&col_c1,&row_c2,&col_c2,&row_p1,&col_p1,&row_p2,&col_p2);
      /* arranging the area points where I copy */
      if (row_c1 <= row_c2){
         top_left_row_c = row_c1;
      }
      else if (row_c1 > row_c2){
         top_left_row_c = row_c2;
      }
      if (col_c1 <= col_c2){
         top_left_col_c = col_c1;
      }
      else if (col_c1 > col_c2){
         top_left_col_c = col_c2;
      }
      /* arranging the area points where I past */
      if (row_p1 <= row_p2){
         top_left_row_p = row_p1;
         bottom_right_row_p = row_p2;
      }
      else if (row_p1 > row_p2){
         top_left_row_p = row_p2;
         bottom_right_row_p = row_p1;
      }
      if (col_p1 <= col_p2){
         top_left_col_p = col_p1;
         bottom_right_col_p = col_p2;
      }
      else if (col_p1 > col_p2){
         top_left_col_p = col_p2;
         bottom_right_col_p = col_p1;
      }
      for(i=0; i<=bottom_right_row_p-top_left_row_p; i++) {
         for(j=0;j<=bottom_right_col_p-top_left_col_p;j++) {
            if (disp[top_left_row_p+i][top_left_col_p+j] != disp[top_left_row_c+i][top_left_col_c+j]){
               disp[top_left_row_p+i][top_left_col_p+j] = disp[top_left_row_c+i][top_left_col_c+j];
               count = count + 1;
               }
            }
         }
      for(i=0; i<max_width; i++) {
         for(j=0;j<max_height;j++) {
            printf("%d ", disp[i][j]);
            if(j==max_height-1){
               printf("\n");
            }
         }
      }
      printf("%d\n", count);
      break;
   case 'R':
      scanf(" %c %d", &direction, &degree);
      scanf(" %d %d %d %d %d %d %d %d",&top_left_row_c,&top_left_col_c,&bottom_right_row_c,&bottom_right_col_c,&top_left_row_p,&top_left_col_p,&bottom_right_row_p,&bottom_right_col_p);
      if (direction == 'L'){
         switch(degree){
            case 0:
               for(i=0; i<=bottom_right_row_p-top_left_row_p; i++) {
                  for(j=0;j<=bottom_right_col_p-top_left_col_p;j++) {
                     if (disp[top_left_row_p+i][top_left_col_p+j] != disp[top_left_row_c+i][top_left_col_c+j]){
                        disp[top_left_row_p+i][top_left_col_p+j] = disp[top_left_row_c+i][top_left_col_c+j];
                        count = count + 1;
                     }
                  }
               }
               break;
            case 90:
               for(i=0; i<=bottom_right_row_c-top_left_row_c; i++) {
                  for(j=0;j<=bottom_right_col_c-top_left_col_c;j++) {
                     if (disp[top_left_row_p+i][top_left_col_p+j] != disp[top_left_row_c+j][bottom_right_col_c-i]){
                        disp[top_left_row_p+i][top_left_col_p+j] = disp[top_left_row_c+j][bottom_right_col_c-i];
                        count = count + 1;
                     }
                  }
               }
               break;
            case 180:
               for(i=0; i<=bottom_right_row_c-top_left_row_c; i++) {
                  for(j=0;j<=bottom_right_col_c-top_left_col_c;j++) {
                     if (disp[top_left_row_p+i][top_left_col_p+j] != disp[bottom_right_row_c-i][bottom_right_col_c-j]){
                        disp[top_left_row_p+i][top_left_col_p+j] = disp[bottom_right_row_c-i][bottom_right_col_c-j];
                        count = count + 1;
                     }
                  }
               }
               break;
            case 270:
               for(i=0; i<=bottom_right_row_c-top_left_row_c; i++) {
                  for(j=0;j<=bottom_right_col_c-top_left_col_c;j++) {
                     if (disp[top_left_row_p+i][top_left_col_p+j] != disp[bottom_right_row_c-j][top_left_col_c+i]){
                        disp[top_left_row_p+i][top_left_col_p+j] = disp[bottom_right_row_c-j][top_left_col_c+i];
                        count = count + 1;
                     }
                  }
               }
               break;
         }
      }
      else if(direction == 'R'){
         switch(degree){
            case 0:
               for(i=0; i<=bottom_right_row_p-top_left_row_p; i++) {
                  for(j=0;j<=bottom_right_col_p-top_left_col_p;j++) {
                     if (disp[top_left_row_p+i][top_left_col_p+j] != disp[top_left_row_c+i][top_left_col_c+j]){
                        disp[top_left_row_p+i][top_left_col_p+j] = disp[top_left_row_c+i][top_left_col_c+j];
                        count = count + 1;
                     }
                  }
               }
               break;
            case 90:
               for(i=0; i<=bottom_right_row_c-top_left_row_c; i++) {
                  for(j=0;j<=bottom_right_col_c-top_left_col_c;j++) {
                     if (disp[top_left_row_p+i][top_left_col_p+j] != disp[bottom_right_row_c-j][top_left_col_c+i]){
                        disp[top_left_row_p+i][top_left_col_p+j] = disp[bottom_right_row_c-j][top_left_col_c+i];
                        count = count + 1;
                     }
                  }
               }
               break;
            case 180:
               for(i=0; i<=bottom_right_row_c-top_left_row_c; i++) {
                  for(j=0;j<=bottom_right_col_c-top_left_col_c;j++) {
                     if (disp[top_left_row_p+i][top_left_col_p+j] != disp[bottom_right_row_c-i][bottom_right_col_c-j]){
                        disp[top_left_row_p+i][top_left_col_p+j] = disp[bottom_right_row_c-i][bottom_right_col_c-j];
                        count = count + 1;
                     }
                  }
               }
               break;
            case 270:
               for(i=0; i<=bottom_right_row_c-top_left_row_c; i++) {
                  for(j=0;j<=bottom_right_col_c-top_left_col_c;j++) {
                     if (disp[top_left_row_p+i][top_left_col_p+j] != disp[top_left_row_c+j][bottom_right_col_c-i]){
                        disp[top_left_row_p+i][top_left_col_p+j] = disp[top_left_row_c+j][bottom_right_col_c-i];
                        count = count + 1;
                     }
                  }
               }
               break;
         }
      }
      for(i=0; i<max_width; i++) {
         for(j=0;j<max_height;j++) {
            printf("%d ", disp[i][j]);
            if(j==max_height-1){
               printf("\n");
            }
         }
      }
      printf("%d\n", count);
      break;
   }
   return 0;
}

