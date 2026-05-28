main

#include <stdio.h>
struct customer {
    char name[30];
    int meter_number;
    long phone_number;
    int category;        // 1=Domestic, 2=Commercial, 3=Industrial
    float remaining_units;
};
struct customer customers[100];
int customerCount = 0;

int main() {
    while(1) {
        int option;
        printf("\n=== PREPAID ELECTRICITY TOKEN SYSTEM ===\n");
        printf("1. Register Customer\n");
        printf("2. Buy Electricity Tokens\n");
        printf("3. Check Remaining Units\n");
        printf("4. Search Customer\n");
        printf("5. Update Customer\n");
        printf("6. Delete Customer\n");
        printf("7. Exit\n");
        printf("Choose option: ");
        scanf("%d", &option);

        switch(option) {
            case 1: // Register Customer
                if(customerCount >= 100) {
                    printf("Database full!\n");
                    break;
                }
                
                printf("Enter name: ");
                scanf("%s", customers[customerCount].name);
                
                printf("Enter meter number: ");
                scanf("%d", &customers[customerCount].meter_number);
                
                printf("Enter phone number: ");
                scanf("%ld", &customers[customerCount].phone_number);
                
                printf("Enter category (1=Domestic, 2=Commercial, 3=Industrial): ");
                scanf("%d", &customers[customerCount].category);
                
                customers[customerCount].remaining_units = 0.0;
                
                printf("Customer registered successfully! ID: %d\n", customerCount + 1);
                customerCount++;
                break;

            case 2: // Buy Electricity Tokens
                {
                    int meter;
                    printf("Enter meter number: ");
                    scanf("%d", &meter);
                    
                    int found = -1;
                    for(int i = 0; i < customerCount; i++) {
                        if(customers[i].meter_number == meter) {
                            found = i;
                            break;
                        }
                    }
                    
                    if(found == -1) {
                        printf("Customer not found!\n");
                        break;
                    }
                    
                    float payment;
                    printf("Enter amount in UGX: ");
                    scanf("%f", &payment);
                    
                    float service_fee = 2000.0;
                    float amount_after_fee = payment - service_fee;
                    
                    if(amount_after_fee <= 0) {
                        printf("Insufficient amount! Minimum payment must cover service fee.\n");
                        break;
                    }
                    
                    float rate = 500.0;
                    if(customers[found].category == 1) rate = 700.0;
                    else if(customers[found].category == 2) rate = 900.0;
                    else rate = 1200.0;
                    
                    float units_bought = amount_after_fee / rate;
                    customers[found].remaining_units += units_bought;
                    
                    printf("\n--- TOKEN PURCHASE SUMMARY ---\n");
                    printf("Amount Paid      : %.2f UGX\n", payment);
                    printf("Service Fee      : %.2f UGX\n", service_fee);
                    printf("Units Purchased  : %.2f kWh\n", units_bought);
                    printf("New Balance      : %.2f kWh\n", customers[found].remaining_units);
                    
                    if(customers[found].remaining_units < 50.0) {
                        printf("WARNING: Low units! Please recharge soon.\n");
                    }
                    if(units_bought > 300.0) {
                        printf("Energy Saving Tip: High usage detected.\n");
                    }
                }
                break;

            case 3: // Check Remaining Units
                {
                    int meter;
                    printf("Enter meter number: ");
                    scanf("%d", &meter);
                    
                    int found = -1;
                    for(int i = 0; i < customerCount; i++) {
                        if(customers[i].meter_number == meter) {
                            found = i;
                            break;
                        }
                    }
                    
                    if(found == -1) {
                        printf("Customer not found!\n");
                        break;
                    }
                    
                    printf("\nCustomer: %s\n", customers[found].name);
                    printf("Meter Number: %d\n", customers[found].meter_number);
                    printf("Remaining Units: %.2f kWh\n", customers[found].remaining_units);
                    
                    if(customers[found].remaining_units < 50.0) {
                        printf("Very low units! Top up immediately.\n");
                    }
                }
                break;

            case 4: // Search Customer
                {
                    int meter;
                    printf("Enter meter number to search: ");
                    scanf("%d", &meter);

                    int found = -1;
                    for(int i = 0; i < customerCount; i++) {
                        if(customers[i].meter_number == meter) {
                            found = i;
                            break;
                        }
                    }

                    if(found == -1) {
                        printf("Customer not found!\n");
                        break;
                    }

                    printf("\n--- Customer Details ---\n");
                    printf("Name          : %s\n", customers[found].name);
                    printf("Meter Number  : %d\n", customers[found].meter_number);
                    printf("Phone Number  : %ld\n", customers[found].phone_number);
                    printf("Category      : %d (1=Domestic, 2=Commercial, 3=Industrial)\n", customers[found].category);
                    printf("Remaining Units: %.2f kWh\n", customers[found].remaining_units);
                }
                break;

            case 5: // Update Customer
                {
                    int meter;
                    printf("Enter meter number to update: ");
                    scanf("%d", &meter);

                    int found = -1;
                    for(int i = 0; i < customerCount; i++) {
                        if(customers[i].meter_number == meter) {
                            found = i;
                            break;
                        }
                    }

                    if(found == -1) {
                        printf("Customer not found!\n");
                        break;
                    }

                    printf("Enter new name: ");
                    scanf("%s", customers[found].name);

                    printf("Enter new phone number: ");
                    scanf("%ld", &customers[found].phone_number);

                    printf("Enter new category (1=Domestic, 2=Commercial, 3=Industrial): ");
                    scanf("%d", &customers[found].category);

                    printf("Customer updated successfully!\n");
                }
                break;

            case 6: // Delete Customer
                {
                    int meter;
                    printf("Enter meter number to delete: ");
                    scanf("%d", &meter);

                    int found = -1;
                    for(int i = 0; i < customerCount; i++) {
                        if(customers[i].meter_number == meter) {
                            found = i;
                            break;
                        }
                    }

                    if(found == -1) {
                        printf("Customer not found!\n");
                        break;
                    }

                    // Shift all customers after the deleted one left by one
                    for(int i = found; i < customerCount - 1; i++) {
                        customers[i] = customers[i + 1];
                    }
                    customerCount--;
                    printf("Customer deleted successfully!\n");
                }
                break;

            case 7: // Exit
                printf("Thank you for using the system. Goodbye!\n");
                return 0;

            default:
                printf("Invalid option! Please try again.\n");
        }
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 100//program handles 100 customers only
#define SERVICE_FEE 2000
#define DOMESTIC_RATE 700
#define COMMERCIAL_RATE 900
#define INDUSTRIAL_RATE 1200
#define LOW_UNITS_THRESHOLD 50
#define HIGH_USAGE_THRESHOLD 500  // For energy-saving warning

typedef struct {
    char name[30];
    int meter_number;
    int phone_number;
    int category;        // 1 = Domestic, 2 = Commercial, 3 = Industrial
    float remaining_units;
} Customer;

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;//Enables us to count the number of customers we have registerd
        //User definied Functions to make the main function clean
// A simple verification system for only the administrators to access
int login() {
    char username[20];
    char password[20];
    
    printf("\nSYSTEM LOGIN\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Simple authentication 
    if (strcmp(username, "group4") == 0 && strcmp(password, "4444") == 0) {
        printf("Login successful! Welcome.\n");
        return 1; //for successful login
    } else {
        printf("Invalid credentials! Access denied.\n");
        return 0;
    }
}


int findCustomerByMeter(int meter) {
    for(int i = 0; i < customerCount; i++) {
        if (customers[i].meter_number == meter) {
            return i;
        }
    }
    return -1; //for an error if the customer is not found
}
//function to display customers details
void displayCustomer(int index) {
    printf("\n--- CUSTOMER DETAILS ---\n");
    printf("Name          : %s\n", customers[index].name);
    printf("Meter Number  : %d\n", customers[index].meter_number);
    printf("Phone         : %d\n", customers[index].phone_number);
    printf("Category      : %s\n", 
           customers[index].category == 1 ? "Domestic" :
           customers[index].category == 2 ? "Commercial" : "Industrial");
    printf("Remaining Units: %.2f kWh\n", customers[index].remaining_units);
}

// function to register a new customer
void registerCustomer() {
    if (customerCount >= MAX_CUSTOMERS) {
        printf("Database full! Cannot register more customers.\n");
        return;
    }

    printf("\n--- REGISTER NEW CUSTOMER ---\n");
    printf("Enter name: ");
    scanf(" %29[^\n]", customers[customerCount].name);

    printf("Enter meter number: ");
    scanf("%d", &customers[customerCount].meter_number);

    // Check for duplicate meter
    if (findCustomerByMeter(customers[customerCount].meter_number) != -1) {
        printf("Error: Meter number already exists!\n");
        return;
    }

    printf("Enter phone number: ");
    scanf("%d", &customers[customerCount].phone_number);

    printf("Enter category (1=Domestic, 2=Commercial, 3=Industrial): ");
    scanf("%d", &customers[customerCount].category);

    if (customers[customerCount].category < 1 || customers[customerCount].category > 3) {
        printf("Invalid category! Defaulting to Domestic.\n");
        customers[customerCount].category = 1;
    }

    customers[customerCount].remaining_units = 0.0f;
    customerCount++;

    printf("Customer registered successfully!\n");
}
//to search for a customer's details
void searchCustomer() {
    int meter;
    printf("Enter meter number to search: ");
    scanf("%d", &meter);

    int index = findCustomerByMeter(meter);
    if (index == -1) {
        printf("Customer not found!\n");
        return;
    }

    displayCustomer(index);
}
//to update customers details
void updateCustomerDetails() {
    int meter;
    printf("Enter meter number to update: ");
    scanf("%d", &meter);

    int index = findCustomerByMeter(meter);
    if (index == -1) {
        printf("Customer not found!\n");
        return;
    }

    printf("\nUpdating customer: %s\n", customers[index].name);
    printf("1. Update Name\n2. Update Phone\n3. Update Category\nChoice: ");
    
    int choice;
    scanf("%d", &choice);
//menu to select which details to update
    switch(choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %29[^\n]", customers[index].name);
            break;
        case 2:
            printf("Enter new phone: ");
            scanf("%d", &customers[index].phone_number);
            break;
        case 3:
            printf("Enter new category (1-3): ");
            scanf("%d", &customers[index].category);
            break;
        default:
            printf("Invalid choice!\n");
            return;
    }
    printf("Customer details updated successfully!\n");
}
//delete a customer's record
void deleteCustomerRecords() {
    int meter;
    printf("Enter meter number to delete: ");
    scanf("%d", &meter);

    int index = findCustomerByMeter(meter);
    if (index == -1) {
        printf("Customer not found!\n");
        return;
    }

    // Shift elements to delete
    for (int i = index; i < customerCount - 1; i++) {
        customers[i] = customers[i + 1];
    }
    customerCount--;

    printf("Customer record deleted successfully!\n");
}
//to buy tokens
void buyTokens() {
    int meter;
    printf("Enter meter number: ");
    scanf("%d", &meter);

    int index = findCustomerByMeter(meter);
    if (index == -1) {
        printf("Customer not found!\n");
        return;
    }
//calculate the amount to pay based on the category and service fee
    float payment;
    printf("Enter amount in UGX: ");
    scanf("%f", &payment);

    if (payment <= SERVICE_FEE) {
        printf("Insufficient amount! Minimum payment must cover service fee (%d UGX).\n", SERVICE_FEE);
        return;
    }

    float amount_after_fee = payment - SERVICE_FEE;
    float rate = (customers[index].category == 1) ? DOMESTIC_RATE :
                 (customers[index].category == 2) ? COMMERCIAL_RATE : INDUSTRIAL_RATE;

    float units_bought = amount_after_fee / rate;
    customers[index].remaining_units += units_bought;

    // Generate simple token 
    int token = rand() % 900000 + 100000;
//diaply the purchase summary and warnings if applicable
    printf("\n=== TOKEN PURCHASE SUMMARY ===\n");
    printf("Customer         : %s\n", customers[index].name);
    printf("Meter Number     : %d\n", customers[index].meter_number);
    printf("Amount Paid      : %.2f UGX\n", payment);
    printf("Service Fee      : %d UGX\n", SERVICE_FEE);
    printf("Units Purchased  : %.2f kWh\n", units_bought);
    printf("New Balance      : %.2f kWh\n", customers[index].remaining_units);
    printf("Token Code       : %d\n", token);

    if (customers[index].remaining_units < LOW_UNITS_THRESHOLD) {
        printf("WARNING: Low units! Please recharge soon.\n");
    }
    if (units_bought > HIGH_USAGE_THRESHOLD) {
        printf("ENERGY SAVING TIP: High consumption detected. Consider energy-efficient appliances.\n");
    }
}
//to check units remaining
void checkUnits() {
    int meter;
    printf("Enter meter number: ");
    scanf("%d", &meter);

    int index = findCustomerByMeter(meter);
    if (index == -1) {
        printf("Customer not found!\n");
        return;
    }

    displayCustomer(index);

    if (customers[index].remaining_units < LOW_UNITS_THRESHOLD) {
        printf("WARNING: Very low units! Top up immediately.\n");
    }
}

//main function to run the program
int main() {
    
    if (!login()) {
        return 0;
    }
//loop to display the main menu and handle user choices to run continuously until the user decides to exit
    while (1) {
    //main menu to select from
        int option;
        printf("\n=== PREPAID ELECTRICITY TOKEN SYSTEM ===\n");
        printf("1. Register Customer\n");
        printf("2. Search Customer Records\n");
        printf("3. Update Customer Details\n");
        printf("4. Delete Customer Records\n");
        printf("5. Buy Electricity Tokens\n");
        printf("6. Check Remaining Units\n");
        printf("7. Exit\n");
        printf("Choose option: ");
        scanf("%d", &option);
//handle user choices
        switch (option) {
            case 1: registerCustomer(); break;
            case 2: searchCustomer(); break;
            case 3: updateCustomerDetails(); break;
            case 4: deleteCustomerRecords(); break;
            case 5: buyTokens(); break;
            case 6: checkUnits(); break;
            case 7: 
                printf("Thank you for using the system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option! Please try again.\n");
        }
    }
    return 0;
}
// we couldn't find a way of storing data after the program terminates
main
