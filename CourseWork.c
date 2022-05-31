#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#define MAXLEN 256
#define FIELDS_AMOUNT 6   
#define SEP ','
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    #define CLS system("clear")
#else 
    #define CLS system("cls")
#endif


/* Element of double-linked list of product types */
typedef struct typeL
{
    char *name;
    int id;
    struct typeL *next;
    struct typeL *prev;
} typeL;


/* Head of list of product types*/
typedef struct TypeHead 
{
    int cnt;
    int max_id;
    typeL *first;
    typeL *last;
} typeHead;


/* Element of list of products */
typedef struct Product 
{
    char *name;
    typeL *type;
    int id;
    int index;
    int num;  
    float price;
    float weight;
    struct Product *next;
} product;


/* Head of list of product*/
typedef struct prodHead 
{
    int cnt;
    int max_id;
    product *first;
    product *last;
} prodHead;


char* fields_names[] = {
    "Id",
    "Name", 
    "Type", 
    "Index",
    "Number",
    "Price", 
    "Weight"
};


/*-----------------------*/
/* --Service functions-- */
/*-----------------------*/

/* Get characters from stdin until get '\n' or EOF */
void empty_stdin(void);

/* Сompares real numbers with a precision of 3 decimal places */
int realcmp(double value1, double value2);

/* Return True if a string is an integer, else False*/
int isInteger(char* str);

/* Return True if a string is a real number in decimal form, else False*/
int isReal(char* str);

/* Return True if entered value is in correct form */
int isCorrectValue(char *field_value, int field_num);


/*-----------------------------------------------*/
/* --Functions for work with list of the types-- */
/*-----------------------------------------------*/

/* Free pointer to a type structure */
void clearType(typeL *pNode);

/* Free list of the types */
void clearTypesList(typeHead *pHead);

/* Create head of a linked list of types */
typeHead *createTypeHead(void);

/* Create new type structure */
typeL *createType(char *name);

/* Print name and id of type */
void printType(typeL *pNode);

/* Print elements of the list of types */
void printTypeList(typeHead *pHead);

/* Return a pointer to type with the given name */
typeL *searchTypeByName(typeHead *pHead, char *word);

/* Return a pointer to type with the given id */
typeL *searchTypeById(typeHead *pHead, int id);

/* Return max id of element of the list of types */
int typeMaxId(typeHead *pHead);

/* Add first element in the list of types */
void addFirstType(typeHead *pHead, typeL *pNode);

/* Insert a new type after the specified type in the list of types */
void insertType(typeHead *pHead, typeL *currentType, typeL *newType);

/* Delete element of the list of types */
void deleteType(typeHead *pHead, typeL *pNode);


/*--------------------------------------------------*/
/* --Functions for work with list of the products-- */
/*--------------------------------------------------*/

/* Free pointer to a product structure */
void clearProduct(product *pNode);

/* Free list of the products */
void clearProductsList(prodHead *pHead);

/* Create head of a linked list of products */
prodHead *createProdHead(void);

/* Create new product structure */
product *createProduct(char **str_array, typeL *type);

/* Print fields of product */
void printProduct(product *str0);

/* Print elements of the list of products */
void printProductList(prodHead *pHead);

/* Return 0 if value of structure field equel value of string */
int isEquel(product *pNode, int field_num, char *str);

/* Change value of the product field */
void changeFieldValue(product *pNode, int field_num, char *field_value);

/* Return a pointer to product with the given id */
product *searchProductById(prodHead *pHead, int id);

/* Return a pointer to product with the given name */
product *searchProductByName(prodHead *pHead, char* name);

/* Return max id of element of the list of products */
int productMaxId(prodHead *pHead);

/* Add first element in the list of products */
void addFirstProduct(prodHead *pHead, product *pNode);

/* Insert a new product after the specified product in the list of products */
void insertProduct(prodHead *pHead, product *currentProd, product *newProd);

/* Print list of all products with given parameters */
void searchProducts(prodHead *pHead, int field_num, char* value);

/* Delete all products with given parameters */
int deleteProducts(prodHead *pHead, typeHead *typeLHead, int field_num, char *value);

/* Return value of the text field of product */
char* getTextField(product *pNode, int field_num);

/* Return value of the numeric field of product */
double getNumField(product *pNode, int field_num);

/* Sort list of products by text field */
void sortByStr(prodHead *pHead, int field_num, int direction);

/* Sort list of products by numeric field */
void sortByNum(prodHead *pHead, int field_num, int direction);

/* Decide which sort function to call */
void sortProducts(prodHead *pHead, int field_num, int direction);


/*----------------------------------------*/
/* --Functions for the work with a file-- */
/*----------------------------------------*/

/* Free array of the strings */
void clearStringArray(char **str, int n);

/* Splitting string from a file */
char **sepsSplit(char* str, int length, char sep);

/* Import products from a file */
void fileImport(prodHead *prodLHead, typeHead *typeLHead, char* filename);

/* Save list of products in the file */
void fileSave(prodHead *prodLHead, char* filename);


/*---------------------------*/
/* --Functions of the menus-- */
/*---------------------------*/

/* Submenu for select a field */
int fieldSelection(void);

/* Submenu for choosing type from the list of types */
typeL *menuChooseType(typeHead *pHead);

/* Enter a value of field from stdin */
void fieldValueInput(int field_num, char *field_value, typeHead *pHead);

/* Print user help */
void printHelp(void);

/* Menu for adding new products */
void addMenu(prodHead *prodLHead, typeHead *typeLHead);

/* Menu for manual creating new product*/
void manualCreateProduct(prodHead *prodLHead, typeHead *typeLHead);

