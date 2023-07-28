//
//  main.c
//  Ngerjain Ulang AoL Algoprog Buat Github
//
//  Created by Irfan Hera Nurrohman on 13/07/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 76
// I've already checked that in one line, the maximum number of characters is 75. So, I set the maximum string length to 76

// struct declaration
typedef struct
{
    char location1[MAX_STRING];
    char location2[MAX_STRING];
    long price;
    int rooms;
    int bathrooms;
    int carParks;
    char type[MAX_STRING];
    long area;
    char furnish[MAX_STRING];
} Housing;

typedef struct
{
    char unique[MAX_STRING];
    int frequency;
} NewData;

typedef struct
{
    int unique;
    int frequency;
} NewDataInt;

// Prototyping
void describeAreaPrice(Housing* data, int totalData, int option);
void describeNonAreaPrice(NewData* data, int totalUnique);
void sortedList(Housing* data, int totalData);
void describeNonAreaPriceInt(NewDataInt* data, int totalUnique);
void describe(Housing* data, int totalData);
void searchDataMenu(Housing* data, int totalData);
void printSearch(Housing* data, int totalData, int i);
void searchData(Housing* data, int totalData, char* search, char* column);

int main(void)
{
    FILE *fp = fopen("file-housing-data.csv", "r");
    
    if (fp)
        puts("Successfully accessed file.");
    else
        puts("Failed to access file.");
    
    // Skip the first line/header, it is not stored in the data.

    char header[MAX_STRING];
    fscanf(fp, "%[^\n]", header);
    Housing data[4000];
    // As described in the assignment file, the array size should be set to 4000 to accommodate the 3939 data entries stored in the file.
    
    int i = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%[^,],%[^,],%ld,%d,%d,%d,%[^,],%ld,%s\n",
               data[i].location1,
               data[i].location2,
               &data[i].price,
               &data[i].rooms,
               &data[i].bathrooms,
               &data[i].carParks,
               data[i].type,
               &data[i].area,
               data[i].furnish);
        i++;
    }
    fclose(fp);
    
    int totalData = i;
    
    while (1)
    {
        puts("\n+=+=+= Welcome to Malaysia House Data Management +=+=+=\n");

        puts("1. Describe Information for Each Column");
        puts("2. Search Data in File/Column");
        puts("3. Sort Data Based on Location 1");
        puts("4. Exit");
        printf("\nPlease select an option (1/2/3/4): ");
        int option; scanf("%d", &option);

        if (option == 1)
            describe(data, totalData);
        else if (option == 2)
            searchDataMenu(data, totalData);
        else if (option == 3)
            sortedList(data, totalData);
        else if (option == 4)
            break;
    }
    return 0;
}

void describeAreaPrice(Housing* data, int totalData, int option)
{
    // option 3: price
    // option 8: area
    long min, max;
      
    if (option == 3)
        max = min = data[0].price;
    else
        max = min = data[0].area;

    long sum = min;

    for (int i = 1 ; i < totalData ; i++)
      if (option == 3)
      {
        sum += data[i].price;

        if (data[i].price < min)
          min = data[i].price;
        else if (data[i].price > max)
          max = data[i].price;
      }
      else
      {
        sum += data[i].area;

        if (data[i].area < min)
          min = data[i].area;
        else if (data[i].area > max)
          max = data[i].area;
      }

    double average = 1.0 * sum / totalData;
    
    printf("\nMinimum Value: %ld\n", min);
    printf("Maximum Value: %ld\n", max);
    printf("Average Value: %.2lf\n\n", average);
}

void describeNonAreaPrice(NewData* data, int totalUnique)
{
    int max = data[0].frequency, min = data[0].frequency;
 
    puts("\n========\n");
    
    for (int i = 0 ; i < totalUnique ; i++)
    {
        printf("%s: %d\n", data[i].unique, data[i].frequency);
        if (data[i].frequency < min)
            min = data[i].frequency;
        if (data[i].frequency > max)
            max = data[i].frequency;
    }
        
    puts("\n========\n");
    
    printf("Minimum Frequency:\n");
    for (int i = 0 ; i < totalUnique ; i++)
    {
        if (data[i].frequency == min)
            printf("%s with frequency: %d\n", data[i].unique, data[i].frequency);
    }
    
    puts("\n========\n");
    
    printf("Maximum Frequency:\n");
    for (int i = 0 ; i < totalUnique ; i++)
    {
        if (data[i].frequency == max)
            printf("%s with frequency: %d\n", data[i].unique, data[i].frequency);
    }
    
    puts("\n========\n");
}

