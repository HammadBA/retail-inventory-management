//Product Inventory Database for retail use to hold and store products and information for inventory purposes
//Made by Hammad Bin Arif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 1024


// List of all similar related products
typedef struct relatedProduct_struct
{
    char namebrand[MAX_STR_LEN];
    struct relatedProduct_struct *next;

} RelatedProductList;

// Storing Information of Product
typedef struct product_struct
{
    char product_name[MAX_STR_LEN];
    char product_company[MAX_STR_LEN];
    int quantity;
    float price;
    RelatedProductList  *relatedProducts;

} Product;

// Used to store a linked list of Product nodes
typedef struct productInfoNode_struct
{
    Product productInfo;
    struct productInfoNode_struct *next;

} productInfoNode;


//Allocates a new and empty productInfoNode and initializes
//content with given values
productInfoNode *newProductNode(char *name, char *company_name, int quantity, float price)
{
    //Points to new node
    productInfoNode *new_node = NULL;

    //Allocates memory needed
    new_node=(productInfoNode *)calloc(1, sizeof(productInfoNode));

    //initializes content
    strcpy(new_node->productInfo.product_name, name);
    strcpy(new_node->productInfo.product_company, company_name);
    new_node->productInfo.quantity = quantity;
    new_node->productInfo.price = price;


    new_node->productInfo.relatedProducts=NULL;
    new_node->next=NULL;

    return new_node;

}

//Finds and returns productInfoNode containing info that matches
//search query (Product Name, Brand Name)
productInfoNode *findProduct(char *name, char *company_name, productInfoNode *head)
{
    productInfoNode *p=NULL;// Traversal pointer
    p=head;
    while (p!=NULL){
        if (strcmp(p->productInfo.product_name, name)== 0 && strcmp(p->productInfo.product_company, company_name)== 0){
                //Return a pointer to this node
                return p;
        }
        p = p->next;
    }
    return NULL;// Search was unsuccessful
}

/*Inserts a new product into he linked list (if unexists already)
* Input with:
*  - name: the name of the product
*  - company_name: the name of the Brand
*  - quantity: the quantity of the product
*  - price: the price of the product
*
*
* Output & Return: - head: the (potentially new) head of the linked list of     *                    Products
*/
productInfoNode *insertProductInfo(char *name, char *company_name, int quantity, float price, productInfoNode *head)
{
    if (findProduct(name, company_name, head) != NULL){
        return head;
    }

    productInfoNode *new_product = NULL;
    new_product = newProductNode(name, company_name, quantity, price);

    new_product->next = head;
    head = new_product;
    return head;

}

/**
 * Returns the length of the linked list that begins at head.
 *
 * Input: - head: the start of a linked list
 * Returns: - the number of elements in this linked list
 */
int inventoryUsed(productInfoNode *head)
{
    productInfoNode *p=NULL;// Traversal pointer
    int counter = 0;

    p = head;
    while (p!=NULL){
        counter++;
        p = p->next;
    }
    return counter;

}

/**
 * Updates the product matching the input query:
 *  - name: the name of the product
 *  - company_name: the name of the Brand
 * with new price and quantity.
 *
 * If no such product is found, the function prints out: "No Product Found"
 *
 * INPUT:
 *  - name: the name of the product
 *  - company_name: the name of the Brand
 *  - quantity: new quantity of product
 *  - price: the new price of the product
 *
 * OUTPUT:
 *  - head: the (potentially new) head of the linked list of products
 *  - error message to the terminal, if no node is found
 */
void updateProductInfo(char *name, char *company_name, productInfoNode *head)
{
    productInfoNode *p = findProduct(name, company_name, head);
    if(p == NULL){
        printf("No Product Found\n");
    }else{
        int quantity;
        float price;
        printf("\nPlease Enter the new info about this product!!\n");

        printf("\nPlease Enter the new name, if no change type 'N/A': ");
        fgets(name, MAX_STR_LEN, stdin);

        //removes whitespace at the end of name from fget
        name[strlen(name) - 1] = '\0';

        printf("\nPlease Enter the new brand, if no change type 'N/A': ");
        fgets(company_name, MAX_STR_LEN, stdin);

         //removes whitespace at the end of company_name from fget
        company_name[strlen(company_name) - 1] = '\0';

        printf("\nPlease Enter the new quantity, if no change type '-1': ");
        scanf("%d", &quantity);

        printf("\nPlease Enter the new price, if no change type '-1': ");
        scanf("%f", &price);

        if(strcmp(name, "N/A") != 0) strcpy(p->productInfo.product_name, name);
        if(strcmp(company_name, "N/A") != 0) strcpy(p->productInfo.product_company, company_name);
        if (quantity != -1) p->productInfo.quantity = quantity;
        if (price != -1) p->productInfo.price = price;
        printf("Update Successful\n");
    }

}

