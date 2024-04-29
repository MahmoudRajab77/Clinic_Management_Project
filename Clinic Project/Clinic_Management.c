/******* Clinic Management Program File *****/
/******* Author : Mahmoud Rajab Mohamed *****/

#include <stdlib.h>
#include <stdio.h>
#include "STD_TYPES.h"
#include "Clinic_Management.h"

#define Saved_Password	1234


		
u32 Slots[5];						// carry the condition : 1- Reserved   0- Available
Patient Objects[5];					// Array of Struct Objects

u32 Global_Patient_Counter = 0;		// represent the number of patients
u32 Selection;
u32 Patient_Id;






int main (void)
{


	while (1)
	{
		u16 PW = 0;
		u8 i = 0;
		
		printf("Who are you?\n");
		printf("1- Admin\n2- User\n");
		scanf("%d", &Selection);
		
		switch (Selection)
		{
			case 1:	  // ADMIN
				
				while (i<3)
				{
					printf("Please enter password :\n");
					scanf("%d", &PW);
				
					// check the password 
					if (PW == Saved_Password)		// Password Correct 
					{
						printf("Welcome Mahmoud!\n");
						printf("Please select what you want to do :\n");
						printf("1- Add new patient\n2- Edit patient record\n3- Reserve a slot\n4- Cancel reservation\n");
						scanf("%d", &Selection);
						
						// Check selection 
						switch (Selection)
						{
							case 1:		// Add patient 
								(void)Add_Patient();
							break;
							
							case 2:		// Edit patient
								Edit_Patient();
							break;
							
							case 3:		// Reserve slot 
								Reserve_Slot();
							break;
							
							case 4: 	// Cancel reservation
								Cancel_Reservation();
							break;
							
							default:
							break;
						}// end switch
						
						break; // mission done get out the loop 
					
					}// end if 
					else		// password incorrect 
					{
						if (i != 2)
						{
							printf("Password is incorrect\n");
							i++;	// increment trial
						}	
						else 
						{
							printf("Trials over, try again later\n");
						}	
					
					}// end else
				}// end while 	
		
			break;// case admin 
			
			case 2:   // User 
				printf("Please select what you want to do :\n");
				printf("1- View Today's reservations\n2- View patient record\n");
				scanf("%d", &Selection);
				
				
				// Check selection 
				switch (Selection)
				{
					case 1:		 // View reservations
						View_TodayReservation();
					break;
			
					case 2:		// View patient
						(void)View_Patient();
					break;
					
					default:
					break;
				}// end switch
			
			break;// case user
			
			default:
			break;
			
		}// end switch
		
		// ask the user if he want to quit the 
		printf("Do you want to Quit?\n1- Y\n2- N\n");
		scanf("%d", &Selection);
		
		if (Selection == 1)
		{
			break; // Terminate the program 
		}	
		else 
		{
			// Do Nothing
		}
	}//end super loop 	
	
	return 0;
	
}//end main 










//-----------------------------------------------------------------------------------------------

u8 Add_Patient(void)
{
	
	u8 counter = 0;
	
	if (Global_Patient_Counter<5)
	{	
		printf("Enter the patient ID :\n");
		scanf("%d", &Patient_Id);
		
		if (Global_Patient_Counter != 0)  	// Not the First patient 
		{
			// Check if ID is valid
			while(counter != Global_Patient_Counter)
			{
				if (Objects[counter].ID == Patient_Id)	// ID is taken
				{
					printf("Invalid ID!\n");
					return 1;
				}
				else 
				{
					counter++;	
				}	
			}// end while 
			
			// ID is valid so add a new patient ID
			Objects[counter].ID = Patient_Id;
			
		}//end if 	
		
		// The first patient to add 
		else 
		{
			Objects[0].ID = Patient_Id;	
		}
		
		// case ID is valid 
		
		printf("Enter the patient name :\n");
		scanf("%s", &Objects[Global_Patient_Counter].Name);
		
		printf("Enter the patient age :\n");
		scanf("%d", &Objects[Global_Patient_Counter].Age);
		
		printf("Enter the patient gender :\n");
		scanf("%s", &Objects[Global_Patient_Counter].Gender);
		
		Objects[Global_Patient_Counter].SlotNum = 0;		//set to defualt case
		
		Global_Patient_Counter++;			// increment the number of patients 
		
		printf("Patient was added successfully\n");
		
		
	
	}//end if 
	else 
	{
		printf("No memory space\n");
		return 1;
	}	
	
	return 0;
}

