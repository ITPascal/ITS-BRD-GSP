#ifndef _ARITH_LIB_H
#define _ARITH_LIB_H
/*
 ****************************************************************************************
 * @brief : This function takes the first 2 entries from the stack, adds the second 
            to the first and puts the result on the stack
 * 
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/
int addition(void);
/*
 ****************************************************************************************
 * @brief : This function takes the first 2 entries from the stack, subtracts the second 
            from the first and puts the result on the stack
 *
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/

int subtraction(void);
/*
 ****************************************************************************************
 * @brief : This function takes the first 2 entries from the stack, multiplies them and 
 *          puts the result on the stack
 *
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/
int multiplication(void);
/*
 ****************************************************************************************
 * @brief : This function takes the first 2 entries from the stack, divides the first by 
 *          the second and puts the result on the stack
 *
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/

 int division(void);
/*
 ****************************************************************************************
 * @brief : This function prints the first entry on the stack. The entry remains on the stack
 *
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/

int printFirst();
/*
 ****************************************************************************************
 * @brief : This function prints the all entries on the stack. All entries remains on the stack
 *
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/

int printAll(void);

/*
 ****************************************************************************************
 * @brief : This function duplicates the first element on the stack and puts the duplicate 
 *          on the stack aswell
 *
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/

int duplicate(void);
/*
 ****************************************************************************************
 * @brief : This function swaps the first and second entries position on the stack
 *
 * @return 0 is returned in case of success. In case of an error the 1 will
 *         be returned.
 ****************************************************************************************/

int swapEntries(void);

#endif