/* Menu for editing fields of products */
void editMenu(prodHead *prodLHead, typeHead *typeLHead);

/* Menu for deleting products */
void deleteMenu(prodHead *prodLHead, typeHead *typeLHead);

/* Menu for sorting products list*/
void sortMenu(prodHead *prodLHead, typeHead *typeLHead);


int main(void)
{
    
    int output_mode; 
    int field_num; /* The number of the field that is being searched */
    char opt[5];
    char field_value[MAXLEN];
    char filename[MAXLEN];
    prodHead *prodLHead = NULL;
    typeHead *typeLHead = NULL;
    
    output_mode = 1;
    /* Create lists */
    prodLHead = createProdHead();
    typeLHead = createTypeHead();
    getchar();
    /* Main menu */
    do
    {
        CLS;
        printf("*--Electronic card library--*\n");
        
        /* Printing list of products or result of search */
        if (output_mode == 1)
        {
            printProductList(prodLHead);
        }
        else if (output_mode == 2)
        {
            searchProducts(prodLHead, field_num, field_value);
        }
        
        printf("--Menu--\n");
        printf("0) Help\n");
        printf("1) Add new cards\n");
        printf("2) Edit cards\n");
        printf("3) Delete cards\n");
        printf("4) Sort list of products\n");
        printf("5) Print list of products\n");
        printf("6) Search products by field value\n");
        printf("7) Save table to file\n");
        printf("8) Exit\n");
        fgets(opt, 5, stdin);

        if (strlen(opt) == 2)
        {
            switch(opt[0])
            {
                case '0':
                    printHelp();
                    break;
                case '1': 
                    addMenu(prodLHead, typeLHead);
                    break;
                case '2':
                    editMenu(prodLHead, typeLHead);
                    break;
                case '3': 
                    deleteMenu(prodLHead, typeLHead);
                    break;
                case '4':
                    sortMenu(prodLHead, typeLHead);
                    break;
                case '5':
                    output_mode = 1;
                    break;
                case '6':
                    field_num = fieldSelection();
                    if (field_num != 6)
                    {
                        output_mode = 2;
                        fieldValueInput(field_num, field_value, typeLHead);
                    }
                    break;
                case '7':
                    printf("Enter the name of the file:");
                    fgets(filename, MAXLEN, stdin);
                    filename[strlen(filename) - 1] = '\0';  
                    fileSave(prodLHead, filename);
                    empty_stdin();
                    break;
            }
        }
        else
        {
            opt[0] = 0;
        }        

    } while (opt[0] != '8');

    /* Free memory */
    clearTypesList(typeLHead);
    clearProductsList(prodLHead); 
    free(typeLHead);
    free(prodLHead);

    CLS;
    return 0;
}