//----------------------------------------------------------------------------------------------

void Edit_Patient(void)
{
	u8 counter = 0;
	
	
	
	// Check if there are patients or not 
	if (Global_Patient_Counter != 0)
	{
		printf("Please enter the patient ID :\n");
		scanf("%d", &Patient_Id);
		
		// Check if ID is valid
		while(counter< Global_Patient_Counter)
		{
			// Patient is Found 
			if (Objects[counter].ID == Patient_Id)
			{
				// display patient information
				printf("1- Patient Name : %s\n", Objects[counter].Name);
				printf("2- Patient Age : %d\n", Objects[counter].Age);
				printf("3- Patient Gender : %s\n", Objects[counter].Gender);
				
				printf("Which information do you want to edit :\n");
				scanf("%d", &Selection);
				
				switch(Selection)
				{
					case 1:		// Name 
						printf("Enter the new patient name :\n");
						scanf("%s", &Objects[counter].Name);
					break;
					
					case 2: 	// Age
						printf("Enter the new patient age :\n");
						scanf("%d", &Objects[counter].Age);
					break;
					
					case 3:		// Gender 
						printf("Enter the new patient gender :\n");
						scanf("%s", &Objects[counter].Gender);
					break;
					
					default:
						printf("Wrong Choice!\n");
					break;
				}// end switch 
				
				printf("Information was updated successfully\n");
				// Mission done get out the loop 
				break;		
			
			}// end if 
			
			else
			{
				counter++;		// increment the counter to the next element 
			}
			
		}// end while
		
		if (counter == Global_Patient_Counter)
		{
			// Patient is not found
			printf("Wrong ID, No patient found!\n");
		}
		else 
		{
			// Do Nothing
		}
	}// end if 
	else 
	{
		printf("There are no patients in database!\n");
	}
	
}//end function 

//----------------------------------------------------------------------------------------------

void Reserve_Slot(void)
{
	// Variables 
	u32 Available_Slots[5] = {0,0,0,0,0};				// carry the available slots numbers
	u8 counter_slot = 0;
	u8 patient_counter = 0;
	u8 av_slot_counter = 0;

	
	// Check if there are patients or not 
	if (Global_Patient_Counter != 0)
	{
		// check the available slots 
		for (counter_slot; counter_slot < 5; counter_slot++)
		{
			if (Slots[counter_slot] == 0) // an available slot 
			{
				Available_Slots[av_slot_counter] = counter_slot+1;		// Save the slot number in the available 
				av_slot_counter++;
			}
		}// end for 
		
		// set the counter to zero 
		av_slot_counter = 0;
		
		
		// No available Slots
		if (Available_Slots[0] == 0)	
		{
			printf("No available slots!\n");
		}
		
		// There are available ones
		else	 
		{
			printf("The available slots are :\n");
			
			// print the available slots
			for (av_slot_counter; av_slot_counter < 5 && Available_Slots[av_slot_counter] != 0; av_slot_counter++)
			{
				switch (Available_Slots[av_slot_counter])
				{
					case 1:
						printf("%d- 2pm to 2:30pm\n", av_slot_counter+1);
					break;
					
					case 2:
						printf("%d- 2:30pm to 3pm\n", av_slot_counter+1);
					break;
					
					case 3:
						printf("%d- 3pm to 3:30pm\n", av_slot_counter+1);
					break;
					
					case 4:
						printf("%d- 4pm to 4:30pm\n", av_slot_counter+1);
					break;
					
					case 5:
						printf("%d- 4:30pm to 5pm\n", av_slot_counter+1);
					break;
					
					default:
					break;
				}//end switch 
				
			}// end for 
			
			// ask the user to enter the ID and the desired slot 	
			printf("Please, enter the patient ID :\n");
			scanf("%d", &Patient_Id);
			printf("Please, enter the desired slot :\n");
			scanf("%d", &Selection); 
			
			while (patient_counter < Global_Patient_Counter)
			{
				// patient found
				if (Objects[patient_counter].ID == Patient_Id)
				{
					
					Objects[patient_counter].SlotNum = Available_Slots[Selection - 1];	// attach the reservation to patient
					Slots[ Available_Slots[Selection - 1] - 1 ] = 1;					// Make the slot reserved
					printf("Reservation was done successfully\n");
					
					break;	// Mission done get out the loop 
				}	
				else 
				{
					patient_counter++;
				}
			}//end while 
			if (patient_counter == Global_Patient_Counter)
			{
				printf("Wrong ID, no patient found!\n");
			}
			else
			{
				// Do Nothing
			}	
			
		}// end else (available slots)
		
	}// end if(There are patients) 	
	else 
	{
		printf("There are no patients in database!\n");
	}	
	
}//end function 

