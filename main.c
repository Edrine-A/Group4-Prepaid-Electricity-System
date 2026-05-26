#include <stdio.h>
struct customer {
    char name[30];
    int meter_number;
    int phone_number;
    int category;        // 1=Domestic, 2=Commercial, 3=Industrial
    float remaining_units;
};
struct customer customers[100];
int customerCount = 0;   // Tracks how many customers are registered
int main() {
    while(1) {
        int option;
        printf("\n=== PREPAID ELECTRICITY TOKEN SYSTEM ===\n");
        printf("1. Register Customer\n");
        printf("2. Buy Electricity Tokens\n");
        printf("3. Check Remaining Units\n");
        printf("4. Exit\n");
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
                scanf("%d", &customers[customerCount].phone_number);
                
                printf("Enter category (1=Domestic, 2=Commercial, 3=Industrial): ");
                scanf("%d", &customers[customerCount].category);
                
                customers[customerCount].remaining_units = 0.0;  // NEW: Automatically start at 0
                
                printf("Customer registered successfully! ID: %d\n", customerCount + 1);
                customerCount++;   // NEW: Increase customer count
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
                    
                    // Get payment
                    float payment;
                    printf("Enter amount in UGX: ");
                    scanf("%f", &payment);
                    
                    float service_fee = 2000.0;           // Fixed service fee
                    float amount_after_fee = payment - service_fee;
                    
                    if(amount_after_fee <= 0) {
                        printf("Insufficient amount! Minimum payment must cover service fee.\n");
                        break;
                    }
                    
                    // Calculate units based on category
                    float rate = 500.0;  // Default rate
                    if(customers[found].category == 1) rate = 700.0;      // Domestic
                    else if(customers[found].category == 2) rate = 900.0; // Commercial
                    else rate = 1200.0;                                   // Industrial
                    
                    float units_bought = amount_after_fee / rate;
                    
                    // Update balance
                    customers[found].remaining_units += units_bought;
                    
                    // Print Summary
                    printf("\n--- TOKEN PURCHASE SUMMARY ---\n");
                    printf("Amount Paid      : %.2f UGX\n", payment);
                    printf("Service Fee      : %.2f UGX\n", service_fee);
                    printf("Units Purchased  : %.2f kWh\n", units_bought);
                    printf("New Balance      : %.2f kWh\n", customers[found].remaining_units);
                    
                    // Warnings
                    if(customers[found].remaining_units < 50.0) {
                        printf("?? WARNING: Low units! Please recharge soon.\n");
                    }
                    if(units_bought > 300.0) {
                        printf("?? Energy Saving Tip: High usage detected.\n");
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
                        printf("?? Very low units! Top up immediately.\n");
                    }
                }
                break;

            case 4:
                printf("Thank you for using the system. Goodbye!\n");
                return 0;

            default:
                printf("Invalid option! Please try again.\n");
        }
    }
    return 0;
}
