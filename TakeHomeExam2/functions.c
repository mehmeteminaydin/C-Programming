#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    int i,j,k;
    float *** sector_times;
    scanf("%u %u\n",n_drivers, n_laps);
    sector_times = (float ***)malloc((*n_drivers)*sizeof(float**));
    for (i = 0; i< (*n_drivers); i++) {
        sector_times[i] = (float **) malloc((*n_laps)*sizeof(float *));
        for (j = 0; j < (*n_laps); j++) {
              sector_times[i][j] = (float *)malloc(n_sector*sizeof(float));
        }
    }
    for(i=0;i<(*n_drivers);i++){
        for(j=0;j<(*n_laps);j++){
            for(k=0;k<n_sector;k++){
                if (k== n_sector-1){
                    scanf("%f\n",&sector_times[i][j][k]);
                }
                else{
                    scanf("%f ",&sector_times[i][j][k]);
                }
            }
        }
    }
    return sector_times;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    int i,j;
    unsigned int ** positions;
    scanf("%u %u\n",p_drivers, n_races);
    positions = (unsigned int **)malloc((*p_drivers)*sizeof(unsigned int*));
    for (i = 0; i< (*p_drivers); i++) {
        positions[i] = (unsigned int *) malloc((*n_races)*sizeof(unsigned int));
    }
    for(i=0;i<(*p_drivers);i++){
        for(j=0;j<(*n_races);j++){
            if(j== (*n_races)-1){
                scanf("%u\n",&positions[i][j]);
            }
            else{
                scanf("%u ",&positions[i][j]);
            }
        }
    }
    return positions;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j,k;
    float **lap_times;
    float total;
    unsigned int drivers_num, laps_num;
    drivers_num = n_drivers;
    laps_num = n_laps;
    lap_times = (float **)malloc(drivers_num*sizeof(float*));
    for (i = 0; i< drivers_num; i++) {
        lap_times[i] = (float *) malloc(laps_num*sizeof(float));
    }
    for(i=0;i<drivers_num;i++){
        for(j=0;j<laps_num;j++){
            total = 0;
            for(k=0; k<n_sector;k++){
                total += sector_times[i][j][k];
            }
            lap_times[i][j]= total;
        }
    }
    return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j;
    float min = lap_times[0][0];
    unsigned int min_id;
    for (i = 0; i < n_drivers; i++){
       for (j = 0; j < n_laps; j++)
       {
           if (min > lap_times[i][j])
           {
               min = lap_times[i][j];
               min_id = i;
           }
       } 
    }
    return min_id;
}


unsigned int find_driver_fastest_lap(float** lap_times_of_driver, unsigned int n_laps){
    int i,j;
    float total;
    unsigned int location = 0;
    float *array = (float*) malloc(n_laps * sizeof(float));
    for(i=0;i<n_laps;i++){
        total = 0;
        for(j=0;j<n_sector;j++){
            total += lap_times_of_driver[i][j];
        }
        array[i] = total;
    }
    for(i=1;i<n_laps;i++){
        if(array[i] < array[location]){
            location = i;
        }
    }
    return location;
}


float* selection_sort(float* arr, unsigned int len, char ord){
    int i,j;
    int count;
    float temp;
    float *sorted_array ;
    sorted_array = (float *) malloc(len * sizeof(float)) ;
    for(i = 0; i<len; i++){
        sorted_array[i] = arr[i];
    }
    if(ord == 'A'){
        for (i = 0; i < len - 1; i++){
            count = i ;
            for (j = i + 1; j < len; j++){
                if(sorted_array[count] > sorted_array[j]){
                    count = j ;
                }
            }
            if(count != i){
                temp = sorted_array[count];
                sorted_array[count] = sorted_array[i];
                sorted_array[i] = temp;
            }
        }
    }
    if (ord == 'D'){
        for (i = 0; i < len - 1; i++){
            count = i;
            for (j = i + 1; j < len; j++){
                if(sorted_array[count] < sorted_array[j]){
                    count = j ;
                }
            }
            if(count != i){
                temp = sorted_array[count] ;
                sorted_array[count] = sorted_array[i];
                sorted_array[i] = temp ;
            }
        }
    }
    return sorted_array ;
}


unsigned int* create_positions_array(unsigned int n_drivers){
    unsigned int *finishing_positions = (unsigned int*) malloc(n_drivers * sizeof(unsigned int));
    unsigned int a;
    for(a=0; a<n_drivers; a++){
        finishing_positions[a] = a;
    }
    return finishing_positions;
}

unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    float *finishing_times = (float*) malloc(n_drivers * sizeof(float));
    int i,j;
    float total=0;
    int switched = 1, temp;
    unsigned int* finishing_positions;
    finishing_positions = create_positions_array(n_drivers);
    for(i =0; i<n_drivers; i++){
        for(j=0; j<n_laps; j++){
            total += lap_times[i][j];
        }
        finishing_times[i] = total;
        total = 0;
    }
    
    while(switched)
    {
        switched = 0;
        for(i = 1; i < n_drivers; i++)
        {
            if(finishing_times[finishing_positions[i - 1]] > finishing_times[finishing_positions[i]])
            {
                temp = finishing_positions[i];
                finishing_positions[i] = finishing_positions[i - 1];
                finishing_positions[i - 1] = temp;
                switched = 1;
            }
        }
    }
    return finishing_positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2){
    int j;
    float *time_diff = (float*) malloc(n_laps * sizeof(float));
    for(j=0;j<n_laps;j++){
        if (j != 0){
            time_diff[j] = time_diff[j-1] + lap_times[driver1][j] - lap_times[driver2][j];
        }
        else{
            time_diff[j] = lap_times[driver1][j] - lap_times[driver2][j];
        }
            
    }
    return time_diff;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    unsigned int *total_points = (unsigned int*) malloc(p_drivers * sizeof(unsigned int));
    int *position_points = (int*) malloc(p_drivers * sizeof(int));
    int i,j,total;
    for(i=0;i<p_drivers;i++){
        scanf("%d ",&position_points[i]);
    }
    for(i=0;i<p_drivers;i++){
        total = 0;
        for(j=0;j<n_races;j++){
            total += position_points[positions[i][j]-1];
        }
        total_points[i] = total;
    }
    return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    unsigned int order;
    int i;
    order = 1;
    for (i=0; i < p_drivers; i++){
        if( total_points[i] > total_points[id]){
            order++;
        }
        else if(total_points[i]==total_points[id]){
            if(i<id){
                order++;
            }
        }
    }
    return order;
}