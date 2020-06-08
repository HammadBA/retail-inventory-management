/*
 * Product Inventory Database for retail use to hold and store products and
 * information for inventory purposes
 * Made by Hammad Bin Arif
 * Interactive File
 */

#include "RetailDatabase.c"
#include <windows.h> //For adding delay to print statements

/**
 * Reads a products's name, company name, and price from the terminal.
 * Required for inserting new products, search, updating, and deletion.
 *
 * INPUT: from terminal only
 *
 * OUTPUT:
 *  - name:
 *      an allocated char buffer (of length MAX_STR_LEN) in which the
 *      products's name will be stored
 *  - company_name:
 *      an allocated char buffer (of length MAX_STR_LEN) in which the product's
 *      studio will be stored
 *  - price: an allocated float buffer in which the product's price will be
 *      stored
 */
void getFullProductInfo(char name[MAX_STR_LEN], char company_name[MAX_STR_LEN], float *price, int *quantity)
{
    printf("    -Please enter the Product's name: ");
    fgets(name, MAX_STR_LEN, stdin);
    name[strlen(name) - 1] = '\0';

    printf("    -Please enter the Product's brand: ");
    fgets(company_name, MAX_STR_LEN, stdin);
    company_name[strlen(company_name) - 1] = '\0';

    printf("    -Please enter the Product's price: ");
    scanf("%f", price);
    printf("    -Please enter the Product's quantity: ");
    scanf("%d", quantity);
    getchar();
}

void getProductNameBrand(char name[MAX_STR_LEN], char company_name[MAX_STR_LEN])
{
    printf("    -Please enter the Product's name: ");
    fgets(name, MAX_STR_LEN, stdin);
    name[strlen(name) - 1] = '\0';

    printf("    -Please enter the Product's brand: ");
    fgets(company_name, MAX_STR_LEN, stdin);
    company_name[strlen(company_name) - 1] = '\0';

}


int main()
{
    productInfoNode *Product_head = NULL;
    productInfoNode *temp = NULL;
    int choice = 0;
    char name[MAX_STR_LEN];
    char company_name[MAX_STR_LEN];
    int quantity;
    float price;

    while (true)
    {
        Sleep(1000); // in milliseconds
        printf("\n*********************************************************\n");
        printf("*********************************************************\n");
        printf("Please choose one of the following options:\n");
        printf("1 - Insert a new product\n");
        printf("2 - Search for a product\n");
        printf("3 - Modify an existing product\n");
        printf("4 - Delete a product\n");
        printf("5 - Print out existing products.\n");
        printf("6 - Query products by brand.\n");
        printf("7 - Query products by minimum quantity.\n");
        printf("8 - Delete list of products and exit.\n");
        scanf("%d", &choice);
        getchar();

        // Read in review information from terminal where needed.

        if (choice == 1)
        {
            getFullProductInfo(name, company_name, &price, &quantity);
            Product_head = insertProductInfo(name, company_name, quantity, price, Product_head);
        }
        // if (choice >= 2 && choice <= 4)
        // {
        //     getProductInfo(name, company_name, &price, &quantity);
        // }
        else if (choice == 2)
        {
            getProductNameBrand(name, company_name);
            temp = findProduct(name, company_name, Product_head);
            if (temp != NULL)
            {
                printf("Found the product:\n");
                printf("Theres %d left in stock\n", temp->productInfo.quantity);
                printf("Price: $%.2f\n", temp->productInfo.price);
            }
            else
            {
                printf("No such product in the current list\n");
            }
        }
        else if (choice == 3)
        {
            getProductNameBrand(name, company_name);
            updateProductInfo(name, company_name, Product_head);

        }
        else if (choice == 4)
        {
            getProductNameBrand(name, company_name);
            Product_head = deleteProduct(name, company_name, Product_head);
        }
        else if (choice == 5)
        {
            printAllProductInfo(Product_head);
        }
        else if (choice == 6)
        {
            printf("    -Please enter the name of the brand you want to list products for: ");
            fgets(company_name, MAX_STR_LEN, stdin);
            company_name[strlen(company_name) - 1] = '\0';

            queryProductsBrand(company_name, Product_head);
        }
        else if (choice == 7)
        {
            printf("    -Enter the minimum quantity to be used to search for products: ");
            scanf("%d", &quantity);
            getchar();
            queryProductsByQuantity(quantity, Product_head);
        }
        else if (choice == 8){
            Product_head = deleteProductList(Product_head);
            printf("Thank You For Using This Service!\n");
            return 0;
        }


        else{
            printf("That is an invalid choice\n");
        }
    }


}