//-----------------------------------------------------------------------------------------------------------------

void Cancel_Reservation(void)
{
	
	u8 patient_counter = 0;
	
	
	if (Global_Patient_Counter != 0)
	{
		// Get the ID from the user 
		printf("Please, enter the patient ID :\n");
		scanf("%d", &Patient_Id);
		
		// Check the ID 
		while (patient_counter < Global_Patient_Counter)
		{
			// Patient Found 
			if (Objects[patient_counter].ID == Patient_Id)
			{
				
				Slots[ Objects[patient_counter].SlotNum-1 ] = 0;	//reset the slot to be available again 
				Objects[patient_counter].SlotNum = 0;				// cancel reservation
				printf("Reservation was canceled successfully\n");
				
				break; 			// Mission done get out the loop
			}
			else 
			{
				patient_counter++;
			}	
		}// end while 
		
		if (patient_counter == Global_Patient_Counter)
		{
			printf("Wrong ID, no patient found!\n");
		}		
		else 
		{
			// Do Nothing 
		}	
	}// end if 	
	else 
	{
		printf("There are no patients in database!\n");
	}	
}// end function

//-----------------------------------------------------------------------------------------------------------------

u8 View_Patient(void)
{
	
	if (Global_Patient_Counter != 0)
	{
		// Get the ID from the user
		printf("Please, enter the patient ID :\n");
		scanf("%d", &Patient_Id);
		
		// check the ID
		for (u8 j = 0; j < Global_Patient_Counter ; j++)
		{
			if (Objects[j].ID == Patient_Id)
			{
				printf("Patient Name : %s\n", Objects[j].Name);
				printf("Patient Age : %d\n", Objects[j].Age);
				printf("Patient Gender : %s\n", Objects[j].Gender);
				
				return 0;
			}	
		}	
		
		printf("Wrong ID, no patient found!\n");		// why this is printed when asking to view second patient??
		return 1;
		
	}// end if 
	else 
	{
		printf("There are no patients in database to view!\n");
		return 1;
	}	
	
}

//-----------------------------------------------------------------------------------------------------------------

void View_TodayReservation(void)
{
	u32 patient_counter = 0;
	u8 reservation_num = 0;
	
	
	if (Global_Patient_Counter != 0)
	{
		// check the reservations
		while (patient_counter < Global_Patient_Counter)
		{
			
			switch (Objects[patient_counter].SlotNum)
			{
				case 1:
					printf("- Patient ID is : %d				", Objects[patient_counter].ID);
					printf("- Reservation is : 2pm to 2:30pm\n");
					
					patient_counter++;
					reservation_num++;
				break;
				
				case 2:
					printf("- Patient ID is : %d				", Objects[patient_counter].ID);
					printf("- Reservation is : 2:30pm to 3pm\n");
					
					patient_counter++;
					reservation_num++;
				break;
				
				case 3:
					printf("- Patient ID is : %d				", Objects[patient_counter].ID);
					printf("- Reservation is : 3pm to 3:30pm\n");
					
					patient_counter++;
					reservation_num++;
				break;
				
				case 4:
					printf("- Patient ID is : %d				", Objects[patient_counter].ID);
					printf("- Reservation is : 4pm to 4:30pm\n");
					
					patient_counter++;
					reservation_num++;
				break;
				
				case 5:
					printf("- Patient ID is : %d				", Objects[patient_counter].ID);
					printf("- Reservation is : 4:30pm to 5pm\n");
					
					patient_counter++;
					reservation_num++;
				break;
				
				default:
					patient_counter++;
				break;
				
			}//end switch
			
			
		}//end while 
		
		if (reservation_num == 0)
		{
			printf("There are no reservation today!\n");
		}
		else 
		{
			// Do Nothing
		}
	}// end if 
	else 
	{
		printf("There are no patients in database!\n");
	}	

}// end function 


//---------------------------------------------------------------------------------