void empty_stdin(void) 
{
    /* Get characters from stdin until get '\n' or EOF */
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


int realcmp(double value1, double value2)
{
    /* Сompares real numbers with a precision of 3 decimal places */
    int res;
    res = 0;
    res = (value1 * 1000 - value2 * 1000);
    return res;
}


int isInteger(char* str)
{
    /* Return True if a string is an integer, else False*/
    int i, res, slen;
    res = 1; 
    slen = strlen(str);  /* Lenght of received string */
    for (i = 0; i < slen; ++i)
    {
        if (!isdigit(str[i]))
        {
            res = 0;
        }
    }
    return res;
}


int isReal(char* str)
{
    /* Return True if a string is a real number in decimal form, else False */
    int i, res, slen, dots_num;
    res = 1;
    dots_num = 0;  /* Number of dots in string */
    slen = strlen(str);  /* Lenght of received string */
    
    for (i = 0; i < slen; ++i)
    {
        if (!isdigit(str[i]))
        {
            if (str[i] == '.')
            {
                dots_num++;
            }
            else
            {
                res = 0;            
            }
        }
    }

    if (dots_num > 1)
    {
        /* In decimal form of real number must be 0 or 1 dot */
        res = 0;
    }

    return res;
}


int isCorrectValue(char *field_value, int field_num)
{   
    /* Return True if entered value is in correct form */
    int res;
    res = 0;
    switch(field_num)
    {
        case 1:
            if (strlen(field_value) < 20)
            {
                res = 1;
            }
            break;
        case 2:
            if (strlen(field_value) < 20)
            {
                res = 1;
            }
            break;
        case 3:
            if (isInteger(field_value) && field_value[0] != '0' && strlen(field_value) == 6)
            {
                res = 1;
            }
            break;
        case 4:
            if (isInteger(field_value) && strlen(field_value) < 6)
            {
                res  = 1;
            }
            break;
        case 5:
            if (isReal(field_value) && strlen(field_value) < 10)
            {
                res  = 1;
            }
            break;
        case 6:
            if (isReal(field_value) && strlen(field_value) < 10)
            {
                res  = 1;
            }
            break;     
    };
    return res;
}


void clearType(typeL *pNode)
{
    /* Free pointer to a type structure */
    if (pNode)
    {
        free(pNode -> name);
        pNode -> name = NULL;
        pNode -> next = NULL;
        pNode -> prev = NULL;
        free(pNode);
        pNode = NULL;
    }
    
}


void clearTypesList(typeHead *pHead)
{
    /* Free list of the types */
    int i;
    typeL *preNode = NULL;
    typeL *pNode = NULL;
    if (pHead)
    {
        preNode = pHead -> first;
        for (i = 0; i < pHead -> cnt; ++i)
        {
            pNode = preNode -> next;
            clearType(preNode);
            preNode = pNode;
        }
    }
}
    

typeHead *createTypeHead(void)
{
    /* Create head of a linked list of types */
    typeHead *pHead = NULL;
    pHead = (typeHead*)malloc(sizeof(typeHead));
    if (pHead)
    {
        pHead -> cnt = 0;
        pHead -> max_id = 0;
        pHead -> first = NULL;
        pHead -> last = NULL;
    }
    /* Return pointer to head of type list */ 
    return pHead;
}


typeL *createType(char *name)
{
    /* Create new type structure */
    typeL *pNode = NULL;
    pNode = (typeL*)malloc(sizeof(typeL));
    if(pNode)
    {
        pNode -> name = name;
        pNode -> id = 1;
        pNode -> next = NULL;
        pNode -> prev = NULL;
    }
    else
    {
        printf("Error with creating new type\n");
    }
    /* Return pointer to type structure */
    return pNode;
}


typeL *searchTypeByName(typeHead *pHead, char *word)
{
    /* Return a pointer to type with the given name. If no element with this name, then return NULL*/
    typeL *res = NULL;
    typeL *pNode = NULL;
    if (pHead)
    {
        pNode = pHead -> first;
        while(pNode != NULL)
        {
            if (!strcmp(word, pNode -> name))
            {
                /* If type was found, stop loop */
                res = pNode;
                pNode = pHead -> last;
            }
            pNode = pNode -> next;
        }
        
    }
    return res;
}


typeL *searchTypeById(typeHead *pHead, int id)
{
    typeL *res = NULL;
    typeL *pNode = NULL;
    if (pHead)
    {
        pNode = pHead -> first;
        while(pNode != NULL)
        {
            if (pNode -> id == id)
            {
                /* If type was found, stop loop */
                res = pNode;
                pNode = pHead -> last;
            }
            pNode = pNode -> next;
        }
    }
    
    return res;
}


int typeMaxId(typeHead *pHead)
{
    /* Searching max id in the list of types */
    int max;
    typeL *pNode = NULL;
    max = 1;
    if (pHead)
    {
        pNode = pHead -> first;
    
        while(pNode != NULL)
        {
            if (pNode -> id > max)
            {
                max = pNode -> id;
            }
            pNode = pNode -> next;
        }
    }
    return max;
}


void addFirstType(typeHead *pHead, typeL *pNode)
{
    /* Add first element in the list of types */
    if (pHead && pNode)
    {
        pHead -> cnt = 1;
        pHead -> max_id++;
        pHead -> first = pNode;
        pHead -> last = pNode;
    }
}


void insertType(typeHead *pHead, typeL *currentType, typeL *newType)
{
    /* Insert a new type after the specified type in the list of types */
    if (pHead && currentType && newType)
    {
        if (currentType -> next == NULL)
        {
            /* If insert after the last element */
            pHead -> last = newType;
        }
        newType -> id = ++pHead -> max_id;
        newType -> next = currentType -> next;
        newType -> prev = currentType;
        currentType -> next = newType;
        pHead -> cnt++;
    }
        
}


void deleteType(typeHead *pHead, typeL *pNode)
{
    /* Delete element of the list of types */
    if (pHead && pNode)
    {
        if (pHead -> cnt > 1)
        {
            if (pNode -> prev == NULL)
            {
                /* Deleting first element */
                pHead -> first = pNode -> next;
                pNode -> next -> prev = NULL;
            }
            else if (pNode -> next == NULL)
            {
                /* Deleting last element*/
                pHead -> last = pNode -> prev;
                pNode -> prev -> next = NULL;
            }
            else
            {
                /* Other cases */
                pNode -> next -> prev = pNode -> prev;
                pNode -> prev -> next = pNode -> next;
            }
        }
        else
        {
            /* Deleting the only one element */
            pHead -> first = NULL;
            pHead -> last = NULL;
            pHead -> max_id = 0;
        }

        pHead -> cnt--;

        if (pNode -> id == pHead -> max_id)
        {
            /* Update max_id field */
            pHead -> max_id = typeMaxId(pHead);
        }
        clearType(pNode);
    }
}


void printType(typeL *pNode)
{
    /* Print name and id of type */
    if (pNode)
    {
        printf("%d) %s\n", pNode -> id, pNode -> name);
    }    
}


void printTypeList(typeHead *pHead)
{
    /* Print elements of the list of types */
    typeL *pNode = NULL;
    if (pHead)
    {
        pNode = pHead -> first;
        if (pHead -> cnt > 0)
        {
            while(pNode != NULL)
            {
                printType(pNode);
                pNode = pNode -> next;
            }
        }
        else
        {
            printf("List of types is empty\n");
            printf("Press enter to back in main menu...\n");
        }  
    }
          
}


void clearProduct(product *pNode)
{
    /* Free pointer to a product structure */
    if (pNode)
    {
        free(pNode -> name);
        pNode -> name = NULL;
        pNode -> type = NULL;
        pNode -> next = NULL;
        free(pNode);
        pNode = NULL; 
    }
}


void clearProductsList(prodHead *pHead)
{
    /* Free list of the products */
    int i;
    product *preNode = NULL;
    product *pNode = NULL;
    if (pHead)
    {
        preNode = pHead -> first;
        for (i = 0; i < pHead -> cnt; ++i)
        {
            pNode = preNode -> next;
            clearProduct(preNode);
            preNode = pNode;
        }
    }
    
}


prodHead *createProdHead(void)
{
    /* Create head of a linked list of products */
    prodHead *pHead = NULL;
    pHead = (prodHead*)malloc(sizeof(prodHead));
    if (pHead)
    {
        pHead -> cnt = 0;
        pHead -> first = NULL;
        pHead -> last = NULL;
    }
    /* Return pointer to Head of product list */
    return pHead;
}


product *createProduct(char **str_array, typeL *type)
{
    /* Create new product structure */
    product *pNode = NULL;
    pNode = (product*)malloc(sizeof(product));
    if (pNode)
    {
        pNode -> name = str_array[0];
        pNode -> type = type;
        pNode -> id = 1;
        pNode -> index = atoi(str_array[2]);
        pNode -> num = atoi(str_array[3]);
        pNode -> price = atof(str_array[4]);
        pNode -> weight = atof(str_array[5]);
        pNode -> next = NULL;
    }
    /* Return pointer to product structure */
    return pNode;
}


void printProduct(product *str0)
{
    /* Print fields of product */
    if (str0)
    {
        printf("| %2d | %20s | %20s | %6d | %6d | %9.3f  | %9.3f  |\n", str0 -> id, str0 -> name, str0 -> type -> name, str0 -> index,
        str0 -> num, str0 -> price, str0 -> weight);
    }   
}


void printProductList(prodHead *pHead)
{
    /* Print elements of the list of products */
    product *pNode = NULL; 
    if (pHead)
    {
        pNode = pHead -> first;
        printf("List of products:\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("| Id | %20s | %20s | %6s | %4s | %10s | %10s |\n", "Name", "Type", "Index", 
        "Number", "Price", "Weight");
        printf("------------------------------------------------------------------------------------------------\n");
        if (pHead -> cnt > 0)
        {
            while (pNode != NULL)
            {
                printProduct(pNode);
                pNode = pNode -> next;
            }
        }
        else
        {
            printf("|                                 The list of products is empty                                |\n");
        }
        printf("------------------------------------------------------------------------------------------------\n");
    }
    
}


int isEquel(product *pNode, int field_num, char *str)
{
    /* Return 0 if field of pNode with number field_num 
       match with value of fiven string */
    double res;
    if (pNode && str)
    {
        switch(field_num)
        {
            case 0:
                res = atoi(str) - pNode -> id;
                break;
            case 1:
                res = strcmp(str, pNode -> name);
                break;
            case 2:
                res = strcmp(str, pNode -> type -> name);
                break;
            case 3:
                res = atoi(str) - pNode -> index;  
                break;
            case 4:
                res = atoi(str) - pNode -> num;  
                break;
            case 5:
                res = realcmp(atof(str), pNode -> price);
                break;
            case 6:
                res = realcmp(atof(str), pNode -> weight);
                break;
        };
    }
    return (int)res;
}


void changeFieldValue(product *pNode, int field_num, char *field_value)
{
    /* Change value of the product field with number field_num */
    if (pNode)
    {
        switch(field_num)
        {
            case 1:
                strcpy(pNode -> name, field_value);
                break;
            case 3:
                pNode -> index = atoi(field_value);
                break;
            case 4:
                pNode -> num = atoi(field_value);
                break;
            case 5:
                pNode -> price = atof(field_value);
                break;
            case 6:
                pNode -> weight = atof(field_value);
                break;
        };
    }  
}


product *searchProductById(prodHead *pHead, int id)
{
    /* Return a pointer to product with the given id */
    product *res = NULL;
    product *pNode = NULL;
    if (pHead)
    {
        /* If the given number is greater than the max_id, then the search is not needed */
        if (pHead -> max_id >= id)
        {
            pNode = pHead -> first;
            while(pNode != NULL)
            {
                if (pNode -> id == id)
                {
                    /* If product was found, stop loop */
                    res = pNode;
                    pNode = pHead -> last;
                }
                pNode = pNode -> next;
            }
        }
    }
    return res;
}


product *searchProductByName(prodHead *pHead, char* name)
{
    /* Returns a pointer to a product if the list 
       contains a product with the given name */
    product *pNode = NULL;
    product *result = NULL;
    if (pHead)
    {
        pNode = pHead -> first;
        while(pNode != NULL) 
        {
            if (!strcmp(pNode -> name, name))
            {
                /* If product was found, stop loop */
                result = pNode;
                pNode = pHead -> last;
            }
            pNode = pNode -> next;
        }
    }
    
    return result;
}


int productMaxId(prodHead *pHead)
{
    /* Searching max id in the list of products */
    int max;
    product *pNode = NULL;

    max = 1;
    pNode = pHead -> first;
    while(pNode != NULL)
    {
        if (pNode -> id > max)
        {
            max = pNode -> id;
        }
        pNode = pNode -> next;
    }

    return max;
}


void addFirstProduct(prodHead *pHead, product *pNode)
{
    /* Add first element in the list of products */
    if (pHead && pNode)
    {
        pHead -> cnt = 1;
        pHead -> max_id = 1;
        pHead -> first = pNode;
        pHead -> last = pNode;
    }
}


void insertProduct(prodHead *pHead, product *currentProd, product *newProd)
{
    /* Insert a new product after the specified product in the list of products */
    if (pHead && currentProd && newProd)
    {
        if (currentProd -> next == NULL)
        {
            /* Insert after last element of the list */
            pHead -> last = newProd;
        }
        newProd-> id = ++pHead -> max_id;
        newProd -> next = currentProd -> next;
        currentProd -> next = newProd;
        pHead -> cnt++;
    }
}


void searchProducts(prodHead *pHead, int field_num, char* value)
{
    /* Print list of all products with given parameters */
    int search;  /* Equal 1, if such products was found */
    product *pNode = NULL;
    
    search = 0;

    if (pHead)
    {
        pNode = pHead -> first;

        printf("Products with %s %s\n", fields_names[field_num], value);
        printf("------------------------------------------------------------------------------------------------\n");
        printf("| Id | %20s | %20s | %6s | %4s | %10s | %10s |\n", "Name", "Type", "Index", 
        "Number", "Price", "Weight");
        printf("------------------------------------------------------------------------------------------------\n");

        while(pNode != NULL)
        {
           if (!isEquel(pNode, field_num, value))
           {
               search = 1;
               printProduct(pNode);
           }
           pNode = pNode -> next;
        }
    }    
    
    if (!search)
    {
        printf("|                                     No such elements in list                                 |\n");
    }
    printf("------------------------------------------------------------------------------------------------\n");
}


int deleteProducts(prodHead *pHead, typeHead *typeLHead, int field_num, char *value)
{
    /* Delete all products with given parameters */
    int i;
    int deleting; /* Equel 1, if deletion has been made*/
    product *pNode = NULL;
    product *preNode = NULL;


    i = deleting = 0;
    preNode = pNode = pHead -> first;

    while(pNode != NULL)
    {
        if (i == 0)
        {
            /* Delete first element of list */
            if (!isEquel(pNode, field_num, value))
            {
                pHead -> first = pNode -> next;
                pHead -> cnt--;
                clearProduct(pNode);
                preNode = pNode = pHead -> first;
                deleting = 1;
            }
            else
            {
                pNode = pNode -> next;
                i++;
            }
        }
        else
        {
            if (!isEquel(pNode, field_num, value))
            {
                preNode -> next = pNode -> next;
                clearProduct(pNode);
                pHead -> cnt--;
                pNode = preNode -> next;
                deleting = 1;
            }
            else
            {
                preNode = preNode -> next;
                pNode = pNode -> next;
                i++;
            }
        } 
    }
    return deleting;
}   


char* getTextField(product *pNode, int field_num)
{
    /* Return value of the text field of product */
    char* res = NULL;
    switch(field_num)
    {
        case 1:
            res = pNode -> name;
            break;
        case 2:
            res = pNode -> type -> name;
            break;
    };
    return res;
}


double getNumField(product *pNode, int field_num)
{
    /* Return value of the numeric field of product */
    double res;
    res = 0;
    switch(field_num)
    {
        case 0:
            res = pNode -> id;
            break;
        case 3:
            res = pNode -> index;
            break;
        case 4:
            res = pNode -> num;
            break;
        case 5:
            res = pNode -> price;
            break;
        case 6:
            res = pNode -> weight;
            break;
    };
    return res;
}


void sortByStr(prodHead *pHead, int field_num, int direction)
{
    /* Insertion sort of list of products by text field */
    int i, j;
    product *pNode = NULL;
    product *tmp = NULL;    
    product **pElems = NULL;    /* Array of pointers to pointers to elements of list */ 

    if (pHead)
    {
        pElems = (product**)malloc(sizeof(product*) * pHead -> cnt);
        if (pElems)
        {
            pNode = pHead -> first;
            
            for (i = 0; i < pHead -> cnt; ++i)
            {
                pElems[i] = pNode;
                pNode = pNode -> next;
            }

            /* Sort of pElems */
            for (i = 1; i < pHead -> cnt; ++i)
            {
                for (j = i; j > 0 && (direction * strcmp(getTextField(pElems[j - 1], field_num), getTextField(pElems[j], field_num))) > 0; --j)
                {
                    tmp = pElems[j];
                    pElems[j] = pElems[j - 1];
                    pElems[j - 1] = tmp;
                }
            }

            /* Linking elements after sorting */
            for (i = 0; i < pHead -> cnt; ++i)
            {
                pElems[i] -> next = pElems[i + 1];  
            }
            pHead -> first = pElems[0];
            pHead -> last = pElems[pHead -> cnt - 1];
            pHead -> last -> next = NULL;

            free(pElems);
            pElems = NULL;
        }
    }    
}


void sortByNum(prodHead *pHead, int field_num, int direction)
{
    /* Insertion sort of list of products by text field */
    int i, j;
    product *pNode = NULL;
    product *tmp = NULL;
    product **pElems = NULL;
    if (pHead)
    {
        pElems = (product**)malloc(sizeof(product*) * pHead -> cnt);
        if (pElems)
        {
            pNode = pHead -> first;
            for (i = 0; i < pHead -> cnt; ++i)
            {
                pElems[i] = pNode;
                pNode = pNode -> next;
            }

            /* Sort of pElems */
            for (i = 1; i < pHead -> cnt; ++i)
            {
                /* if direction > 0, ascending sort; if direction < 0, descending sort*/
                for (j = i; j > 0 && (direction * realcmp(getNumField(pElems[j - 1], field_num), getNumField(pElems[j], field_num))) > 0; --j)
                {
                    tmp = pElems[j];
                    pElems[j] = pElems[j - 1];
                    pElems[j - 1] = tmp;
                }
            }

            /* Linking elements after sorting */
            for (i = 0; i < pHead -> cnt; ++i)
            {
                pElems[i] -> next = pElems[i + 1];  
            }
            pHead -> first = pElems[0];
            pHead -> last = pElems[pHead -> cnt - 1];
            pHead -> last -> next = NULL;

            free(pElems);
            pElems = NULL;
        }
    }   
}


void sortProducts(prodHead *pHead, int field_num, int direction)
{
    /* Call the needed sort type */
    if (field_num > 0 && field_num < 3)
    {
        sortByStr(pHead, field_num, direction);
    }
    else
    {
        sortByNum(pHead, field_num, direction);
    }
}


void clearStringArray(char **str, int n)
{
    /* Free array of strings */
    int i;
    for(i = 0; i < n; i++)
    {
        free(str[i]);
        str[i] = NULL;
    }
    free(str);
    str = NULL;
}


char **sepsSplit(char* str, int length, char sep)
{
    /* Splitting string from a file by separator */
    int i;
    int elem_str; /* Index of the start of a new field in the string*/
    int num_seps; /* Number of separators in the string of file */
    int field; /* Number of element in array of strings */
    char **str_array = NULL;
     
    field = 0;
    
    /* Counting number of separators */
    for (i = 0, num_seps = 0; i < length; ++i)
    {
        if (str[i] == sep)
        {
            num_seps++;
        }
    }

    if (num_seps == FIELDS_AMOUNT - 1)
    {
        /* Filling array of strings */
        str_array = (char**)malloc((FIELDS_AMOUNT) * sizeof(char*));

        if (str_array != NULL)
        {
            str_array[field] = (char*)malloc(length * sizeof(char));
            
            for (i = 0, elem_str = 0; i < length; ++i)
            {
                if (str_array[field] != NULL)
                {
                    if (str[i] != sep)
                    {
                        str_array[field][i - elem_str] = str[i];
                    }
                    else
                    {

                        str_array[field][i - elem_str] = '\0';
                        elem_str = i + 1;
                        str_array[++field] = (char*)malloc(length * sizeof(char));
                    }
                }
                else
                {
                    clearStringArray(str_array, field);
                }
            }
        }
    }    
    return str_array;
}


void fileImport(prodHead *prodLHead, typeHead *typeLHead, char* filename)
{
    /* Import products from a file */
    FILE *fs; 
    int i, n, slen;
    int error;
    char s1[MAXLEN];
    char **str_array = NULL; 
    typeL *pType = NULL;
    product *pProd = NULL;
    
    if (prodLHead && prodLHead)
    {
        error = 0;
        /* Reading file */
        if ((fs = fopen(filename, "r")) != NULL)
        {   
            /* Counting the number of lines in a file */
            n = 0;
            while (fgets(s1, MAXLEN, fs) != NULL) 
            {
                n++;
            }
            rewind(fs);

            for (i = 0; i < n; ++i)
            {  

                fgets(s1, MAXLEN, fs);
                slen = strlen(s1) - 1;
                s1[slen] = '\0';
                str_array = sepsSplit(s1, slen, SEP);
                if (str_array != NULL)
                {
                    /* Name of a type and product must be unique */
                    if (searchProductByName(prodLHead, str_array[0]) == NULL)
                    {
                        pType = createType(str_array[1]);
                        if (searchTypeByName(typeLHead, str_array[1]) == NULL)
                        {
                            if (typeLHead -> cnt == 0)
                            {
                                addFirstType(typeLHead, pType);
                            }
                            else
                            {
                                insertType(typeLHead, typeLHead -> last, pType);
                            }
                        }

                        /* Added new product */
                        pProd = createProduct(str_array, pType);
                        if (prodLHead -> cnt == 0)
                        {
                            addFirstProduct(prodLHead, pProd);
                        }
                        else
                        {
                            insertProduct(prodLHead, prodLHead -> last, pProd);
                        }
                    }
                    else
                    {
                        error = 1;
                    }
                } 
            }
            fclose(fs);
        }
        else
        {
            printf("File not found\n");
        }
        if (error)
        {
            printf("Reading error\n");
        }
        else
        {
            printf("Import succesful\n");
        }
        empty_stdin();
    }
    else
    {
        printf("Error!\n");
        empty_stdin();
    }
}


void fileSave(prodHead *prodLHead, char* filename)
{
    /* Save list of products in the file */
    FILE *fs;
    product *pNode = NULL;
    if (prodLHead)
    {
        if ((fs = fopen(filename, "w")) != NULL)
        {
            pNode = prodLHead -> first;
            while(pNode != NULL)
            {
                fprintf(fs, "%s%c", pNode -> name, SEP);
                fprintf(fs, "%s%c", pNode -> type -> name, SEP);
                fprintf(fs, "%d%c", pNode -> index, SEP);
                fprintf(fs, "%d%c", pNode -> num, SEP);
                fprintf(fs, "%.3f%c", pNode -> price, SEP);
                fprintf(fs, "%.3f\n", pNode -> weight);
                pNode = pNode -> next;
            }
            printf("Writing succesful!\n");
            fclose(fs);
        }
        else
        {
            printf("Writing error!\n");
        }
    }
}


int fieldSelection(void)
{
    /* Submenu for select a field */
    int i;
    char opt[5];
    do
    {
        CLS;
        printf("--Selection a field--\n");
        printf("Choose a field:\n");

        /* Print list of fields */
        for (i = 0; i < FIELDS_AMOUNT + 1; ++i)
        {
            printf("%d) %s\n", i + 1,  fields_names[i]);    
        }

        printf("%d) Back\n", i + 1);
        
        fgets(opt, 5, stdin);
        if (strlen(opt) != 2)
        {
            opt[0] = 0;
        }
    } while (opt[0] > '8' || opt[0] < '1');
    return atoi(opt) - 1;
}


typeL *menuChooseType(typeHead *pHead)
{
    /* Submenu for choosing type from the list of types */
    /* Return pointer to chosen type */
    int opt_num, slen;
    char opt[5];   
    char field_value[MAXLEN];
    char *new_type_name = NULL;   
    typeL *pType = NULL;

    if (pHead)
    {
        do
        {
            CLS;
            printf("--Manually product creating--\n");
            printf("1) Select a type from the list\n");
            printf("2) Enter the name of type\n");
            fgets(opt, 5, stdin);
            if (pHead -> cnt == 0 && opt[0] == '1' && strlen(opt) == 2)
            {
                printf("List is empty!\n");
                opt[0] = 0;
                getchar();
            }
        } while (strlen(opt) != 2 || (opt[0] != '1' && opt[0] != '2'));
        
        if (opt[0] == '1')
        {
            do
            {
                /* The loop will continue until a type is selected from the list */
                CLS;
                printf("--Selection of a type--\n");
                printTypeList(pHead);
                fgets(opt, 5, stdin);
                opt[strlen(opt) - 1] = '\0';
                if (isInteger(opt))
                {
                    opt_num = atoi(opt);
                    pType = searchTypeById(pHead, opt_num); 
                }
            } while (pType == NULL);
        }
        else 
        {
            printf("Enter the type name: ");
            fgets(field_value, MAXLEN, stdin);
            slen = strlen(field_value) - 1;
            field_value[slen] = '\0';
            if (isCorrectValue(field_value, 2))
            {
                if ((pType = searchTypeByName(pHead, field_value)) == NULL)
                {
                    /* If no type with such a name, create new type with such a name */
                    new_type_name = (char*)malloc(sizeof(char) * slen);
                    if (new_type_name)
                    {
                        strcpy(new_type_name, field_value);
                        pType = createType(new_type_name);
                    }
                }     
            }    
        }
    }   
    return pType;
}


void fieldValueInput(int field_num, char *field_value, typeHead *pHead)
{
    /* Enter a value of field from stdin */
    int opt_num;
    char opt[5];
    typeL *pType = NULL;
    
    if (pHead)
    {
        if (field_num == 2)
        {
            /* Select a type value */
            strcpy(field_value, "-");
            printf("Choose the value of the field:\n");
            printTypeList(pHead);
            fgets(opt, 5, stdin);
            opt[strlen(opt) - 1] = '\0';
            if (isInteger(opt))
            {
                opt_num = atoi(opt);
                if ((pType = searchTypeById(pHead, opt_num)) != NULL)
                {
                    strcpy(field_value, pType -> name);    
                }
                else
                {
                    printf("No type with this id!");
                    empty_stdin();
                }
            }
            else
            {
                printf("You must enter a number!\n");
                empty_stdin();
            }
        }
        else
        {
            printf("Enter the value of the field: ");
            fgets(field_value, MAXLEN, stdin);
            field_value[strlen(field_value) - 1] = '\0';
        }
        CLS;
    }    
}


void printHelp(void)
{
    /* Print user help*/
    printf("--Help--\n");
    printf("\n");
    getchar();
}


void addMenu(prodHead *prodLHead, typeHead *typeLHead)
{
    /* Menu for adding new products */
    char opt[5];
    char filename[MAXLEN];
    if (prodLHead && typeLHead)
    {
        do
        {
            CLS;
            printf("--Added new cards--\n");
            printf("1) Import from a file\n");
            printf("2) Create a new product\n");
            printf("3) Back\n");
            fgets(opt, 5, stdin);
            if (strlen(opt) == 2)
            {
                switch(opt[0])
                {
                    case '1': 
                        printf("Enter the name of the file:");
                        fgets(filename, MAXLEN, stdin);
                        filename[strlen(filename) - 1] = '\0';  
                        fileImport(prodLHead, typeLHead, filename);
                        break;
                    case '2': 
                        manualCreateProduct(prodLHead, typeLHead);
                        break; 
                }
            }
            else
            {
                opt[0] = 0;
            }
        } while (opt[0] != '3');
        CLS;
    }  
}


void manualCreateProduct(prodHead *prodLHead, typeHead *typeLHead)
{
    /* Menu for manual creating new product*/
    int i;
    char field_value[MAXLEN];
    char **str_array = NULL; /* Array of the fields strings */
    product *pNode = NULL;
    typeL *pType = NULL;

    if (typeLHead && prodLHead)
    {
        str_array = (char**)malloc(FIELDS_AMOUNT * sizeof(char*));

        if (str_array)
        {
            CLS;
            for (i = 0; i < FIELDS_AMOUNT + 1; ++i)
            {
                str_array[i] = (char*)malloc(sizeof(char) * 100);
            }
            for (i = 1; i < FIELDS_AMOUNT + 1; ++i)
            {
                CLS;
                printf("--Manually product creating--\n");
                if (i != 2)
                {
                    /* Enter value of field type */
                    printf("Enter the %s: ", fields_names[i]);
                    fgets(field_value, MAXLEN, stdin);
                    field_value[strlen(field_value) - 1] = '\0';
                    if (!isCorrectValue(field_value, i))
                    {
                        /* If entered data is not valid, then repeat enter */
                        printf("Invalid data format! Try again...");
                        empty_stdin();
                        i--;
                    }
                    else
                    {
                        strcpy(str_array[i - 1], field_value);
                    }
                }
                else
                {
                    pType = menuChooseType(typeLHead);  
                    if (pType == NULL)
                    {
                        /* If entered data is not valid, then repeat enter */
                        printf("Invalid data format! Try again...");
                        empty_stdin();
                        i--;
                    }
                }
            }
                   
            
            /* Name of a type and product must be unique */
            if (searchProductByName(prodLHead, str_array[0]) == NULL)
            {
                if (searchTypeByName(typeLHead, pType -> name) == NULL)
                {
                    if (typeLHead -> cnt == 0)
                    {
                        addFirstType(typeLHead, pType);
                    }
                    else
                    {
                        insertType(typeLHead, typeLHead -> last, pType);
                    }
                }
                
                /* Added new product */
                pNode = createProduct(str_array, pType);
                if (prodLHead -> cnt == 0)
                {
                    addFirstProduct(prodLHead, pNode);
                }
                else
                {
                    insertProduct(prodLHead, prodLHead -> last, pNode);
                }
            }
            else
            {
                printf("Product with such a name already exist!\n");
                getchar();
                clearStringArray(str_array, FIELDS_AMOUNT);
            } 
        }
    }
    
}


void editMenu(prodHead *prodLHead, typeHead *typeLHead)
{
    /* Menu for editing fields of products */
    int i, field_num;
    char opt[50];
    typeL *pType = NULL;
    product *pNode = NULL;
    
    if (prodLHead && typeLHead)
    {
        CLS;
        printf("--Edit fields of product--\n");
        printProductList(prodLHead);
        printf("Enter id of element\n");
        fgets(opt, 50 ,stdin);
        opt[strlen(opt) - 1] = '\0';
        if (isInteger(opt))
        {
            if ((pNode = searchProductById(prodLHead, atoi(opt))) != NULL)
            {
                do
                {
                    CLS;
                    printf("--Selection a field--\n");
                    printf("Select a field:\n");
                    for (i = 1; i < FIELDS_AMOUNT + 1; ++i)
                    {
                        printf("%d) %s\n", i,  fields_names[i]);    
                    }
                    printf("%d) Back\n", i);
                    fgets(opt, 5, stdin);
                    if (strlen(opt) != 2)
                    {
                        opt[0] = 0;
                    }
                } while (opt[0] > '7' || opt[0] < '1');
                

                if (opt[0] != '7')
                {   
                    /* Enter the new value of selected field */
                    field_num = atoi(opt);
                    
                    if (field_num < 3)
                    {
                        printf("Current value: %s\n", getTextField(pNode, field_num));
                    }
                    else if (field_num == 3 || field_num == 4)
                    {
                        printf("Current value: %.0f\n", getNumField(pNode, field_num));
                    }
                    else
                    {   
                        printf("Current value: %.3f\n", getNumField(pNode, field_num));
                    }
                    
                    if (field_num == 2)
                    {
                        /* Edit type field */
                        pType = menuChooseType(typeLHead);
                        if (pType != NULL)
                        {
                            pNode -> type = pType;
                            printf("Product has been edited!");
                        }
                        else
                        {
                            printf("Invalid value of field!\n");
                        }
                    }
                    else
                    {   
                        /* Edit other fields */
                        printf("Enter the new value:");
                        fgets(opt, 50, stdin);
                        opt[strlen(opt) - 1] = '\0';
                        
                        if (isCorrectValue(opt, field_num))
                        {
                            /* Checking name field for uniqueness */
                            if (field_num != 1 || searchProductByName(prodLHead, opt) == NULL)
                            {
                                changeFieldValue(pNode, field_num, opt);   
                                printf("Product has been edited!");
                            }
                            else
                            {
                                printf("Product with such a name already exist!\n");
                            }
                        }
                        else
                        {
                            printf("Invalid value of field!\n");
                        }
                    } 
                    field_num = 7;
                    empty_stdin();
                }    
            }
            else
            {
                printf("No product with this id!\n");
                empty_stdin();
            }
        }
        else
        {
            printf("No product with this id!\n");
            empty_stdin();
        }
    }  
}


void deleteMenu(prodHead *prodLHead, typeHead *typeLHead)
{    
    /* Menu for deleting products */
    int field_num;
    char field_value[MAXLEN];

    if (prodLHead && typeLHead)
    {
        if (prodLHead -> cnt == 0) 
        {
            CLS;
            printf("List of products is empty!\n");
        }
        else
        {
            do
            {
                field_num = fieldSelection();
                if (field_num >= 0 && field_num <= 5)
                {
                    CLS;
                    printProductList(prodLHead);
                    fieldValueInput(field_num, field_value, typeLHead);
                    printf("--Delete cards by value of the field--\n"); 
                    if (deleteProducts(prodLHead, typeLHead, field_num, field_value))
                    {
                        printf("Deletion succesful!\n");    
                        deleteType(typeLHead, searchTypeByName(typeLHead, field_value));
                    }
                    else
                    {
                        printf("No cards with this data. Deletion failed!\n");
                    }
                    field_num = 6;
                }
            } while (field_num != 6);
        }
        empty_stdin();   
    }
}


void sortMenu(prodHead *prodLHead, typeHead *typeLHead)
{
    /* Menu for sorting products list*/   
    int field_num;
    char opt[5];
    enum {
        ASCEND = 1, DESCEND = -1
    };

    if (prodLHead && typeLHead)
    {
        field_num = -1;
        do
        {
            /* Field selection */
            field_num = fieldSelection();
            if (field_num >= 0 && field_num < 7)
            {
                /* If the field was selected then go to sub menu*/
                do
                {
                    CLS;
                    printf("--Sorting list of products--\n");
                    printf("Select the type of sorting:\n");
                    printf("1) Ascending\n");
                    printf("2) Descending\n");
                    printf("3) Back\n");
                    fgets(opt, 5, stdin);
                    if (strlen(opt) == 2)
                    {   
                        switch(opt[0])
                        {
                            case '1':
                                sortProducts(prodLHead, field_num, ASCEND);
                                field_num = 7;
                                opt[0] = '3';
                                break;
                            case '2':
                                sortProducts(prodLHead, field_num, DESCEND);
                                field_num = 7;
                                opt[0] = '3';
                                break;
                            case '3':
                                break;
                            default:
                                opt[0] = 0;
                        };
                    }   
                    else
                    {
                        opt[0] = 0;
                    }
                } while (opt[0] != '3');      
            }
        } while (field_num != 7);
    }
    
}