/**
 * Removes product matching the input query from the linked list, if such product can be found.
 *
 * INPUT:
 *  - name: the name of the product
 *  - company_name: the name of the Brand
 *
 * OUTPUT: - head: the (potentially new) head node of the linked list
 * RETURN: - the (potentially new) head node of the linked list
 */
productInfoNode *deleteProduct(char *name, char *company_name, productInfoNode *head)
{
    if(findProduct(name, company_name, head) == NULL){
        printf("Sorry, no such product exists in the inventory\n");
    }
    productInfoNode *product = findProduct(name, company_name, head);
    productInfoNode *tr=NULL;
    productInfoNode *pre=NULL;

    // Check if Linked list is empty
    if (head==NULL) return NULL;

    // Set up the first two nodes in the list.
    pre=head;
    tr=head->next;

    // Check if we have to remove the head node
    if (pre == product){
        free(pre);  // Delete the first node in the list
        printf("Deleted Product Successfully\n");
        return tr;  // Return pointer to the second node which is now the new head}
    }

    while(tr!=NULL){
        if (tr == product){
            // Found the node we want to delete
            pre->next = tr->next;
            free(tr); // remove node
            printf("Deleted Product Successfully\n");
            break;
        }
        tr=tr->next;
        pre=pre->next;
    }

    return head; // Head did not change
}

/**
 * Prints out all the products in the linked list and returns the total amount * of products in inventory

 * INPUT: - the head node of the linked list
 *
 * RETURN: - Prints out all information, and final sum of all products
 */
int printAllProductInfo(productInfoNode *head)
{
    productInfoNode *p=NULL;// Traversal pointer
    p=head;
    int total_products = 0;
    printf("%s\n", "************************");
    while (p!=NULL){
        printf("Product Name: %s\n", p->productInfo.product_name);
        printf("Brand: %s\n", p->productInfo.product_company);
        printf("%d Stock Left\n", p->productInfo.quantity);
        printf("Price: $%.2f\n", p->productInfo.price);
        printf("%s\n", "************************");

        total_products++;
        p = p->next;
    }
    printf("TOTAL # OF PRODUCTS: %d\n", total_products);
    return total_products;

}

/**
 * Prints out all the products in the linked list which share the same brand
 * and then returns the sum of all the products
 *
 * INPUT: - the head node of the linked list
 *
 * RETURN:
 *  - the total_products, for all the products that match the query brand
 *  - the product infos: only print and count nodes matching this brand
 */
int queryProductsBrand(char *company_name, productInfoNode *head)
{
    productInfoNode *p=NULL;
    p=head;
    int total_products = 0;

    while (p!=NULL){
        if(strcmp(p->productInfo.product_company, company_name) == 0){
            printf("Product Name: %s\n", p->productInfo.product_name);
            printf("Brand: %s\n", p->productInfo.product_company);
            printf("%d Stock Left\n", p->productInfo.quantity);
            printf("Price: $%.2f\n", p->productInfo.price);
            printf("%s\n", "************************");

            total_products++;
        }
        p = p->next;
    }
    printf("TOTAL # OF PRODUCTS: %d\n", total_products);
    return total_products;
}

/**
 * Prints out the contents of all products whose quantity is less than, or equal to min_quantity.
 *
 * INPUT: - the head node of the linked list
 *
 * RETURN:
 *  - the total_products, for all the products that are equal or below minimum *        min_quantity
 *  - the product infos: only print and count nodes matching the query
 */
int queryProductsByQuantity(int min_quantity, productInfoNode *head)
{
    productInfoNode *p=NULL;
    p=head;
    int total_products = 0;

    while (p!=NULL){
        if(p->productInfo.quantity <= min_quantity){
            printf("Product Name: %s\n", p->productInfo.product_name);
            printf("Brand: %s\n", p->productInfo.product_company);
            printf("%d Stock Left\n", p->productInfo.quantity);
            printf("Price: $%.2f\n", p->productInfo.price);
            printf("%s\n", "************************");
            total_products++;
        }
        p = p->next;
    }
    printf("TOTAL # OF PRODUCTS: %d\n", total_products);
    return total_products;
}


/**
 * Deletes the linked list of products, releasing the memory allocated to each node.
 *
 * INPUT: - the head node of the linked list
 *
 * RETURN: - a NULL pointer (so that the head of the list can be set to NULL after deletion)
 */
productInfoNode *deleteProductList(productInfoNode *head)
{
    productInfoNode *first=NULL;
    productInfoNode *after=NULL;
    first=head;
    while (first!=NULL){
        after=first->next;
        free(first);
        first=after;
    }

    return first;
}