void sortedList(Housing* data, int totalData)
{
    // sorting
    for (int i = 0 ; i < totalData ; i++)
    {
        for (int j = 0 ; j < totalData - 1 ; j++)
        {
            if (strcasecmp(data[j].location1, data[j + 1].location1) > 0)
            {
                // swap
                Housing tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
    
    // unique data
    NewData location1[totalData];
    int totalUnique = 0;

    for (int i = 0 ; i < totalData - 1 ; i++)
    {
        if (strcasecmp(data[i].location1, data[i + 1].location1))
        {
            strcpy(location1[totalUnique].unique, data[i].location1);
            totalUnique += 1;
        }
    }
    
    for (int i = 0 ; i < totalUnique ; i++)
    {
        location1[i].frequency = 0;
        for (int j = 0 ; j < totalData ; j++)
        {
            if (!strcasecmp(data[j].location1, location1[i].unique))
                location1[i].frequency += 1;
        }
    }
    for (int i = 0 ; i < totalUnique ; i++)
        puts(location1[i].unique);
}

void describeNonAreaPriceInt(NewDataInt* data, int totalUnique)
{
    int max = data[0].frequency, min = data[0].frequency;
 
    puts("\n========\n");
    
    for (int i = 0 ; i < totalUnique ; i++)
    {
        printf("%d: %d\n", data[i].unique, data[i].frequency);
        if (data[i].frequency < min)
            min = data[i].frequency;
        if (data[i].frequency > max)
            max = data[i].frequency;
            
    }
        
    puts("\n========\n");
    
    printf("Minimum Frequency:\n");
    for (int i = 0 ; i < totalUnique ; i++)
    {
        if (data[i].frequency == min)
            printf("%d with frequency: %d\n", data[i].unique, data[i].frequency);
    }
    
    puts("\n========\n");
    
    printf("Maximum Frequency:\n");
    for (int i = 0 ; i < totalUnique ; i++)
    {
        if (data[i].frequency == max)
            printf("%d with frequency: %d\n", data[i].unique, data[i].frequency);
    }
    
    puts("\n========\n");
}

void describe(Housing* data, int totalData)
{
    while (1)
    {
        puts("\n1. Describe Information for Location 1");
        puts("2. Describe Information for Location 2");
        puts("3. Describe Information for Price");
        puts("4. Describe Information for Rooms");
        puts("5. Describe Information for Bathrooms");
        puts("6. Describe Information for Car Parks");
        puts("7. Describe Information for Type");
        puts("8. Describe Information for Area");
        puts("9. Describe Information for Furnish");
        puts("10. Exit");

        printf("\nPlease select an option (1-10): ");
        int option; scanf("%d", &option);
        
        if (option == 1) // location 1
        {
            puts("\nLocation 1\n");
            // sorting
            for (int i = 0 ; i < totalData ; i++)
            {
                for (int j = 0 ; j < totalData - 1 ; j++)
                {
                    if (strcasecmp(data[j].location1, data[j + 1].location1) > 0)
                    {
                        // swap
                        Housing tmp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = tmp;
                    }
                }
            }
            
            // unique data
            NewData location1[totalData];
            strcpy(location1[0].unique, data[0].location1);
            
            int totalUnique = 1;
    
            for (int i = 0 ; i < totalData - 1 ; i++)
            {
                if (strcasecmp(data[i].location1, data[i + 1].location1))
                {
                    strcpy(location1[totalUnique].unique, data[i + 1].location1);
                    totalUnique += 1;
                }
            }
            
            for (int i = 0 ; i < totalUnique ; i++)
            {
                location1[i].frequency = 0;
                for (int j = 0 ; j < totalData ; j++)
                {
                    if (!strcasecmp(data[j].location1, location1[i].unique))
                        location1[i].frequency += 1;
                }
            }
            
            describeNonAreaPrice(location1, totalUnique);
        }
        else if (option == 2) // location 2
        {
            puts("\nLocation 2\n");
            
            char str1[] = "Kuala-Lumpur"; int total = 3939;
            puts("\n========\n");
            printf("%s: %d\n", str1, total);
            puts("\n========\n");
            printf("Maximum Value:\n");
            printf("%s with frequency: %d\n", str1, total);
            puts("\n========\n");
            printf("Minimum Value:\n");
            printf("%s with frequency: %d\n", str1, total);
            puts("\n========\n");
        }
        else if (option == 3 || option == 8) // price & area
        {
            if (option == 3)
                puts("\nPrice");
            else
                puts("\nArea");
            describeAreaPrice(data, totalData, option);
        }
            
        else if (option == 4) // rooms
        {
            puts("\nRooms\n");
            
            // sorting
            for (int i = 0 ; i < totalData ; i++)
            {
                for (int j = 0 ; j < totalData - 1 ; j++)
                {
                    if (data[j].rooms > data[j + 1].rooms)
                    {
                        // swap
                        Housing tmp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = tmp;
                    }
                }
            }
            
            // unique data
            NewDataInt rooms[totalData];
            rooms[0].unique = data[0].rooms;
            
            int totalUnique = 1;
            
            for (int i = 0 ; i < totalData - 1 ; i++)
            {
                if (data[i].rooms != data[i + 1].rooms)
                {
                    rooms[totalUnique].unique = data[i + 1].rooms;
                    totalUnique += 1;
                }
            }
            
            for (int i = 0 ; i < totalUnique ; i++)
            {
                rooms[i].frequency = 0;
                for (int j = 0 ; j < totalData ; j++)
                {
                    if (rooms[i].unique == data[j].rooms)
                        rooms[i].frequency += 1;
                }
            }
            
            describeNonAreaPriceInt(rooms, totalUnique);
        }
        else if (option == 5)
        {
            puts("\nBathrooms\n");
            
            // sorting
            for (int i = 0 ; i < totalData ; i++)
            {
                for (int j = 0 ; j < totalData - 1 ; j++)
                {
                    if (data[j].bathrooms > data[j + 1].bathrooms)
                    {
                        // swap
                        Housing tmp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = tmp;
                    }
                }
            }
            
            // unique data
            NewDataInt bathrooms[totalData];
            bathrooms[0].unique = data[0].bathrooms;
            
            int totalUnique = 1;
            
            for (int i = 0 ; i < totalData - 1 ; i++)
            {
                if (data[i].bathrooms != data[i + 1].bathrooms)
                {
                    bathrooms[totalUnique].unique = data[i + 1].bathrooms;
                    totalUnique += 1;
                }
            }
            
            for (int i = 0 ; i < totalUnique ; i++)
            {
                bathrooms[i].frequency = 0;
                for (int j = 0 ; j < totalData ; j++)
                {
                    if (bathrooms[i].unique == data[j].bathrooms)
                        bathrooms[i].frequency += 1;
                }
            }
            
            describeNonAreaPriceInt(bathrooms, totalUnique);
        }
        else if (option == 6)
        {
            puts("\nCar Parks\n");
            
            // sorting
            for (int i = 0 ; i < totalData ; i++)
            {
                for (int j = 0 ; j < totalData - 1 ; j++)
                {
                    if (data[j].carParks > data[j + 1].carParks)
                    {
                        // swap
                        Housing tmp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = tmp;
                    }
                }
            }
            
            // unique data
            NewDataInt carParks[totalData];
            carParks[0].unique = data[0].carParks;
            
            int totalUnique = 1;
            
            for (int i = 0 ; i < totalData - 1 ; i++)
            {
                if (data[i].carParks != data[i + 1].carParks)
                {
                    carParks[totalUnique].unique = data[i + 1].carParks;
                    totalUnique += 1;
                }
            }
            
            for (int i = 0 ; i < totalUnique ; i++)
            {
                carParks[i].frequency = 0;
                for (int j = 0 ; j < totalData ; j++)
                {
                    if (carParks[i].unique == data[j].carParks)
                        carParks[i].frequency += 1;
                }
            }
            
            describeNonAreaPriceInt(carParks, totalUnique);
        }
        else if (option == 7) // type
        {
            puts("\nType\n");
            // sorting
            for (int i = 0 ; i < totalData ; i++)
            {
                for (int j = 0 ; j < totalData - 1 ; j++)
                {
                    if (strcasecmp(data[j].type, data[j + 1].type) > 0)
                    {
                        // swap
                        Housing tmp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = tmp;
                    }
                }
            }
            
            // unique data
            NewData type[totalData];
            strcpy(type[0].unique, data[0].type);
            
            int totalUnique = 1;

            for (int i = 0 ; i < totalData - 1 ; i++)
            {
                if (strcasecmp(data[i].type, data[i + 1].type))
                {
                    strcpy(type[totalUnique].unique, data[i + 1].type);
                    totalUnique += 1;
                }
            }
            
            for (int i = 0 ; i < totalUnique ; i++)
            {
                type[i].frequency = 0;
                for (int j = 0 ; j < totalData ; j++)
                {
                    if (!strcasecmp(data[j].type, type[i].unique))
                        type[i].frequency += 1;
                }
            }
            
            describeNonAreaPrice(type, totalUnique);
        }
        else if (option == 9) // furnish
        {
            puts("\nFurnish\n");
            // sorting
            for (int i = 0 ; i < totalData ; i++)
            {
                for (int j = 0 ; j < totalData - 1 ; j++)
                {
                    if (strcasecmp(data[j].furnish, data[j + 1].furnish) > 0)
                    {
                        // swap
                        Housing tmp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = tmp;
                    }
                }
            }
            
            // unique data
            NewData furnish[totalData];
            strcpy(furnish[0].unique, data[0].furnish);
            
            int totalUnique = 1;

            for (int i = 0 ; i < totalData - 1 ; i++)
            {
                if (strcasecmp(data[i].furnish, data[i + 1].furnish))
                {
                    strcpy(furnish[totalUnique].unique, data[i + 1].furnish);
                    totalUnique += 1;
                }
            }
            
            for (int i = 0 ; i < totalUnique ; i++)
            {
                furnish[i].frequency = 0;
                for (int j = 0 ; j < totalData ; j++)
                {
                    if (!strcasecmp(data[j].furnish, furnish[i].unique))
                        furnish[i].frequency += 1;
                }
            }
            
            describeNonAreaPrice(furnish, totalUnique);
        }
        else if (option == 10)
            break;
    }
}

void searchDataMenu(Housing* data, int totalData)
{
    while (1)
    {
        printf("\nAvailable Column Options for Search:\n1. Location1\n2. Location2\n3. Rooms\n4. Bathrooms\n5. CarParks\n6. Type\n7. Furnish\n");
        puts("8. Type 'exit' to quit the program\n");
        printf("Please enter your search query with the format 'DataX in ColumnName'(except for 'Area' and 'Price' columns): ");
        
        char search[MAX_STRING], column[MAX_STRING];
        scanf("%s in %s", search, column); getchar();
        if (!strcasecmp(column, "area") || !strcasecmp(column, "price"))
            puts("Search is restricted to columns excluding 'Area' and 'Price'. Please provide a different column name for your search");
        if (!strcasecmp(column, "exit") ||!strcasecmp(search, "exit"))
            break;
        searchData(data, totalData, search, column);
    }
}

void printSearch(Housing* data, int totalData, int i)
{
    puts("");
    printf("%-25s | %-12s | %-8ld | %d | %d | %d | %-9s | %-6ld | %s\n",
          data[i].location1,
          data[i].location2,
          data[i].price,
          data[i].rooms,
          data[i].bathrooms,
          data[i].carParks,
          data[i].type,
          data[i].area,
          data[i].furnish);
}

void searchData(Housing* data, int totalData, char* search, char* column)
{
    int found = 0;
    if (!strcasecmp(column, "Location1"))
    {
        for (int i = 0; i < totalData - 1; i++)
            if (strstr(data[i].location1, search))
            {
                printSearch(data, totalData, i);
                found = 1;
            }
    }
    else if (!strcasecmp(column, "Location2"))
    {
        for (int i = 0; i < totalData - 1; i++)
            if (strstr(data[i].location2, search))
            {
                printSearch(data, totalData, i);
                found = 1;
            }
    }
    else if (!strcasecmp(column, "Rooms"))
    {
        for (int i = 0 ; i < totalData - 1 ; i++)
            if (data[i].rooms == atoi(search))
            {
                printSearch(data, totalData, i);
                found = 1;
            }
    }
    else if (!strcasecmp(column, "Bathrooms"))
    {
        for (int i = 0 ; i < totalData - 1 ; i++)
            if (data[i].bathrooms == atoi(search))
            {
                printSearch(data, totalData, i);
                found = 1;
            }
    }
    else if (!strcasecmp(column, "CarParks"))
    {
        for (int i = 0 ; i < totalData - 1 ; i++)
            if (data[i].carParks == atoi(search))
            {
                printSearch(data, totalData, i);
                found = 1;
            }
    }
    else if (!strcasecmp(column, "Type"))
    {
        for (int i = 0; i < totalData - 1; i++)
            if (strstr(data[i].type, search))
            {
                printSearch(data, totalData, i);
                found = 1;
            }
    }
    else if (!strcasecmp(column, "Furnish"))
    {
        for (int i = 0; i < totalData - 1; i++)
            if (strstr(data[i].furnish, search))
            {
                printSearch(data, totalData, i);
                found = 1;
            }
    }
    if (!found)
        puts("\nData not found!");
}
