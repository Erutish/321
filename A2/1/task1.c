#include <stdio.h>

struct Item {
    int quantity;
    float unit_price;
};

int main() {
    struct Item paratha, vegetable, mineral_water;
    int number_of_people;
    float total_bill, per_person_payment;

    
    printf("Quantity of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit Price: ");
    scanf("%f", &paratha.unit_price);

   
    printf("Quantity of Vegetables: ");
    scanf("%d", &vegetable.quantity);
    printf("Unit Price: ");
    scanf("%f", &vegetable.unit_price);

    
    printf("Quantity of Mineral Water: ");
    scanf("%d", &mineral_water.quantity);
    printf("Unit Price: ");
    scanf("%f", &mineral_water.unit_price);

    
    printf("Number of People: ");
    scanf("%d", &number_of_people);

    
    total_bill = (paratha.quantity * paratha.unit_price) +
                 (vegetable.quantity * vegetable.unit_price) +
                 (mineral_water.quantity * mineral_water.unit_price);

   
    per_person_payment = total_bill / number_of_people;

 
    printf("Individual people will pay: %.2f tk\n", per_person_payment);

    return 0;
}

